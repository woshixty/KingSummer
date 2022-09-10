#include "kqtnetworktest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KQtNetworkTest w;
    w.show();
    return a.exec();
}
