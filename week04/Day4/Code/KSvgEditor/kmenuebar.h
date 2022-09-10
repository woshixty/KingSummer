#pragma once

#include <QMenuBar>
#include <QString>

class KMenueBar  : public QMenuBar
{
	Q_OBJECT

public:
	KMenueBar(QWidget *parent = nullptr);
	~KMenueBar();

private:
	QMenu* m_pFileMenu;
	QAction* m_pNewFileAction;
	QAction* m_pOpenFileAction;
	QAction* m_pSaveFileAction;
	QAction* m_pExportPNGAction;
};
