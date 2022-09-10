#include "ksqlmodelutil.h"

#include <QDebug>

KSqlModelUtil::KSqlModelUtil(QObject *parent)
	: QObject(parent)
{}

KSqlModelUtil::~KSqlModelUtil()
= default;

void KSqlModelUtil::generateBetweenDatetime(QSqlTableModel* model, const QDateTime& start, const QDateTime& end)
{
	const QString startStr = start.toString("yyyy-MM-dd") + start.toString("hh:mm:ss");
	const QString endStr = end.toString("yyyy-MM-dd") + end.toString("hh:mm:ss");
	const QString filter = tr("(operation_date || operation_time) >= '%1' AND (operation_date || operation_time) <= '%2'").arg(startStr).arg(endStr);
	model->setFilter(filter);
}

void KSqlModelUtil::generateQueryModel(QSqlTableModel* model, const QString& start, const QString& end,
	const QString& fileName, const QString& owner)
{
	const QString filter = tr("(operation_date || operation_time) >= '%1' AND (operation_date || operation_time) <= '%2' AND file_name LIKE '%%3%' AND file_owner LIKE '%%4%'").arg(start).arg(end).arg(fileName).arg(owner);
	model->setFilter(filter);
	qDebug() << model->filter();
}
