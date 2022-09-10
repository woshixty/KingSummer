#include "krecordtableservice.h"

#include <QDebug>

#include "ksqlmodelutil.h"

KRecordTableService::KRecordTableService(QObject *parent)
	: QObject(parent)
{
}

KRecordTableService::~KRecordTableService()
= default;

void KRecordTableService::updateTable() const
{
	KSqlModelUtil::generateQueryModel(m_pTableModel, m_pGlobalData->startDateTime(), m_pGlobalData->endDateTime(), m_pGlobalData->fileName(), m_pGlobalData->owner());
	m_pTableModel->select();
}

void KRecordTableService::sortByColumnType(int index)
{
	switch (index)
	{
	case 0:
		m_sortColumnName = "operation_date";
		break;
	case 1:
		m_sortColumnName = "operation_time";
		break;
	case 2:
		m_sortColumnName = "file_size";
		break;
	case 3:
		m_sortColumnName = "file_owner";
		break;
	case 4:
		m_sortColumnName = "file_name";
		break;
	default: 
		m_sortColumnName = "operation_date";
	}
	m_pTableModel->sort(m_pTableModel->fieldIndex(m_sortColumnName), m_sortType);
}

void KRecordTableService::sortBySortType(int index)
{
	if (index)
		m_sortType = Qt::DescendingOrder;
	else
		m_sortType = Qt::AscendingOrder;
	m_pTableModel->sort(m_pTableModel->fieldIndex(m_sortColumnName), m_sortType);
}

void KRecordTableService::queryByOperationType(int index)
{
	switch (index)
	{
	case 0:
		m_operationType = KOperationFlag::All;
		break;
	case 1:
		m_operationType = KOperationFlag::Added;
		break;
	case 2:
		m_operationType = KOperationFlag::Deleted;
		break;
	case 3:
		m_operationType = KOperationFlag::Modified;
		break;
	case 4:
		m_operationType = KOperationFlag::Renamed;
		break;
	default:
		m_operationType = KOperationFlag::All;
		break;
	}

}
