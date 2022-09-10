#include "krect.h"

KRect::KRect(QPointF startP, QPointF endP, QGraphicsItem* parent)
	: KShapeBase(startP, endP, KGlobalData::KShapeType::Rect), QGraphicsRectItem(parent)
{
	setNewRect(startP, endP);
}

KRect::~KRect()
= default;

void KRect::setNewRect(QPointF startP, QPointF endP)
{
	m_startPoint = startP;
	m_endPoint = endP;
	setRect(
		startP.x(), startP.y(),
		endP.x() - startP.x(), endP.y() - startP.y()
	);
}

void KRect::setFlags(GraphicsItemFlags flags)
{
	QGraphicsItem::setFlags(flags);
}

void KRect::setPen(QPen pen)
{
	QGraphicsRectItem::setPen(pen);
}

void KRect::setBrush(QBrush brush)
{
	QGraphicsRectItem::setBrush(brush);
}
