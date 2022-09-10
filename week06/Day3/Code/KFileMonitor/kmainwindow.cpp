#include "kmainwindow.h"
#include "ksqlmodelutil.h"

#include <QDebug>
#include <QSqlError>
#include <QTableView>

KFileMonitor::KFileMonitor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    // �������̰߳�ȫ����������
    m_pMQueue = new KMessageQueue(this);
    // �����ļ�����������
    m_pMService = new KMonitorService(this);
    // �����ļ���Ϣ�������߳�
    m_pMConsumer = new KMessageConsumer(this);
	// ������������
    m_pRecordTableService = new KRecordTableService(this);
    m_pSystemTrayIcon = new QSystemTrayIcon(this);
	initPage();
	initDatabase();
    initConnections();
    setPointer();
    initRecordTableView();
	// ��ʼ��״̬�����ļ�����
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
    // ��ʼ�������ļ�ҳ��
	m_pProfilePage->setProfileDao(m_pProfileDao);
    m_pProfilePage->initData();
    // ��ʼ����Ϣ������
    m_pMService->setKMessageQueue(m_pMQueue);
    // ��ʼ����������
    m_pMConsumer->setMessageQueue(m_pMQueue);
    m_pMConsumer->setRecordDao(m_pRecordDao);
    m_pMConsumer->setSqlTableModel(m_pRecordSqlTableModel);
    // ��ʼ����������
    m_pRecordTableService->setSqlTableModel(m_pRecordSqlTableModel);
    // �����������ģ��
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

    // ���������ҳ�棺�����б������������
    m_pDataPage = new QWidget(m_pCentral);
    m_pDataPage->setObjectName(QStringLiteral("m_pDataPage"));
    // ����ҳ��Ĵ�ֱ����
    m_pVerticalLayout2 = new QVBoxLayout(m_pDataPage);
    m_pVerticalLayout2->setSpacing(6);
    m_pVerticalLayout2->setContentsMargins(0, 0, 0, 0);
    m_pVerticalLayout2->setObjectName(QStringLiteral("m_pVerticalLayout2"));
    // ����������
    m_pQueryPage = new KQueryPage(m_pDataPage);
    m_pVerticalLayout2->addWidget(m_pQueryPage);
	// �����б�
	m_pRecordTableView = new QTableView(m_pDataPage);
    m_pRecordTableView->setObjectName(QStringLiteral("m_pRecordTableView"));
    m_pRecordTableView->setMinimumSize(QSize(600, 400));
    m_pVerticalLayout2->addWidget(m_pRecordTableView);
    m_pGridLayout->addWidget(m_pDataPage, 1, 1, 1, 1);

    // ���������ҳ�棺�����ļ����ҳ�桢�����ļ�������Ŀ¼�б�ҳ�桢����״̬��ʾҳ��
	m_pInfoPage = new QWidget(m_pCentral);
    m_pInfoPage->setObjectName(QStringLiteral("m_pInfoPage"));
    m_pVerticalLayout = new QVBoxLayout(m_pInfoPage);
    m_pVerticalLayout->setSpacing(0);
    m_pVerticalLayout->setContentsMargins(0, 0, 0, 0);
    m_pVerticalLayout->setObjectName(QStringLiteral("m_pVerticalLayout"));
    // ���������ҳ�棺�����ļ����ҳ��
    m_pProfilePage = new KProfilePage(m_pInfoPage);
    m_pVerticalLayout->addWidget(m_pProfilePage);
    // ���������ҳ�棺�����ļ�������Ŀ¼�б�ҳ��
    m_pDirectoryPage = new KDirectoryPage(m_pInfoPage);
    m_pVerticalLayout->addWidget(m_pDirectoryPage);
    // ���������ҳ�棺����״̬��ʾҳ��
    m_pStatusPage = new KStatusPage(m_pInfoPage);
    m_pVerticalLayout->addWidget(m_pStatusPage);
    // ������ҳ����ɵ�infoҳ����ӵ�������
    m_pGridLayout->addWidget(m_pInfoPage, 1, 0, 1, 1);

    // ����ϲ㹤����
    m_pToolPage = new KToolBar(m_pCentral);
    m_pGridLayout->addWidget(m_pToolPage, 0, 0, 1, 2);
    // �������ҳ��
    setCentralWidget(m_pCentral);
    // ���״̬��
    m_pStatusBar = new QStatusBar(this);
    m_pStatusBar->setObjectName(QStringLiteral("m_pStatusBar"));
    this->setStatusBar(m_pStatusBar);
}

void KFileMonitor::initRecordTableView() const
{
    // view����ֻ��ѡ����
    m_pRecordTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // ����id��
    m_pRecordTableView->setColumnHidden(m_pRecordSqlTableModel->fieldIndex("id"), true);
    // �����ͷ�������
    m_pRecordTableView->setSortingEnabled(true);
    // �����к�
    m_pRecordTableView->verticalHeader()->hide();
    // ��������Ӧ���
    m_pRecordTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // ���ɱ༭
    m_pRecordTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // ����Ϊ��ǰ��һ��֮���
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
        qDebug() << QStringLiteral("��ʼ�����ݿ�ʧ�� : ") << m_db.lastError().text();
        return;
    }
    // ����Dao��
    m_pRecordDao = new KRecordDao(this);
    m_pProfileDao = new KProfileDao(this);
    // ����Sql����ģ��
    m_pRecordSqlTableModel = new QSqlTableModel(this, m_db);
    // �������ݱ�
    m_pRecordSqlTableModel->setTable("operationRecord");
    // ���ø��Ĳ���ֻҪһ��͸���
    m_pRecordSqlTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    // ���ñ�ͷ
    m_pRecordSqlTableModel->setHeaderData(m_pRecordSqlTableModel->fieldIndex("file_operation"), Qt::Horizontal, QStringLiteral("��������"));
    m_pRecordSqlTableModel->setHeaderData(m_pRecordSqlTableModel->fieldIndex("operation_date"), Qt::Horizontal, QStringLiteral("��������"));
    m_pRecordSqlTableModel->setHeaderData(m_pRecordSqlTableModel->fieldIndex("operation_time"), Qt::Horizontal, QStringLiteral("����ʱ��"));
    m_pRecordSqlTableModel->setHeaderData(m_pRecordSqlTableModel->fieldIndex("file_name"), Qt::Horizontal, QStringLiteral("�ļ�����"));
    m_pRecordSqlTableModel->setHeaderData(m_pRecordSqlTableModel->fieldIndex("file_size"), Qt::Horizontal, QStringLiteral("�ļ���С"));
    m_pRecordSqlTableModel->setHeaderData(m_pRecordSqlTableModel->fieldIndex("file_owner"), Qt::Horizontal, QStringLiteral("�ļ�����"));
}

