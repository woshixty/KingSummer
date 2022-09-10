#include "krecorddao.h"

#include <QSqlError>
#include <QDebug>

KRecordDao::KRecordDao(QObject *parent)
	: QObject(parent)
{
	m_pQuery = new QSqlQuery();
	m_pQueryModel = new QSqlQueryModel();
}

KRecordDao::~KRecordDao()
{
	delete m_pQuery;
	delete m_pQueryModel;
}

bool KRecordDao::saveOneRecord(const KMessage& message) const
{
	m_pQuery->clear();
	const QString sql = "INSERT INTO operationRecord (file_operation, operation_date, operation_time, file_name, file_size, file_owner) VALUES (:FO, :OD, :OT, :FN, :FS, :O)";
	m_pQuery->prepare(sql);
	// 绑定参数
	// (:FO, :OD, :OT, FN, FS, :O)
	m_pQuery->bindValue(":FO", message.operation());
	m_pQuery->bindValue(":OD", message.date());
	m_pQuery->bindValue(":OT", message.time());
	m_pQuery->bindValue(":FN", message.filename());
	m_pQuery->bindValue(":FS", message.filesize());
	m_pQuery->bindValue(":O", message.owner());
	// 执行函数
	if(m_pQuery->exec())
		return true;
	qDebug() << "[KRecordDao::saveOneRecord] : " << m_pQuery->lastError();
	return false;
}

