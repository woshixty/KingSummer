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

	// ����һ���˵�
	m_pFileMenu = new QMenu(QStringLiteral("�ļ�"), this);

	// ������ʽ��
	m_pFileMenu->setStyleSheet(\
		"QMenu { background-color: #FFFFFF; font-size: 15px; font-family: Microsoft YaHei; }"\
		"QMenu::item { color: #000000; background: #FFFFFF; }"\
		"QMenu::item: selected { background: #e5e5e5; color: #000000; }"\
	);

	// �����ļ��˵�
	addMenu(m_pFileMenu);
	m_pNewFileAction = new QAction(QStringLiteral("�½��ļ�"), this);

	// ���ÿ�ݷ�ʽ
	m_pNewFileAction->setShortcut(Qt::CTRL | Qt::Key_N);
	m_pOpenFileAction = new QAction(QStringLiteral("��SVG"), this);
	m_pOpenFileAction->setShortcut(Qt::CTRL | Qt::Key_0);
	m_pSaveFileAction = new QAction(QStringLiteral("����"), this);
	m_pSaveFileAction->setShortcut(Qt::CTRL | Qt::Key_S);
	m_pExportPNGAction = new QAction(QStringLiteral("����PNG"), this);
	m_pExportPNGAction->setShortcut(Qt::CTRL | Qt::Key_E);

	// ���˵������ѡ��
	m_pFileMenu->addAction(m_pNewFileAction);
	m_pFileMenu->addAction(m_pOpenFileAction);
	m_pFileMenu->addAction(m_pSaveFileAction);
	m_pFileMenu->addAction(m_pExportPNGAction);
}

KMenueBar::~KMenueBar()
{}
