#include "kcanvasparamsbar.h"

#include <utility>

KCanvasParamsBar::KCanvasParamsBar(QWidget* parent)
	: KParamsBar(QStringLiteral("Params"), parent)
{
	m_pWidthBox = new KValueBox(QStringLiteral("width"), KGlobalData::getGlobalDataInstance()->getCanvasWidth(), this);

	m_pHeightBox = new KValueBox(QStringLiteral("height"), KGlobalData::getGlobalDataInstance()->getCanvasHeight(), this);
	m_pColorBox = new KColorBox(QStringLiteral("color"), KGlobalData::getGlobalDataInstance()->getCanvasColor(), this);

	// 添加到网格布局
	// 第 0 行 第 0 列
	m_pGridLayout->addWidget(m_pWidthBox, 0, 0);
	// 第 0 行 第 1 列
	m_pGridLayout->addWidget(m_pHeightBox, 0, 1);
	m_pGridLayout->addWidget(m_pColorBox, 1, 0);
}

KCanvasParamsBar::~KCanvasParamsBar()
= default;
