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
	// ����ͷ��¼�,����ͷ�ʱ������ɫѡ��Ի���
	void mouseReleaseEvent(QMouseEvent* event) override;

signals:
	void pickedColor();

public slots:
	void showPickColorDlg();

private:
	// ����˰�ť
	QPushButton* m_pColorBtn;
};
