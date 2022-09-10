// -------------------------------------------------------
// kshapefactory.h
// 创建者： xie tingyu
// 创建时间： 2022/08/09
// 功能描述： 图形创建工场
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_SHAPE_FACTORY_H_
#define _K_SHAPE_FACTORY_H_

#include "kglobaldata.h"
#include "kshape.h"

#include <QGraphicsItem>
#include <QObject>

class KShapeFactory final : public QObject
{
	Q_OBJECT

public:
	KShapeFactory(QObject *parent = nullptr);
	~KShapeFactory() override;

	/**
	 * \brief 传入起始位置创建相应图形
	 * \param shapeT 
	 * \param startP 
	 * \param endP 
	 * \return 
	 */
	static KShapeBase* createShape(KGlobalData::KDrawFlag shapeT, QPointF startP, QPointF endP);
};

#endif