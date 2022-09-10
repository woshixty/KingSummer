#include "khomepage.h"

KHomePage::KHomePage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.m_tips->setVisible(false);
	m_todoitem_dao = new KTodoItemDao(this);
	initTodoList();
	connect(ui.m_todo_list, SIGNAL(currentRowChanged(int)), this, SLOT(currentrow_change_list(int)));
}

KHomePage::~KHomePage()
{
}

void KHomePage::btnSwitch(QPushButton* btn)
{
	if (btn->isChecked())
	{
		// 选中状态 -> 未选中
		btn->setIcon(QIcon(":/homepage/icons/icon-unchoose.png"));
		btn->setStyleSheet(m_uncheck);
	}
	else
	{
		// 未被选中 -> 选中
		ui.m_not_arrange_btn->setIcon(QIcon(":/homepage/icons/icon-unchoose.png"));
		ui.m_not_arrange_btn->setStyleSheet(m_uncheck);

		ui.m_today_todo_btn->setIcon(QIcon(":/homepage/icons/icon-unchoose.png"));
		ui.m_today_todo_btn->setStyleSheet(m_uncheck);

		ui.m_later_seven_days_btn->setIcon(QIcon(":/homepage/icons/icon-unchoose.png"));
		ui.m_later_seven_days_btn->setStyleSheet(m_uncheck);

		ui.m_later_more_days_btn->setIcon(QIcon(":/homepage/icons/icon-unchoose.png"));
		ui.m_later_more_days_btn->setStyleSheet(m_uncheck);


		btn->setIcon(QIcon(":/homepage/icons/icon-choose-green.png"));
		btn->setStyleSheet(m_check);
	}
}

void KHomePage::initTodoList()
{
	m_todoitem_dao->selectAllTodos(m_todo_list);
	if(!m_todo_list.isEmpty())
		emit giveItemInfo(m_todo_list[0]);
}

void KHomePage::initPage()
{
	initList();
}

void KHomePage::initList()
{
	// 清空数据
	ui.m_todo_list->clear();
	size_t rows = m_todoitemw_list.size();
	// 逐个delete窗口
	for (size_t i = 0; i < rows; i++)
	{
		KTodoItem* item = m_todoitemw_list.at(0);
		m_todoitemw_list.removeAt(0);
		delete item;
	}
	// 封装成m_groupitems
	rows = m_todoiteme_list.size();
	// 加入到私有变量list中
	for (size_t i = 0; i < rows; i++)
	{
		KTodoItem* item = new KTodoItem(this);
		item->initItem(m_todoiteme_list[i]);
		m_todoitemw_list.append(item);
		connect(item, SIGNAL(choose_a_todo(KTodoItem_E)), m_todoinfopage, SLOT(on_todoitem_choosed(KTodoItem_E)));
	}
	// 逐个绑定item并显示
	for (size_t i = 0; i < m_todoitemw_list.size(); i++)
	{
		QWidget* todo_item = m_todoitemw_list.at(i);
		QListWidgetItem* item = new QListWidgetItem(ui.m_todo_list);
		QSize size = item->sizeHint();
		item->setSizeHint(QSize(size.height(), todo_item->height()));
		ui.m_todo_list->setItemWidget(item, todo_item);
	}
	connect(this, SIGNAL(to_item_info(KTodoItem_E)), m_todoinfopage, SLOT(on_todoitem_choosed(KTodoItem_E)));
}

void KHomePage::on_m_today_todo_btn_clicked()
{
	QPushButton* btn = ui.m_today_todo_btn;
	btnSwitch(btn);
	m_todoitem_dao->selectTodosToday(m_todoiteme_list);
	initPage();
}

void KHomePage::on_m_later_seven_days_btn_clicked()
{
	QPushButton* btn = ui.m_later_seven_days_btn;
	btnSwitch(btn);
	m_todoitem_dao->selectTodosSeven(m_todoiteme_list);
	initPage();
}

void KHomePage::on_m_later_more_days_btn_clicked()
{
	qDebug() << "KHomePage::on_m_later_more_days_btn_clicked()";
	QPushButton* btn = ui.m_later_more_days_btn;
	btnSwitch(btn);
	m_todoitem_dao->selectTodosLater(m_todoiteme_list);
	qDebug() << m_todoiteme_list.size();
	initPage();
}

void KHomePage::on_m_not_arrange_btn_clicked()
{
	QPushButton *btn = ui.m_not_arrange_btn;
	btnSwitch(btn);
	emit giveItemInfo(m_todo_list[0]);
	m_todoitem_dao->selectTodosNotArrange(m_todoiteme_list);
	initPage();
}

void KHomePage::on_m_todocontent_edit_returnPressed()
{
	// 按下回车键
	qDebug() << "pressed button";
	const QString todoname = ui.m_todocontent_edit->text();
	if (todoname != nullptr && !todoname.isEmpty())
	{
		KTodoItem_E item;
		item.todo_name = todoname;
		item.priority = 0;
		item.belong_group = "无";
		bool flag = m_todoitem_dao->addNewTodoitem(item);
		if (flag)
			QMessageBox::information(this, "添加成功", "成功添加待办事项");
	}
}

void KHomePage::currentrow_change_list(int currentindex)
{
	if (currentindex >= 0 && currentindex < m_todoiteme_list.size())
	{
		KTodoItem_E item = m_todoiteme_list[currentindex];
		emit to_item_info(item);
	}
}
