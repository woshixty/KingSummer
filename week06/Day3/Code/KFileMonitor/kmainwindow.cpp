#include "kmainwindow.h"
#include "ksqlmodelutil.h"

#include <QDebug>
#include <QSqlError>
#include <QTableView>

KFileMonitor::KFileMonitor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    // 创建多线程安全的阻塞队列
    m_pMQueue = new KMessageQueue(this);
    // 创建文件监听服务类
    m_pMService = new KMonitorService(this);
    // 创建文件消息消费者线程
    m_pMConsumer = new KMessageConsumer(this);
	// 创建表格服务类
    m_pRecordTableService = new KRecordTableService(this);
    m_pSystemTrayIcon = new QSystemTrayIcon(this);
	initPage();
	initDatabase();
    initConnections();
    setPointer();
    initRecordTableView();
	// 初始化状态栏和文件夹栏
    const KProfile profile = m_pProfilePage->getCurrentProfile();
    activeProfileChanged();
    m_pDirectoryPage->activeProfileChanged();
}

KFileMonitor::~KFileMonitor()
{
    bool flag = m_pMService->stopServerThread();
    m_pMConsumer->stopConsumerThread();
}

void KFileMonitor::setPointer() const
{
    // 初始化配置文件页面
	m_pProfilePage->setProfileDao(m_pProfileDao);
    m_pProfilePage->initData();
    // 初始化消息服务类
    m_pMService->setKMessageQueue(m_pMQueue);
    // 初始化消费者类
    m_pMConsumer->setMessageQueue(m_pMQueue);
    m_pMConsumer->setRecordDao(m_pRecordDao);
    m_pMConsumer->setSqlTableModel(m_pRecordSqlTableModel);
    // 初始化表格服务类
    m_pRecordTableService->setSqlTableModel(m_pRecordSqlTableModel);
    // 表格设置数据模型
    m_pRecordTableView->setModel(m_pRecordSqlTableModel);
    m_pMConsumer->setSystemTrayIcon(m_pSystemTrayIcon);
}

void KFileMonitor::initPage()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("MainWindow"));
    this->resize(1200, 800);
    m_pCentral = new QWidget(this);
    m_pCentral->setObjectName(QStringLiteral("m_pCentral"));
    m_pGridLayout = new QGridLayout(m_pCentral);
    m_pGridLayout->setSpacing(6);
    m_pGridLayout->setContentsMargins(11, 11, 11, 11);
    m_pGridLayout->setObjectName(QStringLiteral("m_pGridLayout"));

    // 创建并添加页面：数据列表和数据搜索栏
    m_pDataPage = new QWidget(m_pCentral);
    m_pDataPage->setObjectName(QStringLiteral("m_pDataPage"));
    // 数据页面的垂直布局
    m_pVerticalLayout2 = new QVBoxLayout(m_pDataPage);
    m_pVerticalLayout2->setSpacing(6);
    m_pVerticalLayout2->setContentsMargins(0, 0, 0, 0);
    m_pVerticalLayout2->setObjectName(QStringLiteral("m_pVerticalLayout2"));
    // 数据搜索栏
    m_pQueryPage = new KQueryPage(m_pDataPage);
    m_pVerticalLayout2->addWidget(m_pQueryPage);
	// 数据列表
	m_pRecordTableView = new QTableView(m_pDataPage);
    m_pRecordTableView->setObjectName(QStringLiteral("m_pRecordTableView"));
    m_pRecordTableView->setMinimumSize(QSize(600, 400));
    m_pVerticalLayout2->addWidget(m_pRecordTableView);
    m_pGridLayout->addWidget(m_pDataPage, 1, 1, 1, 1);

    // 创建并添加页面：配置文件添加页面、配置文件监听的目录列表页面、监听状态显示页面
	m_pInfoPage = new QWidget(m_pCentral);
    m_pInfoPage->setObjectName(QStringLiteral("m_pInfoPage"));
    m_pVerticalLayout = new QVBoxLayout(m_pInfoPage);
    m_pVerticalLayout->setSpacing(0);
    m_pVerticalLayout->setContentsMargins(0, 0, 0, 0);
    m_pVerticalLayout->setObjectName(QStringLiteral("m_pVerticalLayout"));
    // 创建并添加页面：配置文件添加页面
    m_pProfilePage = new KProfilePage(m_pInfoPage);
    m_pVerticalLayout->addWidget(m_pProfilePage);
    // 创建并添加页面：配置文件监听的目录列表页面
    m_pDirectoryPage = new KDirectoryPage(m_pInfoPage);
    m_pVerticalLayout->addWidget(m_pDirectoryPage);
    // 创建并添加页面：监听状态显示页面
    m_pStatusPage = new KStatusPage(m_pInfoPage);
    m_pVerticalLayout->addWidget(m_pStatusPage);
    // 将三个页面组成的info页面添加到布局中
    m_pGridLayout->addWidget(m_pInfoPage, 1, 0, 1, 1);

    // 添加上层工具栏
    m_pToolPage = new KToolBar(m_pCentral);
    m_pGridLayout->addWidget(m_pToolPage, 0, 0, 1, 2);
    // 添加中央页面
    setCentralWidget(m_pCentral);
    // 添加状态栏
    m_pStatusBar = new QStatusBar(this);
    m_pStatusBar->setObjectName(QStringLiteral("m_pStatusBar"));
    this->setStatusBar(m_pStatusBar);
}

