#include "kglobaldata.h"

#include <utility>

KGlobalData* KGlobalData::s_globalDataObj = NULL;

QString KGlobalData::getCanvasColor()
{
	return m_canvasColor;
}

KGlobalData::KGlobalData()
= default;

KGlobalData* KGlobalData::getGlobalDataIntance()
{
	if (s_globalDataObj == NULL)
		s_globalDataObj = new KGlobalData;
	return s_globalDataObj;
}

KGlobalData::~KGlobalData()
= default;

int KGlobalData::getCanvasWidth() const
{
	return m_canvasWidth;
}

int KGlobalData::getCanvasHeight() const
{
	return m_canvasHeight;
}

void KGlobalData::setCanvasWidth(int width)
{
	m_canvasWidth = width;
}

void KGlobalData::setCanvasHeight(int height)
{
	m_canvasHeight = height;
}

void KGlobalData::setCanvasColor(QString colorStr)
{
	m_canvasColor = std::move(colorStr);
}
