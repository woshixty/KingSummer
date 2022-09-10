// -------------------------------------------------------
// KSendMsgTask.h
// 创建者： xie tingyu
// 创建时间： 2022/7/15
// 功能描述： 发送数据的任务类
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _KSENDMSGTASK_H_
#define _KSENDMSGTASK_H_

#include "KRunnable.h"
#include "KEchoServer.h"

class KSendMsgTask : public KRunnable
{
public:
	KSendMsgTask(KEchoServer* server);

	void runtask() override;
private:
	KEchoServer* m_server;
};

#endif
