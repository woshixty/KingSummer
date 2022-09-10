#include "keditpage.h"

#include <qdialog.h>

#include "kcircle.h"
#include "kfreeline.h"
#include "kglobaldata.h"
#include "kline.h"
#include "kshapefactory.h"

KEditPage::KEditPage(QWidget *parent)
	: QGraphicsView(parent)
{
	// 设置鼠标是否可追踪
	setMouseTracking(true);
	// 拖动鼠标将设置橡皮筋的几何形状，橡皮筋覆盖的所有项目都被选中
	setDragMode(RubberBandDrag);
	// 创建新场景
	m_pScene = new QGraphicsScene();
	setScene(m_pScene);
	// 固定坐标view和scene相对位置
	m_pScene->setSceneRect(0, 0, m_pData->canvasWidth(), m_pData->canvasHeight());
	m_pScene->addRect(0, 0, m_pData->canvasWidth(), m_pData->canvasHeight());
	 
	// 设置临时画笔为虚线
	m_tempPen.setStyle(Qt::DotLine);
}

KEditPage::~KEditPage()
= default;

void KEditPage::enterEvent(QEvent* event)
{
	// TODO: 优化Swith语句
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

void KEditPage::updateSceneBackground() const
{
	const QBrush brush(m_pData->getCanvasColor().toUInt(nullptr, 16));
	m_pScene->setBackgroundBrush(brush);
}

void KEditPage::updateSelectItems() const
{
	// 设置brush和pen
	const QString fillColorStr = KGlobalData::getGlobalDataInstance()->getFillColor();
	const QBrush brush(fillColorStr.toUInt(nullptr, 16));
	QPen pen;
	m_pData->setPen(pen);
	QList<QGraphicsItem*> items = m_pScene->selectedItems();
	for (const auto item : items)
	{
		const auto shapeItem = dynamic_cast<KShapeBase*>(item);
		if(shapeItem == nullptr)
			continue;
		shapeItem->setPen(pen);
		shapeItem->setBrush(brush);
	}
}

void KEditPage::clearAllItems() const
{
	for (const auto item : m_pScene->items())
		m_pScene->removeItem(item);
}

void KEditPage::mouseMoveEvent(QMouseEvent* event)
{
	// 转换成scene的坐标
	m_endPoint = mapToScene(event->pos());
	// 如果是按下左键移动
	if(event->buttons() & Qt::LeftButton)
	{
		// 如果是画笔标志
		if (m_pData->getDrawFlag() == KGlobalData::KDrawFlag::PenFlag)
			m_points.append(m_endPoint);
		// 判断操作类型
		switch (m_opType)
		{
			case KOperationType::None: break;
			case KOperationType::Move:
				QGraphicsView::mouseMoveEvent(event);
				break;
			case KOperationType::Resize:
				{
					// TODO 封装成函数
					// 根据位置更改起始点和终止点
					// m_points = m_pCurrentResizeItem->mapToScene(m_pCurrentResizeItem->boundingRect());

					// QRectF rect =m_pCurrentResizeItem->mapRectToScene(m_pCurrentResizeItem->boundingRect());
					const qreal border_width = dynamic_cast<KShapeBase*>(m_pCurrentResizeItem)->getPen().widthF();
					qDebug() << "border_width" << border_width;
					QRectF rect = m_pCurrentResizeItem->boundingRect();

					QRectF rect2(rect.x() + border_width / 2, rect.y() + border_width / 2, 
						rect.width() - border_width, rect.height() - border_width);

					qDebug() << "rect  " << rect;
					qDebug() << "rect2  " << rect2;

					m_endPoint = m_pCurrentResizeItem->mapFromScene(m_endPoint);

					if (m_posType == KPositionType::TopLeft)
						rect2.setTopLeft(m_endPoint);
					else if (m_posType == KPositionType::TopRight)
						rect2.setTopRight(m_endPoint);
					else if (m_posType == KPositionType::BottomLeft)
						rect2.setBottomLeft(m_endPoint);
					else if (m_posType == KPositionType::Left)
						rect2.setLeft(m_endPoint.x());
					else if (m_posType == KPositionType::Right)
						rect2.setRight(m_endPoint.x());
					else if (m_posType == KPositionType::Top)
						rect2.setTop(m_endPoint.y());
					else if (m_posType == KPositionType::Bottom)
						rect2.setBottom(m_endPoint.y());

					m_pShape->setNewRect(rect2.topLeft(), rect2.bottomRight());

					break;
				}
			case KOperationType::New:
				{
					// 如果当前指向图形不为空
					if (m_pShape != nullptr)
					{
						m_pShape->setNewRect(m_startPoint, m_endPoint);
						m_pShape->setPainter(m_points);
					}
					break;
				}
			default: break;
		}
	}
	// 如果不是按下左键 且 当前为鼠标tool
	else if(m_pData->getDrawFlag() == KGlobalData::KDrawFlag::MouseFlag)
	{
		const QList<QGraphicsItem*> items = m_pScene->selectedItems();
		
		if (items.empty())
			// 没有选中任何图形
			m_mouseCursorShape = Qt::ArrowCursor;
		else if (items.size() == 1)
			// 只选中了一个图形
			m_mouseCursorShape = getSingleCursorShape(items.at(0));
		else
			// 选中了多个图形
			m_mouseCursorShape = Qt::ArrowCursor;
		setCursor(m_mouseCursorShape);
	}
	else
		QGraphicsView::mouseMoveEvent(event);
	emit mouseMovePoint(m_endPoint);
}

/**
 * \brief 获取单个图形的鼠标形状
 * \param item 
 * \return 
 */
Qt::CursorShape KEditPage::getSingleCursorShape(const QGraphicsItem* item)
{
	// 获取四个顶点
	const QPolygonF points = item->mapToScene(item->boundingRect());
	const QRectF rect(points.at(0), points.at(2));
	// 判断是否在图形里面
	if (rect.contains(m_endPoint))
	{
		// 计算两点之间的距离
		const qreal distanceTopLeft = qAbs(QLineF(rect.topLeft(), m_endPoint).length());
		const qreal distanceTopRight = qAbs(QLineF(rect.topRight(), m_endPoint).length());
		const qreal distanceBottomLeft = qAbs(QLineF(rect.bottomLeft(), m_endPoint).length());
		const qreal distanceBottomRight = qAbs(QLineF(rect.bottomRight(), m_endPoint).length());
		// 计算点到边之间的距离
		const qreal distanceLeft = qAbs(rect.left() - m_endPoint.x());
		const qreal distanceRight = qAbs(rect.right() - m_endPoint.x());
		const qreal distanceTop = qAbs(rect.top() - m_endPoint.y());
		const qreal distanceBottom = qAbs(rect.bottom() - m_endPoint.y());
		// 先判断是否在四个点
		if (distanceTopLeft < PRECISION)
		{
			m_posType = KPositionType::TopLeft;
			return Qt::SizeFDiagCursor;
		}
		if (distanceTopRight < PRECISION)
		{
			m_posType = KPositionType::TopRight;
			return Qt::SizeBDiagCursor;
		}
		if (distanceBottomLeft < PRECISION)
		{
			m_posType = KPositionType::BottomLeft;
			return Qt::SizeBDiagCursor;
		}
		if (distanceBottomRight < PRECISION)
		{
			m_posType = KPositionType::BottomRight;
			return Qt::SizeFDiagCursor;
		}
		if (distanceLeft < PRECISION)
		{
			m_posType = KPositionType::Left;
			return Qt::SizeHorCursor;
		}
		if (distanceRight < PRECISION) 
		{
			m_posType = KPositionType::Right;
			return Qt::SizeHorCursor;
		}
		if (distanceTop < PRECISION)
		{
			m_posType = KPositionType::Top;
			return Qt::SizeVerCursor;
		}
		if (distanceBottom < PRECISION)
		{
			m_posType = KPositionType::Bottom;
			return Qt::SizeVerCursor;
		}
		m_posType = KPositionType::Center;
		return Qt::SizeAllCursor;
	}
	m_posType = KPositionType::None;
	return Qt::ArrowCursor;
}

void KEditPage::mousePressEvent(QMouseEvent* event)
{
	switch (event->button())
	{
	case Qt::LeftButton:
		leftButtonPressed(event);
		break;
	default: 
		break;
	}
}

// 鼠标左键按下
void KEditPage::leftButtonPressed(QMouseEvent* event)
{
	m_startPoint = mapToScene(event->pos());
	const QGraphicsItem* item = m_pScene->itemAt(m_startPoint, QTransform());
	if (item != nullptr)
	{
		qDebug() << "item->mapToScene(item->boundingRect()) : " << item->mapToScene(item->boundingRect());
	}
	// 清除选中图形
	// m_pScene->clearSelection();

	// 创建图形
	m_pShape = KShapeFactory::createShape(m_pData->getDrawFlag(), m_startPoint, m_startPoint);
	if (m_pShape != nullptr)
	{
		m_opType = KOperationType::New;
		// 设置临时画笔
		m_pShape->setPen(m_tempPen);
		m_pShape->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
		// 设置当前图形选中状态
		const auto currItem = dynamic_cast<QGraphicsItem*>(m_pShape);
		if (currItem == nullptr)
			return;
		currItem->setSelected(true);
		m_pScene->addItem(currItem);
	}
	else if(m_pData->getDrawFlag() == KGlobalData::KDrawFlag::MouseFlag)
	{
		if(m_posType == KPositionType::Center)
		{
			m_opType = KOperationType::Move;
		}
		else if(m_posType != KPositionType::None)
		{
			const QList<QGraphicsItem*> items = m_pScene->selectedItems();
			if(items.size() == 1)
			{
				m_pCurrentResizeItem = items.at(0);
				m_pShape = dynamic_cast<KShapeBase*>(m_pCurrentResizeItem);
				m_opType = KOperationType::Resize;
			}
			else
				m_opType = KOperationType::None;
		}
		else
			m_opType = KOperationType::None;
	}
	else
		m_opType = KOperationType::None;

	if(m_pData->removable())
		QGraphicsView::mousePressEvent(event);
	emit mouseClicked(m_startPoint);
}

void KEditPage::mouseReleaseEvent(QMouseEvent* event)
{
	m_endPoint = mapToScene(event->pos());
	if (m_pShape != nullptr)
		updateSelectItems();
	// 清空QPainterPath的数据
	m_points.clear();
	m_pShape = nullptr;
	QGraphicsView::mouseReleaseEvent(event);
}

void KEditPage::keyPressEvent(QKeyEvent* event)
{
	if(event->key() == Qt::Key_Backspace)
	{
		qDebug() << "Key_Backspace Pressed";
		const QList<QGraphicsItem*> items = m_pScene->selectedItems();
		for(const auto item : items)
			m_pScene->removeItem(item);
	}
	QGraphicsView::keyPressEvent(event);
}

void KEditPage::keyReleaseEvent(QKeyEvent* event)
{
	QGraphicsView::keyReleaseEvent(event);
} 
