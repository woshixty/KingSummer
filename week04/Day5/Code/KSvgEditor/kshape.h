#pragma once

#include <QObject>
#include <QPaintDevice>

class KShape : public QObject
{
public:
	QPoint getStartPoint() const;
	QPoint getEndPoint() const;
	void setStartPoint(QPoint point);
	void setEndPoint(QPoint point);

	QRect getShapeRect() const;
	bool isValid() const;

	// 在图形子类中进行重写, 实现不同的图形的绘制
	virtual void drawShape(QPaintDevice* parent = Q_NULLPTR) = 0;

	void move(QPoint offset);
	void moveTop(QPoint pos);
	void moveBottom(QPoint pos);
	void moveLeft(QPoint pos);
	void moveRight(QPoint pos);
	void moveTopLeft(QPoint pos);
	void moveTopRight(QPoint pos);
	void moveBottomLeft(QPoint pos);
	void moveBottomRight(QPoint pos);

protected:
	KShape() {}

private:
	// 起始坐标
	QPoint m_startPoint;
	// 结束坐标
	QPoint m_endPoint;
};
