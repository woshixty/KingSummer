#include "ksafequeue.h"

template <typename T>
KSafeQueue<T>::KSafeQueue(QObject *parent)
	: QList<T>(parent)
{}

template <typename T>
KSafeQueue<T>::~KSafeQueue()
{}

template <typename T>
void KSafeQueue<T>::push_back(const T& value)
{
	m_lock.lock();
	QList<T>::push_back(value);
	m_lock.unlock();
	m_wait.notify_all();
}

template <typename T>
bool KSafeQueue<T>::pop_front(T& value)
{
	m_lock.lock();
	if (QList<T>::size() == 0)
		m_wait.wait(&m_lock);
	if (QList<T>::size() == 0)
		return false;
	value = QList<T>::front();
	QList<T>::pop_front();
	m_lock.unlock();
	return true;
}
