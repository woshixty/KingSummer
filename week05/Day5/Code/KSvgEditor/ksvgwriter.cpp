#include "ksvgwriter.h"
#include "kglobaldata.h"

#include <qfile.h>
#include <qtextstream.h>
#include <QDebug>

KSvgWriter::KSvgWriter() : m_pDomDoc(nullptr)
{
	m_pDomDoc = new QDomDocument;
}

KSvgWriter::~KSvgWriter()
{
	delete m_pDomDoc;
}

void KSvgWriter::initFrame()
{
	const int width = KGlobalData::getGlobalDataInstance()->canvasWidth();
	const int height = KGlobalData::getGlobalDataInstance()->canvasHeight();
	// 注释节点
	const QDomComment comment = m_pDomDoc->createComment(QStringLiteral("WPS"));
	// 添加到根节点上
	m_pDomDoc->appendChild(comment);
	// 创建 svg 标签
	m_svgEle = m_pDomDoc->createElement("svg");
	// 设置属性
	m_svgEle.setAttribute("xmlns", "http://www.w3.org/2000/svg");
	m_svgEle.setAttribute("width", width);
	m_svgEle.setAttribute("height", height);
	// g 标签 表示 group
	m_backgroundEle = m_pDomDoc->createElement("g");
	m_objEle = m_pDomDoc->createElement("g");

	m_svgEle.appendChild(m_backgroundEle);
	m_svgEle.appendChild(m_objEle);
	m_pDomDoc->appendChild(m_svgEle);
}

void KSvgWriter::initBackground()
{
	QDomElement backgroundTitle = m_pDomDoc->createElement("title");
	backgroundTitle.appendChild(m_pDomDoc->createTextNode("background"));
	QDomElement backgroundRect = m_pDomDoc->createElement("rect");
	// 设置 fill 属性
	QString color = m_pData->getCanvasColor();
	if (color.length() > 6)color = color.remove(0, 2);
	backgroundRect.setAttribute("fill", QString("#%1").arg(color));
	// 设置 id 属性
	backgroundRect.setAttribute("id", "canvas_background");
	// 设置宽度
	backgroundRect.setAttribute("width", m_pData->canvasWidth() + 2);
	// 设置高度
	backgroundRect.setAttribute("height", m_pData->canvasHeight() + 2);
	// 设置 x 坐标
	backgroundRect.setAttribute("x", -1);
	// 设置 y 坐标
	backgroundRect.setAttribute("y", -1);

	m_backgroundEle.appendChild(backgroundTitle);
	m_backgroundEle.appendChild(backgroundRect);
}

// 保存画布中所有图形
void KSvgWriter::initObject(const QList<KShapeBase*>& list)
{
	// 遍历所有图形
	for (const auto shape_base : list)
	{
		if (shape_base == nullptr)
			continue;
		switch (shape_base->getShapeType())
		{
		case KGlobalData::KShapeType::Rect:
			addRect(dynamic_cast<KRect*>(shape_base));
			break;
		case KGlobalData::KShapeType::StraightLine:
			addLine(dynamic_cast<KLine*>(shape_base));
			break;
		case KGlobalData::KShapeType::FreeLine:
			break;
		case KGlobalData::KShapeType::None:
			break;
		case KGlobalData::KShapeType::Circle:
			addCircle(dynamic_cast<KCircle*>(shape_base));
			break;
		case KGlobalData::KShapeType::Pentagon:
		case KGlobalData::KShapeType::Hexagon:
		case KGlobalData::KShapeType::Star:
			addPolygon(dynamic_cast<QGraphicsPolygonItem*>(shape_base));
			break;
		case KGlobalData::KShapeType::Text:
			break;
		default:
			break;
		}
	}
}

void KSvgWriter::save(const QString& filePath) const
{
	QFile file(filePath);
	// 只写模式打开文件
	if (file.open(QFile::WriteOnly | QFile::Text))
	{
		QTextStream out(&file);
		// 保存 svg 文件
		m_pDomDoc->save(out, QDomNode::EncodingFromDocument);
		file.close();
	}
}

