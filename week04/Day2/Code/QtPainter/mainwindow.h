#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QKeyEvent>

// 该指令仅支持VS环境
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

namespace Ui {
class MainWindow;
}

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    // 鼠标点击事件
    void mousePressEvent(QMouseEvent* event) override;
    // 鼠标移动事件
    void mouseMoveEvent(QMouseEvent* event) override;
    // 鼠标释放事件
    void mouseReleaseEvent(QMouseEvent* event) override;
    // 鼠标双击事件
    void mouseDoubleClickEvent(QMouseEvent* event) override;

    void keyPressEvent(QKeyEvent* event) override;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Ui::MainWindow *ui;
    void myDrawFilledRect();
    void myDrawTextureRect();
    void myDrawGradient();
    void total();
    // 绘制基本图形
    void myDrawShape();
};

#endif // MAINWINDOW_H
