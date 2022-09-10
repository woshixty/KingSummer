#pragma once

#include "kshape.h"

#include <QGraphicsRectItem>
#include <qpainter.h>

class KRect final : public KShape, public QGraphicsRectItem
{
	Q_OBJECT

public:
	KRect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent = nullptr);
	explicit KRect(const QRectF& rect, QGraphicsItem* parent = nullptr);
	explicit KRect(QGraphicsItem* parent = nullptr);
	~KRect() override;

	void drawShape(QPaintDevice* parent = Q_NULLPTR) override;
};
