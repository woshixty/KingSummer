// -------------------------------------------------------
// KSendMsgTask.h
// 创建者： xie tingyu
// 创建时间： 2022/7/15
// 功能描述： 发送信息的任务类
// Copyright 2013 Kingsoft
// --------------------------------------------------------
#ifndef _KSENDMSGTASK_H_
#define _KSENDMSGTASK_H_

#include "KEchoClient.h"
#include "KRunnable.h"

class KSendMsgTask : public KRunnable
{
public:
	KSendMsgTask(KEchoClient* client);
	void runtask() override;
private:
	KEchoClient* m_client;
};

#endif