#pragma once

#include "kparamsbar.h"
#include "kcolorbox.h"
#include "kvaluebox.h"
#include "kchoosebox.h"


class KCanvasParamsBar final : public KParamsBar
{
	Q_OBJECT

public:
	KCanvasParamsBar(QWidget* parent = Q_NULLPTR);
	~KCanvasParamsBar() override;

	KColorBox* getColorBox() const { return m_pColorBox; }

private:
	KValueBox* m_pWidthBox;
	KValueBox* m_pHeightBox;
	KValueBox* m_pScalingBox;
	KColorBox* m_pColorBox;
	KValueBox* m_pBorderWidthBox;
	KChooseBox* m_pBorderStyleBox;
	KColorBox* m_pBorderColorBox;
	KColorBox* m_pFillColorBox;
};
