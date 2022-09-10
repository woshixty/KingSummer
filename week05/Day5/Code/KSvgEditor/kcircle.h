// -------------------------------------------------------
// kcircle.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/09
// ���������� Բ����
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_CIRCLE_H_
#define _K_CIRCLE_H_

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
};

#endif
