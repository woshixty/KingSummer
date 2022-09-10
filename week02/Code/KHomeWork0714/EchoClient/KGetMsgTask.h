// -------------------------------------------------------
// KGetMsgTask.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/15
// ���������� ������Ϣ��������
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
