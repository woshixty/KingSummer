#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // ���ô���Ϊ��ɫ����
    setPalette(QPalette(Qt::white));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    // ���������������
    if (event->button() == Qt::LeftButton)
    {
        qDebug() << "����������";
    }
    // ���������Ҽ�����
    else if (event->button() == Qt::RightButton)
    {
        qDebug() << "����Ҽ�����";
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        qDebug() << "x���꣺" << event->globalX() << "---y���꣺" << event->globalY();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    qDebug() << "����ͷ�";
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent* event)
{
	if(event->button() == Qt::LeftButton)
	{
        qDebug() << "������˫��";
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
	// ������ͼ
    // ����QPainter����
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::TextAntialiasing);

    // ��ͼ�����
	const int W = this->width();
    // ��ͼ���߶�
	const int H = this->height();
    // �м�������ο�
	const QRect rect(W / 4, H / 4, W / 2, H / 2);

    // ���û���
    QPen pen;
    pen.setWidth(3); // �߿�
    pen.setColor(Qt::red); // ������ɫ

    //Qt::NoPen,Qt::SolidLine, Qt::DashLine, Qt::DotLine,Qt::DashDotLine,Qt::DashDotDotLine,Qt::CustomDashLine
    pen.setStyle(Qt::SolidLine);// �ߵ����ͣ�ʵ�ߡ����ߵ�

    //Qt::FlatCap, Qt::SquareCap,Qt::RoundCap
    pen.setCapStyle(Qt::FlatCap);// �߶˵���ʽ

    //Qt::MiterJoin,Qt::BevelJoin,Qt::RoundJoin,Qt::SvgMiterJoin
    pen.setJoinStyle(Qt::BevelJoin);// �ߵ����ӵ���ʽ
    painter.setPen(pen);

    // ���û�ˢ
    //QPixmap texturePixmap(":images/images/texture.jpg");
    QBrush  brush;
    brush.setColor(Qt::yellow); // ��ˢ��ɫ
    brush.setStyle(Qt::SolidPattern); // ��ˢ�����ʽ
    //brush.setStyle(Qt::TexturePattern); // ��ˢ�����ʽ
    //brush.setTexture(texturePixmap); // ���ò���ͼƬ
    painter.setBrush(brush);

    //Qt::NoBrush,Qt::SolidPattern,Qt::Dense1Pattern,Qt::Dense2Pattern,..,Qt::Dense7Pattern,Qt::HorPattern
    //Qt::VerPattern, Qt::CrossPattern, Qt::BDiagPattern,Qt::FDiagPattern,Qt::DiagCrossPattern,
    //Qt::LinearGradientPattern,Qt::ConicalGradientPattern,Qt::RadialGradientPattern
    //Qt::TexturePattern

    // ��ͼ
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
