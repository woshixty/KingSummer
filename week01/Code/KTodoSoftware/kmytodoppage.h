#pragma once

#include <QWidget>
#include "ui_kmytodoppage.h"
#include "ktodoitemdao.h"
#include "ktodoitem_e.h"
#include "ktodoitem.h"
#include "ktodoiteminfo.h"

class KMytodopPage : public QWidget
{
	Q_OBJECT

signals:
	void to_item_info(KTodoItem_E item);

public:
	KMytodopPage(QWidget *parent = nullptr);
	~KMytodopPage();
	void initPage();
	void initList();
	void setPageInfoP(KTodoItemInfo* page) { m_todoinfopage = page; }

private:
	Ui::KMytodopPageClass ui;
	KTodoItemDao* m_todoitem_dao;
	QString m_group_name;
	size_t m_count;
	QList<KTodoItem_E> m_todoiteme_list;
	QList<KTodoItem*> m_todoitemw_list;
	KTodoItemInfo* m_todoinfopage;

private slots:
	void on_m_todocontent_edit_returnPressed();
	void currentrow_change_list(int currentindex);
};
