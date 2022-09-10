#pragma once

#include <QRadioButton>
#include <QtSvg/qsvgrenderer.h>
#include <qpainter.h>

class KToolButton  : public QRadioButton
{
	Q_OBJECT

public:
	KToolButton(QString iconName, QWidget *parent);
	~KToolButton();

	// ��ͼ�¼�
	virtual void paintEvent(QPaintEvent* event) override;
	// �������
	virtual void enterEvent(QEvent* event) override;
	// �뿪���
	virtual void leaveEvent(QEvent* event) override;
	// ����ͷ��¼�
	virtual void mouseReleaseEvent(QMouseEvent* event) override;

private slots:
	void onToggle();

private:
	// svgͼ������
	QString m_iconName;
	// ���ڶ�ȡsvgͼƬ
	QSvgRenderer* m_svg;
};
