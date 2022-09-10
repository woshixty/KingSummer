#include "kstar.h"

KStar::KStar(QPointF startP, QPointF endP, QGraphicsPolygonItem* parent)
	: KShapeBase(KGlobalData::KShapeType::Star), QGraphicsPolygonItem(parent)
{
	setNewRect(startP, endP);
}

KStar::~KStar()
= default;

void KStar::setNewRect(QPointF startP, QPointF endP)
{
	calculateStarPoints(m_points, QRectF(startP, endP));
	setPolygon(m_points);
}

void KStar::setFlags(GraphicsItemFlags flags)
{
	QGraphicsItem::setFlags(flags);
}

void KStar::setPen(QPen pen)
{
	QGraphicsPolygonItem::setPen(pen);
}

void KStar::setBrush(QBrush brush)
{
	QGraphicsPolygonItem::setBrush(brush);
}

QPen KStar::getPen()
{
	return pen();
}
