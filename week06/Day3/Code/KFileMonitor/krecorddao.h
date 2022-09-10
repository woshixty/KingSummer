// -------------------------------------------------------
// krecorddao.h
// 创建者： xie tingyu
// 创建时间： 2022/08/18
// 功能描述： 数据记录数据库持久层
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_RECORDDAO_H_
#define _K_RECORDDAO_H_

#include "kmessage.h"

#include <QObject>
#include <QSqlQuery>
#include <QSqlQueryModel>

class KRecordDao final : public QObject
{
	Q_OBJECT

public:
	KRecordDao(QObject *parent);
	~KRecordDao() override;

	bool saveOneRecord(const KMessage& message) const;

private:
	QSqlQuery* m_pQuery;
	QSqlQueryModel* m_pQueryModel;
};

#endif