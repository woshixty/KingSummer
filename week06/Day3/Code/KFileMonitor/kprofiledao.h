// -------------------------------------------------------
// kprofile.h
// 创建者： xie tingyu
// 创建时间： 2022/08/12
// 功能描述： 配置文件数据库持久层
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_PROFILERECORD_H_
#define _K_PROFILERECORD_H_

#include "kprofile.h"

#include <QObject>
#include <QSqlQuery>
#include <QSqlQueryModel>

class KProfileDao final : public QObject
{
	Q_OBJECT

public:
	KProfileDao(QObject *parent);
	~KProfileDao();

	bool updateOrInsertProfile(KProfile& profile) const;
	bool getProfileByName(KProfile& profile) const;
	bool getAllProfiles(QList<KProfile>& list);

private:
	QSqlQuery* m_pQuery;
	QSqlQueryModel* m_pQueryModel;
};

#endif