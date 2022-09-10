#include "kcircle.h"

KCircle::KCircle(QPointF startP, QPointF endP, QGraphicsItem*parent)
	:KShapeBase(startP, endP, KGlobalData::KShapeType::Circle), QGraphicsEllipseItem(parent)
{
	setNewRect(startP, endP);
}

KCircle::~KCircle()
= default;

void KCircle::setNewRect(QPointF startP, QPointF endP)
{
	m_startPoint = startP;
	m_endPoint = endP;
	setRect(QRectF(startP, endP));
}

void KCircle::setFlags(GraphicsItemFlags flags)
{
	QGraphicsItem::setFlags(flags);
}

void KCircle::setPen(QPen pen)
{
	QGraphicsEllipseItem::setPen(pen);
}

void KCircle::setBrush(QBrush brush)
{
	QGraphicsEllipseItem::setBrush(brush);
}

