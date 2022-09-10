#include "qgraphicspathitemtest.h"
#include <QtWidgets/QApplication>
#include <QtWidgets>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("м╪пн©Р╪э");

    QGraphicsView view;

    int x = -200, y = -200;
    int w = 400, h = 400;

    QGraphicsScene scene(x, y, w, h);
    scene.setBackgroundBrush(QBrush(qRgb(173, 241, 174)));

    QPen pen(qRgb(140, 159, 141));
    pen.setWidth(0);

    for (int i = x + 20; i < x + w; i += 20) {
        scene.addLine(x, i, x + w, i, pen);
        scene.addLine(i, y, i, y + h, pen);
    }

    QGraphicsItemGroup xAxis;
    scene.addItem(&xAxis);
    xAxis.addToGroup(new QGraphicsLineItem(x, 0, x + w, 0));
    xAxis.addToGroup(new QGraphicsLineItem(x + w - 10, -10, x + w, -1));
    xAxis.addToGroup(new QGraphicsLineItem(x + w - 10, 10, x + w, 1));

    QGraphicsItemGroup yAxis;
    scene.addItem(&yAxis);

    yAxis.addToGroup(new QGraphicsLineItem(0, y, 0, y + h));
    yAxis.addToGroup(new QGraphicsLineItem(-1, y + h, -10, y + h - 10));
    yAxis.addToGroup(new QGraphicsLineItem(1, y + h, 10, y + h - 10));

    auto* gi = new QGraphicsPathItem;
    gi->setFlag(QGraphicsItem::ItemIsMovable);
    QPainterPath path;
    path.moveTo(0, 0);
    path.cubicTo(120, -20, 60, 100, 120, 80);
    gi->setPath(path);

    QLinearGradient gLg;
    gLg.setStart(0, 0);
    gLg.setFinalStop(100, 100);
    gLg.setColorAt(0, qRgb(221, 186, 68));
    gLg.setColorAt(1, qRgb(221, 226, 68));
    gi->setPen(pen);
    gi->setBrush(gLg);
    gi->setOpacity(0.8);

    gi->moveBy(-60, -50);

    scene.addItem(gi);

    view.setScene(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setWindowFlag(Qt::WindowMinMaxButtonsHint, false);
    view.show();
    view.setWindowOpacity(0.8);
    return a.exec();
}

