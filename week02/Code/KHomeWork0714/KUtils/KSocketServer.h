// -------------------------------------------------------
// KSocketServer.h
// 创建者： xie tingyu
// 创建时间： 2022/7/15
// 功能描述： 封装SocketServer类
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _KSOCKETSERVER_H_
#define _KSOCKETSERVER_H_

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "KSocket.h"

#pragma comment(lib,"ws2_32.lib")

class KSocketServer
{
	using string = std::string;
public:
	bool initSocket();
	bool bindPort(u_short port);
	bool listenSocket();
	string getMsg();
	KSocket* acceptSocket();

private:
	int m_ret;
	int m_rbytes = 0, m_sbytes = 0;
	WSADATA m_wsadata;
	SOCKET m_ssocket;
	SOCKADDR_IN m_svr_addr, m_cli_addr;
	int m_len = sizeof(SOCKADDR);
	char m_cli_ip[64] = { 0 };
	// 接收数据缓冲区
	char m_rbuffer[1024] = { 0 };
};

#endif