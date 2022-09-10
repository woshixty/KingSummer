// -------------------------------------------------------
// kstar.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/09
// ���������� �����ͼ���࣬ʵ�ʱ���Ϊ�������
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
