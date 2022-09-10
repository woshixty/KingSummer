// -------------------------------------------------------
// KAcceptTask.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/15
// ���������� ����socket���ӵ�������
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
