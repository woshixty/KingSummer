#include "kmenuebar.h"

KMenueBar::KMenueBar(QWidget *parent)
	: QMenuBar(parent)
{
	m_pFileMenu = nullptr;
	setMaximumHeight(30);

	setStyleSheet(
		"QMenuBar { background-color: #2f2f2c; font-size: 15px; font-family: Microsoft YaHei; padding:0px 0px 0px 100px; }"\
		"QMenuBar::item {color: #FFFFFF; background: #2f2f2c; }"\
		"QMenuBar::item::selected{ background-color: #444442; color: #FFFFFF; }"\
	);

	// 创建一个菜单
	m_pFileMenu = new QMenu(QStringLiteral("文件"), this);

	// 设置样式表
	m_pFileMenu->setStyleSheet(\
		"QMenu { background-color: #FFFFFF; font-size: 15px; font-family: Microsoft YaHei; }"\
		"QMenu::item { color: #000000; background: #FFFFFF; }"\
		"QMenu::item: selected { background: #e5e5e5; color: #000000; }"\
	);

	// 增加文件菜单
	addMenu(m_pFileMenu);
	m_pNewFileAction = new QAction(QStringLiteral("新建文件"), this);

	// 设置快捷方式
	m_pNewFileAction->setShortcut(Qt::CTRL | Qt::Key_N);
	m_pOpenFileAction = new QAction(QStringLiteral("打开SVG"), this);
	m_pOpenFileAction->setShortcut(Qt::CTRL | Qt::Key_0);
	m_pSaveFileAction = new QAction(QStringLiteral("保存"), this);
	m_pSaveFileAction->setShortcut(Qt::CTRL | Qt::Key_S);
	m_pExportPNGAction = new QAction(QStringLiteral("导出PNG"), this);
	m_pExportPNGAction->setShortcut(Qt::CTRL | Qt::Key_E);

	// 给菜单栏添加选项
	m_pFileMenu->addAction(m_pNewFileAction);
	m_pFileMenu->addAction(m_pOpenFileAction);
	m_pFileMenu->addAction(m_pSaveFileAction);
	m_pFileMenu->addAction(m_pExportPNGAction);
}

KMenueBar::~KMenueBar()
{}
