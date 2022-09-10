#pragma once

#include <QGraphicsView>
#include <QLabel>
#include <QMouseEvent>
#include <QPainterPath>
#include <QPolygonF>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QColor>
#include <QPen>

#include "kglobaldata.h"
#include "krect.h"

class KEditPage final : public QGraphicsView
{
	Q_OBJECT

public:
	enum class KPositionType
	{
		None = 0,
		Center,
		Top,
		Bottom,
		Left,
		Right,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
	};

	enum class KOperationType
	{
		None = 0,
		Move,
		Resize,
		New,
	};

	constexpr static qreal PRECISION = 10.0;

	KEditPage(QWidget *parent);
	~KEditPage() override;

	void setViewCord(QLabel* lab) { m_pLabViewCord = lab; }
	void setSceneCord(QLabel* lab) { m_pLabSceneCord = lab; }
	void setItemCord(QLabel* lab) { m_pLabItemCord = lab; }

	void enterEvent(QEvent* event) override;
	void leaveEvent(QEvent* event) override;

	void updateSceneBackground() const;
	void updateSelectItems() const;
	void clearAllItems() const;

	QString m_colorStr;

protected:
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;

	void leftButtonPressed(QMouseEvent* event);

	Qt::CursorShape getSingleCursorShape(const QGraphicsItem* item);

signals:
	void mouseMovePoint(QPointF point);
	void mouseClicked(QPointF point);

private:
	QLabel* m_pLabViewCord{};
	QLabel* m_pLabSceneCord{};
	QLabel* m_pLabItemCord{};

	QPointF m_startPoint;
	QPointF m_endPoint;

	QPointF m_startPointMin;
	QPointF m_endPointMax;

	QPen m_tempPen = QColor(128, 128, 128);

	QGraphicsScene* m_pScene{};
	KShapeBase* m_pShape{};
	QPolygonF m_points;

	KGlobalData* m_pData = KGlobalData::getGlobalDataInstance();
	KPositionType m_posType = KPositionType::None;
	KOperationType m_opType = KOperationType::None;
	QGraphicsItem* m_pCurrentResizeItem = nullptr;
	Qt::CursorShape m_mouseCursorShape = Qt::ArrowCursor;
};
