// -------------------------------------------------------
// KThread.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/15
// ���������� ��װ�߳���
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _KTHREAD_H_
#define _KTHREAD_H_

#include "KRunnable.h"
#include <process.h>

class KThread
{
public:
	KThread(KRunnable *task);
	HANDLE getHandle() { return m_thread; }
	void run();

private:
	HANDLE m_thread;
	KRunnable* m_task;
	unsigned int threadID;
};

#endif