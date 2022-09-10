#include "ksvgmainwindow.h"

KSvgMainWindow::KSvgMainWindow(QWidget *parent)
	: QScrollArea(parent)
{
	initialization();

	setStyleSheet("background-color: #3f3f3c");
	setFrameShape(QFrame::NoFrame);

	m_pCanvas = new QGraphicsView(this);
	m_pCanvas->setStyleSheet(QString("background-color: #%1").arg(m_canvasColor));
	m_pCanvas->setFrameShape(QFrame::NoFrame);
	m_pCanvas->setGeometry(m_canvasX, m_canvasY, m_canvasWidth, m_canvasWidth);
}

KSvgMainWindow::~KSvgMainWindow()
= default;

void KSvgMainWindow::paintEvent(QPaintEvent* event)
{
	//KShape* shape = KShapeFactory::createShape(KGlobalData::KDrawFlag::RectFlag);
	//shape->setStartPoint(QPoint(40, 40));
	//shape->setEndPoint(QPoint(100, 100));
	///*shape->drawShape(m_pCanvas);*/
	//QPainter painter(this);
	//QPen pen;
	//// 设置画笔的颜色
	//pen.setColor(QColor(79, 128, 255));
	//// 设置线宽
	//pen.setWidth(3000);
	//painter.setPen(pen);

	//// 绘制矩形
	//painter.drawRect(QRect(shape->getStartPoint(), shape->getEndPoint()));
}

void KSvgMainWindow::initialization()
{
	m_canvasWidth = KGlobalData::getGlobalDataInstance()->getCanvasWidth();
	m_canvasHeight = KGlobalData::getGlobalDataInstance()->getCanvasHeight();
	m_canvasColor = KGlobalData::getGlobalDataInstance()->getCanvasColor();
	m_canvasX = 0;
	m_canvasY = 0;
}

void KSvgMainWindow::validateCanvasParams()
{
	// 重新设置窗口大小
	this->resize(m_canvasWidth, m_canvasHeight);

	// 重新设置窗口背景颜色
	m_pCanvas->setStyleSheet(QString("background-color:#%1").arg(m_canvasColor));
}
