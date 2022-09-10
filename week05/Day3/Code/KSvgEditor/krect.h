#pragma once

#include "kshape.h"

#include <QGraphicsRectItem>
#include <qpainter.h>

class KRect final : public KShapeBase, public QGraphicsRectItem
{
	Q_OBJECT

public:
	KRect(QPointF startP, QPointF endP, QGraphicsItem* parent = nullptr);
	~KRect() override;

	void setNewRect(QPointF startP, QPointF endP) override;
	void setFlags(GraphicsItemFlags flags) override;

	void setPen(QPen pen) override;
	void setBrush(QBrush brush) override;
	QPen getPen() override;
};
