#include "kshape.h"

QPoint KShape::getStartPoint() const
{
	return m_startPoint;
}

QPoint KShape::getEndPoint() const
{
	return m_endPoint;
}

void KShape::setStartPoint(QPoint point)
{
	m_startPoint = point;
}

void KShape::setEndPoint(QPoint point)
{
	m_endPoint = point;
}

// 获取图形的矩形区域
QRect KShape::getShapeRect() const
{
	return QRect(m_startPoint, m_endPoint);
}

bool KShape::isValid() const
{
	return m_startPoint.x() != m_endPoint.x() || m_startPoint.y() != m_endPoint.y();
}

void KShape::move(QPoint offset)
{
	m_startPoint += offset;
	m_endPoint += offset;
}

void KShape::moveTop(QPoint pos)
{
	m_startPoint.ry() = pos.y();
}

void KShape::moveBottom(QPoint pos)
{
	m_endPoint.ry() = pos.y();
}

void KShape::moveLeft(QPoint pos)
{
	m_startPoint.rx() = pos.x();
}

void KShape::moveRight(QPoint pos)
{
	m_endPoint.rx() = pos.x();
}

void KShape::moveTopLeft(QPoint pos)
{
	m_startPoint = pos;
}

void KShape::moveTopRight(QPoint pos)
{
	m_startPoint.ry() = pos.y();
	m_endPoint.rx() = pos.x();
}

void KShape::moveBottomLeft(QPoint pos)
{
	m_startPoint.rx() = pos.x();
	m_endPoint.ry() = pos.y();
}

void KShape::moveBottomRight(QPoint pos)
{
	m_endPoint = pos;
}