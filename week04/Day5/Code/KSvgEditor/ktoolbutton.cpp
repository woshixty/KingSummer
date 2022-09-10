#include "ktoolbutton.h"

KToolButton::KToolButton(QString iconName, KGlobalData::KDrawFlag flag, QWidget *parent)
	: QRadioButton(parent)
{
	m_iconName = std::move(iconName);
	m_svg = new QSvgRenderer(":/icons/normal/" + m_iconName, this);
	m_flag = flag;
	// ������С��С 32 * 32
	setMinimumSize(32, 32);
	(void)connect(this, SIGNAL(toggled(bool)), SLOT(onToggle()));
}

KToolButton::~KToolButton()
= default;

void KToolButton::paintEvent(QPaintEvent * event)
{
	// ������ͼ����
	QPainter painter(this);
	// ����svgͼ��
	m_svg->render(&painter, QRectF(0, 0, 32, 32));
}

void KToolButton::enterEvent(QEvent* event)
{
	if (isChecked() == false)
		m_svg->load(":/icons/hover/" + m_iconName);
	// ���ù����ʽ
	setCursor(Qt::PointingHandCursor);
	update();
}

void KToolButton::leaveEvent(QEvent* event)
{
	if (isChecked() == false)
		m_svg->load(":/icons/normal/" + m_iconName);
	// ���ù����ʽ
	setCursor(Qt::ArrowCursor);
	update();
}

void KToolButton::mouseReleaseEvent(QMouseEvent* event)
{
	// ���õ�ǰ��ťΪѡ��״̬
	setChecked(true);
	KGlobalData::getGlobalDataInstance()->setCurrentFlag(m_flag);
}

void KToolButton::onToggle()
{
	if (isChecked())
		m_svg->load(":/icons/selected/" + m_iconName);
	else
		m_svg->load(":/icons/normal/" + m_iconName);
	update();
}
