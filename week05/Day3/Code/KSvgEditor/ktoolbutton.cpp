#include "ktoolbutton.h"

KToolButton::KToolButton(QString iconName, KGlobalData::KDrawFlag flag, QWidget *parent)
	: QRadioButton(parent)
{
	m_iconName = std::move(iconName);
	m_svg = new QSvgRenderer(":/icons/normal/" + m_iconName, this);
	m_flag = flag;
	// 设置最小大小 32 * 32
	setMinimumSize(32, 32);
	(void)connect(this, SIGNAL(toggled(bool)), SLOT(onToggle()));
	setAttribute(Qt::WA_StyledBackground, true);
	setStyleSheet("background-color: rgb(47, 47, 47);");
}

KToolButton::~KToolButton()
= default;

void KToolButton::paintEvent(QPaintEvent * event)
{
	// 创建绘图对象
	QPainter painter(this);
	// 绘制svg图标
	m_svg->render(&painter, QRectF(0, 0, 32, 32));
}

void KToolButton::enterEvent(QEvent* event)
{
	if (isChecked() == false)
		m_svg->load(":/icons/hover/" + m_iconName);
	// 设置光标样式
	setCursor(Qt::PointingHandCursor);
	update();
}

void KToolButton::leaveEvent(QEvent* event)
{
	if (isChecked() == false)
		m_svg->load(":/icons/normal/" + m_iconName);
	// 设置光标样式
	setCursor(Qt::ArrowCursor);
	update();
}

void KToolButton::mouseReleaseEvent(QMouseEvent* event)
{
	// 设置当前按钮为选中状态
	setChecked(true);
	KGlobalData::getGlobalDataInstance()->setCurrentFlag(m_flag);
	switch (m_flag)
	{
	case KGlobalData::KDrawFlag::MouseFlag: 
		KGlobalData::getGlobalDataInstance()->setRemovable(true);
		break;
	case KGlobalData::KDrawFlag::NoneFlag:
	case KGlobalData::KDrawFlag::PenFlag:
	case KGlobalData::KDrawFlag::LineFlag:
	case KGlobalData::KDrawFlag::CircleFlag:
	case KGlobalData::KDrawFlag::RectFlag:
	case KGlobalData::KDrawFlag::PengatonFlag:
	case KGlobalData::KDrawFlag::HexagonFlag:
	case KGlobalData::KDrawFlag::StarFlag:
	case KGlobalData::KDrawFlag::TextFlag:
	case KGlobalData::KDrawFlag::ZoomFlag:
	default:
		KGlobalData::getGlobalDataInstance()->setRemovable(false);
		break;
	}
}

void KToolButton::onToggle()
{
	if (isChecked())
		m_svg->load(":/icons/selected/" + m_iconName);
	else
		m_svg->load(":/icons/normal/" + m_iconName);
	update();
}
