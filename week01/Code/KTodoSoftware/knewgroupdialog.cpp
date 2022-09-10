#include "knewgroupdialog.h"

KNewGroupDialog::KNewGroupDialog(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint & ~Qt::WindowMinimizeButtonHint);
	ui.m_check_btn->setEnabled(false);
}

KNewGroupDialog::~KNewGroupDialog()
{}

void KNewGroupDialog::on_m_check_btn_clicked()
{
	qDebug()<<"·¢ËÍÐÅºÅ";
	emit add_group(ui.m_group_name_edit->text());
	this->setVisible(false);
	ui.m_group_name_edit->clear();
}

void KNewGroupDialog::on_m_group_name_edit_textChanged()
{
	if (!ui.m_group_name_edit->text().isEmpty())
		ui.m_check_btn->setEnabled(true);
}

void KNewGroupDialog::on_m_cancel_btn_clicked()
{
	this->setVisible(false);
	ui.m_group_name_edit->clear();
}