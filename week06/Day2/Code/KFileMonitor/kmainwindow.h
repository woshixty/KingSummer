// -------------------------------------------------------
// kmainwindow.h
// 创建者： xie tingyu
// 创建时间： 2022/08/11
// 功能描述： 
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_MAINWINDOW_H_
#define _K_MAINWINDOW_H_

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include "ui_KMainWindow.h"
#include "ktoolbar.h"

class KToolBar;

class KFileMonitor : public QMainWindow
{
    Q_OBJECT

public:
    KFileMonitor(QWidget *parent = nullptr);
    ~KFileMonitor() override;

    void initPage();

private:
    Ui::KFileMonitorClass ui{};
    QWidget* m_pFuncBar{};
    QGridLayout* gridLayout{};
    QWidget* m_pDataPage{};
    QVBoxLayout* verticalLayout_2{};
    QListView* m_pInfoList{};
    QWidget* m_pFilterPage{};
    QWidget* m_pInfoPage{};
    QVBoxLayout* verticalLayout{};
    QWidget* m_pProPage{};
    QWidget* m_pDirPage{};
    QWidget* m_pStatusPage{};
    KToolBar* m_pToolPage{};
    QMenuBar* m_pMenuBar{};
    QStatusBar* m_pStatusBar{};
};

#endif