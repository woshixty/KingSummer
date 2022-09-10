#include "kglobaldata.h"

#include <utility>

KGlobalData* KGlobalData::s_globalDataObj = nullptr;

KGlobalData::KGlobalData(QObject* parent) : QObject(parent)
{
}

KGlobalData* KGlobalData::getGlobalDataInstance(QObject* parent)
{
	if (s_globalDataObj == nullptr)
		s_globalDataObj = new KGlobalData(parent);
	return s_globalDataObj;
}

void KGlobalData::setPen(QPen& pen) const
{
	pen.setColor(m_borderColor.toUInt(nullptr, 16));
	pen.setWidth(m_borderWidth);
	switch (m_lineFlag)
	{
	case KLineFlag::NoneFlag:
		pen.setStyle(Qt::SolidLine);
		break;
	case KLineFlag::SolidFlag:
		pen.setStyle(Qt::SolidLine);
		break;
	case KLineFlag::DottedFlag:
		pen.setStyle(Qt::DotLine);
		break;
	default:
		pen.setStyle(Qt::SolidLine);
	}
}

int KGlobalData::canvasWidth() const
{
	return m_canvasWidth;
}

int KGlobalData::canvasHeight() const
{
	return m_canvasHeight;
}

int KGlobalData::getCanvasScaling() const
{
	return m_canvasScaling;
}

int KGlobalData::getBorderWidth() const
{
	return m_borderWidth;
}

KGlobalData::KLineFlag KGlobalData::getBorderStyle() const
{
	return m_lineFlag;
}

QString KGlobalData::getCanvasColor() const
{
	return m_canvasColor;
}

QString KGlobalData::getBorderColor() const
{
	return m_borderColor;
}

QString KGlobalData::getFillColor() const
{
	return m_fillColor;
}

KGlobalData::KDrawFlag KGlobalData::getDrawFlag() const
{
	return m_drawFlag;
}

void KGlobalData::setCanvasWidth(int width)
{
	m_canvasWidth = width;
}

void KGlobalData::setCanvasHeight(int height)
{
	m_canvasHeight = height;
}

void KGlobalData::setCanvasScaling(int scaling)
{
	m_canvasScaling = scaling;
}

void KGlobalData::setBorderWidth(int width)
{
	m_borderWidth = width;
}

void KGlobalData::setBorderStyle(KLineFlag flag)
{
	m_lineFlag = flag;
}

void KGlobalData::setBorderColor(QString colorStr)
{
	m_borderColor = std::move(colorStr);
}


void KGlobalData::setCanvasColor(QString colorStr)
{
	m_canvasColor = std::move(colorStr);
}

void KGlobalData::setFillColor(QString colorStr)
{
	m_fillColor = std::move(colorStr);
}

void KGlobalData::setCurrentFlag(KDrawFlag flag)
{
	m_drawFlag = flag;
}

void KGlobalData::setMouseCursorShape(Qt::CursorShape shape)
{
	m_mouseCursorShape = shape;
}
