#include "kchoosebox.h"

KChooseBox::KChooseBox(QString title, QWidget* parent)
	: KParamBox(std::move(title), parent)
{
	m_pLineChooser = new QComboBox();
}

KChooseBox::~KChooseBox()
= default;