void KSvgWriter::addRect(const KRect* shape)
{
	const QRectF rect = shape->boundingRect();
	// 创建一个 xml 元素
	QDomElement domEle = m_pDomDoc->createElement("rect");
	// 填充x y位置
	domEle.setAttribute("x", rect.topLeft().x());
	domEle.setAttribute("y", rect.topLeft().y());
	// 填充长 宽
	domEle.setAttribute("width", qAbs(rect.width()));
	domEle.setAttribute("height", qAbs(rect.height()));
	// 填充颜色
	QString colorBrush = QString::number(shape->brush().color().rgb(), 16);
	if (colorBrush.length() > 6)
		colorBrush = colorBrush.remove(0, 2);
	colorBrush = "#" + colorBrush;
	domEle.setAttribute("fill", colorBrush);
	// 边框宽
	domEle.setAttribute("stroke-width", shape->pen().widthF());
	// 边框颜色
	QString color = QString::number(shape->pen().color().rgb(), 16);
	if (color.length() > 6)color = color.remove(0, 2);
	color = "#" + color;
	domEle.setAttribute("stroke", color); 
	// 添加到父节点中
	m_objEle.appendChild(domEle);
}

void KSvgWriter::addLine(const KLine* shape)
{
	const QRectF rect = shape->boundingRect();
	// 创建一个 xml 元素
	QDomElement domEle = m_pDomDoc->createElement("line");
	domEle.setAttribute("x1", rect.topLeft().x());
	domEle.setAttribute("y1", rect.topLeft().y());
	domEle.setAttribute("x2", rect.bottomRight().x());
	domEle.setAttribute("y2", rect.bottomRight().y());
	// 边框宽
	domEle.setAttribute("stroke-width", shape->pen().widthF());
	// 边框颜色
	QString color = QString::number(shape->pen().color().rgb(), 16);
	if (color.length() > 6)color = color.remove(0, 2);
	color = "#" + color;
	domEle.setAttribute("stroke", color);
	// 添加到父节点中
	m_objEle.appendChild(domEle);
}

void KSvgWriter::addCircle(const KCircle* shape)
{
	const QRectF rect = shape->boundingRect();
	// 创建一个 xml 元素
	QDomElement domEle = m_pDomDoc->createElement("ellipse");
	domEle.setAttribute("cx", (rect.topLeft().x() + rect.bottomRight().x()) / 2);
	domEle.setAttribute("cy", (rect.topLeft().y() + rect.bottomRight().y()) / 2);
	domEle.setAttribute("rx", qAbs(rect.topLeft().x() - rect.bottomRight().x()) / 2);
	domEle.setAttribute("ry", qAbs(rect.topLeft().y() - rect.bottomRight().y()) / 2);
	// 填充颜色
	QString colorBrush = QString::number(shape->brush().color().rgb(), 16);
	if (colorBrush.length() > 6)
		colorBrush = colorBrush.remove(0, 2);
	colorBrush = "#" + colorBrush;
	domEle.setAttribute("fill", colorBrush);
	domEle.setAttribute("width", qAbs(rect.width()));
	domEle.setAttribute("height", qAbs(rect.height()));
	// 线宽
	domEle.setAttribute("stroke-width", shape->pen().widthF());
	// 线颜色
	QString color = QString::number(shape->pen().color().rgb(), 16);
	if (color.length() > 6)color = color.remove(0, 2);
	color = "#" + color;
	domEle.setAttribute("stroke", color);
	// 添加到父节点中
	m_objEle.appendChild(domEle);
}

void KSvgWriter::addPolygon(const QGraphicsPolygonItem* shape)
{
	const QRectF rect = shape->boundingRect();
	// 创建一个 xml 元素
	QDomElement domEle = m_pDomDoc->createElement("polygon");
	domEle.setAttribute("points", points2str(shape->polygon()));
	// 填充颜色
	QString colorBrush = QString::number(shape->brush().color().rgb(), 16);
	if (colorBrush.length() > 6)
		colorBrush = colorBrush.remove(0, 2);
	colorBrush = "#" + colorBrush;
	domEle.setAttribute("fill", colorBrush);
	domEle.setAttribute("width", qAbs(rect.width()));
	domEle.setAttribute("height", qAbs(rect.height()));
	// 线宽
	domEle.setAttribute("stroke-width", shape->pen().widthF());
	// 线颜色
	QString color = QString::number(shape->pen().color().rgb(), 16);
	if (color.length() > 6)color = color.remove(0, 2);
	color = "#" + color;
	domEle.setAttribute("stroke", color);
	// 添加到父节点中
	m_objEle.appendChild(domEle);
}

void KSvgWriter::addPen(KFreeLine* shape)
{
}

QString KSvgWriter::points2str(QPolygonF& points) const
{
	QString pointStr;
	for (auto point : points)
		pointStr.append(QString::number(point.x()) + "," + QString::number(point.y()) + " ");
	return pointStr;
}

QString KSvgWriter::points2str(QPolygonF&& points) const
{
	return points2str(points);
}
