// -------------------------------------------------------
// kstar.h
// 创建者： xie tingyu
// 创建时间： 2022/08/09
// 功能描述： 五角星图形类，实际本质为五角星类
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_STAR_H_
#define _K_STAR_H_

#include "kshape.h"

#include <QGraphicsPolygonItem>

class KStar final : public KShapeBase, public QGraphicsPolygonItem
{
	Q_OBJECT

public:
	KStar(QPointF startP, QPointF endP, QGraphicsItem* parent = nullptr);
	~KStar() override;

	void setNewRect(QPointF startP, QPointF endP) override;
	void setFlags(GraphicsItemFlags flags) override;

	void setPen(QPen pen) override;
	void setBrush(QBrush brush) override;

private:
	QPolygonF m_points;
};

#endif
