#include "ktext.h"

KText::KText(QPointF startP, QPointF endP, QGraphicsItem* parent)
	: KShapeBase(startP, endP, KGlobalData::KShapeType::Text),
		QGraphicsTextItem(QStringLiteral("请选择鼠标工具点击输入文本"), parent)
{
	setTextInteractionFlags(Qt::TextEditorInteraction);
	setFont(QFont(QStringLiteral("宋体"), 15));
	setNewRect(startP, endP);
}

KText::~KText()
= default;

void KText::setNewRect(QPointF startP, QPointF endP)
{
	m_startPoint = startP;
	m_endPoint = endP;
	setPos(endP);
}

void KText::setFlags(GraphicsItemFlags flags)
{
	QGraphicsTextItem::setFlags(flags);
}
