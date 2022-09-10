// -------------------------------------------------------
// kcolorbox.h
// 创建者： xie tingyu
// 创建时间： 2022/08/09
// 功能描述： 颜色盒子选择类
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
	// 鼠标释放事件,鼠标释放时弹出颜色选择对话框
	void mouseReleaseEvent(QMouseEvent* event) override;

public slots:
	void showPickColorDlg();

private:
	// 添加了按钮
	QPushButton* m_pColorBtn;
};

#endif
