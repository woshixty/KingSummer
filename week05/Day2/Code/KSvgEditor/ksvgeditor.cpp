#include "ksvgeditor.h"

KSvgEditor::KSvgEditor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    initializePage();
    initializeConn();
}

KSvgEditor::~KSvgEditor()
= default;

void KSvgEditor::initializePage()
{
    m_pMenuBar = new KMenuBar(this);
    m_pMenuBar->setObjectName(QStringLiteral("menuBar"));
    m_pMenuBar->setGeometry(QRect(0, 0, 807, 23));
    setMenuBar(m_pMenuBar);

    m_pToolBar = new KToolBar(this);
    m_pToolBar->setObjectName(QStringLiteral("toolBar"));
    m_pToolBar->setMaximumSize(QSize(50, 16777215));
    m_pToolBar->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
    ui.horizontalLayout->addWidget(m_pToolBar);

    m_pEditPage = new KEditPage(this);
    m_pEditPage->setObjectName(QStringLiteral("editPage"));
    m_pEditPage->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
    ui.horizontalLayout->addWidget(m_pEditPage);

    m_pParamBar = new KParamBar(this);
    m_pParamBar->setObjectName(QStringLiteral("paramBar"));
    m_pParamBar->setStyleSheet(QStringLiteral("background-color: rgb(255, 85, 127);"));
    ui.horizontalLayout->addWidget(m_pParamBar);

    m_pLabViewCord= new QLabel(QStringLiteral("View ���꣺"));
    m_pLabViewCord->setMinimumWidth(150);
    ui.statusBar->addWidget(m_pLabViewCord);

    m_pLabSceneCord = new QLabel(QStringLiteral("Scene ���꣺"));
    m_pLabSceneCord->setMinimumWidth(150);
    ui.statusBar->addWidget(m_pLabSceneCord);

    m_pLabItemCord = new QLabel(QStringLiteral("Item ���꣺"));
    m_pLabItemCord->setMinimumWidth(150);
    ui.statusBar->addWidget(m_pLabItemCord);
}

void KSvgEditor::initializeConn() const
{
    connect(m_pEditPage, SIGNAL(mouseMovePoint(QPoint)),
        this, SLOT(on_mouseMovePoint(QPoint)));
    connect(m_pEditPage, SIGNAL(mouseClicked(QPoint)),
        this, SLOT(on_mouseClicked(QPoint)));

    QList<KParamBaseBox*> paramBoxes = m_pParamBar->getParamBoxes();
    for (const auto paramBox : paramBoxes)
    {
        switch (paramBox->getFlag())
    	{
        	case KGlobalData::KParamFlag::CanvasWidth:
                connect(paramBox, SIGNAL(canvasWidthChanged()),
                    this, SLOT(on_canvasWidthChanged()));
                break;
	        case KGlobalData::KParamFlag::CanvasHeight: 
                connect(paramBox, SIGNAL(canvasHeightChanged()),
                    this, SLOT(on_canvasHeightChanged()));
                break;
	        case KGlobalData::KParamFlag::CanvasScaling: 
                connect(paramBox, SIGNAL(canvasScalingChanged()),
                    this, SLOT(on_canvasScalingChanged()));
                break;
	        case KGlobalData::KParamFlag::CanvasColor: 
                connect(paramBox, SIGNAL(canvasColorChanged()),
                    this, SLOT(on_canvasColorChanged()));
                break;
	        case KGlobalData::KParamFlag::BorderWidth: 
                connect(paramBox, SIGNAL(borderWidthChanged()),
                    this, SLOT(on_borderWidthChanged()));
                break;
	        case KGlobalData::KParamFlag::BorderStyle: 
                connect(paramBox, SIGNAL(borderStyleChanged()),
                    this, SLOT(on_borderStyleChanged()));
                break;
	        case KGlobalData::KParamFlag::BorderColor:
                connect(paramBox, SIGNAL(borderColorChanged()),
                    this, SLOT(on_borderColorChanged()));
                break;
	        case KGlobalData::KParamFlag::FillColor: 
                connect(paramBox, SIGNAL(fillColorChanged()),
                    this, SLOT(on_fillColorChanged()));
                break;
    	}
    }
}

void KSvgEditor::on_mouseMovePoint(QPoint point) const
{
    // ����ƶ��¼���point�� GraphicsView�����꼴��������
    m_pLabViewCord->setText(QString::asprintf("View ���꣺%d, %d", point.x(), point.y()));
    // ת����Scene����
    const QPointF pointScene = m_pEditPage->mapToScene(point);
    m_pLabSceneCord->setText(QString::asprintf("Scene ���꣺%.0f, %.0f", pointScene.x(), pointScene.y()));
}

void KSvgEditor::on_mouseClicked(QPoint point) const
{
 //   // ��굥���¼�
 //   // ת����Scene����
 //   const QPointF pointScene = m_pEditPage->mapToScene(point);
 //   const QGraphicsItem* item = nullptr;
 //   // ��ȡ����µĻ�ͼ��
 //   item = scene->itemAt(pointScene, m_pEditPage->transform());
 //   // �л�ͼ��
	//if (item != nullptr)
 //   {
 //       // ת��Ϊ��ͼ��ľֲ�����
	//    const QPointF pointItem = item->mapFromScene(pointScene);
 //       m_pLabItemCord->setText(QString::asprintf("Item ���꣺%.0f, %.0f", pointItem.x(), pointItem.y()));
 //   }
}

void KSvgEditor::on_canvasWidthChanged()
{
    qDebug() << "KSvgEditor::on_canvasWidthChanged" << m_pData->canvasWidth() << endl;
}

void KSvgEditor::on_canvasHeightChanged()
{
    qDebug() << "KSvgEditor::on_canvasHeightChanged" << m_pData->canvasHeight() << endl;
}

void KSvgEditor::on_canvasScalingChanged()
{
    qDebug() << "KSvgEditor::on_canvasScalingChanged" << m_pData->getCanvasScaling() << endl;
}

void KSvgEditor::on_canvasColorChanged()
{
    qDebug() << "KSvgEditor::on_canvasColorChanged" << m_pData->getCanvasColor() << endl;
}

void KSvgEditor::on_borderWidthChanged()
{
    qDebug() << "KSvgEditor::on_borderWidthChanged" << m_pData->getBorderWidth() << endl;
}

void KSvgEditor::on_borderStyleChanged()
{
    qDebug() << "KSvgEditor::on_borderStyleChanged" << static_cast<int>(m_pData->getBorderStyle()) << endl;
}

void KSvgEditor::on_borderColorChanged()
{
    qDebug() << "KSvgEditor::on_borderColorChanged" << m_pData->getBorderColor() << endl;
}

void KSvgEditor::on_fillColorChanged()
{
    qDebug() << "KSvgEditor::on_fillColorChanged" << m_pData->getFillColor() << endl;
}
