#include "ksvgeditor.h"

KSvgEditor::KSvgEditor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    initializePage();
    connect(m_pEditPage, SIGNAL(mouseMovePoint(QPoint)),
        this, SLOT(on_mouseMovePoint(QPoint)));
    connect(m_pEditPage, SIGNAL(mouseClicked(QPoint)),
        this, SLOT(on_mouseClicked(QPoint)));
    connect(m_pParamBar->getColorBox(), SIGNAL(pickedColor()),
        m_pEditPage, SLOT(changeSceneColor()));
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

    m_pParamBar = new KCanvasParamsBar(this);
    m_pParamBar->setObjectName(QStringLiteral("paramBar"));
    m_pParamBar->setStyleSheet(QStringLiteral("background-color: rgb(255, 85, 127);"));
    ui.horizontalLayout->addWidget(m_pParamBar);

    m_pLabViewCord= new QLabel("View ���꣺");
    m_pLabViewCord->setMinimumWidth(150);
    ui.statusBar->addWidget(m_pLabViewCord);

    m_pLabSceneCord = new QLabel("Scene ���꣺");
    m_pLabSceneCord->setMinimumWidth(150);
    ui.statusBar->addWidget(m_pLabSceneCord);

    m_pLabItemCord = new QLabel("Item ���꣺");
    m_pLabItemCord->setMinimumWidth(150);
    ui.statusBar->addWidget(m_pLabItemCord);
}

void KSvgEditor::on_mouseMovePoint(QPoint point) const
{
    // ����ƶ��¼���point�� GraphicsView������<��������
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
