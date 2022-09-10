#pragma once

#include <qgraphicsitem.h>
#include <QObject>

#include "kglobaldata.h"
#include "kshape.h"

class KShapeFactory final : public QObject
{
	Q_OBJECT

public:
	KShapeFactory(QObject *parent);
	~KShapeFactory() override;

	static KShapeBase* createShape(KGlobalData::KDrawFlag shapeT, QPointF startP, QPointF endP);
};
