#pragma once

#include "kparambox.h"
#include "kglobaldata.h"

#include <QPushButton>
#include <utility>
#include <QColorDialog>

class KColorBox : public KParamBox
{
	Q_OBJECT

public:
	KColorBox(QString title, const QString& colorStr, QWidget* parent = Q_NULLPTR);
	~KColorBox() override;
	// 鼠标释放事件,鼠标释放时弹出颜色选择对话框
	void mouseReleaseEvent(QMouseEvent* event) override;

signals:
	void pickedColor();

public slots:
	void showPickColorDlg();

private:
	// 添加了按钮
	QPushButton* m_pColorBtn;
};
