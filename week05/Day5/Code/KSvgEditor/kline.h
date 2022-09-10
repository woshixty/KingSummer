// -------------------------------------------------------
// kline.h
// 创建者： xie tingyu
// 创建时间： 2022/08/09
// 功能描述： 直线图形类
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_LINE_H_
#define _K_LINE_H_

#include "kshape.h"

#include <QGraphicsLineItem>

class KLine : public KShapeBase, public QGraphicsPathItem
{
	Q_OBJECT

public:
	KLine(QPointF startP, QPointF endP, QGraphicsItem* parent = nullptr);
	~KLine() override;

	void setNewRect(QPointF startP, QPointF endP) override;
	void setFlags(GraphicsItemFlags flags) override;

	void setPen(QPen pen) override;
	void setBrush(QBrush brush) override;

private:
	QPolygonF m_points;
};

#endif
