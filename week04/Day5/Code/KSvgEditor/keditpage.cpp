#include "keditpage.h"

#include "kglobaldata.h"
#include "kshapefactory.h"

KEditPage::KEditPage(QWidget *parent)
	: QGraphicsView(parent)
{
	// ���ù����״
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
	// һ��λ��scene���ĵ���Բ�����Ծֲ�����
	auto* item2 = new QGraphicsEllipseItem(-200, -100, 400, 200);
	item2->setBrush(QBrush(Qt::blue));
	item2->setFlags(QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsSelectable
		| QGraphicsItem::ItemIsFocusable);
	scene->addItem(item2);

	// һ��Բ������λ��scene�ı�Ե
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
	// ����ƶ��¼�
	// QGraphicsView������
	const QPoint point = event->pos();
	// �ͷ��ź�
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
	// �����������¼�
	if (event->button() == Qt::LeftButton)
	{
		// QGraphicsView������
		const QPoint point = event->pos();
		// �ͷ��ź�
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