void KFileMonitor::initRecordTableView() const
{
    // view设置只能选择行
    m_pRecordTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // 隐藏id列
    m_pRecordTableView->setColumnHidden(m_pRecordSqlTableModel->fieldIndex("id"), true);
    // 允许表头点击排序
    m_pRecordTableView->setSortingEnabled(true);
    // 隐藏列号
    m_pRecordTableView->verticalHeader()->hide();
    // 设置自适应宽度
    m_pRecordTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // 不可编辑
    m_pRecordTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 设置为当前和一天之后的
    setNowAndDayAfterRecord();
    m_pRecordSqlTableModel->select();
}

void KFileMonitor::initDatabase()
{
    const QString database = "kmonitor.db";
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(database);
    const bool ok = m_db.open();
    if (!ok)
    {
        qDebug() << QStringLiteral("初始化数据库失败 : ") << m_db.lastError().text();
        return;
    }
    // 创建Dao层
    m_pRecordDao = new KRecordDao(this);
    m_pProfileDao = new KProfileDao(this);
    // 创建Sql数据模型
    m_pRecordSqlTableModel = new QSqlTableModel(this, m_db);
    // 设置数据表
    m_pRecordSqlTableModel->setTable("operationRecord");
    // 设置更改策略只要一变就更改
    m_pRecordSqlTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    // 设置表头
    m_pRecordSqlTableModel->setHeaderData(m_pRecordSqlTableModel->fieldIndex("file_operation"), Qt::Horizontal, QStringLiteral("操作类型"));
    m_pRecordSqlTableModel->setHeaderData(m_pRecordSqlTableModel->fieldIndex("operation_date"), Qt::Horizontal, QStringLiteral("操作日期"));
    m_pRecordSqlTableModel->setHeaderData(m_pRecordSqlTableModel->fieldIndex("operation_time"), Qt::Horizontal, QStringLiteral("操作时间"));
    m_pRecordSqlTableModel->setHeaderData(m_pRecordSqlTableModel->fieldIndex("file_name"), Qt::Horizontal, QStringLiteral("文件名称"));
    m_pRecordSqlTableModel->setHeaderData(m_pRecordSqlTableModel->fieldIndex("file_size"), Qt::Horizontal, QStringLiteral("文件大小"));
    m_pRecordSqlTableModel->setHeaderData(m_pRecordSqlTableModel->fieldIndex("file_owner"), Qt::Horizontal, QStringLiteral("文件属主"));
}

void KFileMonitor::initConnections() const
{
    // 下拉框的信号与槽函数
    connect(
        m_pQueryPage->sortContentComboBox(), SIGNAL(currentIndexChanged(int)),
        m_pRecordTableService, SLOT(sortByColumnType(int))
    );
	connect(
        m_pQueryPage->sortTypeComboBox(), SIGNAL(currentIndexChanged(int)),
        m_pRecordTableService, SLOT(sortBySortType(int))
    );
	connect(
        m_pQueryPage->operationTypeComboBox(), SIGNAL(currentIndexChanged(int)),
        m_pRecordTableService, SLOT(sortBySortType(int))
    );
    // 当前活跃配置文件更改
	connect(
		m_pProfilePage, SIGNAL(sendCurrentProfile()),
		this, SLOT(activeProfileChanged())
	);
	connect(
		m_pProfilePage, SIGNAL(sendCurrentProfile()),
		m_pDirectoryPage, SLOT(activeProfileChanged())
	);
    // 文件夹添加页面添加配置文件监听的目录
    connect(
		m_pDirectoryPage, SIGNAL(addDirectory(QString)),
		m_pProfilePage, SLOT(addDirToWatch(QString))
	);
    // 点击开始监听按钮
    connect(
		m_pToolPage->startMonitorBtn(), SIGNAL(clicked()),
		this, SLOT(startMonitor())
	);
    // 点击暂停监听按钮
	connect(
		m_pToolPage->pauseMonitorBtn(), SIGNAL(clicked()),
		this, SLOT(pauseMonitor())
	);
    // 点击重置监听按钮
	connect(
		m_pToolPage->resetMonitorBtn(), SIGNAL(clicked()),
		this, SLOT(resetMonitor())
	);
    // 点击停止监听按钮
	connect(
		m_pToolPage->stopMonitorBtn(), SIGNAL(clicked()),
		this, SLOT(stopMonitor())
	);
    // 导入导出配置文件
    connect(
        m_pToolPage->importMonitorBtn(), SIGNAL(clicked()),
        m_pProfilePage, SLOT(importProfile())
    );
    connect(
        m_pToolPage->exportMonitorBtn(), SIGNAL(clicked()),
        m_pProfilePage, SLOT(exportProfile())
    );
    // 最小化运行按钮
    connect(
        m_pToolPage->minimizeWindow(), SIGNAL(clicked()),
        this, SLOT(minimizeRun())
    );
    // 更新表单
    connect(
        m_pQueryPage->queryBtn(), SIGNAL(clicked()),
        m_pRecordTableService, SLOT(updateTable())
    );
}

