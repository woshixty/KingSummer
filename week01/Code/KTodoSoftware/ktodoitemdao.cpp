#include "ktodoitemdao.h"

#include <QDateTime>
#include <QSqlError>

KTodoItemDao::KTodoItemDao(QObject *parent)
	: QObject(parent)
{
	m_query = new QSqlQuery;
	m_query_model = new QSqlQueryModel;
}

KTodoItemDao::~KTodoItemDao()
{
	delete m_query;
	delete m_query_model;
}

bool KTodoItemDao::addNewTodoitem(KTodoItem_E& item)
{
	// m_query->clear();
	QString sql = "INSERT INTO todoitem (todo_name, priority, create_time, belong_group, is_check) VALUES (:TN, :P, :CT, :BG, :IC)";
	
	m_query->prepare(sql);
	m_query->bindValue(":TN", item.todo_name);
	m_query->bindValue(":P", item.priority);
	const QDateTime ctime = QDateTime::currentDateTime();
	m_query->bindValue(":CT", ctime.toString("yyyyMMdd hhmmss"));
	m_query->bindValue(":BG", item.belong_group);
	m_query->bindValue(":IC", 0);
	m_query->exec();
	qDebug() << "KTodoItemDao::addNewTodoitem: " << m_query->lastError();
	return m_query->isActive();
}

void KTodoItemDao::selectAllTodos(QList<KTodoItem_E> &result)
{
	result.clear();
	const QString sql = "SELECT * FROM todoitem";
	m_query_model->setQuery(sql);
	packageResult(result);
}

void KTodoItemDao::selectTodosByGroupname(QList<KTodoItem_E>& result, const QString name)
{
	result.clear();
	const QString sql = "SELECT * FROM todoitem WHERE belong_group = '" + name + "'";
	m_query_model->setQuery(sql);
	packageResult(result);
}

void KTodoItemDao::selectTodosLater(QList<KTodoItem_E>& result)
{
	result.clear();
	QDateTime now = QDateTime::currentDateTime();
	now.addDays(7);
	QString sql = "SELECT * FROM todoitem WHERE until_date > '" + now.toString("yyyyMMdd hhmmss") + "'";
	m_query_model->setQuery(sql);
	packageResult(result);
}

void KTodoItemDao::selectTodosSeven(QList<KTodoItem_E>& result)
{
	result.clear();
	QDateTime now = QDateTime::currentDateTime();
	QString now_s = now.toString("yyyyMMdd hhmmss");
	now.addDays(7);
	QString now_7_s = now.toString("yyyyMMdd hhmmss");
	QString sql = 
		"SELECT * FROM todoitem WHERE until_date < '" + now_7_s + "' AND until_date > '" + now_s + "'";
	m_query_model->setQuery(sql);
	packageResult(result);
}

void KTodoItemDao::selectTodosToday(QList<KTodoItem_E>& result)
{
	result.clear();
	QDateTime now = QDateTime::currentDateTime();
	QString now_s = now.toString("yyyyMMdd");
	QString sql =
		"SELECT * FROM todoitem WHERE until_date LIKE '%" + now_s + "%'";
	m_query_model->setQuery(sql);
	packageResult(result);
}

void KTodoItemDao::selectTodosNotArrange(QList<KTodoItem_E>& result)
{
	result.clear();
	QString sql = "SELECT * FROM todoitem WHERE until_date IS NULL";
	m_query_model->setQuery(sql);
	packageResult(result);
}

void KTodoItemDao::packageResult(QList<KTodoItem_E>& result)
{
	int rows = m_query_model->rowCount();
	for (int i = 0; i < rows; i++)
	{
		QSqlRecord record = m_query_model->record(i);
		KTodoItem_E rec;
		rec.id = record.value(0).toInt();
		rec.todo_name = record.value(1).toString();
		rec.until_date = record.value(2).toString();
		rec.remind_time = record.value(3).toString();
		rec.description = record.value(4).toString();
		rec.location = record.value(5).toString();
		rec.remark = record.value(6).toString();
		rec.repeat_type = record.value(7).toString();
		rec.priority = record.value(8).toInt();
		rec.create_time = record.value(9).toString();
		rec.belong_group = record.value(10).toString();
		rec.is_check = record.value(11).toInt();
		result.append(rec);
	}
}

bool KTodoItemDao::updateTodoItem(KTodoItem_E& item)
{
	// 完成待办事项
	QString sql = "UPDATE todoitem SET todo_name=:TN, until_date=:UD, remind_time=:RT, description=:D, location=:L, remark=:R, repeat_type=:UR, priority=:P, create_time=:CT, belong_group=:BG, is_check=:IC WHERE id=:ID";
	m_query->prepare(sql);
	/*
	todo_name=:TN
	until_date=:UD
	remind_time=:RT
	description=:D
	location=:L
	remark=:R
	repeat_type=:UR
	priority=:P
	create_time=:CT
	belong_group=:BG
	is_check=:IC
	id=:ID"
	*/
	m_query->bindValue(":TN", item.todo_name);
	m_query->bindValue(":UD", item.until_date);
	m_query->bindValue(":RT", item.remind_time);
	m_query->bindValue(":D", item.description);
	m_query->bindValue(":L", item.location);
	m_query->bindValue(":R", item.remark);
	m_query->bindValue(":UR", item.repeat_type);
	m_query->bindValue(":P", item.priority);
	m_query->bindValue(":CT", item.create_time);
	m_query->bindValue(":BG", item.belong_group);
	m_query->bindValue(":IC", item.is_check);
	m_query->bindValue(":ID", item.id);
	m_query->exec();
	qDebug() << "KTodoItemDao::updateTodoItem: " << m_query->lastError();
	return m_query->isActive();
}

int KTodoItemDao::selectGroupNum(QString group_name)
{
	QString sql = "SELECT COUNT(*) FROM todoitem WHERE belong_group = '" + group_name + "' AND is_check = 0";
	m_query_model->setQuery(sql);
	return m_query_model->record(0).value(0).toInt();
}
