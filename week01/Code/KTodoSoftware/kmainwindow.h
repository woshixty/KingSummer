#ifndef KMAINWINDOW_H
#define KMainWindow_H

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

#include <QtWidgets/QMainWindow>
#include <qsqldatabase.h>
#include <qsqlerror.h>
#include "ui_kmainwindow.h"
#include "khomepage.h"
#include "kgroupitem.h"
#include "kgroupdao.h"
#include "kconstants.h"
#include "knewgroupdialog.h"
#include "ktodoitemdao.h"
#include "kmytodoppage.h"
#include "ktodogrouppage.h"

class KMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    KMainWindow(QWidget *parent = Q_NULLPTR);
    void initGroups();
    void initDatabase();
    void initStackWidget();

    KGroupDao* m_group_dao{};
    KTodoItemDao* m_todoitem_dao{};
    QSqlDatabase m_db;

private:
    Ui::KMainWindowClass ui{};
    QList<KGroup> m_groups;
    QList<KGroupItem*> m_groupitems;
    KNewGroupDialog* m_new_group_dialog;
    KHomePage* m_home_page{};
    KMytodopPage* m_mytodo_page{};
    KTodoGroupPage* m_grouptodo_page{};
    KTodoItemInfo* m_todoiteminfo;

private slots:
    void on_m_myhome_btn_clicked() const;
    void on_m_mytodos_btn_clicked() const;
    void on_m_addgroup_btn_clicked() const;
    // 自定义槽函数
    void on_add_new_group(QString group_name);
    void change_to_group_page(QString group_name, size_t count) const;
    void on_grouptodo_complete_g();
};

#endif
