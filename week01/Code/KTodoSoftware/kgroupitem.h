#pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

#include <QWidget>
#include <qdebug.h>
#include "ui_kgroupitem.h"

class KGroupItem : public QWidget
{
	Q_OBJECT

public:
	KGroupItem(QWidget *parent = Q_NULLPTR);
	~KGroupItem() override;
	void setGroupNameLabel(QString name, size_t count);

private:
	Ui::KGroupItem ui;
	QString m_name;
	size_t m_count;

signals:
	void show_group_todos(QString, size_t);

private slots:
	void on_m_move_btn_clicked();
	void on_m_more_btn_clicked();
	void on_m_group_name_btn_clicked();
};
