#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ksvgeditor.h"
#include "kmenuebar.h"
#include "ktoolbar.h"
#include "ksvgmainwindow.h"

class KSvgEditor : public QMainWindow
{
    Q_OBJECT

public:
    KSvgEditor(QWidget *parent = nullptr);
    ~KSvgEditor() override;

    void initializePage();

private:
    Ui::KSvgEditorClass ui{};
    KMenueBar* m_pMenuBar{};
    KToolBar* m_pToolBar{};
};
