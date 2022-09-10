#include "ktodogrouppage.h"

KTodoGroupPage::KTodoGroupPage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_todoitem_dao = new KTodoItemDao(this);
    connect(ui.m_todo_list, SIGNAL(currentRowChanged(int)), this, SLOT(currentrow_change_list(int)));
}

KTodoGroupPage::~KTodoGroupPage()
{}

void KTodoGroupPage::initPage(QString group_name, size_t count)
{
	m_group_name = group_name;
	m_count = count;
	ui.mypage->setText(group_name);
	initList();
}

void KTodoGroupPage::initList()
{
	m_todoitem_dao->selectTodosByGroupname(m_todoiteme_list, m_group_name);
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
    // 数据库查询m_groups
    m_todoitem_dao->selectTodosByGroupname(m_todoiteme_list, m_group_name);
    // 封装成m_groupitems
    rows = m_todoiteme_list.size();
    // 加入到私有变量list中
    for (size_t i = 0; i < rows; i++)
    {
        KTodoItem* item = new KTodoItem(this);
        item->initItem(m_todoiteme_list[i]);
        m_todoitemw_list.append(item);
        connect(item, SIGNAL(choose_a_todo(KTodoItem_E)), m_todoinfopage, SLOT(on_todoitem_choosed(KTodoItem_E)));
        connect(item, SIGNAL(update_a_todo_g()), this->parentWidget()->parentWidget(), SLOT(on_grouptodo_complete_g()));
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

void KTodoGroupPage::currentrow_change_list(int currentindex)
{
    qDebug() << "currentindex" << "：" << currentindex;
    if (currentindex >= 0 && currentindex < m_todoiteme_list.size())
    {
        KTodoItem_E item = m_todoiteme_list[currentindex];
        emit to_item_info(item);
    }
}

void KTodoGroupPage::on_m_todocontent_edit_returnPressed()
{
    // 按下回车键
    // 清空edit - 下方列表添加数据 - 数据库添加数据 - 右边显示该待办事项的数据
    QString todoname = ui.m_todocontent_edit->text();
    if (todoname != nullptr && !todoname.isEmpty())
    {
        KTodoItem_E item;
        item.todo_name = todoname;
        item.priority = 0;
        item.belong_group = m_group_name;
        // 添加到数据库
        bool flag = m_todoitem_dao->addNewTodoitem(item);
        if (flag)
            QMessageBox::information(this, "添加成功", "成功添加待办事项");
        ui.m_todocontent_edit->clear();
        // TODO 右边显示该新建待办事项的数据
        initPage(m_group_name, m_count);
    }
}
