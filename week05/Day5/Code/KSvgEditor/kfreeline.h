// -------------------------------------------------------
// kfreeline.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/09
// ���������� ������ͼ����
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_FREELINE_H_
#define _K_FREELINE_H_

#include "kshape.h"

#include <QGraphicsPathItem>
#include <QPainterPath>

class KFreeLine final : public KShapeBase, public QGraphicsPathItem
{
	Q_OBJECT

public:
	KFreeLine(QPointF startP, QPointF endP, QGraphicsItem* parent = nullptr);
	~KFreeLine() override;

	void setNewRect(QPointF startP, QPointF endP) override;
	void setPainter(QPolygonF points) override;
	void setFlags(GraphicsItemFlags flags) override;

	void setPen(QPen pen) override;

private:
	QPainterPath m_path;
};

#endif

