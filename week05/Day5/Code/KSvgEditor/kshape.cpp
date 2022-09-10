#include "kshape.h"

KShapeBase::KShapeBase(QPointF startP, QPointF endP, KGlobalData::KShapeType shape, QObject* parent)
	: QObject(parent)
{
	m_startPoint = startP;
	m_endPoint = endP;
	m_shapeType = shape;
}

KShapeBase::~KShapeBase()
{
}

void KShapeBase::setNewRect(QRectF rect)
{
	setNewRect(rect.topLeft(), rect.bottomRight());
}

void KShapeBase::setPen(QPen pen)
{
}

void KShapeBase::setBrush(QBrush brush)
{
}

void KShapeBase::setPainter(QPolygonF points)
{
}

void KShapeBase::calculateHexagonPoints(QPolygonF& points, QRectF rect)
{
	points.clear();
	const qreal leftX = rect.left();
	const qreal rightX = rect.right();
	const qreal topY = rect.top();
	const qreal bottomY = rect.bottom();
	const qreal right_left_4 = (rightX - leftX) / 4;
	const qreal bottom_top_2 = (bottomY - topY) / 2;

	points.append(QPointF(leftX + right_left_4, topY));
	points.append(QPointF(leftX, topY + bottom_top_2));
	points.append(QPointF(leftX + right_left_4, bottomY));
	points.append(QPointF(rightX - right_left_4, bottomY));
	points.append(QPointF(rightX, topY + bottom_top_2));
	points.append(QPointF(rightX - right_left_4, topY));
}

void KShapeBase::calculatePengatonPoints(QPolygonF& points, QRectF rect)
{
	points.clear();
	const qreal leftX = rect.left();
	const qreal rightX = rect.right();
	const qreal topY = rect.top();
	const qreal bottomY = rect.bottom();
	const qreal right_left_2 = (rightX - leftX) / 2;
	const qreal right_left_5 = (rightX - leftX) / 5;
	const qreal top_bottom_top_5_2 = topY + (bottomY - topY) / 5 * 2;

	points.append(QPointF(leftX + right_left_2, topY));
	points.append(QPointF(leftX, top_bottom_top_5_2));
	points.append(QPointF(leftX + right_left_5, bottomY));
	points.append(QPointF(rightX - right_left_5, bottomY));
	points.append(QPointF(rightX, top_bottom_top_5_2));
}

void KShapeBase::calculateStarPoints(QPolygonF& points, QRectF rect)
{
	points.clear();

	const qreal width = rect.width();
	const qreal height = rect.height();
	const qreal height_5_2 = height / 5.0 * 2.0;
	const qreal height_4 = height / 4.0;
	const qreal width_2 = width / 2.0;
	const qreal width_3 = width / 3.0;
	const qreal width_5 = width / 5.0;
	const qreal width_5_2 = width / 5.0 * 2.0;
	
	points.append(QPointF(rect.left() + width_2, rect.top()));
	points.append(QPointF(rect.left() + width_5_2, rect.top() + height_5_2));
	points.append(QPointF(rect.left(), rect.top() + height_5_2));

	points.append(QPointF(rect.left() + width_3, rect.bottom() - height_5_2));
	points.append(QPointF(rect.left() + width_5, rect.bottom()));
	points.append(QPointF(rect.left() + width_2, rect.bottom() - height_4));

	points.append(QPointF(rect.right() - width_5, rect.bottom()));
	points.append(QPointF(rect.right() - width_3, rect.bottom() - height_5_2));
	points.append(QPointF(rect.right(), rect.top() + height_5_2));

	points.append(QPointF(rect.right() - width_5_2, rect.top() + height_5_2));
}
