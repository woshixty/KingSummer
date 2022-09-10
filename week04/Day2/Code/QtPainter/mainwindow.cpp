#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 设置窗口为白色背景
    setPalette(QPalette(Qt::white));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    // 如果是鼠标左键按下
    if (event->button() == Qt::LeftButton)
    {
        qDebug() << "鼠标左键按下";
    }
    // 如果是鼠标右键按下
    else if (event->button() == Qt::RightButton)
    {
        qDebug() << "鼠标右键按下";
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        qDebug() << "x坐标：" << event->globalX() << "---y坐标：" << event->globalY();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    qDebug() << "鼠标释放";
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent* event)
{
	if(event->button() == Qt::LeftButton)
	{
        qDebug() << "鼠标左键双击";
	}
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(rect(), Qt::AlignCenter, "Qt");
    // myDrawFilledRect();
}

void MainWindow::myDrawFilledRect()
{
	// 基本绘图
    // 创建QPainter对象
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::TextAntialiasing);

    // 绘图区宽度
	const int W = this->width();
    // 绘图区高度
	const int H = this->height();
    // 中间区域矩形框
	const QRect rect(W / 4, H / 4, W / 2, H / 2);

    // 设置画笔
    QPen pen;
    pen.setWidth(3); // 线宽
    pen.setColor(Qt::red); // 划线颜色

    //Qt::NoPen,Qt::SolidLine, Qt::DashLine, Qt::DotLine,Qt::DashDotLine,Qt::DashDotDotLine,Qt::CustomDashLine
    pen.setStyle(Qt::SolidLine);// 线的类型，实线、虚线等

    //Qt::FlatCap, Qt::SquareCap,Qt::RoundCap
    pen.setCapStyle(Qt::FlatCap);// 线端点样式

    //Qt::MiterJoin,Qt::BevelJoin,Qt::RoundJoin,Qt::SvgMiterJoin
    pen.setJoinStyle(Qt::BevelJoin);// 线的连接点样式
    painter.setPen(pen);

    // 设置画刷
    //QPixmap texturePixmap(":images/images/texture.jpg");
    QBrush  brush;
    brush.setColor(Qt::yellow); // 画刷颜色
    brush.setStyle(Qt::SolidPattern); // 画刷填充样式
    //brush.setStyle(Qt::TexturePattern); // 画刷填充样式
    //brush.setTexture(texturePixmap); // 设置材质图片
    painter.setBrush(brush);

    //Qt::NoBrush,Qt::SolidPattern,Qt::Dense1Pattern,Qt::Dense2Pattern,..,Qt::Dense7Pattern,Qt::HorPattern
    //Qt::VerPattern, Qt::CrossPattern, Qt::BDiagPattern,Qt::FDiagPattern,Qt::DiagCrossPattern,
    //Qt::LinearGradientPattern,Qt::ConicalGradientPattern,Qt::RadialGradientPattern
    //Qt::TexturePattern

    // 绘图
    painter.drawRect(rect);
}

void MainWindow::myDrawTextureRect()
{
}

void MainWindow::myDrawGradient()
{
}

void MainWindow::total()
{
}

void MainWindow::myDrawShape()
{
}
