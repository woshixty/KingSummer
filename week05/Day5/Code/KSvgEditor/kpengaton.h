// -------------------------------------------------------
// kpengaton.h
// 创建者： xie tingyu
// 创建时间： 2022/08/09
// 功能描述： 五边形图形类
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_PENGATON_H_
#define _K_PENGATON_H_

#include "kshape.h"

#include <QGraphicsPolygonItem>

class KPengaton : public KShapeBase, public QGraphicsPolygonItem
{
	Q_OBJECT

public:
	KPengaton(QPointF startP, QPointF endP, QGraphicsItem* parent = nullptr);
	~KPengaton() override;

	void setNewRect(QPointF startP, QPointF endP) override;
	void setFlags(GraphicsItemFlags flags) override;

	void setPen(QPen pen) override;
	void setBrush(QBrush brush) override;

private:
	QPolygonF m_points;
};

#endif
