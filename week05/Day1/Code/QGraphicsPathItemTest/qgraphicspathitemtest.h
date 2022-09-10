#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qgraphicspathitemtest.h"

class QGraphicsPathItemTest : public QMainWindow
{
    Q_OBJECT

public:
    QGraphicsPathItemTest(QWidget *parent = nullptr);
    ~QGraphicsPathItemTest();

private:
    Ui::QGraphicsPathItemTestClass ui;
};
