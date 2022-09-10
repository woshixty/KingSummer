// -------------------------------------------------------
// EchoClient.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/15
// ���������� socket�ͻ��ˣ��շ�����
// Copyright 2013 Kingsoft
// --------------------------------------------------------
#ifndef _ECHOCLIENT_H_
#define _ECHOCLIENT_H_

#include "KSocket.h"
#include <iostream>
#include <process.h>

class KEchoClient
{
	using string = std::string;

public:
	KEchoClient(string ipv4_addr, u_short port);
	~KEchoClient();
	void msgSendLoop();
	void msgGetLoop();
	void closeclient() { m_loop_tag = false; }

private:
	KSocket* m_socket;
	BOOL m_ret;
	string m_msg;
	BOOL m_loop_tag = true;
};

#endif