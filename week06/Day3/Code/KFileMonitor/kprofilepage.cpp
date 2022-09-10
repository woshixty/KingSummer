#include "kprofilepage.h"
#include "kprofileutil.h"

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QTextCodec>
#include <utility>

KProfilePage::KProfilePage(QWidget* parent)
	: KListBasePage(parent)
{
	setUiName("Profile");
	setObjectName(QStringLiteral("m_pProfilePage"));
	setMinimumSize(QSize(400, 200));
	// ���add��ť
	connect(
		m_addBtn, 
		SIGNAL(clicked(bool)), 
		this, 
		SLOT(addProfileBtn(bool))
	);
	// ˫�������ļ����༭ҳ��
	connect(
		m_profileList, 
		SIGNAL(itemDoubleClicked(QListWidgetItem*)),
		this, 
		SLOT(profileDoubleClicked(QListWidgetItem*))
	);
	// ���������ļ����û�Ծ�����ļ�
	connect(
		m_profileList, 
		SIGNAL(itemClicked(QListWidgetItem*)),
		this, 
		SLOT(profileClicked(QListWidgetItem*))
	);
}

KProfilePage::~KProfilePage()
= default;

void KProfilePage::initData()
{
	int currentRow = m_profileList->currentRow();
	if (currentRow == -1)
		currentRow = 0;
	m_profileList->clear();
	m_profileDao->getAllProfiles(m_profiles);
	for (KProfile profile : m_profiles)
	{
		m_profileList->addItem(profile.profileName());
		QListWidgetItem* item = m_profileList->item(m_profileList->count() - 1);
		item->setIcon(QIcon(":/icons/profile2.svg"));
	}
		
	m_profileList->setCurrentRow(currentRow);
	m_currentProfile = m_profiles.at(currentRow);
	// ���õ�ǰ��Ծ�����ļ�
	m_globalData->setActiveProfile(m_currentProfile);
}

void KProfilePage::setProfileDao(KProfileDao* profileDao)
{
	m_profileDao = profileDao;
}

void KProfilePage::addProfileBtn(bool flag)
{
	const auto dialog = new KProfileEditDialog(this);
	// ���������ļ��༭��ɵ��ź����
	connect(
		dialog, 
		SIGNAL(profileEdited(KProfile)), 
		this, 
		SLOT(profileEdited(KProfile))
	);
	dialog->show();
}

void KProfilePage::profileDoubleClicked(QListWidgetItem* item)
{
	const int row = m_profileList->currentRow();
	// ��ȡ��ǰ�е������ļ�
	KProfile profile = m_profiles.at(row);
	const auto dialog = new KProfileEditDialog(this);
	// ���������ļ��༭��ɵ��ź����
	connect(
		dialog,
		SIGNAL(profileFinishEdited(KProfile)),
		this, 
		SLOT(profileEdited(KProfile))
	);
	dialog->setProfile(profile);
	dialog->show();
}

void KProfilePage::profileClicked(QListWidgetItem* item)
{
	// ���õ�ǰ�����ļ���
	m_currentProfile = m_profiles.at(m_profileList->currentRow());
	m_globalData->setActiveProfile(m_currentProfile);
	emit sendCurrentProfile();
}

void KProfilePage::profileEdited(KProfile profile)
{
	m_profileDao->updateOrInsertProfile(profile);
	initData();
}

void KProfilePage::addDirToWatch(const QString& dir)
{
	const int currentRow = m_profileList->currentRow();
	m_currentProfile.addDirToWatch(dir);
	m_profileDao->updateOrInsertProfile(m_currentProfile);
	initData();
	m_profileList->setCurrentRow(currentRow);
}

void KProfilePage::importProfile()
{
	const QString filePath =
		QFileDialog::getOpenFileName(this, "Save Config",
			"", "config files (*.conf)");
	// ָ��ΪGBK 
	const QTextCodec* codec = QTextCodec::codecForName("GBK");
	QString json = "";
	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	while (!file.atEnd())
		// ��ȡ����������ת��ΪUnicode
		json = codec->toUnicode(file.readAll());
	KProfile profile;
	KProfileUtil::parseJson(profile, json);
	profileEdited(profile);
	QMessageBox::information(this, "info", "import success!");
}

void KProfilePage::exportProfile()
{
	const QString filePath =
		QFileDialog::getSaveFileName(this, "Save Config",
			"", "config files (*.conf)");
	if (filePath == "")
		return;
	QFile file(filePath);
	// TODO ������־
	if (file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QString content;
		KProfileUtil::toJson(m_currentProfile, content);
		QTextStream stream(&file);
		stream << content;
		file.close();
		QMessageBox::information(this, "info", "save success!");
	}
}


