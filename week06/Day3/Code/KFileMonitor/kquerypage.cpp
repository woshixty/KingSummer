#include "kquerypage.h"

KQueryPage::KQueryPage(QWidget *parent)
	: QWidget(parent)
{
    initPage();
    initValue();
    // 修改开始时间
    connect(
        m_startDateTimeEdit, SIGNAL(dateTimeChanged(const QDateTime&)),
        this, SLOT(startDateTimeChanged(const QDateTime&))
    );
    // 修改结束时间
    connect(
        m_endDateTimeEdit, SIGNAL(dateTimeChanged(const QDateTime&)),
        this, SLOT(endDateTimeChanged(const QDateTime&))
    );
    // 修改文件名
    connect(
        m_fileNameLineEdit, SIGNAL(editingFinished()),
        this, SLOT(fileNameChanged())
    );
    // 修改属主名
    connect(
        m_ownerLineEdit, SIGNAL(editingFinished()),
        this, SLOT(ownerChanged())
    );
}

KQueryPage::~KQueryPage()
= default;

void KQueryPage::initPage()
{
    setObjectName(QStringLiteral("m_pQueryPage"));
    setMinimumSize(QSize(600, 200));
    gridLayout_2 = new QGridLayout(this);
    gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
    gridLayout = new QGridLayout();
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    m_sortVerticalLayout = new QVBoxLayout();
    m_sortVerticalLayout->setObjectName(QStringLiteral("m_sortVerticalLayout"));
    m_sortLabel = new QLabel(this);
    m_sortLabel->setObjectName(QStringLiteral("m_sortLabel"));
    m_sortLabel->setAlignment(Qt::AlignCenter);

    m_sortVerticalLayout->addWidget(m_sortLabel);

    m_sortHorizontalLayout = new QHBoxLayout();
    m_sortHorizontalLayout->setObjectName(QStringLiteral("m_sortHorizontalLayout"));
    m_sortContent = new QComboBox(this);
    m_sortContent->setObjectName(QStringLiteral("m_sortContent"));
    m_sortHorizontalLayout->addWidget(m_sortContent);

    m_sortType = new QComboBox(this);
    m_sortType->setObjectName(QStringLiteral("m_sortType"));
    m_sortHorizontalLayout->addWidget(m_sortType);
    m_sortVerticalLayout->addLayout(m_sortHorizontalLayout);
    gridLayout->addLayout(m_sortVerticalLayout, 0, 0, 1, 1);

    m_operationVerticalLayout = new QVBoxLayout();
    m_operationVerticalLayout->setObjectName(QStringLiteral("m_operationVerticalLayout"));

    m_operationLabel = new QLabel(this);
    m_operationLabel->setObjectName(QStringLiteral("m_operationLabel"));
    m_operationLabel->setAlignment(Qt::AlignCenter);
    m_operationVerticalLayout->addWidget(m_operationLabel);

    m_operationHorizontalLayout = new QHBoxLayout();
    m_operationHorizontalLayout->setObjectName(QStringLiteral("m_operationHorizontalLayout"));
    m_operationType = new QComboBox(this);
    m_operationType->setObjectName(QStringLiteral("m_operationType"));

    m_operationHorizontalLayout->addWidget(m_operationType);


    m_operationVerticalLayout->addLayout(m_operationHorizontalLayout);


    gridLayout->addLayout(m_operationVerticalLayout, 0, 1, 1, 1);

    m_startVerticalLayout = new QVBoxLayout();
    m_startVerticalLayout->setObjectName(QStringLiteral("m_startVerticalLayout"));
    m_startLabel = new QLabel(this);
    m_startLabel->setObjectName(QStringLiteral("m_startLabel"));
    m_startLabel->setAlignment(Qt::AlignCenter);

    m_startVerticalLayout->addWidget(m_startLabel);

    m_startDateTimeEdit = new QDateTimeEdit(this);
    m_startDateTimeEdit->setObjectName(QStringLiteral("m_startDateTimeEdit"));
    m_startVerticalLayout->addWidget(m_startDateTimeEdit);
    gridLayout->addLayout(m_startVerticalLayout, 1, 0, 1, 1);

    m_endVerticalLayout = new QVBoxLayout();
    m_endVerticalLayout->setObjectName(QStringLiteral("m_endVerticalLayout"));
    m_endLabel = new QLabel(this);
    m_endLabel->setObjectName(QStringLiteral("m_endLabel"));
    m_endLabel->setAlignment(Qt::AlignCenter);
    m_endVerticalLayout->addWidget(m_endLabel);
    
    m_endDateTimeEdit = new QDateTimeEdit(this);
    m_endDateTimeEdit->setObjectName(QStringLiteral("m_endDateTimeEdit"));
    m_endVerticalLayout->addWidget(m_endDateTimeEdit);
    gridLayout->addLayout(m_endVerticalLayout, 1, 1, 1, 1);

    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    m_fileNameHorizontalLayout = new QHBoxLayout();
    m_fileNameHorizontalLayout->setObjectName(QStringLiteral("m_fileNameHorizontalLayout"));

    m_fileNameLabel = new QLabel(this);
    m_fileNameLabel->setObjectName(QStringLiteral("m_fileNameLabel"));
    m_fileNameHorizontalLayout->addWidget(m_fileNameLabel);

    m_fileNameLineEdit = new QLineEdit(this);
    m_fileNameLineEdit->setObjectName(QStringLiteral("m_fileNameLineEdit"));
    m_fileNameHorizontalLayout->addWidget(m_fileNameLineEdit);

    horizontalLayout->addLayout(m_fileNameHorizontalLayout);

    m_ownerHorizontalLayout = new QHBoxLayout();
    m_ownerHorizontalLayout->setObjectName(QStringLiteral("m_ownerHorizontalLayout"));

    m_fuzzyLabel = new QLabel(this);
    m_fuzzyLabel->setObjectName(QStringLiteral("m_fuzzyLabel"));
    m_fuzzyLabel->setAlignment(Qt::AlignCenter);
    m_fuzzyLabel->setMinimumHeight(25);
    verticalLayout->addWidget(m_fuzzyLabel);

    m_ownerLabel = new QLabel(this);
    m_ownerLabel->setObjectName(QStringLiteral("m_ownerLabel"));
    m_ownerHorizontalLayout->addWidget(m_ownerLabel);

    m_ownerLineEdit = new QLineEdit(this);
    m_ownerLineEdit->setObjectName(QStringLiteral("m_ownerLineEdit"));
    m_ownerHorizontalLayout->addWidget(m_ownerLineEdit);
    horizontalLayout->addLayout(m_ownerHorizontalLayout);
    verticalLayout->addLayout(horizontalLayout);

    m_queryBtn = new QPushButton(this);
    m_queryBtn->setObjectName(QStringLiteral("m_queryBtn"));
    m_queryBtn->setMaximumWidth(100);
    verticalLayout->addWidget(m_queryBtn);

    gridLayout->addLayout(verticalLayout, 2, 0, 1, 2);
    gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

    retranslateUi();
}

