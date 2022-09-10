// -------------------------------------------------------
// ksocketserver.h
// 创建者： xie tingyu
// 创建时间： 2022/7/15
// 功能描述： 封装SocketServer类
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_SOCKET_SERVER_H_
#define _K_SOCKET_SERVER_H_

#include <WinSock2.h>

#pragma comment(lib,"ws2_32.lib")

class KSocketServer
{
public:
	KSocketServer();
	~KSocketServer();
	bool createSocket();
	u_short bindPort();
	bool listenSocket();
	SOCKET acceptSocket();
	bool closeconnection();

private:
	int m_len = sizeof(SOCKADDR);
	int m_ret;
	bool m_isConnected = false;
	char m_buffer[1024] = { 0 };
	WSADATA m_wsadata{};
	SOCKET m_socket{};
	SOCKADDR_IN m_svr_addr{}, m_cli_addr{};
	u_short m_port{};
};

#endif