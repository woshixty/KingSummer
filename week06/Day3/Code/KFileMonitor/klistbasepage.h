// -------------------------------------------------------
// klistbasepage.h
// 创建者： xie tingyu
// 创建时间： 2022/08/15
// 功能描述： 列表页面基类
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_LISTBASEPAGE_H_
#define _K_LISTBASEPAGE_H_

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QListWidget>
#include <QComboBox>

class KListBasePage : public QComboBox
{
	Q_OBJECT

public:
	KListBasePage(QWidget *parent);
	~KListBasePage() override;
    void initPage();
    void setUiName(const QString& labelName);

protected:
    QWidget* m_topBar{};
    QVBoxLayout* verticalLayout{};
    QHBoxLayout* horizontalLayout{};
    QLabel* m_label{};
    QPushButton* m_addBtn{};
    QPushButton* m_deleteBtn{};
    QListWidget* m_profileList{};
    QSpacerItem* m_spacer{};
};

#endif