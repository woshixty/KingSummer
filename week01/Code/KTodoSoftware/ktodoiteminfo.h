#pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

#include <QWidget>
#include <QDate>
#include <QTime>
#include <qdebug.h>
#include <QMessageBox>
#include "ui_ktodoiteminfo.h"
#include "ktodoitem_e.h"
#include "ktodoitemdao.h"

class KTodoItemInfo : public QWidget
{
	Q_OBJECT

public:
	KTodoItemInfo(QWidget *parent = Q_NULLPTR);
	~KTodoItemInfo();
	void setItemInfo(KTodoItem_E &item);

private:
	Ui::KTodoItemInfo ui;
	KTodoItem_E m_item;
	KTodoItemDao* m_todoitem_dao;

private slots:
	void getItemInfo(KTodoItem_E item);
	void on_m_is_check_box_stateChanged();
	void on_todoitem_choosed(KTodoItem_E item);
	void on_m_save_btn_clicked();
	void on_m_proirity_box_currentIndexChanged(int index);
	void on_m_add_description_btn_clicked();
	void on_m_add_remark_btn_clicked();
	void on_m_location_edit_returnPressed();
	void on_m_date_btn_clicked();
	void on_m_clock_btn_clicked();
};
