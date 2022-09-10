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
	// ��ȡ�����¼�
	void focusInEvent(QFocusEvent* event) override;

private:
	// ��չ QLineEdit
	QLineEdit* m_pParamEdit;
};
