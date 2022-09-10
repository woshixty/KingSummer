#pragma once

#include "kshape.h"

#include <QGraphicsLineItem>

class KLine : public KShapeBase, public QGraphicsPathItem
{
	Q_OBJECT

public:
	KLine(QPointF startP, QPointF endP, QGraphicsItem* parent = nullptr);
	~KLine() override;

	void setNewRect(QPointF startP, QPointF endP) override;
	void setFlags(GraphicsItemFlags flags) override;

	void setPen(QPen pen) override;
	void setBrush(QBrush brush) override;
	QPen getPen() override;

private:
	QPolygonF m_points;
};
