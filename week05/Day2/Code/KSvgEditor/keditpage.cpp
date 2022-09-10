#include "keditpage.h"

#include "kglobaldata.h"
#include "kshapefactory.h"

KEditPage::KEditPage(QWidget *parent)
	: QGraphicsView(parent)
{
	setMouseTracking(true);
	setDragMode(RubberBandDrag);

	scene = new QGraphicsScene();
	setScene(scene);
}

KEditPage::~KEditPage()
= default;

void KEditPage::drawItem() const
{
	const QPointF pref = mapToScene(m_startPoint);
	const int w = m_endPoint.x() - m_startPoint.x();
	const int h = m_endPoint.y() - m_startPoint.y();
	auto* item = new QGraphicsRectItem(pref.x(), pref.y(), w, h);

	QString colorStr = KGlobalData::getGlobalDataInstance()->getFillColor();
	QColor color1;
	color1.setRgb(colorStr.toUInt(nullptr, 16));
	qDebug() << "colorStr:" << colorStr;
	QBrush brush;
	brush.setColor(Qt::blue);
	item->setBrush(brush);

	colorStr = KGlobalData::getGlobalDataInstance()->getBorderColor();
	color1.setRgb(colorStr.toUInt(nullptr, 16));
	QPen pen;
	pen.setColor(color1);
	pen.setStyle(Qt::DotLine);
	pen.setWidth(KGlobalData::getGlobalDataInstance()->getBorderWidth());
	item->setPen(pen);

	item->setFlags(QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsSelectable
		| QGraphicsItem::ItemIsFocusable);
	drawItem(item);
}

void KEditPage::drawItem(QGraphicsItem* item) const
{
	scene->addItem(item);
}

void KEditPage::enterEvent(QEvent* event)
{
	switch (m_pData->getDrawFlag())
	{
	case KGlobalData::KDrawFlag::NoneFlag: break;
	case KGlobalData::KDrawFlag::MouseFlag: break;
	case KGlobalData::KDrawFlag::PenFlag: 
	case KGlobalData::KDrawFlag::LineFlag:
	case KGlobalData::KDrawFlag::CircleFlag:
	case KGlobalData::KDrawFlag::RectFlag:
	case KGlobalData::KDrawFlag::PengatonFlag:
	case KGlobalData::KDrawFlag::HexagonFlag:
	case KGlobalData::KDrawFlag::StarFlag:
		setCursor(Qt::CrossCursor);
		break;
	case KGlobalData::KDrawFlag::TextFlag:
		setCursor(Qt::IBeamCursor);
		break;
	case KGlobalData::KDrawFlag::ZoomFlag:
		setCursor(Qt::OpenHandCursor);
		break;
	default: break;
	}
}

void KEditPage::leaveEvent(QEvent* event)
{
	setCursor(Qt::ArrowCursor);
}

void KEditPage::changeSceneColor() const
{
	const QString colorStr = KGlobalData::getGlobalDataInstance()->getCanvasColor();
	scene->setBackgroundBrush(QColor(colorStr.toUInt(nullptr, 16)));
}

void KEditPage::mouseMoveEvent(QMouseEvent* event)
{
	// 鼠标移动事件
	// QGraphicsView的坐标
	const QPoint point = event->pos();
	// 释放信号
	emit mouseMovePoint(point);

	QGraphicsView::mouseMoveEvent(event);
}

void KEditPage::mousePressEvent(QMouseEvent* event)
{
	if (QGraphicsItem* item = itemAt(event->pos())) {
		qDebug() << "You clicked on item" << item;
	}
	else {
		qDebug("You didn't click on an item.");
	}
	scene->clearSelection();
	// 鼠标左键按下事件
	switch (event->button())
	{
	case Qt::LeftButton:
		leftButtonPressed(event);
		break;
	
	default: break;
	}
}

void KEditPage::leftButtonPressed(QMouseEvent* event)
{
	scene->clearSelection();
	// QGraphicsView的坐标
	const QPoint point = event->pos();
	// 释放信号
	emit mouseClicked(point);
	m_startPoint = event->pos();

	if (m_pData->removable())
		QGraphicsView::mousePressEvent(event);
}

void KEditPage::mouseReleaseEvent(QMouseEvent* event)
{
	m_endPoint = event->pos();
	switch (m_pData->getDrawFlag())
	{
		case KGlobalData::KDrawFlag::NoneFlag: break;
		case KGlobalData::KDrawFlag::MouseFlag: break;
		case KGlobalData::KDrawFlag::PenFlag: break;
		case KGlobalData::KDrawFlag::LineFlag: break;
		case KGlobalData::KDrawFlag::CircleFlag: break;
		case KGlobalData::KDrawFlag::RectFlag: 
			drawItem();
			break;
		case KGlobalData::KDrawFlag::PengatonFlag: break;
		case KGlobalData::KDrawFlag::HexagonFlag: break;
		case KGlobalData::KDrawFlag::StarFlag: break;
		case KGlobalData::KDrawFlag::TextFlag: break;
		case KGlobalData::KDrawFlag::ZoomFlag: break;
		default: break;
	}
	QGraphicsView::mouseReleaseEvent(event);
} 
