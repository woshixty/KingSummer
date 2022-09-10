#pragma once

#include "kglobaldata.h"

#include <QLabel>
#include <QVBoxLayout>

#pragma execution_character_set("utf-8")

class KParamBaseBox : public QWidget
{
	Q_OBJECT

public:
	KParamBaseBox(QString title, KGlobalData::KParamFlag flag, QWidget* parent);
	~KParamBaseBox() override;

	void enterEvent(QEvent* event) override;
	void leaveEvent(QEvent* event) override;

	KGlobalData::KParamFlag getFlag() const { return m_flag; }

protected:
	QVBoxLayout* m_pVLayout;
	KGlobalData* m_pData = KGlobalData::getGlobalDataInstance();
	KGlobalData::KParamFlag m_flag;

signals:
	void canvasWidthChanged();
	void canvasHeightChanged();
	void canvasScalingChanged();
	void canvasColorChanged();
	void borderWidthChanged();
	void borderStyleChanged();
	void borderColorChanged();
	void fillColorChanged();

private:
	QString m_title;
	QLabel* m_pTitleLabel;
};
