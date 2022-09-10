#include "kcanvasparamsbar.h"

#include <utility>

KCanvasParamsBar::KCanvasParamsBar(QWidget* parent)
	: KParamsBar(QStringLiteral("参数设置"), parent)
{
	m_pWidthBox = new KValueBox(QStringLiteral("宽度"), KGlobalData::getGlobalDataIntance()->getCanvasWidth(), this);
	m_pHeightBox = new KValueBox(QStringLiteral("高度"), KGlobalData::getGlobalDataIntance()->getCanvasHeight(), this);
	m_pColorBox = new KColorBox(QStringLiteral("颜色"), KGlobalData::getGlobalDataIntance()->getCanvasColor(), this);

	// 添加到网格布局
	// 第 0 行 第 0 列
	m_pGridLayout->addWidget(m_pWidthBox, 0, 0);
	// 第 0 行 第 1 列
	m_pGridLayout->addWidget(m_pHeightBox, 0, 1);
	m_pGridLayout->addWidget(m_pColorBox, 1, 0);
}

KCanvasParamsBar::~KCanvasParamsBar()
= default;
