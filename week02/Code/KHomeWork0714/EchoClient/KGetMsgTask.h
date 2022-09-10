// -------------------------------------------------------
// KGetMsgTask.h
// 创建者： xie tingyu
// 创建时间： 2022/7/15
// 功能描述： 接受信息的任务类
// Copyright 2013 Kingsoft
// --------------------------------------------------------
#ifndef _KGETMSGTASK_H_
#define _KGETMSGTASK_H_

#include <iostream>
#include "KEchoClient.h"
#include "KRunnable.h"

class KGetMsgTask : public KRunnable
{
public:
	KGetMsgTask(KEchoClient* client);
	void runtask() override;
private:
	KEchoClient* m_client;
};

#endif
