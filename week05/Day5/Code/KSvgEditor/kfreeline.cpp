#include "kfreeline.h"

KFreeLine::KFreeLine(QPointF startP, QPointF endP, QGraphicsItem*parent)
	: KShapeBase(startP, endP, KGlobalData::KShapeType::FreeLine), QGraphicsPathItem(parent)
{
}

KFreeLine::~KFreeLine()
= default;

void KFreeLine::setNewRect(QPointF startP, QPointF endP)
{
	m_startPoint = startP;
	m_endPoint = endP;
	// TODO �㼯֮���ӳ��
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

