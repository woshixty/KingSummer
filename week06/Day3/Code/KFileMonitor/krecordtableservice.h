// -------------------------------------------------------
// krecordtableservice.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/11
// ���������� ��¼������
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_RECORDTABLESERVICE_H_
#define _K_RECORDTABLESERVICE_H_

#include "kglobaldata.h"

#include <QObject>
#include <QSqlTableModel>

class KRecordTableService final : public QObject
{
	Q_OBJECT

public:
	KRecordTableService(QObject *parent);
	~KRecordTableService() override;

	void setSqlTableModel(QSqlTableModel* tableModel) { m_pTableModel = tableModel; }

private slots:
	void sortByColumnType(int index);
	void sortBySortType(int index);
	void queryByOperationType(int index);
	// ���±�
	void updateTable() const;

private:
	QSqlTableModel* m_pTableModel{};
	QString m_sortColumnName = "operation_date";
	Qt::SortOrder m_sortType = Qt::AscendingOrder;
	KOperationFlag m_operationType = KOperationFlag::All;
	KGlobalData* m_pGlobalData = KGlobalData::getGlobalDataInstance();
};

#endif