#pragma once

#include "kshape.h"

#include <QGraphicsEllipseItem>


class KCircle final : public KShapeBase, public QGraphicsEllipseItem
{
	Q_OBJECT

public:
	KCircle(QPointF startP, QPointF endP, QGraphicsItem *parent = nullptr);
	~KCircle() override;

	void setNewRect(QPointF startP, QPointF endP) override;
	void setFlags(GraphicsItemFlags flags) override;

	void setPen(QPen pen) override;
	void setBrush(QBrush brush) override;
	QPen getPen() override;
};
