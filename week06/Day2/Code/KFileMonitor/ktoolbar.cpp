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
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("KToolBar"));
    this->resize(1000, 58);
    this->setMaximumSize(QSize(1000, 58));
    horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

    m_pMonitorBtn = KUIFactory::createToolBtn(this, "m_pMonitorBtn", "M");
    horizontalLayout->addWidget(m_pMonitorBtn);

    m_pPauseBtn = KUIFactory::createToolBtn(this, "m_pPauseBtn", "P");
    horizontalLayout->addWidget(m_pPauseBtn);

    m_pResetBtn = KUIFactory::createToolBtn(this, "m_pResetBtn");
    horizontalLayout->addWidget(m_pResetBtn);

    m_pStopBtn = KUIFactory::createToolBtn(this, "m_pStopBtn");
    horizontalLayout->addWidget(m_pStopBtn);

    m_pWizardBtn = KUIFactory::createToolBtn(this, "m_pWizardBtn");
    horizontalLayout->addWidget(m_pWizardBtn);

    m_pSaveBtn = KUIFactory::createToolBtn(this, "m_pSaveBtn");
    horizontalLayout->addWidget(m_pSaveBtn);

    m_p1 = KUIFactory::createToolBtn(this, "m_p1");
    horizontalLayout->addWidget(m_p1);

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
