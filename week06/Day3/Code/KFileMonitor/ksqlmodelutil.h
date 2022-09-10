// -------------------------------------------------------
// ksqlmodelutil.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/11
// ���������� filter������
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_SQLMODELUTIL_H_
#define _K_SQLMODELUTIL_H_

#include <QObject>
#include <QDateTime>
#include <QSqlTableModel>

class KSqlModelUtil final : public QObject
{
	Q_OBJECT

public:
	KSqlModelUtil(QObject *parent);
	~KSqlModelUtil() override;

	static void generateBetweenDatetime(QSqlTableModel* model, const QDateTime& start, const QDateTime& end);
	static void generateQueryModel(QSqlTableModel* model, const QString& start, const QString& end, const QString& fileName, const QString& owner);
};

#endif