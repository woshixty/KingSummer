#include "kshapefactory.h"

#include "krect.h"
#include "kline.h"
#include "kcircle.h"
#include "kfreeline.h"
#include "khexagon.h"
#include "kpengaton.h"
#include "kstar.h"
#include "ktext.h"

KShapeFactory::KShapeFactory(QObject *parent)
	: QObject(parent)
{}

KShapeFactory::~KShapeFactory()
= default;

KShapeBase* KShapeFactory::createShape(KGlobalData::KDrawFlag shapeT, QPointF startP, QPointF endP)
{
	switch (shapeT)
	{
	case KGlobalData::KDrawFlag::NoneFlag: 
	case KGlobalData::KDrawFlag::MouseFlag: 
	case KGlobalData::KDrawFlag::ZoomFlag:
		return nullptr;
	case KGlobalData::KDrawFlag::RectFlag: 
		return new KRect(startP, endP);
	case KGlobalData::KDrawFlag::PenFlag:
		return new KFreeLine(startP, endP);
	case KGlobalData::KDrawFlag::LineFlag: 
		return new KLine(startP, endP);
	case KGlobalData::KDrawFlag::CircleFlag:
		return new KCircle(startP, endP);
	case KGlobalData::KDrawFlag::TextFlag:
		return new KText(startP, endP);
	case KGlobalData::KDrawFlag::PengatonFlag:
		return new KPengaton(startP, endP);
	case KGlobalData::KDrawFlag::HexagonFlag:
		return new KHexagon(startP, endP);
	case KGlobalData::KDrawFlag::StarFlag:
		return new KStar(startP, endP);
	default:
		return nullptr;
	}
}
