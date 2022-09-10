#pragma once

#include <QGraphicsPathItem>
#include <QPainterPath>

#include "kshape.h"

class KFreeLine final : public KShapeBase, public QGraphicsPathItem
{
	Q_OBJECT

public:
	KFreeLine(QPointF startPoint, QPointF endpoint, QGraphicsPathItem*parent = nullptr);
	~KFreeLine() override;

	void setNewRect(QPointF startP, QPointF endP) override;
	void setPainter(QPolygonF points) override;
	void setFlags(GraphicsItemFlags flags) override;

	void setPen(QPen pen) override;
	void setBrush(QBrush brush) override;
	QPen getPen() override;

private:
	QPainterPath m_path;
};
