#pragma once

#include "KParamBaseBox.h"

#include <QLineEdit>
#include <QRegExpValidator>

class KValueBox final : public KParamBaseBox
{
	Q_OBJECT

public:
	KValueBox(QString title, int val, KGlobalData::KParamFlag flag, QWidget* parent = Q_NULLPTR);
	~KValueBox() override;
	// 获取焦点事件
	void focusInEvent(QFocusEvent* event) override;

private slots:
	void writeFinish();
	
private:
	// 扩展 QLineEdit
	QLineEdit* m_pParamEdit;
};
