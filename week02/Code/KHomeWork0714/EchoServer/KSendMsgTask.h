// -------------------------------------------------------
// KSendMsgTask.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/15
// ���������� �������ݵ�������
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
