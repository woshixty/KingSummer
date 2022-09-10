#include "kgroup.h"

#include <utility>

KGroup::KGroup(QObject *parent)
	: QObject(parent)
{
	m_group_name = "null";
	m_count = 0;
}

KGroup::KGroup(QString group_name, size_t count)
{
	m_group_name = std::move(group_name);
	m_count = count;
}

KGroup::KGroup(const KGroup& obj)
{
	m_group_name = obj.getGroupName();
	m_count = obj.getCount();
}

KGroup::~KGroup()
{}
