#pragma once

#include <QMainWindow>
#include <qdebug.h>
#include "ui_knewgroupdialog.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

class KNewGroupDialog : public QMainWindow
{
	Q_OBJECT

signals:
	void add_group(QString groupname);

public:
	KNewGroupDialog(QWidget *parent = nullptr);
	~KNewGroupDialog();

private:
	Ui::KNewGroupDialogClass ui;

private slots:
	void on_m_cancel_btn_clicked();
	void on_m_check_btn_clicked();
	void on_m_group_name_edit_textChanged();
};
