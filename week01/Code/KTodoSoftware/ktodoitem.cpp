#include "ktodoitem.h"

KTodoItem::KTodoItem(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_todoitem_dao = new KTodoItemDao(this);
}

KTodoItem::~KTodoItem()
{
}

void KTodoItem::initItem(KTodoItem_E item)
{
	m_item = KTodoItem_E(item);
	// ���ȼ�
	switch (m_item.priority)
	{
	case 0:
		ui.m_priority_btn->setIcon(QIcon(":/todoitem/icons/priority_null.png"));
		break;
	case 1:
		ui.m_priority_btn->setIcon(QIcon(":/todoitem/icons/priority_low.png"));
		break;
	case 2:
		ui.m_priority_btn->setIcon(QIcon(":/todoitem/icons/priority_mid.png"));
		break;
	case 3:
		ui.m_priority_btn->setIcon(QIcon(":/todoitem/icons/priority_high.png"));
		break;
	}
	// ����
	ui.m_todocontent_label->setText(item.todo_name);
	// ����ʱ��
	if (m_item.until_date != nullptr && !m_item.until_date.isEmpty())
	{
		QString until_date = item.until_date;
		QDateTime datetime = QDateTime::fromString(until_date, "yyyyMMdd hhmmss");
		ui.m_endtime_label->setText(datetime.toString("yyyy-MM-dd"));
	}
	else
		ui.m_endtime_label->setText("δ���õ���ʱ��");
	// �ظ�����
	if (m_item.repeat_type != nullptr && !m_item.repeat_type.isEmpty())
		ui.m_repeat_label->setText(m_item.repeat_type);
	else
		ui.m_repeat_label->setText("���ظ�");
	// ����ʱ��
	// m_remindtime_label
	// ����ʱ��
	if (m_item.remind_time != nullptr && !m_item.remind_time.isEmpty())
	{
		QString remind_time = item.remind_time;
		QDateTime datetime = QDateTime::fromString(remind_time, "yyyyMMdd hhmmss");
		ui.m_remindtime_label->setText(datetime.toString("MM-dd hh:mm"));
	}
	else
		ui.m_remindtime_label->setText("δ��������ʱ��");
	// �����
	if (m_item.is_check == 1)
	{
		QFont font = ui.m_todocontent_label->font();
		font.setStrikeOut(true);
		ui.m_todocontent_label->setFont(font);
		ui.m_check_btn->setChecked(true);
	}
}

void KTodoItem::on_m_check_btn_stateChanged()
{
	const QCheckBox *btn = ui.m_check_btn;
	QFont font = ui.m_todocontent_label->font();
	if (btn->isChecked()) {
		font.setStrikeOut(true);
		// ͬʱ�޸�����
		m_item.is_check = 1;
	}
	else
	{
		font.setStrikeOut(false);
		// ͬʱ�޸�����
		m_item.is_check = 0;
	}
	ui.m_todocontent_label->setFont(font);
	// �������ݿ�
	m_todoitem_dao->updateTodoItem(m_item);
	// ���·�������
	emit update_a_todo_g();
	// ��item infoҳ�淢���ź�
	emit choose_a_todo(m_item);
}
