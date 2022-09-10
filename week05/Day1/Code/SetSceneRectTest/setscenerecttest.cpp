#include "setscenerecttest.h"

SetSceneRectTest::SetSceneRectTest(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	ui.graphicsView->setStyleSheet("QGraphicsView{background-color: rgb(80, 80, 80);}");

	//m_pMyScene = new QGraphicsScene(ui.graphicsView);
	//ui.graphicsView->setScene(m_pMyScene);

 //   const QRect viewRect = ui.graphicsView->geometry();
	//m_pPixmapItem = new QGraphicsPixmapItem(QPixmap(":/SetSceneRectTest/image/1.jpg"));

	//// ������ԭ��������ʾ���ڵ����Ͻ�
	//m_pMyScene->setSceneRect(1, 1, viewRect.width() - 2, viewRect.height() - 2);
	//// ��ɫ���������������
	//m_pMyScene->addRect(1, 1, viewRect.width() - 4, viewRect.height() - 4, QPen(Qt::red));
	//// �趨ͼƬ�ڳ����е�����
	//m_pPixmapItem->setPos((viewRect.width() - m_pPixmapItem->pixmap().width()) / 2,
	//                      (viewRect.height() - m_pPixmapItem->pixmap().height()) / 2);
	//m_pMyScene->addItem(m_pPixmapItem);


	m_pMyScene = new QGraphicsScene(ui.graphicsView);
	ui.graphicsView->setScene(m_pMyScene);
    const QRect viewRect = ui.graphicsView->geometry();
	m_pPixmapItem = new QGraphicsPixmapItem(QPixmap(":/SetSceneRectTest/image/1.jpg"));

	// ������ԭ��������ʾ���ڵ����ĵ�
	m_pMyScene->setSceneRect(-viewRect.width() / 2, -viewRect.height() / 2, viewRect.width() - 2,
	                         viewRect.height() - 2);
	// ��ɫ���������������
	m_pMyScene->addRect(-viewRect.width() / 2, -viewRect.height() / 2, viewRect.width() - 4, viewRect.height() - 4,
	                    QPen(Qt::red));
	// �趨ͼƬ�ڳ����е�����
	m_pPixmapItem->setPos(-m_pPixmapItem->pixmap().width() / 2,
		-m_pPixmapItem->pixmap().height() / 2);
	m_pMyScene->addItem(m_pPixmapItem);
}

SetSceneRectTest::~SetSceneRectTest()
{}
