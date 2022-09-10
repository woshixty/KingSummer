// -------------------------------------------------------
// kcircle.h
// 创建者： xie tingyu
// 创建时间： 2022/08/09
// 功能描述： 圆形类
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
