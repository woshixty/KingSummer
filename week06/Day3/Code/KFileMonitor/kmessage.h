// -------------------------------------------------------
// kmessage.h
// 创建者： xie tingyu
// 创建时间： 2022/08/12
// 功能描述： 消息封装类
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_MESSAGE_H_
#define _K_MESSAGE_H_

#include <QObject>
#include <QTime>
#include <QListWidgetItem>
#include <QSqlTableModel>
#include <QSqlRecord>

#include "kglobaldata.h"

class KMessage final : public QObject
{
	Q_OBJECT

public:
	KMessage();
	KMessage(KOperationFlag operation, QString fileName, qreal filesize, QString owner);
	KMessage(const KMessage& other);
	KMessage& operator=(const KMessage& other);
	~KMessage() override;

	QString date() const { return m_date.toString("yyyy-MM-dd"); }
	QString time() const { return m_time.toString("hh:mm:ss"); }
	int operation() const { return static_cast<int>(m_operation); }
	KOperationFlag operationFlag() const { return m_operation; }
	QString filename() const { return m_fileName; }
	qreal filesize() const { return m_fileSize; }
	QString owner() const { return m_owner; }

	QString title() const;
	QString content() const;

	void generateRow(QSqlTableModel* model) const;

private:
	QDate m_date;
	QTime m_time;
	KOperationFlag m_operation;
	QString m_fileName;
	qreal m_fileSize{};
	QString m_owner;
};

#endif