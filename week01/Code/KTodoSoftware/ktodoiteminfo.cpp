#include "ktodoiteminfo.h"

KTodoItemInfo::KTodoItemInfo(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QAction* location = new QAction(ui.m_location_edit);
	location->setIcon(QIcon(":/todoiteminfo/icons/location.png"));
	ui.m_location_edit->addAction(location, QLineEdit::LeadingPosition);
	m_todoitem_dao = new KTodoItemDao(this);
}

KTodoItemInfo::~KTodoItemInfo()
{
}

void KTodoItemInfo::setItemInfo(KTodoItem_E &item)
{
	ui.m_todocontent_label->setText(item.todo_name);
	ui.m_proirity_box->setCurrentIndex(item.priority);
	if (item.until_date != nullptr && !item.until_date.isEmpty())
	{
		QString until_date = item.until_date;
		QDateTime datetime = QDateTime::fromString(until_date, "yyyyMMdd hhmmss");
		ui.m_date_btn->setText(datetime.toString("MM-dd") + " ����");
	}
	else
	{
		ui.m_date_btn->setText("���õ���ʱ��");
	}
	// 08��07�� 09:45 ������
	if (item.remind_time != nullptr && !item.remind_time.isEmpty())
	{
		QString remind_time = item.remind_time;
		QDateTime datetime = QDateTime::fromString(remind_time, "yyyyMMdd hhmmss");
		ui.m_clock_btn->setText(datetime.toString("MM-dd hh:mm") + "������");
	}
	else
	{
		ui.m_date_btn->setText("��������ʱ��");
	}
	// ��������
	if (item.description != nullptr && !item.description.isEmpty())
		ui.m_description_edit->setText(item.description);
	// �ص�
	if (item.location != nullptr && !item.location.isEmpty())
		ui.m_location_edit->setText(item.location);
	// ���챸ע
	if (item.remark != nullptr && !item.remark.isEmpty())
		ui.m_remark_edit->setText(item.remark);
	// �Ƿ������
	if (item.is_check == 1)
	{
		QFont font = ui.m_todocontent_label->font();
		font.setStrikeOut(true); // ɾ����
		ui.m_todocontent_label->setFont(font);
		ui.m_is_check_box->setChecked(true);
	}
	else
	{
		QFont font = ui.m_todocontent_label->font();
		font.setStrikeOut(false); // ȥ��ɾ����
		ui.m_todocontent_label->setFont(font);
		ui.m_is_check_box->setChecked(false);
	}

	// ��������
	m_item.id = item.id;
	m_item.todo_name = item.todo_name;
	m_item.until_date = item.until_date;
	m_item.remind_time = item.remind_time;
	m_item.description = item.description;
	m_item.location = item.location;
	m_item.remark = item.remark;
	m_item.repeat_type = item.repeat_type;
	m_item.priority = item.priority;
	m_item.create_time = item.create_time;
	m_item.belong_group = item.belong_group;
	m_item.is_check = item.is_check;
}

void KTodoItemInfo::on_m_is_check_box_stateChanged()
{
	QFont font = ui.m_todocontent_label->font();
	if (ui.m_is_check_box->isChecked())
	{
		font.setStrikeOut(true); // ɾ����
		m_item.is_check = 1;
	}
	else
	{
		font.setStrikeOut(false);
		m_item.is_check = 0;
	}
	ui.m_todocontent_label->setFont(font);
}

void KTodoItemInfo::getItemInfo(KTodoItem_E item)
{
	qDebug() << "KTodoItemInfo::getItemInfo";
	qDebug() << item.id << item.todo_name;
	setItemInfo(item);
}

void KTodoItemInfo::on_todoitem_choosed(KTodoItem_E item)
{
	qDebug() << "KTodoItemInfo::on_todoitem_choosed";
	setItemInfo(item);
}

void KTodoItemInfo::on_m_save_btn_clicked()
{
	bool flag = m_todoitem_dao->updateTodoItem(m_item);
	if (flag)
		QMessageBox::information(this, "����ɹ�", "�ɹ������������");
}

void KTodoItemInfo::on_m_proirity_box_currentIndexChanged(int index)
{
	m_item.priority = index;
}

void KTodoItemInfo::on_m_add_description_btn_clicked()
{
	m_item.description = ui.m_description_edit->toPlainText();
}

void KTodoItemInfo::on_m_add_remark_btn_clicked()
{
	m_item.remark = ui.m_remark_edit->toPlainText();
}

void KTodoItemInfo::on_m_location_edit_returnPressed()
{
	m_item.location = ui.m_location_edit->text();
}

void KTodoItemInfo::on_m_date_btn_clicked()
{
	QDateTime t = ui.m_datetime_edit->dateTime();
	m_item.until_date = t.toString("yyyyMMdd hhmmss");
	ui.m_date_btn->setText(t.toString("MM-dd") + "����");
}

void KTodoItemInfo::on_m_clock_btn_clicked()
{
	QDateTime t = ui.m_datetime_edit->dateTime();
	m_item.remind_time = t.toString("yyyyMMdd hhmmss");
	ui.m_clock_btn->setText(t.toString("MM-dd hh:mm") + "������");
}
