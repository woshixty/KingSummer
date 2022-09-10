// -------------------------------------------------------
// KAcceptTask.h
// 创建者： xie tingyu
// 创建时间： 2022/7/15
// 功能描述： 接受socket连接的任务类
// Copyright 2013 Kingsoft
// --------------------------------------------------------
#ifndef _KACCEPTTASK_H_
#define _KACCEPTTASK_H_

#include "KEchoServer.h"
#include "KRunnable.h"

class KAcceptThread : public KRunnable
{
public:
	KAcceptThread(KEchoServer* server);
	void runtask() override;
private:
	KEchoServer* m_server;
};

#endif
