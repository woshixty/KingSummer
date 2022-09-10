// -------------------------------------------------------
// kvaluebox.h
// 创建者： xie tingyu
// 创建时间： 2022/08/09
// 功能描述： 数字参数盒
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_VALUEBOX_H_
#define _K_VALUEBOX_H_

#include "KParamBaseBox.h"

#include <QLineEdit>
#include <QRegExpValidator>

class KValueBox final : public KParamBaseBox
{
	Q_OBJECT

public:
	KValueBox(QString title, int val, KGlobalData::KParamFlag flag, QWidget* parent = nullptr);
	~KValueBox() override;

	// 获取焦点事件
	void focusInEvent(QFocusEvent* event) override;

private slots:
	// 输入结束调用的槽函数
	void writeFinish();
	
private:
	QLineEdit* m_pParamEdit;
};

#endif
