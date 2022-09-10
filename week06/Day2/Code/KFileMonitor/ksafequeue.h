#pragma once

#include <QObject>
#include <QList>
#include <QMutex>
#include <QWaitCondition>

template <typename T>
class KSafeQueue final : protected QList<T>
{
	Q_OBJECT

public:
	KSafeQueue(QObject *parent);
	~KSafeQueue();

	void push_back(const T& value);
	bool pop_front(T& value);

private:
	QMutex m_lock;
	QWaitCondition m_wait;
};
