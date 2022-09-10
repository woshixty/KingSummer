#include "kprofiledao.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>

KProfileDao::KProfileDao(QObject *parent)
	: QObject(parent)
{
	m_pQuery = new QSqlQuery();
	m_pQueryModel = new QSqlQueryModel();
}

KProfileDao::~KProfileDao()
{
	delete m_pQuery;
	delete m_pQueryModel;
}

bool KProfileDao::updateOrInsertProfile(KProfile& profile) const
{
	m_pQuery->clear();
	const QString sql = "INSERT OR REPLACE INTO profileRecord VALUES (:ID, :PN, :PO, :IF, :EF, :WD)";
	m_pQuery->prepare(sql);
	// 绑定参数
	m_pQuery->bindValue(":ID", profile.id());
	m_pQuery->bindValue(":PN", profile.profileName());
	m_pQuery->bindValue(":PO", profile.profileOptions());
	m_pQuery->bindValue(":IF", profile.includeFiles());
	m_pQuery->bindValue(":EF", profile.excludeFiles());
	m_pQuery->bindValue(":WD", profile.watchDirs());
	// 执行函数
	if (m_pQuery->exec())
		return true;
	qDebug() << "[KProfileDao::updateOrInsertProfile] : " << m_pQuery->lastError();
	return false;
}

bool KProfileDao::getProfileByName(KProfile& profile) const
{
	const QString sql = "SELECT * FROM profileRecord where profile_name = '"+ profile.profileName() +"'";
	m_pQueryModel->setQuery(sql);
	const int rows = m_pQueryModel->rowCount();
	if (rows == 0)
		return false;
	const QSqlRecord record = m_pQueryModel->record(0);
	profile.setId(record.value(0).toInt());
	profile.setProfileName(record.value(1).toString());
	profile.setProfileOptions(record.value(2).toString());
	profile.setIncludeFiles(record.value(3).toString());
	profile.setExcludeFiles(record.value(4).toString());
	profile.setWatchDirs(record.value(5).toString());
	return true;
}

bool KProfileDao::getAllProfiles(QList<KProfile>& list)
{
	list.clear();
	const QString sql = "SELECT * FROM profileRecord";
	m_pQueryModel->setQuery(sql);
	const int rows = m_pQueryModel->rowCount();
	for (int i = 0; i < rows; ++i)
	{
		const QSqlRecord record = m_pQueryModel->record(i);
		KProfile profile(this);
		profile.setId(record.value(0).toInt());
		profile.setProfileName(record.value(1).toString());
		profile.setProfileOptions(record.value(2).toString());
		profile.setIncludeFiles(record.value(3).toString());
		profile.setExcludeFiles(record.value(4).toString());
		profile.setWatchDirs(record.value(5).toString());
		list.append(profile);
	}
	return true;
}
