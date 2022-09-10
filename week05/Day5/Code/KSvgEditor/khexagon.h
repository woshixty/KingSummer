// -------------------------------------------------------
// khexagon.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/09
// ���������� ������ͼ����
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_HEXAGON_H_
#define _K_HEXAGON_H_

#include "kshape.h"

#include <QGraphicsPolygonItem>

class KHexagon final : public KShapeBase, public QGraphicsPolygonItem
{
	Q_OBJECT

public:
	KHexagon(QPointF startP, QPointF endP, QGraphicsItem* parent = nullptr);
	~KHexagon() override;

	void setNewRect(QPointF startP, QPointF endP) override;
	void setFlags(GraphicsItemFlags flags) override;

	void setPen(QPen pen) override;
	void setBrush(QBrush brush) override;

private:
	QPolygonF m_points;
};

#endif
