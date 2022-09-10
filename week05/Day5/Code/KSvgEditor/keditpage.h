// -------------------------------------------------------
// keditpage.h
// 创建者： xie tingyu
// 创建时间： 2022/08/09
// 功能描述： 图形绘制页面类，继承自QGraphicsView
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_EDITPAGE_H_
#define _K_EDITPAGE_H_

#include "kglobaldata.h"
#include "ksvgwriter.h"

#include <QGraphicsView>
#include <QLabel>
#include <QMouseEvent>
#include <QPainterPath>
#include <QPolygonF>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QColor>
#include <QPen>

class KEditPage final : public QGraphicsView
{
	Q_OBJECT

public:
	// 鼠标所在位置
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

	// 操作类型
	enum class KOperationType
	{
		None = 0,
		Move,
		Resize,
		New,
	};

	// 鼠标距离精度（例如当鼠标距离当前选中图形精度为10像素点时改变形状）
	constexpr static qreal PRECISION = 10.0;

	KEditPage(QWidget* parent = nullptr);
	~KEditPage() override;

	void enterEvent(QEvent* event) override;
	void leaveEvent(QEvent* event) override;

	void updateSceneBackground() const;
	void updateSelectItems() const;
	void updateSceneSize() const;

protected:
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;

	// 左键按下处理函数
	void leftButtonPressed(QMouseEvent* event);
	// 选中一个图形时鼠标形状随位置的变换
	Qt::CursorShape getSingleCursorShape(const QGraphicsItem* item);

signals:
	void mouseMovePoint(QPointF point);
	void mouseClicked(QPointF point);

private slots:
	void clearAllItems() const;
	void newSVGFile();
	void saveSVGFile();
	void openSVGFile();
	void exportPngAction();

private:
	QPointF m_startPoint;
	QPointF m_endPoint;

	QPointF m_startPointMin;
	QPointF m_endPointMax;

	QPen m_tempPen = QColor(128, 128, 128);

	QGraphicsScene* m_pScene{};
	QPolygonF m_points;

	KGlobalData* m_pData = KGlobalData::getGlobalDataInstance();
	KShapeBase* m_pShape{};
	KPositionType m_posType = KPositionType::None;
	KOperationType m_opType = KOperationType::None;
	KSvgWriter m_svgWriter;

	Qt::CursorShape m_mouseCursorShape = Qt::ArrowCursor;
};

#endif
