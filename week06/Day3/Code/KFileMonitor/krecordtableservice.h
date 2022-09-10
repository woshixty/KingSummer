// -------------------------------------------------------
// krecordtableservice.h
// 创建者： xie tingyu
// 创建时间： 2022/08/11
// 功能描述： 记录服务类
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
	// 更新表单
	void updateTable() const;

private:
	QSqlTableModel* m_pTableModel{};
	QString m_sortColumnName = "operation_date";
	Qt::SortOrder m_sortType = Qt::AscendingOrder;
	KOperationFlag m_operationType = KOperationFlag::All;
	KGlobalData* m_pGlobalData = KGlobalData::getGlobalDataInstance();
};

#endif