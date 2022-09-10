#include "ktoolbar.h"
#include "kuifactory.h"

KToolBar::KToolBar(QWidget *parent)
	: QWidget(parent)
{
    initPage();
}

KToolBar::~KToolBar()
= default;

void KToolBar::initPage()
{
    setMinimumSize(QSize(500, 58));
    setObjectName(QStringLiteral("KToolBar"));
    horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

    m_pStartMonitorBtn = KUIFactory::createToolBtn(this, "m_pStartMonitorBtn", QStringLiteral("��ʼ����"));
    horizontalLayout->addWidget(m_pStartMonitorBtn);

    m_pPauseMonitorBtn = KUIFactory::createToolBtn(this, "m_pPauseMonitorBtn", QStringLiteral("��ͣ����"));
    horizontalLayout->addWidget(m_pPauseMonitorBtn);
    m_pPauseMonitorBtn->setEnabled(false);

    m_pResetMonitorBtn = KUIFactory::createToolBtn(this, "m_pResetMonitorBtn", QStringLiteral("���ü���"));
    horizontalLayout->addWidget(m_pResetMonitorBtn);
    m_pResetMonitorBtn->setEnabled(false);

    m_pStopMonitorBtn = KUIFactory::createToolBtn(this, "m_pStopMonitorBtn", QStringLiteral("ֹͣ����"));
    horizontalLayout->addWidget(m_pStopMonitorBtn);
    m_pStopMonitorBtn->setEnabled(false);

    m_pImportProfileBtn = KUIFactory::createToolBtn(this, "m_pImportProfileBtn", QStringLiteral("���������ļ�"));
    horizontalLayout->addWidget(m_pImportProfileBtn);

    m_pExportProfileBtn = KUIFactory::createToolBtn(this, "m_pExportProfileBtn", QStringLiteral("���������ļ�"));
    horizontalLayout->addWidget(m_pExportProfileBtn);

    m_pMinimizeWindow = KUIFactory::createToolBtn(this, "m_pMinimizeWindow", QStringLiteral("��С������"));
    horizontalLayout->addWidget(m_pMinimizeWindow);

    m_p2 = KUIFactory::createToolBtn(this, "m_p2");
    horizontalLayout->addWidget(m_p2);

    m_p3 = KUIFactory::createToolBtn(this, "m_p3");
    horizontalLayout->addWidget(m_p3);

    m_p4 = KUIFactory::createToolBtn(this, "m_p4");
    horizontalLayout->addWidget(m_p4);

    m_p5 = KUIFactory::createToolBtn(this, "m_p5");
    horizontalLayout->addWidget(m_p5);

    m_pSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout->addItem(m_pSpacer);

    QMetaObject::connectSlotsByName(this);
}
