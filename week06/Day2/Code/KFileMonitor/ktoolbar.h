// -------------------------------------------------------
// ktoolbar.h
// 创建者： xie tingyu
// 创建时间： 2022/08/11
// 功能描述： 
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_TOOLBAR_H_
#define _K_TOOLBAR_H_

#include <QHBoxLayout>
#include <QPushButton>

class KToolBar final : public QWidget
{
	Q_OBJECT

public:
	KToolBar(QWidget *parent);
	~KToolBar() override;

	void initPage();

private:
    QHBoxLayout* horizontalLayout;
    QPushButton* m_pMonitorBtn;
    QPushButton* m_pPauseBtn;
    QPushButton* m_pResetBtn;
    QPushButton* m_pStopBtn;
    QPushButton* m_pWizardBtn;
    QPushButton* m_pSaveBtn;
    QPushButton* m_p1;
    QPushButton* m_p2;
    QPushButton* m_p3;
    QPushButton* m_p4;
    QPushButton* m_p5;
    QSpacerItem* m_pSpacer;
};

#endif
