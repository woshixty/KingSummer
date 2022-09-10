#ifndef KGROUPDAO_H
#define KGROUPDAO_H

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

#include "kgroup.h"

#include <qobject.h>
#include <qsqlquery.h>
#include <qsqlquerymodel.h>
#include <qdebug.h>

class KGroupDao final : public QObject
{
	Q_OBJECT
public:
	KGroupDao(QObject* parent = nullptr);
	~KGroupDao() override;
	void getAllGroups(QList<KGroup> &result) const;
	bool addNewGroup(const QString& groupName) const;

private:
	QSqlQuery* m_query;
	QSqlQueryModel* m_query_model;
};

#endif
