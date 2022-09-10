#include "ktoolbar.h"

KToolBar::KToolBar(QWidget* parent)
	: QWidget(parent)
{
	setMaximumWidth(50);
	setMinimumWidth(50);
	setAttribute(Qt::WA_StyledBackground, true);
	setStyleSheet("background-color: rgb(47, 47, 47);");
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
	m_pMouseBtn = new KToolButton("mouse.svg", KGlobalData::KDrawFlag::MouseFlag, this);
	m_pPenBtn = new KToolButton("pen.svg", KGlobalData::KDrawFlag::PenFlag, this);
	m_pLineBtn = new KToolButton("line.svg", KGlobalData::KDrawFlag::LineFlag, this);
	m_pCircleBtn = new KToolButton("circle.svg", KGlobalData::KDrawFlag::CircleFlag, this);
	m_pRectBtn = new KToolButton("rect.svg", KGlobalData::KDrawFlag::RectFlag, this);
	m_pPentBtn = new KToolButton("pent.svg", KGlobalData::KDrawFlag::PengatonFlag, this);
	m_pHexaBtn = new KToolButton("hexa.svg", KGlobalData::KDrawFlag::HexagonFlag, this);
	m_pStarBtn = new KToolButton("star.svg", KGlobalData::KDrawFlag::StarFlag, this);
	m_pTextBtn = new KToolButton("text.svg", KGlobalData::KDrawFlag::TextFlag, this);
	m_pZoomBtn = new KToolButton("zoom.svg", KGlobalData::KDrawFlag::ZoomFlag, this);

	// 将按钮添加到按钮组
	m_pBtnGroup->addButton(m_pMouseBtn);
	m_pBtnGroup->addButton(m_pPenBtn);
	m_pBtnGroup->addButton(m_pLineBtn);
	m_pBtnGroup->addButton(m_pCircleBtn);
	m_pBtnGroup->addButton(m_pRectBtn);
	m_pBtnGroup->addButton(m_pPentBtn);
	m_pBtnGroup->addButton(m_pHexaBtn);
	m_pBtnGroup->addButton(m_pStarBtn);
	m_pBtnGroup->addButton(m_pTextBtn);
	m_pBtnGroup->addButton(m_pZoomBtn);

	// 添加布局
	m_pVLayout->addWidget(m_pMouseBtn);
	m_pVLayout->addWidget(m_pPenBtn);
	m_pVLayout->addWidget(m_pLineBtn);
	m_pVLayout->addWidget(m_pCircleBtn);
	m_pVLayout->addWidget(m_pRectBtn);
	m_pVLayout->addWidget(m_pPentBtn);
	m_pVLayout->addWidget(m_pHexaBtn);
	m_pVLayout->addWidget(m_pStarBtn);
	m_pVLayout->addWidget(m_pTextBtn);
	m_pVLayout->addWidget(m_pZoomBtn);

	// 添加布局器
	setLayout(m_pVLayout);

	m_pMouseBtn->click();
}

KToolBar::~KToolBar()
= default;
