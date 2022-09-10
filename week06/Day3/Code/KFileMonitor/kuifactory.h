// -------------------------------------------------------
// kuifactory.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/12
// ���������� ui������
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_UIFACTORY_H_
#define _K_UIFACTORY_H_

#include <QPushButton>
#include <QLabel>

class KUIFactory
{
public:
	static QPushButton* createToolBtn(QWidget* parent, const QString& name, const QString& text = "");
	static QPushButton* createAddOrBtn(QWidget* parent, const QString& name, const QString& iconStr = "");
	static QLabel* createIconLabel(QWidget* parent, const QString& name, const QString& iconStr = "");
	static QLabel* createValueLabel(QWidget* parent, const QString& name, const QString& value = "");
	static QLabel* createStatusLabel(QWidget* parent, const QString& name, const QString& value = "");
};

#endif