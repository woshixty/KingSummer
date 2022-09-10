// -------------------------------------------------------
// kmenubar.h
// 创建者： xie tingyu
// 创建时间： 2022/08/09
// 功能描述： 菜单栏
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_MENUBAR_H_
#define _K_MENUBAR_H_

#include <QMenuBar>
#include <QString>

class KMenuBar  : public QMenuBar
{
	Q_OBJECT

public:
	KMenuBar(QWidget *parent = nullptr);
	~KMenuBar() override;

	QAction* newFileAction() const { return m_pNewFileAction; }
	QAction* openFileAction() const { return m_pOpenFileAction; }
	QAction* saveFileAction() const { return m_pSaveFileAction; }
	QAction* exportPngAction() const { return m_pExportPNGAction; }

private:
	QMenu* m_pFileMenu;
	QAction* m_pNewFileAction;
	QAction* m_pOpenFileAction;
	QAction* m_pSaveFileAction;
	QAction* m_pExportPNGAction;
};

#endif
