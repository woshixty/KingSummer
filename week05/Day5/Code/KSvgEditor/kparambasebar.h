// -------------------------------------------------------
// kparambasebar.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/09
// ���������� ����������
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_PARAMBASEBAR_H_
#define _K_PARAMBASEBAR_H_

#include <QWidget>
#include <qgridlayout.h>
#include <qlabel.h>

#pragma execution_character_set("utf-8")

class KParamBaseBar : public QWidget
{
	Q_OBJECT

public:
	KParamBaseBar(QString title, QWidget* parent);
	~KParamBaseBar() override;

protected:
	// ���񲼾�
	QGridLayout* m_pGridLayout;

private:
	QVBoxLayout* m_pVBoxLayout;
	QString m_title;
	QLabel* m_titleLabel;
};

#endif
