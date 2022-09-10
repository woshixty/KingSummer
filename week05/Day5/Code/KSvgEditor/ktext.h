// -------------------------------------------------------
// ktext.h
// 创建者： xie tingyu
// 创建时间： 2022/08/09
// 功能描述： 文字图形类
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_TEXT_H_
#define _K_TEXT_H_

#include "kshape.h"

#include <QGraphicsTextItem>
#include <QFont>

class KText final : public KShapeBase, public QGraphicsTextItem
{
	Q_OBJECT

public:
	KText(QPointF startP, QPointF endP, QGraphicsItem* parent = nullptr);
	~KText() override;

	void setNewRect(QPointF startP, QPointF endP) override;
	void setFlags(GraphicsItemFlags flags) override;
};

#endif
