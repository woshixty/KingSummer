#pragma once

#include <QGraphicsView>
#include <QLabel>
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QColor>
#include <QPen>

#include "kglobaldata.h"

class KEditPage final : public QGraphicsView
{
	Q_OBJECT

public:
	KEditPage(QWidget *parent);
	~KEditPage() override;

	void setViewCord(QLabel* lab) { m_pLabViewCord = lab; }
	void setSceneCord(QLabel* lab) { m_pLabSceneCord = lab; }
	void setItemCord(QLabel* lab) { m_pLabItemCord = lab; }
	
	void iniGraphicsSystem() const;

	void drawItem() const;
	void drawItem(QGraphicsItem* item) const;

	// 进入组件
	void enterEvent(QEvent* event) override;
	// 离开组件
	void leaveEvent(QEvent* event) override;

protected:
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void leftButtonPressed(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event) override;

signals:
	void mouseMovePoint(QPoint point);
	void mouseClicked(QPoint point);

private slots:
	void changeSceneColor() const;

private:
	QLabel* m_pLabViewCord{};
	QLabel* m_pLabSceneCord{};
	QLabel* m_pLabItemCord{};

	QPoint m_startPoint;
	QPoint m_endPoint;

	QGraphicsScene* scene{};

	KGlobalData* m_pData = KGlobalData::getGlobalDataInstance();

	QBrush m_brush;
	QPen m_pen;
	QColor m_color;
};
