// -------------------------------------------------------
// kuifactory.h
// 创建者： xie tingyu
// 创建时间： 2022/08/12
// 功能描述： 
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_UIFACTORY_H_
#define _K_UIFACTORY_H_

#include <QPushButton>

class KUIFactory
{
public:
	static QPushButton* createToolBtn(QWidget* parent, const QString& name = "NULL", const QString& text = "");
};

#endif