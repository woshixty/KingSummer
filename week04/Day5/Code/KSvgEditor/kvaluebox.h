#pragma once

#include "kparambox.h"

#include <QLineEdit>
#include <QRegExpValidator>

class KValueBox final : public KParamBox
{
	Q_OBJECT

public:
	KValueBox(QString title, int val, QWidget* parent = Q_NULLPTR);
	~KValueBox() override;
	// 获取焦点事件
	void focusInEvent(QFocusEvent* event) override;

private:
	// 扩展 QLineEdit
	QLineEdit* m_pParamEdit;
};
