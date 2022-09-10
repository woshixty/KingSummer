#include "kgroupdao.h"

#include <QSqlRecord>
#include <QSqlError>

KGroupDao::KGroupDao(QObject* parent)
	: QObject{ parent }
{
	m_query = new QSqlQuery();
	m_query_model = new QSqlQueryModel();
}

KGroupDao::~KGroupDao()
{
	delete m_query;
	delete m_query_model;
}

void KGroupDao::getAllGroups(QList<KGroup>& result) const
{
	m_query_model->clear();
	result.clear();
	const QString sql = "SELECT * FROM \"group\"";
	m_query_model->setQuery(sql);
	const int rows = m_query_model->rowCount();
	for (int i = 0; i < rows; i++)
	{
		QSqlRecord record = m_query_model->record(i);
		KGroup rec(record.value(0).toString(), record.value(1).toInt());
		result.append(rec);
	}
}

bool KGroupDao::addNewGroup(const QString& groupName) const
{
	m_query->clear();
	const QString sql = "INSERT INTO \"group\" (group_name) VALUES (:GN)";
	m_query->prepare(sql);
	m_query->bindValue(":GN", groupName);
	m_query->exec();
	qDebug() << "KGroupDao::addNewGroup£º" << m_query->lastError();
	return m_query->isActive();
}
