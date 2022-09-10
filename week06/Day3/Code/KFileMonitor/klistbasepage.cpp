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
    // ��ֱ����
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(0);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    // �洢�Ϸ���ǩ�Ͱ�ťWidget
	m_topBar = new QWidget(this);
    m_topBar->setObjectName(QStringLiteral("m_topBar"));
    // ˮƽ���֣���ǩ�Ͱ�ť
	horizontalLayout = new QHBoxLayout(m_topBar);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    // ������ǩ��ӵ�ˮƽ����
	m_label = new QLabel(m_topBar);
    m_label->setObjectName(QStringLiteral("m_label"));
    horizontalLayout->addWidget(m_label);
    // �����ָ�����ӵ�ˮƽ����
    m_spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout->addItem(m_spacer);
    // ����ť��ӵ�ˮƽ����
    m_addBtn = KUIFactory::createAddOrBtn(m_topBar, QStringLiteral("m_addBtn"), ":/icons/add.svg");
	m_deleteBtn = KUIFactory::createAddOrBtn(m_topBar, QStringLiteral("m_deleteBtn"), ":/icons/delete.svg");
    horizontalLayout->addWidget(m_deleteBtn);
    horizontalLayout->addWidget(m_addBtn);
    // ��ˮƽ������ӵ��Ϸ�ҳ��
    verticalLayout->addWidget(m_topBar);
    // �����б���
    m_profileList = new QListWidget(this);
    m_profileList->setObjectName(QStringLiteral("m_profileList"));
    verticalLayout->addWidget(m_profileList);
    // ���õ�ǰWidget��stylesheet�ᵼ�¸�ҳ���µ����пؼ�������Ϊ��style
    m_label->setStyleSheet(QString("border: none; font-family: \"Microsoft YaHei\";"));
}

void KListBasePage::setUiName(const QString& labelName)
{
    setWindowTitle(QApplication::translate("ProPage", "Form", Q_NULLPTR));
    m_label->setText(labelName);
}
