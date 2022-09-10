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
	// ��ȡ�����¼�
	void focusInEvent(QFocusEvent* event) override;

private slots:
	void writeFinish();
	
private:
	// ��չ QLineEdit
	QLineEdit* m_pParamEdit;
};
