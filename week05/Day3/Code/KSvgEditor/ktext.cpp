#include "ktext.h"

KText::KText(QPointF startP, QPointF endP, QGraphicsTextItem* parent)
	: KShapeBase(KGlobalData::KShapeType::Text), QGraphicsTextItem(QStringLiteral("��ѡ����깤�ߵ�������ı�"), parent)
{
	setTextInteractionFlags(Qt::TextEditorInteraction);
	setFont(QFont(QStringLiteral("����"), 15));
	setNewRect(startP, endP);
}

KText::~KText()
= default;

void KText::setNewRect(QPointF startP, QPointF endP)
{
	setPos(endP);
}

void KText::setFlags(GraphicsItemFlags flags)
{
	QGraphicsTextItem::setFlags(flags);
}

QPen KText::getPen()
{
	return {};
}
