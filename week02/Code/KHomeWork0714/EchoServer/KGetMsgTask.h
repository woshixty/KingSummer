// -------------------------------------------------------
// KGetMsgTask.h
// 创建者： xie tingyu
// 创建时间： 2022/7/15
// 功能描述： 接收数据的任务类
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _KECHOSERVER_H_
#define _KECHOSERVER_H_

#include "KRunnable.h"
#include "KSocket.h"

class KGetMsgTask : public KRunnable
{
public:
	KGetMsgTask(KSocket* socket);
	void runtask() override;
private:
	KSocket* m_socket;
};

#endif
