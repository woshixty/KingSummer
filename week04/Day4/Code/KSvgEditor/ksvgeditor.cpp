#include "ksvgeditor.h"

KSvgEditor::KSvgEditor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    initializePage();
}

KSvgEditor::~KSvgEditor()
= default;

void KSvgEditor::initializePage()
{
    m_pMenuBar = new KMenueBar(this);
    m_pMenuBar->setObjectName(QStringLiteral("menuBar"));
    m_pMenuBar->setGeometry(QRect(0, 0, 807, 23));
    setMenuBar(m_pMenuBar);
}
