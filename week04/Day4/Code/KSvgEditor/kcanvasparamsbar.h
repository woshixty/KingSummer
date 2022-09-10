#pragma once

#include "kparamsbar.h"
#include "kcolorbox.h"
#include "kvaluebox.h"

class KCanvasParamsBar : public KParamsBar
{
	Q_OBJECT

public:
	KCanvasParamsBar(QWidget* parent = Q_NULLPTR);
	~KCanvasParamsBar() override;

private:
	KValueBox* m_pWidthBox;
	KValueBox* m_pHeightBox;
	KColorBox* m_pColorBox;
};
