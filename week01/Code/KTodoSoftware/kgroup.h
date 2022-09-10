#pragma once

#include <QObject>

class KGroup  : public QObject
{
	Q_OBJECT

public:
	KGroup(QObject *parent);
	KGroup(QString group_name, size_t count);
	KGroup(const KGroup& obj);
	~KGroup() override;
	QString getGroupName() const { return m_group_name; }
	size_t getCount() const { return m_count; }

private:
	QString m_group_name;
	size_t m_count;
};
