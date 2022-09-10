#pragma once

#include "kglobaldata.h"

#include <QObject>
#include <QPen>
#include <QBrush>
#include <QGraphicsItem>

class KShapeBase : public QObject
{
	Q_OBJECT

public:

	explicit KShapeBase(KGlobalData::KShapeType shapeType);

	// virtual QPointF getStartPoint() const = 0;
	// virtual QPointF getEndPoint() const = 0;
	virtual void setNewRect(QPointF startP, QPointF endP) = 0;
	void setNewRect(QRectF rect);
	virtual void setFlags(QGraphicsItem::GraphicsItemFlags flags) = 0;
	virtual QPen getPen() = 0;
	virtual void setPen(QPen pen);
	virtual void setBrush(QBrush brush);
	virtual void setPainter(QPolygonF points);

	KGlobalData::KShapeType getShapeType() const { return m_shapeType; }
	static void calculateHexagonPoints(QPolygonF& points, QRectF rect);
	static void calculatePengatonPoints(QPolygonF& points, QRectF rect);
	static void calculateStarPoints(QPolygonF& points, QRectF rect);

protected:
	KGlobalData* m_pData = KGlobalData::getGlobalDataInstance();

private:
	KGlobalData::KShapeType m_shapeType;
	QBrush m_brush;
	QPen m_pen;
};
