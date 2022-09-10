#pragma once

#include <QVBoxLayout>
#include <qwidget.h>
#include <qbuttongroup.h>
#include "ktoolbutton.h"

class KToolBar : public QWidget
{
	Q_OBJECT

public:
	KToolBar(QWidget* parent = nullptr);
	~KToolBar() override;

private:
	QVBoxLayout* m_pVLayout;
	QButtonGroup* m_pBtnGroup;
	KToolButton* m_pMouseBtn;
	KToolButton* m_pPenBtn;
	KToolButton* m_pLineBtn;
	KToolButton* m_pCircleBtn;
	KToolButton* m_pRectBtn;
	KToolButton* m_pPentBtn;
	KToolButton* m_pHexaBtn;
	KToolButton* m_pStarBtn;
	KToolButton* m_pZoomBtn;
	KToolButton* m_pTextBtn;
};
