#include "kpengaton.h"

KPengaton::KPengaton(QPointF startP, QPointF endP, QGraphicsItem* parent)
	: KShapeBase(startP, endP, KGlobalData::KShapeType::Pentagon), QGraphicsPolygonItem(parent)
{
	KPengaton::setNewRect(startP, endP);
}

KPengaton::~KPengaton()
= default;

void KPengaton::setNewRect(QPointF startP, QPointF endP)
{
	m_startPoint = startP;
	m_endPoint = endP;
	calculatePengatonPoints(m_points, QRectF(startP, endP));
	setPolygon(m_points);
}

void KPengaton::setFlags(GraphicsItemFlags flags)
{
	QGraphicsItem::setFlags(flags);
}

void KPengaton::setPen(QPen pen)
{
	QGraphicsPolygonItem::setPen(pen);
}

void KPengaton::setBrush(QBrush brush)
{
	QGraphicsPolygonItem::setBrush(brush);
}
