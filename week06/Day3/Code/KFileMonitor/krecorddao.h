// -------------------------------------------------------
// krecorddao.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/18
// ���������� ���ݼ�¼���ݿ�־ò�
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