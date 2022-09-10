#pragma once

#include <QtWidgets/QMainWindow>
#include <QGraphicsRectItem>
#include <QStatusBar>
#include "ui_ksvgeditor.h"
#include "kmenubar.h"
#include "ktoolbar.h"
#include "kcanvasparamsbar.h"
#include "ksvgmainwindow.h"
#include "keditpage.h"

class KSvgEditor : public QMainWindow
{
    Q_OBJECT

public:
    KSvgEditor(QWidget *parent = nullptr);
    ~KSvgEditor() override;

    void initializePage();

private slots:
    void on_mouseMovePoint(QPoint point) const;
    void on_mouseClicked(QPoint point) const;

private:
    Ui::KSvgEditorClass ui{};
    KMenuBar* m_pMenuBar{};
    KToolBar* m_pToolBar{};
    KEditPage* m_pEditPage{};
    KCanvasParamsBar* m_pParamBar{};

    QLabel* m_pLabViewCord{};
    QLabel* m_pLabSceneCord{};
    QLabel* m_pLabItemCord{};
};
