#include "kmainwindow.h"

KFileMonitor::KFileMonitor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    initPage();
}

KFileMonitor::~KFileMonitor()
= default;

void KFileMonitor::initPage()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("MainWindow"));
    this->resize(1060, 739);
    m_pFuncBar = new QWidget(this);
    m_pFuncBar->setObjectName(QStringLiteral("m_pFuncBar"));
    gridLayout = new QGridLayout(m_pFuncBar);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    m_pDataPage = new QWidget(m_pFuncBar);
    m_pDataPage->setObjectName(QStringLiteral("m_pDataPage"));
    verticalLayout_2 = new QVBoxLayout(m_pDataPage);
    verticalLayout_2->setSpacing(6);
    verticalLayout_2->setContentsMargins(11, 11, 11, 11);
    verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
    m_pInfoList = new QListView(m_pDataPage);
    m_pInfoList->setObjectName(QStringLiteral("m_pInfoList"));
    m_pInfoList->setMinimumSize(QSize(600, 400));

    verticalLayout_2->addWidget(m_pInfoList);

    m_pFilterPage = new QWidget(m_pDataPage);
    m_pFilterPage->setObjectName(QStringLiteral("m_pFilterPage"));
    m_pFilterPage->setMinimumSize(QSize(600, 200));
    m_pFilterPage->setStyleSheet(QStringLiteral("background-color: rgb(85, 170, 255);"));

    verticalLayout_2->addWidget(m_pFilterPage);


    gridLayout->addWidget(m_pDataPage, 1, 1, 1, 1);

    m_pInfoPage = new QWidget(m_pFuncBar);
    m_pInfoPage->setObjectName(QStringLiteral("m_pInfoPage"));
    m_pInfoPage->setStyleSheet(QStringLiteral("background-color: rgb(255, 170, 127);"));
    verticalLayout = new QVBoxLayout(m_pInfoPage);
    verticalLayout->setSpacing(6);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    m_pProPage = new QWidget(m_pInfoPage);
    m_pProPage->setObjectName(QStringLiteral("m_pProPage"));
    m_pProPage->setMinimumSize(QSize(400, 200));
    m_pProPage->setStyleSheet(QStringLiteral("background-color: rgb(85, 0, 255);"));

    verticalLayout->addWidget(m_pProPage);

    m_pDirPage = new QWidget(m_pInfoPage);
    m_pDirPage->setObjectName(QStringLiteral("m_pDirPage"));
    m_pDirPage->setMinimumSize(QSize(400, 200));
    m_pDirPage->setStyleSheet(QStringLiteral("background-color: rgb(255, 85, 0);"));

    verticalLayout->addWidget(m_pDirPage);

    m_pStatusPage = new QWidget(m_pInfoPage);
    m_pStatusPage->setObjectName(QStringLiteral("m_pStatusPage"));
    m_pStatusPage->setMinimumSize(QSize(400, 200));
    m_pStatusPage->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 0);"));

    verticalLayout->addWidget(m_pStatusPage);


    gridLayout->addWidget(m_pInfoPage, 1, 0, 1, 1);

    m_pToolPage = new KToolBar(m_pFuncBar);
    m_pToolPage->setObjectName(QStringLiteral("m_pToolPage"));
    m_pToolPage->setMinimumSize(QSize(500, 40));
    m_pToolPage->setStyleSheet(QStringLiteral("background-color: rgb(170, 255, 0);"));

    gridLayout->addWidget(m_pToolPage, 0, 0, 1, 2);

    this->setCentralWidget(m_pFuncBar);
    m_pMenuBar = new QMenuBar(this);
    m_pMenuBar->setObjectName(QStringLiteral("m_pMenuBar"));
    m_pMenuBar->setGeometry(QRect(0, 0, 1060, 23));
    this->setMenuBar(m_pMenuBar);
    m_pStatusBar = new QStatusBar(this);
    m_pStatusBar->setObjectName(QStringLiteral("m_pStatusBar"));
    this->setStatusBar(m_pStatusBar);

    QMetaObject::connectSlotsByName(this);
}