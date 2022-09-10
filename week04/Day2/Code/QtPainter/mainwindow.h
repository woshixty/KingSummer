#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QKeyEvent>

// ��ָ���֧��VS����
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
    // ������¼�
    void mousePressEvent(QMouseEvent* event) override;
    // ����ƶ��¼�
    void mouseMoveEvent(QMouseEvent* event) override;
    // ����ͷ��¼�
    void mouseReleaseEvent(QMouseEvent* event) override;
    // ���˫���¼�
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
    // ���ƻ���ͼ��
    void myDrawShape();
};

#endif // MAINWINDOW_H
