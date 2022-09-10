#include "khexagon.h"

KHexagon::KHexagon(QPointF startP, QPointF endP, QGraphicsItem*parent)
	: KShapeBase(startP, endP, KGlobalData::KShapeType::Hexagon), QGraphicsPolygonItem(parent)
{
	KHexagon::setNewRect(startP, endP);
}

KHexagon::~KHexagon()
= default;

void KHexagon::setNewRect(QPointF startP, QPointF endP)
{
	m_startPoint = startP;
	m_endPoint = endP;
	calculateHexagonPoints(m_points, QRectF(startP, endP));
	setPolygon(m_points);
}

void KHexagon::setFlags(GraphicsItemFlags flags)
{
	QGraphicsItem::setFlags(flags);
}

void KHexagon::setPen(QPen pen)
{
	QGraphicsPolygonItem::setPen(pen);
}

void KHexagon::setBrush(QBrush brush)
{
	QGraphicsPolygonItem::setBrush(brush);
}
