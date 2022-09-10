#ifndef __K_SVG_DOC_WRITER_H_
#define __K_SVG_DOC_WRITER_H_

#include <QtXml/qdom.h>

#include "kcircle.h"
#include "kfreeline.h"
#include "kglobaldata.h"
#include "khexagon.h"
#include "kline.h"
#include "kpengaton.h"
#include "krect.h"
#include "kshape.h"
#include "kstar.h"

class KSvgWriter
{

public:
	KSvgWriter();
	~KSvgWriter();
	void initFrame();
	void initBackground();
	void initObject(const QList<KShapeBase*>& list);
	void save(const QString& filePath) const;

private:
	void addRect(const KRect* shape);
	void addLine(const KLine* shape);
	void addCircle(const KCircle* shape);
	void addPolygon(const QGraphicsPolygonItem* shape);
	void addPen(KFreeLine* shape);
	// void addText(KText* shape);
	QString points2str(QPolygonF& points) const;
	QString points2str(QPolygonF&& points) const;

	QDomDocument* m_pDomDoc;
	QDomElement m_svgEle;
	QDomElement m_backgroundEle;
	QDomElement m_objEle;
	KGlobalData* m_pData = KGlobalData::getGlobalDataInstance();
};

#endif