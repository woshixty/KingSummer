#include "wheeleventtest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WheelEventTest w;
    w.show();
    return a.exec();
}
