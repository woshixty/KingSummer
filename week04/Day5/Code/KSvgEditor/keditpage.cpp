#include "keditpage.h"

#include "kglobaldata.h"
#include "kshapefactory.h"

KEditPage::KEditPage(QWidget *parent)
	: QGraphicsView(parent)
{
	// 设置光标形状
	setCursor(Qt::CrossCursor);
	setMouseTracking(true);
	setDragMode(RubberBandDrag);

	scene = new QGraphicsScene();
	setScene(scene);
}

KEditPage::~KEditPage()
= default;

void KEditPage::iniGraphicsSystem() const
{
	// 一个位于scene中心的椭圆，测试局部坐标
	auto* item2 = new QGraphicsEllipseItem(-200, -100, 400, 200);
	item2->setBrush(QBrush(Qt::blue));
	item2->setFlags(QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsSelectable
		| QGraphicsItem::ItemIsFocusable);
	scene->addItem(item2);

	// 一个圆，中心位于scene的边缘
	auto* item3 = new QGraphicsEllipseItem(-50, -50, 100, 100);
	item3->setBrush(QBrush(Qt::red));
	item3->setFlags(QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsSelectable
		| QGraphicsItem::ItemIsFocusable);
	scene->addItem(item3);
	scene->clearSelection();
}

void KEditPage::drawPic() const
{
	const QPointF pref = mapToScene(m_startPoint);
	const int w = m_endPoint.x() - m_startPoint.x();
	const int h = m_endPoint.y() - m_startPoint.y();
	auto* item = new QGraphicsRectItem(pref.x(), pref.y(), w, h);
	item->setBrush(QBrush(Qt::white));
	item->setFlags(QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsSelectable
		| QGraphicsItem::ItemIsFocusable);
	drawItem(item);
}

void KEditPage::drawItem(QGraphicsItem* item) const
{
	scene->addItem(item);
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
	// 鼠标左键按下事件
	if (event->button() == Qt::LeftButton)
	{
		// QGraphicsView的坐标
		const QPoint point = event->pos();
		// 释放信号
		emit mouseClicked(point);
		m_startPoint = event->pos();
	}
	QGraphicsView::mousePressEvent(event);
}

void KEditPage::mouseReleaseEvent(QMouseEvent* event)
{
	m_endPoint = event->pos();
	drawPic();
	QGraphicsView::mouseReleaseEvent(event);
}
