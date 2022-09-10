// -------------------------------------------------------
// ktoolbutton.h
// 创建者： xie tingyu
// 创建时间： 2022/08/09
// 功能描述： 工具按钮
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

	// 绘图事件
	void paintEvent(QPaintEvent* event) override;
	// 进入组件
	void enterEvent(QEvent* event) override;
	// 离开组件
	void leaveEvent(QEvent* event) override;
	// 鼠标释放事件
	void mouseReleaseEvent(QMouseEvent* event) override;

private slots:
	void onToggle();

private:
	// svg图标名称
	QString m_iconName;
	// 用于读取svg图片
	QSvgRenderer* m_svg;
	// 保存按钮类型
	KGlobalData::KDrawFlag m_flag;
};

#endif
