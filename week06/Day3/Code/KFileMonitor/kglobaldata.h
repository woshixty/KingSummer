// -------------------------------------------------------
// kglobaldata.h
// 创建者： xie tingyu
// 创建时间： 2022/08/15
// 功能描述： 全局数据类
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_GLOBALDATA_H_
#define _K_GLOBALDATA_H_

#include "kprofile.h"

#include <QObject>
#include <QTime>

// 操作类型
enum class KOperationFlag
{
	BadData = 0,
	Added,
	Deleted,
	Modified,
	RenamedFrom,
	RenamedTo,
	All,
	Renamed
};

static const std::map<KOperationFlag, QString> OPERATOR_MAP =
{
	{KOperationFlag::BadData, "BadData"},
	{KOperationFlag::Added, "Added"},
	{KOperationFlag::Deleted, "Deleted"},
	{KOperationFlag::Modified, "Modified"},
	{KOperationFlag::RenamedFrom, "RenamedFrom"},
	{KOperationFlag::RenamedTo, "RenamedTo"},
};

// 数据列类型
enum class KDataColumnType
{
	id = 0,
	fileOperation,
	operationDate,
	operationTime,
	fileName,
	fileSize,
	fileOwner
};

// 升降类型
enum class KDataSortType
{
	Ascending = 0,
	Descending
};

class KGlobalData final : public QObject
{
	Q_OBJECT

public:
	static KGlobalData* getGlobalDataInstance(QObject* parent = nullptr);
	KProfile activeProfile() { return m_activeProfile; }
	void setActiveProfile(KProfile& profile) { m_activeProfile = profile; }
	bool isVisible() { return m_visible; }
	void setVisible(bool visible) { m_visible = visible; }

	void setStartDateTime(QDateTime dateTime) { m_startDateTime = dateTime; }
	void setEndDateTime(QDateTime dateTime) { m_endDateTime = dateTime; }
	void setFileName(QString fileName) { m_fileName = fileName; }
	void setOwner(QString owner) { m_owner = owner; }

	QString startDateTime() { return m_startDateTime.toString("yyyy-MM-dd") + m_startDateTime.toString("hh:mm:ss"); }
	QString endDateTime() { return m_endDateTime.toString("yyyy-MM-dd") + m_endDateTime.toString("hh:mm:ss"); }
	QString fileName() { return m_fileName; }
	QString owner() { return m_owner; }

private:
	KGlobalData(QObject* parent = nullptr);
	static KGlobalData* s_globalDataObj;
	KProfile m_activeProfile;
	bool m_visible = true;
	// query参数
	QDateTime m_startDateTime = QDateTime::currentDateTime();
	QDateTime m_endDateTime = QDateTime::currentDateTime().addDays(1);
	QString m_fileName;
	QString m_owner;
};

#endif