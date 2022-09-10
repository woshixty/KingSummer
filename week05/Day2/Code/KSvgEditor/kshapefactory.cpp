#include "kshapefactory.h"

#include "krect.h"

KShapeFactory::KShapeFactory(QObject *parent)
	: QObject(parent)
{}

KShapeFactory::~KShapeFactory()
= default;

KShape* KShapeFactory::createShape(KGlobalData::KDrawFlag shapeType)
{
	switch (shapeType)
	{
	case KGlobalData::KDrawFlag::RectFlag:
		return new KRect();
	case KGlobalData::KDrawFlag::NoneFlag: break;
	case KGlobalData::KDrawFlag::MouseFlag: break;
	case KGlobalData::KDrawFlag::PenFlag: break;
	case KGlobalData::KDrawFlag::LineFlag: break;
	case KGlobalData::KDrawFlag::CircleFlag: break;
	case KGlobalData::KDrawFlag::TextFlag: break;
	case KGlobalData::KDrawFlag::PengatonFlag: break;
	case KGlobalData::KDrawFlag::HexagonFlag: break;
	case KGlobalData::KDrawFlag::StarFlag: break;
	case KGlobalData::KDrawFlag::ZoomFlag: break;
	default:
		return nullptr;
	}
	return nullptr;
}
