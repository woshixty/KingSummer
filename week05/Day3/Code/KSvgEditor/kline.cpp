#include "kline.h"

KLine::KLine(QPointF startP, QPointF endP, QGraphicsItem* parent)
	: KShapeBase(KGlobalData::KShapeType::StraightLine), QGraphicsPathItem(parent)
{
	KLine::setNewRect(startP, endP);
}

KLine::~KLine()
= default;

void KLine::setNewRect(QPointF startP, QPointF endP)
{
	m_points.clear();
	m_points.append(startP);
	m_points.append(endP);
	QPainterPath path;
	path.addPolygon(m_points);
	setPath(path);
}

void KLine::setFlags(GraphicsItemFlags flags)
{
	QGraphicsItem::setFlags(flags);
}

void KLine::setPen(QPen pen)
{
	QGraphicsPathItem::setPen(pen);
}

void KLine::setBrush(QBrush brush)
{
	QGraphicsPathItem::setBrush(brush);
}

QPen KLine::getPen()
{
	return pen();
}
