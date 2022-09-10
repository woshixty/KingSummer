#include "KParamBar.h"

#include <utility>

KParamBar::KParamBar(QWidget* parent)
	: KParamBaseBar(QStringLiteral("Params"), parent)
{
	m_pData = KGlobalData::getGlobalDataInstance();
	m_boxes.append(
		new KValueBox(QStringLiteral("canvas-width"), m_pData->canvasWidth(), 
			KGlobalData::KParamFlag::CanvasWidth, this)
	);
	m_boxes.append(
		new KValueBox(QStringLiteral("canvas-height"), m_pData->canvasHeight(), 
		KGlobalData::KParamFlag::CanvasHeight, this)
	);
	m_boxes.append(
		new KValueBox(QStringLiteral("canvas-scaling"), m_pData->getCanvasScaling(),
			KGlobalData::KParamFlag::CanvasScaling, this)
	);
	m_boxes.append(
		new KColorBox(QStringLiteral("canvas-color"), m_pData->getCanvasColor(), 
			KGlobalData::KParamFlag::CanvasColor, this)
	);
	m_boxes.append(
		new KValueBox(QStringLiteral("border-width"), m_pData->getBorderWidth(), 
			KGlobalData::KParamFlag::BorderWidth, this)
	);
	m_boxes.append(
		new KChooseBox(QStringLiteral("border-style"), 
			KGlobalData::KParamFlag::BorderStyle, this)
	);
	m_boxes.append(
		new KColorBox(QStringLiteral("border-color"), m_pData->getBorderColor(),
			KGlobalData::KParamFlag::BorderColor, this)
	);
	m_boxes.append(
		new KColorBox(QStringLiteral("fill-clolor"), m_pData->getFillColor(), 
			KGlobalData::KParamFlag::FillColor, this)
	);

	int i = 0;
	for (const auto m_box : m_boxes)
	{
		m_pGridLayout->addWidget(m_box, i / 2, i % 2);
		i++;
	}
}

KParamBar::~KParamBar()
= default;

KParamBaseBox* KParamBar::getBox(KGlobalData::KParamFlag flag) const
{
	return m_boxes.at(static_cast<int>(flag));
}

QList<KParamBaseBox*> KParamBar::getParamBoxes()
{
	return m_boxes;
}
