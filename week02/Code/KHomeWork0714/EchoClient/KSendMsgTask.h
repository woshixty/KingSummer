// -------------------------------------------------------
// KSendMsgTask.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/15
// ���������� ������Ϣ��������
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