#include "keditpage.h"

#include <qdialog.h>
#include <QFileDialog>
#include <QMessageBox>

#include "kglobaldata.h"
#include "kshapefactory.h"

KEditPage::KEditPage(QWidget *parent)
	: QGraphicsView(parent)
{
	// ��������Ƿ��׷��
	setMouseTracking(true);
	// �϶���꽫������Ƥ��ļ�����״����Ƥ��ǵ�������Ŀ����ѡ��
	setDragMode(RubberBandDrag);
	// �����³���
	m_pScene = new QGraphicsScene(this);
	setScene(m_pScene);
	updateSceneSize();
	// ������ʱ����Ϊ����
	m_tempPen.setStyle(Qt::DotLine);
}

KEditPage::~KEditPage()
{
	clearAllItems();
}

void KEditPage::enterEvent(QEvent* event)
{
	// TODO: �Ż�Swith���
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
	// ����brush��pen
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

void KEditPage::updateSceneSize() const
{
	// TODO ��������е�ͼ�Σ�������
	clearAllItems();
	// �̶�����view��scene���λ��
	m_pScene->setSceneRect(0, 0, m_pData->canvasWidth(), m_pData->canvasHeight());
	m_pScene->addRect(0, 0, m_pData->canvasWidth(), m_pData->canvasHeight());
}

void KEditPage::clearAllItems() const
{
	for (const auto item : m_pScene->items())
	{
		m_pScene->removeItem(item);
		delete item;
	}
}

void KEditPage::newSVGFile()
{
	saveSVGFile();
	clearAllItems();
	updateSceneSize();
}

void KEditPage::saveSVGFile()
{
	const QString filePath = QFileDialog::getSaveFileName(nullptr, "Save SVG", "", "SVG files (*.svg)");
	if (filePath == "")
		return;
	m_svgWriter.initFrame();
	m_svgWriter.initBackground();
	QList<KShapeBase*> list;
	for (const auto item : m_pScene->items())
		list.append(dynamic_cast<KShapeBase*>(item));
	m_svgWriter.initObject(list);
	m_svgWriter.save(filePath);
	QMessageBox::information(this, "success", "save success!");
}

void KEditPage::openSVGFile()
{
}

void KEditPage::exportPngAction()
{
}

void KEditPage::mouseMoveEvent(QMouseEvent* event)
{
	// ת����scene������
	m_endPoint = mapToScene(event->pos());
	// ����ǰ�������ƶ�
	if(event->buttons() & Qt::LeftButton)
	{
		// ����ǻ��ʱ�־
		if (m_pData->getDrawFlag() == KGlobalData::KDrawFlag::PenFlag)
			m_points.append(m_endPoint);
		// �жϲ�������
		switch (m_opType)
		{
			case KOperationType::None:
			case KOperationType::Move:
				QGraphicsView::mouseMoveEvent(event);
				break;
			case KOperationType::Resize:
			{
				// TODO ��װ�ɺ���
				// ����λ�ø�����ʼ�����ֹ��
				if(m_pShape == nullptr)
					return;
				QRectF rect = m_pShape->getRectF();
				if (m_posType == KPositionType::TopLeft)
					rect.setTopLeft(m_endPoint);
				else if (m_posType == KPositionType::TopRight)
					rect.setTopRight(m_endPoint);
				else if (m_posType == KPositionType::BottomLeft)
					rect.setBottomLeft(m_endPoint);
				else if (m_posType == KPositionType::Left)
					rect.setLeft(m_endPoint.x());
				else if (m_posType == KPositionType::Right)
					rect.setRight(m_endPoint.x());
				else if (m_posType == KPositionType::Top)
					rect.setTop(m_endPoint.y());
				else if (m_posType == KPositionType::Bottom)
					rect.setBottom(m_endPoint.y());
				m_pShape->setNewRect(rect.topLeft(), rect.bottomRight());
				break;
			}
			case KOperationType::New:
			{
				// �����ǰָ��ͼ�β�Ϊ��
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
	// ������ǰ������ �� ��ǰΪ���tool
	else if(m_pData->getDrawFlag() == KGlobalData::KDrawFlag::MouseFlag)
	{
		const QList<QGraphicsItem*> items = m_pScene->selectedItems();
		
		if (items.empty())
			// û��ѡ���κ�ͼ��
			m_mouseCursorShape = Qt::ArrowCursor;
		else if (items.size() == 1)
			// ֻѡ����һ��ͼ��
			m_mouseCursorShape = getSingleCursorShape(items.at(0));
		else
			// ѡ���˶��ͼ��
			m_mouseCursorShape = Qt::ArrowCursor;
		setCursor(m_mouseCursorShape);
	}
	else
		QGraphicsView::mouseMoveEvent(event);
	emit mouseMovePoint(m_endPoint);
}

Qt::CursorShape KEditPage::getSingleCursorShape(const QGraphicsItem* item)
{
	// ��ȡ�ĸ�����
	const QPolygonF points = item->mapToScene(item->boundingRect());
	const QRectF rect(points.at(0), points.at(2));
	// �ж��Ƿ���ͼ������
	if (rect.contains(m_endPoint))
	{
		// ��������֮��ľ���
		const qreal distanceTopLeft = qAbs(QLineF(rect.topLeft(), m_endPoint).length());
		const qreal distanceTopRight = qAbs(QLineF(rect.topRight(), m_endPoint).length());
		const qreal distanceBottomLeft = qAbs(QLineF(rect.bottomLeft(), m_endPoint).length());
		const qreal distanceBottomRight = qAbs(QLineF(rect.bottomRight(), m_endPoint).length());
		// ����㵽��֮��ľ���
		const qreal distanceLeft = qAbs(rect.left() - m_endPoint.x());
		const qreal distanceRight = qAbs(rect.right() - m_endPoint.x());
		const qreal distanceTop = qAbs(rect.top() - m_endPoint.y());
		const qreal distanceBottom = qAbs(rect.bottom() - m_endPoint.y());
		// ���ж��Ƿ����ĸ���
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

void KEditPage::leftButtonPressed(QMouseEvent* event)
{
	m_startPoint = mapToScene(event->pos());

	// ����ͼ��
	m_pShape = KShapeFactory::createShape(m_pData->getDrawFlag(), m_startPoint, m_startPoint);
	if (m_pShape != nullptr)
	{
		m_opType = KOperationType::New;
		// ������ʱ����
		m_pShape->setPen(m_tempPen);
		m_pShape->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
		// ���õ�ǰͼ��ѡ��״̬
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
				m_pShape = dynamic_cast<KShapeBase*>(items.at(0));
				m_opType = KOperationType::Resize;
			}
			else
			{
				m_opType = KOperationType::None;
			}
		}
		else
		{
			m_opType = KOperationType::None;
		}
	}
	else
	{
		m_opType = KOperationType::None;
	}

	if(m_pData->removable() && (m_opType == KOperationType::None || m_opType == KOperationType::Move))
		QGraphicsView::mousePressEvent(event);
	emit mouseClicked(m_startPoint);
}

void KEditPage::mouseReleaseEvent(QMouseEvent* event)
{
	m_endPoint = mapToScene(event->pos());
	if (m_pShape != nullptr)
		updateSelectItems();
	// ���QPainterPath������
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
