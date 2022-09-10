#include "ksvgmainwindow.h"

KSvgMainWindow::KSvgMainWindow(QWidget *parent)
	: QScrollArea(parent)
{
	setStyleSheet("background-color: #3f3f3c");
	setFrameShape(QFrame::NoFrame);

	m_pCanvas = new QGraphicsView(this);
	m_pCanvas->setStyleSheet("background-color: #FFFFFF");
	m_pCanvas->setFrameShape(QFrame::NoFrame);
}

KSvgMainWindow::~KSvgMainWindow()
{}

void KSvgMainWindow::paintEvent(QPaintEvent* event)
{
	m_canvasX = width() / 2 - width() * 0.9 / 2;
	m_canvasY = height() / 2 - height() * 0.9 / 2;
	m_pCanvas->setGeometry(m_canvasX, m_canvasY, width() * 0.9, height() * 0.9);
	QScrollArea::paintEvent(event);
}
