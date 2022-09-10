// -------------------------------------------------------
// ksvgeditor.h
// 创建者： xie tingyu
// 创建时间： 2022/08/09
// 功能描述： 主界面类
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_SVGEDIT_H_
#define _K_SVGEDIT_H_

#include <QtWidgets/QMainWindow>
#include <QGraphicsRectItem>
#include <QStatusBar>

#include "ui_ksvgeditor.h"
#include "kmenubar.h"
#include "ktoolbar.h"
#include "KParamBar.h"
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
    void on_mouseMovePoint(QPointF point) const;
    void on_mouseClicked(QPointF point) const;

    void on_canvasWidthChanged() const;
    void on_canvasHeightChanged() const;
    void on_canvasScalingChanged();
    void on_canvasColorChanged() const;
    void on_borderWidthChanged() const;
    void on_borderStyleChanged() const;
    void on_borderColorChanged() const;
    void on_fillColorChanged() const;

private:
    Ui::KSvgEditorClass ui{};
    KMenuBar* m_pMenuBar{};
    KToolBar* m_pToolBar{};
    KEditPage* m_pEditPage{};
    KParamBar* m_pParamBar{};
    KGlobalData* m_pData = KGlobalData::getGlobalDataInstance(this);

    QLabel* m_pLabViewCord{};
    QLabel* m_pLabSceneCord{};
    QLabel* m_pLabItemCord{};
};

#endif
