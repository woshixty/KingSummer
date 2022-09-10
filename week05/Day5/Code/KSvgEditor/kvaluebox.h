// -------------------------------------------------------
// kvaluebox.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/09
// ���������� ���ֲ�����
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

	// ��ȡ�����¼�
	void focusInEvent(QFocusEvent* event) override;

private slots:
	// ����������õĲۺ���
	void writeFinish();
	
private:
	QLineEdit* m_pParamEdit;
};

#endif
