#include "kglobaldata.h"

#include <utility>

KGlobalData* KGlobalData::s_globalDataObj = nullptr;

QString KGlobalData::getCanvasColor()
{
	return m_canvasColor;
}

KGlobalData::KGlobalData()
= default;

KGlobalData* KGlobalData::getGlobalDataInstance()
{
	if (s_globalDataObj == nullptr)
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

void KGlobalData::setCurrentFlag(KDrawFlag flag)
{
	m_currentFlag = flag;
}
