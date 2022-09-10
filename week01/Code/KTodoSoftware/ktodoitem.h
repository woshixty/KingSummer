#pragma once

#include <QWidget>
#include "ui_ktodoitem.h"
#include "ktodoitem_e.h"
#include "ktodoitemdao.h"
#include <QDateTime>

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

class KTodoItem : public QWidget
{
	Q_OBJECT

public:
	KTodoItem(QWidget *parent = Q_NULLPTR);
	~KTodoItem();
	void initItem(KTodoItem_E item);

private:
	Ui::KTodoItem ui;
	KTodoItem_E m_item;
	KTodoItemDao* m_todoitem_dao;

private slots:
	void on_m_check_btn_stateChanged();

signals:
	void choose_a_todo(KTodoItem_E item);
	void update_a_todo_g();
};
