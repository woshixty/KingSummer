#pragma once

#include "KParamBaseBar.h"
#include "kcolorbox.h"
#include "kvaluebox.h"
#include "kchoosebox.h"


class KParamBar final : public KParamBaseBar
{
	Q_OBJECT

public:
	KParamBar(QWidget* parent = Q_NULLPTR);
	~KParamBar() override;

	KParamBaseBox* getBox(KGlobalData::KParamFlag flag) const;
	QList<KParamBaseBox*> getParamBoxes();

private:
	QList<KParamBaseBox*> m_boxes;
	KGlobalData* m_data;
};
