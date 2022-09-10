#include "kmainwindow.h"

#include <utility>

KMainWindow::KMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    // 设置窗口名称和图标
    setWindowIcon(QIcon(":/appicon/icons/todoist.png"));
    setWindowTitle("KingTodo");

    const QPixmap pix(":/appicon/icons/todoist.png");
    const QPixmap dest = pix.scaled(ui.left_up_icon->size(), Qt::KeepAspectRatio);
    ui.left_up_icon->setPixmap(dest);

    // 初始化参数
    initDatabase();

    m_todoiteminfo = new KTodoItemInfo(this);
    m_todoiteminfo->setObjectName(QStringLiteral("widget"));
    m_todoiteminfo->setGeometry(QRect(970, 10, 210, 540));

    initStackWidget();
    initGroups();
    m_new_group_dialog = new KNewGroupDialog(this);
    m_new_group_dialog->setVisible(false);
    connect(m_new_group_dialog, SIGNAL(add_group(QString)), this, SLOT(on_add_new_group(QString)));
    connect(m_home_page, SIGNAL(giveItemInfo(KTodoItem_E)), m_todoiteminfo, SLOT(getItemInfo(KTodoItem_E)));
}

void KMainWindow::initGroups()
{
    // 清空数据
    ui.m_group_list->clear();
    size_t rows = m_groupitems.size();
    for (size_t i = 0; i < rows; i++)
    {
        KGroupItem* item = m_groupitems.at(0);
        m_groupitems.removeAt(0);
        delete item;
    }
    // 数据库查询m_groups
    m_group_dao->getAllGroups(m_groups);
    // 封装成m_groupitems
    rows = m_groups.size();
    // 加入到私有变量list中
    for (int i = 0; i < rows; i++)
    {
	    auto item = new KGroupItem(this);
	    const int count = m_todoitem_dao->selectGroupNum(m_groups[i].getGroupName());
        item->setGroupNameLabel(m_groups[i].getGroupName(), count);
        m_groupitems.append(item);
        connect(item, SIGNAL(show_group_todos(QString, size_t)), this, SLOT(change_to_group_page(QString, size_t)));
    }
    // 逐个绑定item并显示
    for (int i = 0; i < m_groups.size(); i++)
    {
        QWidget* group_item = m_groupitems.at(i);
        const auto item = new QListWidgetItem(ui.m_group_list);
        QSize size = item->sizeHint();
        item->setSizeHint(QSize(size.height(), group_item->height()));
        ui.m_group_list->setItemWidget(item, group_item);
    }
}

void KMainWindow::initDatabase()
{
	const QString database = "ktodo.db3";
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(database);

	const bool ok = m_db.open();
    if (!ok)
    {
        qDebug() << "[KDataBase::initDataBase]:: " << m_db.lastError().text();
        return;
    }

    m_group_dao = new KGroupDao(this);
    m_todoitem_dao = new KTodoItemDao(this);
}

void KMainWindow::initStackWidget()
{
    m_home_page = new KHomePage(this);
    ui.stackedWidget->addWidget(m_home_page);
    m_home_page->setPageInfoP(m_todoiteminfo);

    m_mytodo_page = new KMytodopPage(this);
    ui.stackedWidget->addWidget(m_mytodo_page);
    m_mytodo_page->setPageInfoP(m_todoiteminfo);
    m_mytodo_page->initPage();

    m_grouptodo_page = new KTodoGroupPage(this);
    ui.stackedWidget->addWidget(m_grouptodo_page);
    m_grouptodo_page->setPageInfoP(m_todoiteminfo);

    ui.stackedWidget->setCurrentIndex(0);
}

void KMainWindow::on_m_myhome_btn_clicked() const
{
    ui.m_myhome_btn->setStyleSheet(m_check);
    ui.m_myhome_btn->setIcon(QIcon(":/mainwindow/icons/home-on-mouse.png"));
    ui.m_mytodos_btn->setStyleSheet(m_uncheck);
    ui.m_mytodos_btn->setIcon(QIcon(":/mainwindow/icons/todo.png"));
    ui.stackedWidget->setCurrentIndex(0);
}

void KMainWindow::on_m_mytodos_btn_clicked() const
{
    ui.m_myhome_btn->setStyleSheet(m_uncheck);
    ui.m_myhome_btn->setIcon(QIcon(":/mainwindow/icons/home.png"));
    ui.m_mytodos_btn->setStyleSheet(m_check);
    ui.m_mytodos_btn->setIcon(QIcon(":/mainwindow/icons/todo-on-mouse.png"));
    ui.stackedWidget->setCurrentIndex(1);
}

void KMainWindow::on_m_addgroup_btn_clicked() const
{
    m_new_group_dialog->show();
}

void KMainWindow::on_add_new_group(QString group_name)
{
    m_group_dao->addNewGroup(std::move(group_name));
    initGroups();
}

void KMainWindow::change_to_group_page(QString group_name, size_t count) const
{
    ui.stackedWidget->setCurrentIndex(2);
    m_grouptodo_page->initPage(std::move(group_name), count);
    // 修改我的首页和我的待办按钮样式
    ui.m_myhome_btn->setStyleSheet(m_uncheck);
    ui.m_myhome_btn->setIcon(QIcon(":/mainwindow/icons/home.png"));
    ui.m_mytodos_btn->setStyleSheet(m_uncheck);
    ui.m_mytodos_btn->setIcon(QIcon(":/mainwindow/icons/todo.png"));
}

void KMainWindow::on_grouptodo_complete_g()
{
    qDebug() << "KMainWindow::on_grouptodo_complete_g()";
    initGroups();
}
