#pragma once

#include <QGraphicsTextItem>
#include <QFont>

#include "kshape.h"

class KText final : public KShapeBase, public QGraphicsTextItem
{
	Q_OBJECT

public:
	KText(QPointF startP, QPointF endP, QGraphicsTextItem* parent = nullptr);
	~KText() override;
	void setNewRect(QPointF startP, QPointF endP) override;
	void setFlags(GraphicsItemFlags flags) override;
	QPen getPen() override;
};
