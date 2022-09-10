// -------------------------------------------------------
// ktoolbar.h
// 创建者： xie tingyu
// 创建时间： 2022/08/11
// 功能描述： 工具栏
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_TOOL_BAR_H_
#define _K_TOOL_BAR_H_

#include <QHBoxLayout>
#include <QPushButton>

class KToolBar final : public QWidget
{
	Q_OBJECT

public:
	KToolBar(QWidget *parent);
	~KToolBar() override;

	void initPage();
    QPushButton* startMonitorBtn() const { return m_pStartMonitorBtn; }
    QPushButton* pauseMonitorBtn() const { return m_pPauseMonitorBtn; }
    QPushButton* resetMonitorBtn() const { return m_pResetMonitorBtn; }
    QPushButton* stopMonitorBtn() const { return m_pStopMonitorBtn; }
    QPushButton* importMonitorBtn() const { return m_pImportProfileBtn; }
    QPushButton* exportMonitorBtn() const { return m_pExportProfileBtn; }
    QPushButton* minimizeWindow() const { return m_pMinimizeWindow; }

private:
    QHBoxLayout* horizontalLayout{};
    QPushButton* m_pStartMonitorBtn{};
    QPushButton* m_pPauseMonitorBtn{};
    QPushButton* m_pResetMonitorBtn{};
    QPushButton* m_pStopMonitorBtn{};
    QPushButton* m_pImportProfileBtn{};
    QPushButton* m_pExportProfileBtn{};
    QPushButton* m_pMinimizeWindow{};
    // 预留工具按钮
    QPushButton* m_p2{};
    QPushButton* m_p3{};
    QPushButton* m_p4{};
    QPushButton* m_p5{};
    QSpacerItem* m_pSpacer{};
};

#endif
