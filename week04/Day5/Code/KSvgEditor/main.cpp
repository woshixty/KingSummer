#include "ksvgeditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    KSvgEditor w;
    w.show();
    return QApplication::exec();
}
