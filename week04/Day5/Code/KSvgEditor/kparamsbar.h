#pragma once

#include <QWidget>
#include <qgridlayout.h>
#include <qlabel.h>

#pragma execution_character_set("utf-8")

class KParamsBar : public QWidget
{
	Q_OBJECT

public:
	KParamsBar(QString title, QWidget* parent);
	~KParamsBar() override;

protected:
	// Íø¸ñ²¼¾Ö
	QGridLayout* m_pGridLayout;

private:
	QVBoxLayout* m_pVBoxLayout;
	QString m_title;
	QLabel* m_titleLabel;
};
