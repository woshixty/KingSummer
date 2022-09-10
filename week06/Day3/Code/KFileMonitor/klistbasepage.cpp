#include "klistbasepage.h"

#include <QApplication>

#include "kuifactory.h"

KListBasePage::KListBasePage(QWidget *parent)
	: QComboBox(parent)
{
    initPage();
}

KListBasePage::~KListBasePage()
= default;

void KListBasePage::initPage()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("this"));
    // 垂直布局
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(0);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    // 存储上方标签和按钮Widget
	m_topBar = new QWidget(this);
    m_topBar->setObjectName(QStringLiteral("m_topBar"));
    // 水平布局：标签和按钮
	horizontalLayout = new QHBoxLayout(m_topBar);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    // 创建标签添加到水平布局
	m_label = new QLabel(m_topBar);
    m_label->setObjectName(QStringLiteral("m_label"));
    horizontalLayout->addWidget(m_label);
    // 创建分割器添加到水平布局
    m_spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout->addItem(m_spacer);
    // 将按钮添加到水平布局
    m_addBtn = KUIFactory::createAddOrBtn(m_topBar, QStringLiteral("m_addBtn"), ":/icons/add.svg");
	m_deleteBtn = KUIFactory::createAddOrBtn(m_topBar, QStringLiteral("m_deleteBtn"), ":/icons/delete.svg");
    horizontalLayout->addWidget(m_deleteBtn);
    horizontalLayout->addWidget(m_addBtn);
    // 将水平布局添加到上方页面
    verticalLayout->addWidget(m_topBar);
    // 创建列表项
    m_profileList = new QListWidget(this);
    m_profileList->setObjectName(QStringLiteral("m_profileList"));
    verticalLayout->addWidget(m_profileList);
    // 设置当前Widget的stylesheet会导致该页面下的所有控件都设置为该style
    m_label->setStyleSheet(QString("border: none; font-family: \"Microsoft YaHei\";"));
}

void KListBasePage::setUiName(const QString& labelName)
{
    setWindowTitle(QApplication::translate("ProPage", "Form", Q_NULLPTR));
    m_label->setText(labelName);
}
