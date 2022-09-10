// -------------------------------------------------------
// EchoClient.h
// 创建者： xie tingyu
// 创建时间： 2022/7/15
// 功能描述： socket客户端，收发数据
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