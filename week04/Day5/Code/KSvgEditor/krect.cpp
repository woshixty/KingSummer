#include "krect.h"

KRect::KRect()
{}

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
