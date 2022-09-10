#include "wheeleventtest.h"

WheelEventTest::WheelEventTest(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

WheelEventTest::~WheelEventTest()
= default;

void WheelEventTest::wheelEvent(QWheelEvent* event)
{
    qDebug() << event->pos();
    if (!ui.textEdit->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        return;
    if (event->delta() > 0) // ���������ϻ���Զ��ʹ����
		qDebug() << "up";
    else // ���������»�������ʹ����
        qDebug() << "down";
}
