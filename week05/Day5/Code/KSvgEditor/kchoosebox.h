// -------------------------------------------------------
// kchoosebox.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/09
// ���������� ������������ѡ����
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_CHOOSEBOX_H_
#define _K_CHOOSEBOX_H_

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

#endif
