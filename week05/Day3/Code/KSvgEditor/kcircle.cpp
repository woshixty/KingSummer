#include "kcircle.h"

KCircle::KCircle(QPointF startP, QPointF endP, QGraphicsItem*parent)
	:KShapeBase(KGlobalData::KShapeType::Circle), QGraphicsEllipseItem(parent)
{
	setNewRect(startP, endP);
}

KCircle::~KCircle()
= default;

void KCircle::setNewRect(QPointF startP, QPointF endP)
{
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

QPen KCircle::getPen()
{
	return pen();
}

