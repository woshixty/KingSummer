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

	// 绘图事件
	virtual void paintEvent(QPaintEvent* event) override;
	// 进入组件
	virtual void enterEvent(QEvent* event) override;
	// 离开组件
	virtual void leaveEvent(QEvent* event) override;
	// 鼠标释放事件
	virtual void mouseReleaseEvent(QMouseEvent* event) override;

private slots:
	void onToggle();

private:
	// svg图标名称
	QString m_iconName;
	// 用于读取svg图片
	QSvgRenderer* m_svg;
};
