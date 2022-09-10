#include "kfreeline.h"

KFreeLine::KFreeLine(QPointF startPoint, QPointF endpoint, QGraphicsPathItem*parent)
	: KShapeBase(KGlobalData::KShapeType::FreeLine), QGraphicsPathItem(parent)
{
}

KFreeLine::~KFreeLine()
= default;

void KFreeLine::setNewRect(QPointF startP, QPointF endP)
{
}

void KFreeLine::setPainter(QPolygonF points)
{
	// TODO��̽��addPolygon�Ƿ�Ḳ��֮ǰ�㼯
	m_path = QPainterPath();
	m_path.addPolygon(points);
	setPath(m_path);
}

void KFreeLine::setFlags(GraphicsItemFlags flags)
{
	QGraphicsItem::setFlags(flags);
}

void KFreeLine::setPen(QPen pen)
{
	QGraphicsPathItem::setPen(pen);
}

void KFreeLine::setBrush(QBrush brush)
{
	QGraphicsPathItem::setBrush(brush);
}

QPen KFreeLine::getPen()
{
	return pen();
}
