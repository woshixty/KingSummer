#pragma once

#include <QMenuBar>
#include <QString>

class KMenuBar  : public QMenuBar
{
	Q_OBJECT

public:
	KMenuBar(QWidget *parent = nullptr);
	~KMenuBar() override;

private:
	QMenu* m_pFileMenu;
	QAction* m_pNewFileAction;
	QAction* m_pOpenFileAction;
	QAction* m_pSaveFileAction;
	QAction* m_pExportPNGAction;
};
