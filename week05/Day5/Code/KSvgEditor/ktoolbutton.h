// -------------------------------------------------------
// ktoolbutton.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/09
// ���������� ���߰�ť
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_TOOLBUTTON_H_
#define _K_TOOLBUTTON_H_

#include "kglobaldata.h"

#include <QRadioButton>
#include <QtSvg/qsvgrenderer.h>
#include <qpainter.h>

class KToolButton final : public QRadioButton
{
	Q_OBJECT

public:
	KToolButton(QString iconName, KGlobalData::KDrawFlag flag, QWidget *parent);
	~KToolButton() override;

	// ��ͼ�¼�
	void paintEvent(QPaintEvent* event) override;
	// �������
	void enterEvent(QEvent* event) override;
	// �뿪���
	void leaveEvent(QEvent* event) override;
	// ����ͷ��¼�
	void mouseReleaseEvent(QMouseEvent* event) override;

private slots:
	void onToggle();

private:
	// svgͼ������
	QString m_iconName;
	// ���ڶ�ȡsvgͼƬ
	QSvgRenderer* m_svg;
	// ���水ť����
	KGlobalData::KDrawFlag m_flag;
};

#endif
