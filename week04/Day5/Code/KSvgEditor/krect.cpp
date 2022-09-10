#include "krect.h"

KRect::KRect()
{}

KRect::~KRect()
= default;

void KRect::drawShape(QPaintDevice* parent)
{
	QPainter painter(parent);
	QPen pen;
	// 设置画笔的颜色
	pen.setColor(QColor(79, 128, 255));
	// 设置线宽
	pen.setWidth(3);
	painter.setPen(pen);

	// 绘制矩形
	painter.drawRect(QRect(getStartPoint(), getEndPoint()));
}
