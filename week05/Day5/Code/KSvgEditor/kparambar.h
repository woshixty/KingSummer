// -------------------------------------------------------
// kparambar.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/09
// ���������� ������
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_PARAMBAR_H_
#define _K_PARAMBAR_H_

#include "KParamBaseBar.h"
#include "kcolorbox.h"
#include "kvaluebox.h"
#include "kchoosebox.h"

class KParamBar final : public KParamBaseBar
{
	Q_OBJECT

public:
	KParamBar(QWidget* parent = nullptr);
	~KParamBar() override;

	KParamBaseBox* getBox(KGlobalData::KParamFlag flag) const;
	QList<KParamBaseBox*> getParamBoxes();

private:
	QList<KParamBaseBox*> m_boxes;
	KGlobalData* m_pData;
};

#endif
