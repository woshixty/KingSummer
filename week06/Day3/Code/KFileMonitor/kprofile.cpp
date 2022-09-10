#include "kprofile.h"

KProfile::KProfile(QObject *parent)
	: QObject(parent)
{}

KProfile::KProfile(const KProfile& other)
{
	m_id = other.m_id;
	m_profileName = other.m_profileName;
	m_profileOptions = other.m_profileOptions;
	m_excludeFiles = other.m_excludeFiles;
	m_includeFiles = other.m_includeFiles;
	m_watchDirs= other.m_watchDirs;
}

KProfile::~KProfile()
= default;

KProfile& KProfile::operator=(const KProfile& other)
{
	this->m_id = other.m_id;
	this->m_profileName = other.m_profileName;
	this->m_profileOptions = other.m_profileOptions;
	this->m_excludeFiles = other.m_excludeFiles;
	this->m_includeFiles = other.m_includeFiles;
	this->m_watchDirs = other.m_watchDirs;
	return *this;
}

void KProfile::setId(const int id)
{
	m_id = id;
}

void KProfile::setProfileName(const QString& string)
{
	m_profileName = string;
}

void KProfile::setProfileOptions(const QString& string)
{
	m_profileOptions.clear();
	QStringList list = string.split("-");
	for (const auto& chars : list)
		if (!chars.isEmpty())
			m_profileOptions.append(chars.toInt());
}

void KProfile::setIncludeFiles(const QString& string)
{
	m_includeFiles.clear();
	QStringList list = string.split(' ');
	for (const auto& chars : list)
		if (!chars.isEmpty())
			m_includeFiles.append(chars);
}

void KProfile::setExcludeFiles(const QString& string)
{
	m_excludeFiles.clear();
	QStringList list = string.split(' ');
	for (const auto& chars : list)
		if (!chars.isEmpty())
			m_excludeFiles.append(chars);
}

void KProfile::setWatchDirs(const QString& string)
{
	m_watchDirs.clear();
	QStringList list = string.split("-.-");
	for (const auto& chars : list)
		if (!chars.isEmpty())
			m_watchDirs.append(chars);
}

QString KProfile::profileOptions()
{
	QString result;
	for (const auto item : m_profileOptions)
		result.append(QString::number(item) + '-');
	return result;
}

QString KProfile::includeFiles()
{
	QString result;
	for (const auto& item : m_includeFiles)
		result.append(item + ' ');
	return result;
}

QString KProfile::excludeFiles()
{
	QString result;
	for (const auto& item : m_excludeFiles)
		result.append(item + ' ');
	return result;
}

QString KProfile::watchDirs()
{
	QString result;
	for (const auto& item : m_watchDirs)
		result.append(item + "-.-");
	return result;
}

void KProfile::addDirToWatch(const QString& dir)
{
	m_watchDirs.append(dir);
}
