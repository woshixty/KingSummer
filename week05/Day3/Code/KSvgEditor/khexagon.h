#pragma once

#include <QGraphicsPolygonItem>

#include "kshape.h"

class KHexagon final : public KShapeBase, public QGraphicsPolygonItem
{
	Q_OBJECT

public:
	KHexagon(QPointF startP, QPointF endP, QGraphicsPolygonItem* parent = nullptr);
	~KHexagon() override;

	void setNewRect(QPointF startP, QPointF endP) override;
	void setFlags(GraphicsItemFlags flags) override;

	void setPen(QPen pen) override;
	void setBrush(QBrush brush) override;
	QPen getPen() override;

private:
	QPolygonF m_points;
};
