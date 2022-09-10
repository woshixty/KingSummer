// -------------------------------------------------------
// kmainwindow.h
// 创建者： xie tingyu
// 创建时间： 2022/08/11
// 功能描述： 主窗口
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_MAINWINDOW_H_
#define _K_MAINWINDOW_H_

#include "ui_KMainWindow.h"

#include "kdirectorypage.h"
#include "ktoolbar.h"
#include "kmonitorservice.h"
#include "kmessageconsumer.h"
#include "kprofilepage.h"
#include "krecorddao.h"
#include "kprofiledao.h"
#include "kquerypage.h"
#include "kstatuspage.h"
#include "krecordtableservice.h"

#include <QSystemTrayIcon>

class KFileMonitor final : public QMainWindow
{
    Q_OBJECT

public:
    
    KFileMonitor(QWidget *parent = nullptr);
    ~KFileMonitor() override;
    void setPointer() const;

    void initPage();
	void initRecordTableView() const;
    void initDatabase();
	void initConnections() const;

    void setNowAndDayAfterRecord() const;

private slots:
    void activeProfileChanged() const;
    void startMonitor() const;
    void pauseMonitor() const;
    void resetMonitor() const;
    void stopMonitor() const;
    void minimizeRun();

private:
    Ui::KFileMonitorClass ui{};
    QWidget* m_pCentral{};
    QWidget* m_pDataPage{};
    QWidget* m_pInfoPage{};

    QGridLayout* m_pGridLayout{};
    QVBoxLayout* m_pVerticalLayout2{};
    QVBoxLayout* m_pVerticalLayout{};

    QTableView* m_pRecordTableView{};
    KQueryPage* m_pQueryPage{};
    KProfilePage* m_pProfilePage{};
    KDirectoryPage* m_pDirectoryPage{};
    KStatusPage* m_pStatusPage{};
    KToolBar* m_pToolPage{};
    QMenuBar* m_pMenuBar{};
    QStatusBar* m_pStatusBar{};

    KMessageQueue* m_pMQueue{};
    KMonitorService* m_pMService{};
    KMessageConsumer* m_pMConsumer{};
    KRecordDao* m_pRecordDao{};
    KProfileDao* m_pProfileDao{};
    KRecordTableService* m_pRecordTableService{};

    QSqlDatabase m_db;
    QSqlTableModel* m_pRecordSqlTableModel{};
    QSystemTrayIcon* m_pSystemTrayIcon;

    KGlobalData* m_pGlobalData = KGlobalData::getGlobalDataInstance(this);
};

#endif