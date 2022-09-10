#include "kparambox.h"

KParamBox::KParamBox(QString title, QWidget* parent)
	: QWidget(parent)
{
	m_title = std::move(title);
	setMinimumSize(70, 70);
	setMaximumSize(70, 70);

	// 焦点 : 当前正在与用户交互的组件
	// 通过单击获取焦点事件
	setFocusPolicy(Qt::ClickFocus);
	// 自定义控件样式表生效
	setAttribute(Qt::WA_StyledBackground, true);
	setStyleSheet("background-color:#3f3f3c");

	m_pVLayout = new QVBoxLayout(this);
	// 设置外边距
	m_pVLayout->setMargin(0);
	m_pTitleLabel = new QLabel(this);
	// 设置最大高度
	m_pTitleLabel->setMaximumHeight(20);
	// 设置对齐
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
	// 设置鼠标样式
	setCursor(Qt::PointingHandCursor);
}

void KParamBox::leaveEvent(QEvent* event)
{
	QWidget::leaveEvent(event);
	// 设置鼠标样式
	setCursor(Qt::ArrowCursor);
}
