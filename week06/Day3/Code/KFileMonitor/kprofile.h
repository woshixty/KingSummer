// -------------------------------------------------------
// kprofile.h
// 创建者： xie tingyu
// 创建时间： 2022/08/12
// 功能描述： 配置文件属性封装类
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_PROFILE_H_
#define _K_PROFILE_H_

#include <QObject>
#include <Windows.h>

class KProfile final : public QObject
{
	Q_OBJECT

public:
	KProfile(QObject *parent = nullptr);
	KProfile(const KProfile& other);
	~KProfile();

	KProfile& operator=(const KProfile& other);

	void setId(int id);
	void setProfileName(const QString& string);
	void setProfileOptions(const QString& string);
	void setIncludeFiles(const QString& string);
	void setExcludeFiles(const QString& string);
	void setWatchDirs(const QString& string);

	int id() { return m_id; }
	QString profileName() { return m_profileName; }
	QString profileOptions();
	QString includeFiles();
	QString excludeFiles();
	QString watchDirs();

	QList<int> profileOptionsList() { return m_profileOptions; }
	QList<QString> includeFilesList() { return m_includeFiles; }
	QList<QString> excludeFilesList() { return m_excludeFiles; }
	QList<QString> watchDirsList() { return m_watchDirs; }

	void addDirToWatch(const QString& dir);

private:
	int m_id{};
	QString m_profileName;
	QList<int> m_profileOptions;
	QList<QString> m_includeFiles;
	QList<QString> m_excludeFiles;
	QList<QString> m_watchDirs;
};

#endif