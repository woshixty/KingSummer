#pragma once

#include <QScrollArea>
#include <QWidget>
#include <QGraphicsView>
#include <qpainter.h>


class KSvgMainWindow : public QScrollArea
{
	Q_OBJECT

public:
	KSvgMainWindow(QWidget *parent = nullptr);
	~KSvgMainWindow();

	virtual void paintEvent(QPaintEvent* event) override;


private:
	QGraphicsView* m_pCanvas;
	int m_canvasX;
	int m_canvasY;
	int m_canvsWidth;
	int m_canvasHeight;
	qreal m_canvasRate = 1.0;
};
