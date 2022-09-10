// -------------------------------------------------------
// kcolorbox.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/09
// ���������� ��ɫ����ѡ����
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_COLORBOX_H_
#define _K_COLORBOX_H_

#include "KParamBaseBox.h"
#include "kglobaldata.h"

#include <QPushButton>
#include <utility>
#include <QColorDialog>

class KColorBox : public KParamBaseBox
{
	Q_OBJECT

public:
	KColorBox(QString title, const QString& colorStr, KGlobalData::KParamFlag flag, QWidget* parent = Q_NULLPTR);
	~KColorBox() override;
	// ����ͷ��¼�,����ͷ�ʱ������ɫѡ��Ի���
	void mouseReleaseEvent(QMouseEvent* event) override;

public slots:
	void showPickColorDlg();

private:
	// ����˰�ť
	QPushButton* m_pColorBtn;
};

#endif
