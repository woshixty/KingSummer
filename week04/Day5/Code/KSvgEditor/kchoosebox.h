#pragma once

#include "kparambox.h"

#include <QWidget>
#include <QComboBox>

class KChooseBox final : public KParamBox
{
	Q_OBJECT

public:
	KChooseBox(QString title, QWidget* parent = Q_NULLPTR);
	~KChooseBox() override;

private:
	QComboBox* m_pLineChooser;
};
