#include "kglobaldata.h"

KGlobalData* KGlobalData::s_globalDataObj = nullptr;

KGlobalData* KGlobalData::getGlobalDataInstance(QObject* parent)
{
	if (s_globalDataObj == nullptr)
		s_globalDataObj = new KGlobalData(parent);
	return s_globalDataObj;
}

KGlobalData::KGlobalData(QObject *parent)
	: QObject(parent)
{}
