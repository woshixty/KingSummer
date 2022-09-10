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

	// ��ͼ�������н�����д, ʵ�ֲ�ͬ��ͼ�εĻ���
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
	// ��ʼ����
	QPoint m_startPoint;
	// ��������
	QPoint m_endPoint;
};
