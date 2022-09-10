#pragma once

#include <list>

template <typename C>
class CThreadSafeQueue : protected std::list<C>
{
public:
	CThreadSafeQueue(int nMaxCount)
	{
		m_bOverflow = false;

		m_hSemaphore = ::CreateSemaphore(
			nullptr,	// no security attributes
			0,				// initial count
			nMaxCount,		// max count
			nullptr				// anonymous
		);
	}

	~CThreadSafeQueue()
	{
		CloseHandle(m_hSemaphore);
		m_hSemaphore = nullptr;
	}

	void push(C& c)
	{
		CComCritSecLock<CComAutoCriticalSection> lock( m_crit, true );
		push_back( c );
		lock.Unlock();

		if (!ReleaseSemaphore(m_hSemaphore, 1, nullptr))
		{
			// If the semaphore is full, then take back the entry.
			lock.Lock();
			std::list<C>::pop_back();
			if (GetLastError() == ERROR_TOO_MANY_POSTS)
			{
				m_bOverflow = true;
			}
		}
	}

	bool pop(C& c)
	{
		CComCritSecLock<CComAutoCriticalSection> lock( m_crit, true );

		// If the user calls pop() more than once after the
		// semaphore is signaled, then the semaphore count will
		// get out of sync.  We fix that when the queue empties.
		if (std::list<C>::empty())
		{
			while (WaitForSingleObject(m_hSemaphore, 0) != WAIT_TIMEOUT) 
			{}
			return false;
		}

		c = std::list<C>::front();
		std::list<C>::pop_front();

		return true;
	}

	// If overflow, use this to clear the queue.
	void clear()
	{
		CComCritSecLock<CComAutoCriticalSection> lock( m_crit, true );
		for (DWORD i = 0; i < std::list<C>::size(); i++)
			WaitForSingleObject(m_hSemaphore, 0);
		std::list<C>::clear();
		m_bOverflow = false;
	}

	bool overflow() const
	{
		return m_bOverflow;
	}

	// 获取线程安全容器类的信号量句柄
	HANDLE GetWaitHandle() const { return m_hSemaphore; }

protected:
	HANDLE m_hSemaphore;

	CComAutoCriticalSection m_crit;

	bool m_bOverflow;
};
