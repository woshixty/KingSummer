// -------------------------------------------------------
// kparambar.h
// 创建者： xie tingyu
// 创建时间： 2022/08/09
// 功能描述： 参数栏
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
