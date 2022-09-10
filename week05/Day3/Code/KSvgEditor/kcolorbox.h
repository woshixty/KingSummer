#pragma once

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
	// ����ͷ��¼�,����ͷ�ʱ������ɫѡ��Ի���
	void mouseReleaseEvent(QMouseEvent* event) override;

public slots:
	void showPickColorDlg();

private:
	// ����˰�ť
	QPushButton* m_pColorBtn;
};
