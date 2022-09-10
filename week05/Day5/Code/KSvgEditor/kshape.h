// -------------------------------------------------------
// kshape.h
// 创建者： xie tingyu
// 创建时间： 2022/08/09
// 功能描述： 具体图形化类基类
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_SHAPE_H_
#define _K_SHAPE_H_

#include "kglobaldata.h"

#include <QObject>
#include <QPen>
#include <QBrush>
#include <QGraphicsItem>

class KShapeBase : public QObject
{
	Q_OBJECT

public:
	explicit KShapeBase(QPointF startP, QPointF endP, KGlobalData::KShapeType shape, QObject* parent = nullptr);
	~KShapeBase();

	/**
	 * \brief 设置图形的实际起止点（非渲染边界之后的）
	 * \param startP 
	 * \param endP 
	 */
	virtual void setNewRect(QPointF startP, QPointF endP) = 0;

	/**
	 * \brief 设置图形属性
	 * \param flags 
	 */
	virtual void setFlags(QGraphicsItem::GraphicsItemFlags flags) = 0;

	/**
	 * \brief 设置图形的画笔（某些图形无需设置画刷故非纯虚函数）
	 * \param pen 
	 */
	virtual void setPen(QPen pen);

	/**
	 * \brief 设置图形画刷（某些图形无需设置画刷故非纯虚函数）
	 * \param brush 
	 */
	virtual void setBrush(QBrush brush);

	/**
	 * \brief 设置多边形的点集
	 * \param points 
	 */
	virtual void setPainter(QPolygonF points);

	/**
	 * \brief 用于重载，直接调用子类重写的纯虚方法setNewRect
	 * \param rect 
	 */
	void setNewRect(QRectF rect);

	/**
	 * \brief 获取图形的实际绘制的矩形框
	 * \return 
	 */
	QRectF getRectF() const { return QRectF(m_startPoint, m_endPoint); }

	/**
	 * \brief 获取该图形的类型
	 * \return 
	 */
	KGlobalData::KShapeType getShapeType() const { return m_shapeType; }

	/**
	 * \brief 计算五边形
	 * \param points 
	 * \param rect 
	 */
	static void calculateHexagonPoints(QPolygonF& points, QRectF rect);

	/**
	 * \brief 计算六边形
	 * \param points 
	 * \param rect 
	 */
	static void calculatePengatonPoints(QPolygonF& points, QRectF rect);

	/**
	 * \brief 计算五角星
	 * \param points 
	 * \param rect 
	 */
	static void calculateStarPoints(QPolygonF& points, QRectF rect);

protected:
	QPointF m_startPoint;
	QPointF m_endPoint;

private:
	KGlobalData::KShapeType m_shapeType;
};

#endif