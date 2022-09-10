#include "kdirectorypage.h"

#include <QFileDialog>

KDirectoryPage::KDirectoryPage(QWidget* parent)
	: KListBasePage(parent)
{
	setUiName("Directory");
	setObjectName(QStringLiteral("m_pDirectoryPage"));
	setMinimumSize(QSize(400, 200));
	connect(m_addBtn, SIGNAL(clicked(bool)), this, SLOT(addProfileDir(bool)));
}

KDirectoryPage::~KDirectoryPage()
= default;

void KDirectoryPage::addProfileDir(bool flag)
{
	// 将将文件夹添加到列表
	const QString dir = QFileDialog
		::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if(!dir.isEmpty())
		m_profileList->addItem(dir);
	// 将文件夹通过信号与槽传出去
	emit addDirectory(dir);
}

void KDirectoryPage::activeProfileChanged() const
{
	// 获取配置文件监视文件夹列表
	QList<QString> dirs = m_globalData->activeProfile().watchDirsList();
	m_profileList->clear();
	for (const QString& chars : dirs)
		if(!chars.isEmpty())
		{
			m_profileList->addItem(chars);
			QListWidgetItem* item = m_profileList->item(m_profileList->count() - 1);
			item->setIcon(QIcon(":/icons/dir2.svg"));
		}
}