void KFileMonitor::initConnections() const
{
    // ��������ź���ۺ���
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
    // ��ǰ��Ծ�����ļ�����
	connect(
		m_pProfilePage, SIGNAL(sendCurrentProfile()),
		this, SLOT(activeProfileChanged())
	);
	connect(
		m_pProfilePage, SIGNAL(sendCurrentProfile()),
		m_pDirectoryPage, SLOT(activeProfileChanged())
	);
    // �ļ������ҳ����������ļ�������Ŀ¼
    connect(
		m_pDirectoryPage, SIGNAL(addDirectory(QString)),
		m_pProfilePage, SLOT(addDirToWatch(QString))
	);
    // �����ʼ������ť
    connect(
		m_pToolPage->startMonitorBtn(), SIGNAL(clicked()),
		this, SLOT(startMonitor())
	);
    // �����ͣ������ť
	connect(
		m_pToolPage->pauseMonitorBtn(), SIGNAL(clicked()),
		this, SLOT(pauseMonitor())
	);
    // ������ü�����ť
	connect(
		m_pToolPage->resetMonitorBtn(), SIGNAL(clicked()),
		this, SLOT(resetMonitor())
	);
    // ���ֹͣ������ť
	connect(
		m_pToolPage->stopMonitorBtn(), SIGNAL(clicked()),
		this, SLOT(stopMonitor())
	);
    // ���뵼�������ļ�
    connect(
        m_pToolPage->importMonitorBtn(), SIGNAL(clicked()),
        m_pProfilePage, SLOT(importProfile())
    );
    connect(
        m_pToolPage->exportMonitorBtn(), SIGNAL(clicked()),
        m_pProfilePage, SLOT(exportProfile())
    );
    // ��С�����а�ť
    connect(
        m_pToolPage->minimizeWindow(), SIGNAL(clicked()),
        this, SLOT(minimizeRun())
    );
    // ���±�
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
    // ״̬����ʾ��ǰ�����ļ���
    m_pStatusBar->showMessage(QStringLiteral("��ǰ�����ļ�: ") + m_pGlobalData->activeProfile().profileName());
}

void KFileMonitor::startMonitor() const
{
    m_pStatusPage->timer()->start();
    // ���ÿؼ�ʹ��
    m_pToolPage->startMonitorBtn()->setEnabled(false);
    m_pToolPage->resetMonitorBtn()->setEnabled(true);
    m_pToolPage->pauseMonitorBtn()->setEnabled(true);
    m_pToolPage->stopMonitorBtn()->setEnabled(true);
    // ��ѯ���ݽ���ʹ�ܹر�
    m_pQueryPage->setEnabled(false);
    // �����ļ��������ļ�����Ŀ¼ҳ��ʹ�ܹر�
    m_pProfilePage->setEnabled(false);
    m_pDirectoryPage->setEnabled(false);
    // �����ļ����������߳�
    if (!m_pMService->startServerThread())
        qDebug() << QStringLiteral("�ļ������߳�����ʧ��");
    m_pMService->startMonitor(m_pProfilePage->getCurrentProfile());
	// �����������߳�
    if(!m_pMConsumer->isRunning())
    {
        m_pMConsumer->startConsumerThread();
        m_pMConsumer->start();
    }
    if (!m_pMConsumer->isRunning())
        qDebug() << QStringLiteral("�������߳�����ʧ��");
}

void KFileMonitor::pauseMonitor() const
{
    m_pStatusPage->timer()->stop();
    // ���ÿؼ�ʹ��
    m_pToolPage->startMonitorBtn()->setEnabled(true);
    m_pToolPage->pauseMonitorBtn()->setEnabled(false);
    m_pMService->pauseServer();
}

void KFileMonitor::resetMonitor() const
{
    // �����ǰ��ʾ����
    setNowAndDayAfterRecord();
	m_pRecordSqlTableModel->select();
}

void KFileMonitor::stopMonitor() const
{
    m_pStatusPage->timer()->stop();
    m_pStatusPage->initValue();
    // ���ÿؼ�ʹ��
    m_pToolPage->startMonitorBtn()->setEnabled(true);
    m_pToolPage->resetMonitorBtn()->setEnabled(false);
    m_pToolPage->pauseMonitorBtn()->setEnabled(false);
    m_pToolPage->stopMonitorBtn()->setEnabled(false);
    // ��ѯ���ݽ���ʹ�ܴ�
    m_pQueryPage->setEnabled(true);
    // �����ļ��������ļ�����Ŀ¼ҳ��ʹ�ܴ�
    m_pProfilePage->setEnabled(true);
    m_pDirectoryPage->setEnabled(true);
    // �ر��߳�
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
