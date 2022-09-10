#pragma once

#include <QObject>

#include "kglobaldata.h"
#include "kshape.h"

class KShapeFactory : public QObject
{
	Q_OBJECT

public:
	KShapeFactory(QObject *parent);
	~KShapeFactory() override;

	static KShape* createShape(KGlobalData::KDrawFlag shapeType);
};
