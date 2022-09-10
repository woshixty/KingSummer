#include "pch.h"
#include "KThread.h"

//unsigned __stdcall SecondThreadFunc(void* pArguments)
//{
//	KRunnable* task = (KRunnable*)pArguments;
//	// 执行任务函数
//	task->runtask();
//	_endthreadex(0);
//	return 0;
//}
DWORD WINAPI TASKT(LPVOID lpThreadParameter)
{
	KRunnable* task = (KRunnable*)lpThreadParameter;
	task->runtask();
	return 0;
}


KThread::KThread(KRunnable *task)
{
	m_task = task;
}

void KThread::run()
{
	if (m_task == nullptr)
		throw "任务为空，不可执行";
	// m_thread = (HANDLE)_beginthreadex(m_task, 0, SecondThreadFunc, NULL, 0, &threadID);
	m_thread = CreateThread(NULL, 0, TASKT, (LPVOID)m_task, 0, NULL);
}
