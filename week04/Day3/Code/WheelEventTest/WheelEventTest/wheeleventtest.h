#pragma once

#include "ui_wheeleventtest.h"
#include <QWheelEvent>
#include <QDebug>

class WheelEventTest final : public QMainWindow
{
    Q_OBJECT

public:
    WheelEventTest(QWidget *parent = nullptr);
    ~WheelEventTest() override;
    void wheelEvent(QWheelEvent* event) override;

private:
    Ui::WheelEventTestClass ui{};
};
