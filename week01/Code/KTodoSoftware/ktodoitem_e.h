#pragma once

#include <QObject>

class KTodoItem_E : public QObject
{
	Q_OBJECT

public:
	KTodoItem_E(QObject* parent = Q_NULLPTR);
	KTodoItem_E(const KTodoItem_E& obj);
	~KTodoItem_E() override;
	KTodoItem_E operator =(KTodoItem_E obj);
	int id;
	QString todo_name;
	QString until_date;
	QString remind_time;	
	QString description;
	QString location;
	QString remark;
	QString repeat_type;
	int priority;
	QString create_time;
	QString belong_group;
	int is_check;
};
