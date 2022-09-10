// -------------------------------------------------------
// KThread.h
// 创建者： xie tingyu
// 创建时间： 2022/7/15
// 功能描述： 封装线程类
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