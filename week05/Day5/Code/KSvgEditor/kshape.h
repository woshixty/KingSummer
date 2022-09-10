// -------------------------------------------------------
// kshape.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/09
// ���������� ����ͼ�λ������
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
	 * \brief ����ͼ�ε�ʵ����ֹ�㣨����Ⱦ�߽�֮��ģ�
	 * \param startP 
	 * \param endP 
	 */
	virtual void setNewRect(QPointF startP, QPointF endP) = 0;

	/**
	 * \brief ����ͼ������
	 * \param flags 
	 */
	virtual void setFlags(QGraphicsItem::GraphicsItemFlags flags) = 0;

	/**
	 * \brief ����ͼ�εĻ��ʣ�ĳЩͼ���������û�ˢ�ʷǴ��麯����
	 * \param pen 
	 */
	virtual void setPen(QPen pen);

	/**
	 * \brief ����ͼ�λ�ˢ��ĳЩͼ���������û�ˢ�ʷǴ��麯����
	 * \param brush 
	 */
	virtual void setBrush(QBrush brush);

	/**
	 * \brief ���ö���εĵ㼯
	 * \param points 
	 */
	virtual void setPainter(QPolygonF points);

	/**
	 * \brief �������أ�ֱ�ӵ���������д�Ĵ��鷽��setNewRect
	 * \param rect 
	 */
	void setNewRect(QRectF rect);

	/**
	 * \brief ��ȡͼ�ε�ʵ�ʻ��Ƶľ��ο�
	 * \return 
	 */
	QRectF getRectF() const { return QRectF(m_startPoint, m_endPoint); }

	/**
	 * \brief ��ȡ��ͼ�ε�����
	 * \return 
	 */
	KGlobalData::KShapeType getShapeType() const { return m_shapeType; }

	/**
	 * \brief ���������
	 * \param points 
	 * \param rect 
	 */
	static void calculateHexagonPoints(QPolygonF& points, QRectF rect);

	/**
	 * \brief ����������
	 * \param points 
	 * \param rect 
	 */
	static void calculatePengatonPoints(QPolygonF& points, QRectF rect);

	/**
	 * \brief ���������
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