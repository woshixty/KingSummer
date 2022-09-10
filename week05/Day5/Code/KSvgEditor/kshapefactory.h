// -------------------------------------------------------
// kshapefactory.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/09
// ���������� ͼ�δ�������
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_SHAPE_FACTORY_H_
#define _K_SHAPE_FACTORY_H_

#include "kglobaldata.h"
#include "kshape.h"

#include <QGraphicsItem>
#include <QObject>

class KShapeFactory final : public QObject
{
	Q_OBJECT

public:
	KShapeFactory(QObject *parent = nullptr);
	~KShapeFactory() override;

	/**
	 * \brief ������ʼλ�ô�����Ӧͼ��
	 * \param shapeT 
	 * \param startP 
	 * \param endP 
	 * \return 
	 */
	static KShapeBase* createShape(KGlobalData::KDrawFlag shapeT, QPointF startP, QPointF endP);
};

#endif