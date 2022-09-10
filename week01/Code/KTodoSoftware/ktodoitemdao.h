#pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

#include <QObject>
#include <qsqlquery.h>
#include <qsqlquerymodel.h>
#include <qdebug.h>
#include "ktodoitem_e.h"

class KTodoItemDao : public QObject
{
	Q_OBJECT

public:
	KTodoItemDao(QObject* parent = nullptr);
	~KTodoItemDao();
	bool addNewTodoitem(KTodoItem_E &item);
	void selectAllTodos(QList<KTodoItem_E>& result);
	void selectTodosByGroupname(QList<KTodoItem_E>& result, QString name);
	void packageResult(QList<KTodoItem_E>& result);
	bool updateTodoItem(KTodoItem_E& item);
	int selectGroupNum(QString group_name);
	void selectTodosNotArrange(QList<KTodoItem_E>& result);
	void selectTodosLater(QList<KTodoItem_E>& result);
	void selectTodosSeven(QList<KTodoItem_E>& result);
	void selectTodosToday(QList<KTodoItem_E>& result);

private:
	QSqlQuery* m_query;
	QSqlQueryModel* m_query_model;
};