void KFileMonitor::setNowAndDayAfterRecord() const
{
    const QDateTime start = QDateTime::currentDateTime();
    const QDateTime end = QDateTime::currentDateTime().addDays(1);
    KSqlModelUtil::generateBetweenDatetime(m_pRecordSqlTableModel, start, end);
}

void KFileMonitor::activeProfileChanged() const
{
    // 状态栏显示当前配置文件名
    m_pStatusBar->showMessage(QStringLiteral("当前配置文件: ") + m_pGlobalData->activeProfile().profileName());
}

void KFileMonitor::startMonitor() const
{
    m_pStatusPage->timer()->start();
    // 设置控件使能
    m_pToolPage->startMonitorBtn()->setEnabled(false);
    m_pToolPage->resetMonitorBtn()->setEnabled(true);
    m_pToolPage->pauseMonitorBtn()->setEnabled(true);
    m_pToolPage->stopMonitorBtn()->setEnabled(true);
    // 查询数据界面使能关闭
    m_pQueryPage->setEnabled(false);
    // 配置文件和配置文件监听目录页面使能关闭
    m_pProfilePage->setEnabled(false);
    m_pDirectoryPage->setEnabled(false);
    // 启动文件监听服务线程
    if (!m_pMService->startServerThread())
        qDebug() << QStringLiteral("文件监听线程启动失败");
    m_pMService->startMonitor(m_pProfilePage->getCurrentProfile());
	// 启动消费者线程
    if(!m_pMConsumer->isRunning())
    {
        m_pMConsumer->startConsumerThread();
        m_pMConsumer->start();
    }
    if (!m_pMConsumer->isRunning())
        qDebug() << QStringLiteral("消费者线程启动失败");
}

void KFileMonitor::pauseMonitor() const
{
    m_pStatusPage->timer()->stop();
    // 设置控件使能
    m_pToolPage->startMonitorBtn()->setEnabled(true);
    m_pToolPage->pauseMonitorBtn()->setEnabled(false);
    m_pMService->pauseServer();
}

void KFileMonitor::resetMonitor() const
{
    // 清除当前显示数据
    setNowAndDayAfterRecord();
	m_pRecordSqlTableModel->select();
}

void KFileMonitor::stopMonitor() const
{
    m_pStatusPage->timer()->stop();
    m_pStatusPage->initValue();
    // 设置控件使能
    m_pToolPage->startMonitorBtn()->setEnabled(true);
    m_pToolPage->resetMonitorBtn()->setEnabled(false);
    m_pToolPage->pauseMonitorBtn()->setEnabled(false);
    m_pToolPage->stopMonitorBtn()->setEnabled(false);
    // 查询数据界面使能打开
    m_pQueryPage->setEnabled(true);
    // 配置文件和配置文件监听目录页面使能打开
    m_pProfilePage->setEnabled(true);
    m_pDirectoryPage->setEnabled(true);
    // 关闭线程
    bool flag = m_pMService->stopServerThread();
    m_pMConsumer->stopConsumerThread();
}

void KFileMonitor::minimizeRun()
{
    m_pSystemTrayIcon->setIcon(QIcon(":/icons/monitoring.svg"));
    m_pSystemTrayIcon->setToolTip("KFileMonitor");
    m_pSystemTrayIcon->show();
    connect(
        m_pSystemTrayIcon, &QSystemTrayIcon::activated, 
        [=] { this->setVisible(true); m_pGlobalData->setVisible(true); });
	this->setVisible(false);
    m_pGlobalData->setVisible(false);
}
