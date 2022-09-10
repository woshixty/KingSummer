#pragma once

#include "kshape.h"

#include <QGraphicsRectItem>
#include <qpainter.h>

class KRect final : public KShape, public QGraphicsRectItem
{
	Q_OBJECT

public:
	KRect();
	~KRect() override;

	void drawShape(QPaintDevice* parent = Q_NULLPTR) override;
};
