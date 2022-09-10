#include "kstatuspage.h"
#include "kuifactory.h"

KStatusPage::KStatusPage(QWidget *parent)
	: QComboBox(parent)
{
    initPage();
	// 创建一个定时器
    m_timer = new QTimer(this);
    initValue();
	// 手动连接槽函数
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    setStyleSheet(QString("font-family: \"Microsoft YaHei\";"));
}

KStatusPage::~KStatusPage()
= default;

void KStatusPage::initPage()
{
    setObjectName(QStringLiteral("m_pStatusPage"));
    setMinimumSize(QSize(400, 200));
    gridLayout_2 = new QGridLayout(this);
    gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
    gridLayout = new QGridLayout();
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    m_totalChangeLabel = KUIFactory::createStatusLabel(this, QStringLiteral("m_totalChangeLabel"));
    gridLayout->addWidget(m_totalChangeLabel, 1, 1, 1, 1);

    m_totalChangeValue = KUIFactory::createValueLabel(this, QStringLiteral("m_totalChangeValue"));
    gridLayout->addWidget(m_totalChangeValue, 1, 2, 1, 1);

    m_dirChangeIcon = KUIFactory::createIconLabel(this, QStringLiteral("m_dirChangeIcon"), ":/statuspage/icons/dir2.svg");
    gridLayout->addWidget(m_dirChangeIcon, 2, 0, 1, 1);

    m_dirChangeLabel = KUIFactory::createStatusLabel(this, QStringLiteral("m_dirChangeLabel"));

    gridLayout->addWidget(m_dirChangeLabel, 2, 1, 1, 1);

    m_dirChangeValue = KUIFactory::createValueLabel(this, QStringLiteral("m_dirChangeValue"));
    gridLayout->addWidget(m_dirChangeValue, 2, 2, 1, 1);

    m_totalChangeIcon = KUIFactory::createIconLabel(this, QStringLiteral("m_totalChangeIcon"), ":/statuspage/icons/number.svg");
    gridLayout->addWidget(m_totalChangeIcon, 1, 0, 1, 1);

    m_processRateLabel = KUIFactory::createStatusLabel(this, QStringLiteral("m_processRateLabel"));
    gridLayout->addWidget(m_processRateLabel, 4, 1, 1, 1);

    m_processTimeValue = KUIFactory::createValueLabel(this, QStringLiteral("m_processTimeValue"));
    gridLayout->addWidget(m_processTimeValue, 5, 2, 1, 1);

    m_processRateIcon = KUIFactory::createIconLabel(this, QStringLiteral("m_processRateIcon"), ":/statuspage/icons/rate.svg");
    gridLayout->addWidget(m_processRateIcon, 4, 0, 1, 1);

    m_fileChangeValue = KUIFactory::createValueLabel(this, QStringLiteral("m_fileChangeValue"));
    gridLayout->addWidget(m_fileChangeValue, 3, 2, 1, 1);

    m_fileChangeIcon = KUIFactory::createIconLabel(this, QStringLiteral("m_fileChangeIcon"), ":/statuspage/icons/file.svg");
    gridLayout->addWidget(m_fileChangeIcon, 3, 0, 1, 1);

    m_fileChangeLabel = KUIFactory::createStatusLabel(this, QStringLiteral("m_fileChangeLabel"));
    gridLayout->addWidget(m_fileChangeLabel, 3, 1, 1, 1);

    m_processTimeLabel = KUIFactory::createStatusLabel(this, QStringLiteral("m_processTimeLabel"));
    gridLayout->addWidget(m_processTimeLabel, 5, 1, 1, 1);

    m_processRateValue = KUIFactory::createValueLabel(this, QStringLiteral("m_processRateValue"));
    gridLayout->addWidget(m_processRateValue, 4, 2, 1, 1);

    m_processTimeIcon = KUIFactory::createIconLabel(this, QStringLiteral("m_processTimeIcon"), ":/statuspage/icons/time.svg");
    gridLayout->addWidget(m_processTimeIcon, 5, 0, 1, 1);

    m_value = new QLabel(this);
    m_value->setObjectName(QStringLiteral("m_value"));
    m_value->setMinimumSize(QSize(80, 30));
    gridLayout->addWidget(m_value, 0, 2, 1, 1);

    m_key = new QLabel(this);
    m_key->setObjectName(QStringLiteral("m_key"));
    m_key->setMinimumSize(QSize(80, 30));

    gridLayout->addWidget(m_key, 0, 1, 1, 1);
    gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

    retranslateUi();
}

void KStatusPage::initValue()
{
    // 设置初始值
    m_time.setHMS(0, 0, 0, 0);
    m_processTimeValue->setText(m_time.toString("\tmm:ss SEC"));
}

void KStatusPage::retranslateUi()
{
    setWindowTitle(QApplication::translate("KStatusPage", "Form", Q_NULLPTR));
    m_totalChangeLabel->setText(QApplication::translate("KStatusPage", "\346\200\273\346\224\271\345\217\230\351\207\217", Q_NULLPTR));
    m_totalChangeValue->setText(QString("\t0"));
    m_dirChangeIcon->setText(QString());
    m_dirChangeLabel->setText(QApplication::translate("KStatusPage", "\346\226\207\344\273\266\345\244\271\346\224\271\345\217\230\351\207\217", Q_NULLPTR));
    m_dirChangeValue->setText(QString("\t0"));
    m_totalChangeIcon->setText(QString());
    m_processRateLabel->setText(QApplication::translate("KStatusPage", "\345\244\204\347\220\206\351\200\237\347\216\207", Q_NULLPTR));
    m_processTimeValue->setText(QString("\t0.00 SEC"));
    m_processRateIcon->setText(QString());
    m_fileChangeValue->setText(QString("\t0"));
    m_fileChangeIcon->setText(QString());
    m_fileChangeLabel->setText(QApplication::translate("KStatusPage", "\346\226\207\344\273\266\346\224\271\345\217\230\351\207\217", Q_NULLPTR));
    m_processTimeLabel->setText(QApplication::translate("KStatusPage", "\345\244\204\347\220\206\346\227\266\351\227\264", Q_NULLPTR));
    m_processRateValue->setText(QString("\t0 CH/MIN"));
    m_processTimeIcon->setText(QString());
    m_value->setText(QApplication::translate("KStatusPage", "\t\345\200\274", Q_NULLPTR));
    m_key->setText(QApplication::translate("KStatusPage", "\345\217\230\351\207\217", Q_NULLPTR));
}

void KStatusPage::update()
{
    static quint32 time_out = 0;
    time_out++;
    m_time = m_time.addMSecs(1);
    m_processTimeValue->setText(m_time.toString("\tmm:ss SEC"));
}
