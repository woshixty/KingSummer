#pragma once

#include <QRadioButton>
#include <QtSvg/qsvgrenderer.h>
#include <qpainter.h>

#include "kglobaldata.h"

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
