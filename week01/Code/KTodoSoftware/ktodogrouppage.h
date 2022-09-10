#pragma once

#include <QWidget>
#include <QMessageBox>
#include "ui_ktodogrouppage.h"
#include "ktodoitem_e.h"
#include "ktodoitemdao.h"
#include "ktodoitem.h"
#include "ktodoiteminfo.h"

class KTodoGroupPage : public QWidget
{
	Q_OBJECT

signals:
	void to_item_info(KTodoItem_E item);

public:
	KTodoGroupPage(QWidget *parent = nullptr);
	~KTodoGroupPage();
	void initPage(QString group_name, size_t count);
	void initList();
	void setPageInfoP(KTodoItemInfo* page) { m_todoinfopage = page; }

private:
	Ui::KTodoGroupPageClass ui;
	QString m_group_name;
	size_t m_count;
	QList<KTodoItem_E> m_todoiteme_list;
	KTodoItemDao *m_todoitem_dao;
	QList<KTodoItem *> m_todoitemw_list;
	KTodoItemInfo* m_todoinfopage;

private slots:
	void on_m_todocontent_edit_returnPressed();
	void currentrow_change_list(int currentindex);
};
