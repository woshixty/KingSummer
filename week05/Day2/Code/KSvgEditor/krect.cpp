#include "krect.h"

KRect::KRect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent)
	: QGraphicsRectItem(x, y, width, height, parent)
{
}

KRect::KRect(const QRectF& rect, QGraphicsItem* parent)
	: QGraphicsRectItem(rect, parent)
{
}

KRect::KRect(QGraphicsItem* parent)
	: QGraphicsRectItem(parent)
{
}

KRect::~KRect()
= default;

void KRect::drawShape(QPaintDevice* parent)
{
	QPainter painter(parent);
	QPen pen;
	// ���û��ʵ���ɫ
	pen.setColor(QColor(79, 128, 255));
	// �����߿�
	pen.setWidth(3);
	painter.setPen(pen);
	// ���ƾ���
	painter.drawRect(QRect(getStartPoint(), getEndPoint()));
}
