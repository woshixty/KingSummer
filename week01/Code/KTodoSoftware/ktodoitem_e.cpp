#include "ktodoitem_e.h"

KTodoItem_E::KTodoItem_E(QObject *parent)
	: QObject(parent)
{

}

KTodoItem_E::KTodoItem_E(const KTodoItem_E & obj)
{
	id = obj.id;
	todo_name = obj.todo_name;
	until_date = obj.until_date;
	remind_time = obj.remind_time;
	description = obj.description;
	location = obj.location;
	remark = obj.remark;
	repeat_type = obj.repeat_type;
	priority = obj.priority;
	create_time = obj.create_time;
	belong_group = obj.belong_group;
	is_check = obj.is_check;
}

KTodoItem_E::~KTodoItem_E()
{}

KTodoItem_E KTodoItem_E::operator=(KTodoItem_E obj)
{
	id = obj.id;
	todo_name = obj.todo_name;
	until_date = obj.until_date;
	remind_time = obj.remind_time;
	description = obj.description;
	location = obj.location;
	remark = obj.remark;
	repeat_type = obj.repeat_type;
	priority = obj.priority;
	create_time = obj.create_time;
	belong_group = obj.belong_group;
	is_check = obj.is_check;
	return this;
}
