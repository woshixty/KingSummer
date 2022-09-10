// -------------------------------------------------------
// krect.h
// 创建者： xie tingyu
// 创建时间： 2022/08/09
// 功能描述： 矩形图形类
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_RECT_H_
#define _K_RECT_H_

#include "kshape.h"

#include <QGraphicsRectItem>
#include <QPainter>

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
};

#endif