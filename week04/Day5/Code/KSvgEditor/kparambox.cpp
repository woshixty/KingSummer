#include "kparambox.h"

KParamBox::KParamBox(QString title, QWidget* parent)
	: QWidget(parent)
{
	m_title = std::move(title);
	setMinimumSize(70, 70);
	setMaximumSize(70, 70);

	// ���� : ��ǰ�������û����������
	// ͨ��������ȡ�����¼�
	setFocusPolicy(Qt::ClickFocus);
	// �Զ���ؼ���ʽ����Ч
	setAttribute(Qt::WA_StyledBackground, true);
	setStyleSheet("background-color:#3f3f3c");

	m_pVLayout = new QVBoxLayout(this);
	// ������߾�
	m_pVLayout->setMargin(0);
	m_pTitleLabel = new QLabel(this);
	// �������߶�
	m_pTitleLabel->setMaximumHeight(20);
	// ���ö���
	m_pTitleLabel->setAlignment(Qt::AlignCenter);
	m_pTitleLabel->setStyleSheet("background-color:#3f3f3c; font-size:13px; color:#cccccc; font-family: Microsoft YaHei; padding: 0px 5px;");
	m_pTitleLabel->setText(m_title);

	m_pVLayout->addWidget(m_pTitleLabel);
}

KParamBox::~KParamBox()
= default;

void KParamBox::enterEvent(QEvent* event)
{
	QWidget::enterEvent(event);
	// ���������ʽ
	setCursor(Qt::PointingHandCursor);
}

void KParamBox::leaveEvent(QEvent* event)
{
	QWidget::leaveEvent(event);
	// ���������ʽ
	setCursor(Qt::ArrowCursor);
}
