#pragma once

#include <QScrollArea>
#include <QWidget>
#include <QGraphicsView>
#include <qpainter.h>

#include "kglobaldata.h"
#include "kshape.h"
#include "kshapefactory.h"


class KSvgMainWindow final : public QScrollArea
{
	Q_OBJECT

public:
	KSvgMainWindow(QWidget *parent = nullptr);
	~KSvgMainWindow() override;

	void paintEvent(QPaintEvent* event) override;

	void initialization();

private slots:
	void validateCanvasParams();

private:
	QGraphicsView* m_pCanvas;
	int m_canvasX{};
	int m_canvasY{};
	int m_canvasWidth{};
	int m_canvasHeight{};
	QString m_canvasColor;
	qreal m_canvasRate = 1.0;
};
