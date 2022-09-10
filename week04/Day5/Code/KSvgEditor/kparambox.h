#pragma once

#include <QLabel>
#include <QVBoxLayout>

#pragma execution_character_set("utf-8")

class KParamBox : public QWidget
{
	Q_OBJECT

public:
	KParamBox(QString title, QWidget* parent);
	~KParamBox() override;

	void enterEvent(QEvent* event) override;
	void leaveEvent(QEvent* event) override;

protected:
	QVBoxLayout* m_pVLayout;

private:
	QString m_title;
	QLabel* m_pTitleLabel;
};
