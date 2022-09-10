#pragma once

#include <QGraphicsPolygonItem>

#include "kshape.h"

class KPengaton : public KShapeBase, public QGraphicsPolygonItem
{
	Q_OBJECT

public:
	KPengaton(QPointF startP, QPointF endP, QGraphicsPolygonItem*parent = nullptr);
	~KPengaton() override;

	void setNewRect(QPointF startP, QPointF endP) override;
	void setFlags(GraphicsItemFlags flags) override;

	void setPen(QPen pen) override;
	void setBrush(QBrush brush) override;
	QPen getPen() override;

private:
	QPolygonF m_points;
};
