#pragma once

#include <QtWidgets/QMainWindow>
#include <QGraphicsRectItem>
#include <QStatusBar>

#include "ui_ksvgeditor.h"
#include "kmenubar.h"
#include "ktoolbar.h"
#include "KParamBar.h"
#include "ksvgmainwindow.h"
#include "keditpage.h"

class KSvgEditor : public QMainWindow
{
    Q_OBJECT

public:
    KSvgEditor(QWidget *parent = nullptr);
    ~KSvgEditor() override;

    void initializePage();
    void initializeConn() const;

private slots:
    void on_mouseMovePoint(QPoint point) const;
    void on_mouseClicked(QPoint point) const;

    void on_canvasWidthChanged();
    void on_canvasHeightChanged();
    void on_canvasScalingChanged();
    void on_canvasColorChanged();
    void on_borderWidthChanged();
    void on_borderStyleChanged();
    void on_borderColorChanged();
    void on_fillColorChanged();

private:
    Ui::KSvgEditorClass ui{};
    KMenuBar* m_pMenuBar{};
    KToolBar* m_pToolBar{};
    KEditPage* m_pEditPage{};
    KParamBar* m_pParamBar{};
    KGlobalData* m_pData = KGlobalData::getGlobalDataInstance();

    QLabel* m_pLabViewCord{};
    QLabel* m_pLabSceneCord{};
    QLabel* m_pLabItemCord{};
};
