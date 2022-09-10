#pragma once

#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "ui_setscenerecttest.h"

class SetSceneRectTest : public QMainWindow
{
    Q_OBJECT

public:
    SetSceneRectTest(QWidget *parent = nullptr);
    ~SetSceneRectTest();

private:
    Ui::SetSceneRectTestClass ui{};
    QGraphicsScene* m_pMyScene;
    QGraphicsPixmapItem* m_pPixmapItem;
};
