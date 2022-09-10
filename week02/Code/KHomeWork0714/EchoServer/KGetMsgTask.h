// -------------------------------------------------------
// KGetMsgTask.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/15
// ���������� �������ݵ�������
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
