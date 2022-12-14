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
    m_pToolBar->setStyleSheet(QStringLiteral("background-color: rgb(47, 47, 47);"));
    ui.horizontalLayout->addWidget(m_pToolBar);

    m_pEditPage = new KEditPage(this);
    m_pEditPage->setObjectName(QStringLiteral("editPage"));
    m_pEditPage->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
    ui.horizontalLayout->addWidget(m_pEditPage);

    m_pParamBar = new KParamBar(this);
    m_pParamBar->setObjectName(QStringLiteral("paramBar"));
    m_pParamBar->setStyleSheet(QStringLiteral("background-color: rgb(255, 85, 127);"));
    ui.horizontalLayout->addWidget(m_pParamBar);

    m_pLabViewCord= new QLabel(QStringLiteral("View Pos "));
    m_pLabViewCord->setMinimumWidth(150);
    ui.statusBar->addWidget(m_pLabViewCord);

    m_pLabSceneCord = new QLabel(QStringLiteral("Scene Pos "));
    m_pLabSceneCord->setMinimumWidth(150);
    ui.statusBar->addWidget(m_pLabSceneCord);

    m_pLabItemCord = new QLabel(QStringLiteral("Item Pos "));
    m_pLabItemCord->setMinimumWidth(150);
    ui.statusBar->addWidget(m_pLabItemCord);
}

void KSvgEditor::initializeConn() const
{
    connect(m_pEditPage, SIGNAL(mouseMovePoint(QPointF)),
        this, SLOT(on_mouseMovePoint(QPointF)));
    connect(m_pEditPage, SIGNAL(mouseClicked(QPointF)),
        this, SLOT(on_mouseClicked(QPointF)));

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

void KSvgEditor::on_mouseMovePoint(QPointF point) const
{
    m_pLabSceneCord->setText(QString::asprintf("Scene Pos %.0f, %.0f", point.x(), point.y()));
    point = m_pEditPage->mapFromScene(point.toPoint());
    m_pLabViewCord->setText(QString::asprintf("View Pos %.0f, %.0f", point.x(), point.y()));
}

void KSvgEditor::on_mouseClicked(QPointF point) const
{
    const QGraphicsItem* item = nullptr;
    // ??????????????????
    item = m_pEditPage->scene()->itemAt(point, QTransform());
	if (item != nullptr)
        m_pLabItemCord->setText(QString::asprintf("Item Pos %.0f, %.0f", item->pos().x(), item->pos().x()));
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

void KSvgEditor::on_canvasColorChanged() const
{
    qDebug() << "KSvgEditor::on_canvasColorChanged" << m_pData->getCanvasColor() << endl;
    m_pEditPage->updateSceneBackground();
}

void KSvgEditor::on_borderWidthChanged() const
{
    qDebug() << "KSvgEditor::on_borderWidthChanged" << m_pData->getBorderWidth() << endl;
    m_pEditPage->updateSelectItems();
}

void KSvgEditor::on_borderStyleChanged() const
{
    qDebug() << "KSvgEditor::on_borderStyleChanged" << static_cast<int>(m_pData->getBorderStyle()) << endl;
    m_pEditPage->updateSelectItems();
}

void KSvgEditor::on_borderColorChanged() const
{
    qDebug() << "KSvgEditor::on_borderColorChanged" << m_pData->getBorderColor() << endl;
    m_pEditPage->updateSelectItems();
}

void KSvgEditor::on_fillColorChanged() const
{
    qDebug() << "KSvgEditor::on_fillColorChanged" << m_pData->getFillColor() << endl;
    m_pEditPage->updateSelectItems();
}
