#include "kmessagequeue.h"

#include <QDebug>

KMessageQueue::KMessageQueue(QObject* parent)
	: QObject(parent)
{
	m_bTerminate = false;
}

KMessageQueue::~KMessageQueue()
= default;

void KMessageQueue::push_back(const KMessage& value)
{
	m_lock.lock();
	m_messageList.push_back(value);
	m_lock.unlock();
	m_condition.notify_all();
}

bool KMessageQueue::pop_front(KMessage& value)
{
	m_lock.lock();
	while (m_messageList.empty())
	{
		m_condition.wait(&m_lock);
		if (m_bTerminate)
		{
			// 主动停止线程导致的列表为空的判断
			m_lock.unlock();
			return false;
		}
	}
	if (m_bTerminate)
	{
		m_lock.unlock();
		return false;
	}
	value = m_messageList.front();
	m_messageList.pop_front();
	m_lock.unlock();
	return true;
}

void KMessageQueue::stopQueue()
{
	m_bTerminate = true;
	m_lock.lock();
	m_condition.notify_all();
	m_lock.unlock();
}

void KMessageQueue::startQueue()
{
	m_bTerminate = false;
}
