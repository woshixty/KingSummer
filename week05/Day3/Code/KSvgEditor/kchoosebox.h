#pragma once

#include "KParamBaseBox.h"

#include <QWidget>
#include <QComboBox>

class KChooseBox final : public KParamBaseBox
{
	Q_OBJECT

public:
	KChooseBox(QString title, KGlobalData::KParamFlag flag, QWidget* parent = Q_NULLPTR);
	~KChooseBox() override;

private slots:
	void selectLineType(int index);

private:
	QComboBox* m_pLineChooser;
	QIcon m_solidIcon;
	QIcon m_dottedIcon;
};
