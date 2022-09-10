#include "kgroupitem.h"

KGroupItem::KGroupItem(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

KGroupItem::~KGroupItem()
{
}

void KGroupItem::setGroupNameLabel(QString name, size_t count)
{
	m_name = name;
	m_count = count;
	QString labeltxt;
	labeltxt.append(name);
	labeltxt.append("----");
	labeltxt.append('(');
	labeltxt.append(QString::number(count));
	labeltxt.append(')');
	ui.m_group_name_btn->setText(labeltxt);
}

void KGroupItem::on_m_more_btn_clicked()
{
	qDebug() << "on_m_more_btn_clicked";
}

void KGroupItem::on_m_group_name_btn_clicked()
{
	emit show_group_todos(m_name, m_count);
}

void KGroupItem::on_m_move_btn_clicked()
{
	qDebug() << "on_m_move_btn_clicked";
}
