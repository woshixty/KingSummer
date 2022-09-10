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
    if (event->delta() > 0) // 当滚轮向上滑，远离使用者
		qDebug() << "up";
    else // 当滚轮向下滑，靠近使用者
        qDebug() << "down";
}
