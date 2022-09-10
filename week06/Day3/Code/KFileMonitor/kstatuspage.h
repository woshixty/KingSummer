// -------------------------------------------------------
// kstatuspage.h
// 创建者： xie tingyu
// 创建时间： 2022/08/17
// 功能描述： 状态窗口
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_STATUSPAGE_H_
#define _K_STATUSPAGE_H_

#include <QGridLayout>
#include <QLabel>
#include <QApplication>
#include <QComboBox>
#include <QTimer>
#include <QTime>

class KStatusPage final : public QComboBox
{
	Q_OBJECT

public:
	KStatusPage(QWidget *parent);
	~KStatusPage() override;

	void initPage();
    void initValue();
    void retranslateUi();

    QTimer* timer() const { return m_timer; }

private slots:
    void update();

private:
    QGridLayout* gridLayout_2{};
    QGridLayout* gridLayout{};

    QLabel* m_totalChangeLabel{};
    QLabel* m_totalChangeValue{};
    QLabel* m_dirChangeIcon{};
    QLabel* m_dirChangeLabel{};
    QLabel* m_dirChangeValue{};
    QLabel* m_totalChangeIcon{};
    QLabel* m_processRateLabel{};
    QLabel* m_processTimeValue{};
    QLabel* m_processRateIcon{};
    QLabel* m_fileChangeValue{};
    QLabel* m_fileChangeIcon{};
    QLabel* m_fileChangeLabel{};
    QLabel* m_processTimeLabel{};
    QLabel* m_processRateValue{};
    QLabel* m_processTimeIcon{};
    QLabel* m_value{};
    QLabel* m_key{};

    QTimer* m_timer;
    QTime   m_time;
};

#endif