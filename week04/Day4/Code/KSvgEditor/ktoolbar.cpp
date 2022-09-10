#include "ktoolbar.h"

KToolBar::KToolBar(QWidget* parent)
	: QWidget(parent)
{
	setMaximumWidth(50);
	setMinimumWidth(32);
	setAttribute(Qt::WA_StyledBackground, true);
	setStyleSheet("background-color: black;");
	// 垂直布局
	m_pVLayout = new QVBoxLayout(this);
	// 对齐方式
	m_pVLayout->setAlignment(Qt::AlignCenter | Qt::AlignTop);
	// 设置组件间距
	m_pVLayout->setSpacing(25);

	m_pBtnGroup = new QButtonGroup(this);
	// 设置互斥
	m_pBtnGroup->setExclusive(true);

	// 创建自定义按钮
	m_pMouseBtn = new KToolButton("mouse.svg", this);
	m_pPenBtn = new KToolButton("pen.svg", this);
	m_pLineBtn = new KToolButton("line.svg", this);
	m_pRectBtn = new KToolButton("rect.svg", this);
	m_pCircleBtn = new KToolButton("circle.svg", this);
	m_pTextBtn = new KToolButton("text.svg", this);

	// 将按钮添加到按钮组
	m_pBtnGroup->addButton(m_pMouseBtn);
	m_pBtnGroup->addButton(m_pPenBtn);
	m_pBtnGroup->addButton(m_pLineBtn);
	m_pBtnGroup->addButton(m_pRectBtn);
	m_pBtnGroup->addButton(m_pCircleBtn);
	m_pBtnGroup->addButton(m_pTextBtn);

	// 添加布局
	m_pVLayout->addWidget(m_pMouseBtn);
	m_pVLayout->addWidget(m_pPenBtn);
	m_pVLayout->addWidget(m_pLineBtn);
	m_pVLayout->addWidget(m_pRectBtn);
	m_pVLayout->addWidget(m_pCircleBtn);
	m_pVLayout->addWidget(m_pTextBtn);

	// 添加布局器
	setLayout(m_pVLayout);
}

KToolBar::~KToolBar()
= default;