void KQueryPage::initValue() const
{
    m_startDateTimeEdit->setDateTime(QDateTime::currentDateTime());
    m_endDateTimeEdit->setDateTime(QDateTime::currentDateTime().addDays(1));
}

void KQueryPage::retranslateUi()
{
    setWindowTitle(QApplication::translate("KQueryPage", "Form", Q_NULLPTR));
    m_sortLabel->setText(QApplication::translate("KQueryPage", "\346\216\222\345\272\217", Q_NULLPTR));
    m_sortContent->clear();
    m_sortContent->insertItems(0, QStringList()
        << QApplication::translate("KQueryPage", "\346\223\215\344\275\234\346\227\245\346\234\237", Q_NULLPTR)
        << QApplication::translate("KQueryPage", "\346\223\215\344\275\234\346\227\266\351\227\264", Q_NULLPTR)
        << QApplication::translate("KQueryPage", "\346\226\207\344\273\266\345\244\247\345\260\217", Q_NULLPTR)
        << QApplication::translate("KQueryPage", "\346\226\207\344\273\266\345\261\236\344\270\273", Q_NULLPTR)
        << QApplication::translate("KQueryPage", "\346\226\207\344\273\266\345\220\215\347\247\260", Q_NULLPTR)
    );
    m_sortType->clear();
    m_sortType->insertItems(0, QStringList()
        << QApplication::translate("KQueryPage", "\345\215\207\345\272\217", Q_NULLPTR)
        << QApplication::translate("KQueryPage", "\351\231\215\345\272\217", Q_NULLPTR)
    );
    m_operationLabel->setText(QApplication::translate("KQueryPage", "\346\223\215\344\275\234\347\261\273\345\236\213", Q_NULLPTR));
    m_operationType->clear();
    m_operationType->insertItems(0, QStringList()
        << QApplication::translate("KQueryPage", "\345\205\250\351\203\250", Q_NULLPTR)
        << QApplication::translate("KQueryPage", "\346\267\273\345\212\240", Q_NULLPTR)
        << QApplication::translate("KQueryPage", "\345\210\240\351\231\244", Q_NULLPTR)
        << QApplication::translate("KQueryPage", "\344\277\256\346\224\271", Q_NULLPTR)
        << QApplication::translate("KQueryPage", "\351\207\215\345\221\275\345\220\215", Q_NULLPTR)
    );
    m_startLabel->setText(QApplication::translate("KQueryPage", "\345\274\200\345\247\213\346\227\245\346\234\237\346\227\266\351\227\264", Q_NULLPTR));
    m_endLabel->setText(QApplication::translate("KQueryPage", "\347\273\223\346\235\237\346\227\245\346\234\237\346\227\266\351\227\264", Q_NULLPTR));
    m_fuzzyLabel->setText(QApplication::translate("KQueryPage", "\346\250\241\347\263\212\346\237\245\346\211\276", Q_NULLPTR));
	m_fileNameLabel->setText(QApplication::translate("KQueryPage", "\346\226\207\344\273\266\345\220\215", Q_NULLPTR));
    m_ownerLabel->setText(QApplication::translate("KQueryPage", "\345\261\236\344\270\273\345\220\215", Q_NULLPTR));
    m_queryBtn->setText(QApplication::translate("KQueryPage", "\346\237\245\350\257\242", Q_NULLPTR));
}

void KQueryPage::startDateTimeChanged(const QDateTime& datetime) const
{
    m_pGlobalData->setStartDateTime(datetime);
}

void KQueryPage::endDateTimeChanged(const QDateTime& datetime) const
{
    m_pGlobalData->setEndDateTime(datetime);
}

void KQueryPage::fileNameChanged() const
{
    m_pGlobalData->setFileName(m_fileNameLineEdit->text());
}

void KQueryPage::ownerChanged() const
{
    m_pGlobalData->setOwner(m_ownerLineEdit->text());
}
