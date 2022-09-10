#ifndef KHOMEPAGE_H
#define KHOMEPAGE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

#include <QWidget>
#include <QDebug>
#include <qmessagebox.h>
#include "ui_khomepage.h"
#include "KConstants.h"
#include "ktodoitem_e.h"
#include "ktodoitemdao.h"
#include "ktodoiteminfo.h"
#include "ktodoitem.h"

class KHomePage : public QWidget
{
	Q_OBJECT

signals:
	void to_item_info(KTodoItem_E item);

public:
	KHomePage(QWidget *parent = nullptr);
	~KHomePage();
	void btnSwitch(QPushButton* btn);
	void initTodoList();
	void initPage();
	void initList();
	void setPageInfoP(KTodoItemInfo* page) { m_todoinfopage = page; }

private:
	Ui::KHomePage ui;
	KTodoItemDao* m_todoitem_dao;
	QList<KTodoItem_E> m_todo_list;
	QString m_group_name;
	size_t m_count;
	QList<KTodoItem_E> m_todoiteme_list;
	QList<KTodoItem*> m_todoitemw_list;
	KTodoItemInfo* m_todoinfopage;

signals:
	void giveItemInfo(KTodoItem_E item);

private slots:
	void on_m_not_arrange_btn_clicked();
	void on_m_today_todo_btn_clicked();
	void on_m_later_seven_days_btn_clicked();
	void on_m_later_more_days_btn_clicked();
	void on_m_todocontent_edit_returnPressed();
	void currentrow_change_list(int currentindex);
};

#endif