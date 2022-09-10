// -------------------------------------------------------
// ksocket.h
// 创建者： xie tingyu
// 创建时间： 2022/7/15
// 功能描述： 封装Socket类
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_SOCKET_H_
#define _K_SOCKET_H_

#include "kprint.h"

#include <iostream>
#include <WinSock2.h>

#pragma comment(lib,"ws2_32.lib")

#define DATA_LEN 2048

class KSocket
{
public:
	explicit KSocket();
	~KSocket();
	bool createSocket();
	bool connectToHost(string ipv4addr, u_short port);
	bool sendMsg(const char* msg, size_type size);
	bool recvMsg(string& msg);
	bool recvLongMsg(string& msg);
	bool recvFile(FILE* pFile);
	bool sendFile(FILE* pFile);
	bool shutdownConnection();
	bool closeConnection();
	bool setSocket(SOCKET otherSocket);

	string ipv4addr() { return m_ipv4addr; }

private:
	int m_ret = 0;
	char m_buffer[DATA_LEN]{};
	bool m_isConnected = false;
	WSADATA m_wsadata{};
	SOCKET m_socket{};
	SOCKADDR_IN m_svrAddr{};
	string m_ipv4addr;
	u_short m_port{};
};

#endif