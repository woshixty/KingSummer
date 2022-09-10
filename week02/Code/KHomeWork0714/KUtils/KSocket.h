// -------------------------------------------------------
// KSocket.h
// 创建者： xie tingyu
// 创建时间： 2022/7/15
// 功能描述： 封装Socket类
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _KSOCKET_H_
#define _KSOCKET_H_

#include <iostream>
#include <WinSock2.h>

#pragma comment(lib,"ws2_32.lib")

#define DATA_LEN_1 1024;

const int DATA_LEN_2 = 1024;

class KSocket
{
	using string = std::string;

public:
	KSocket();
	KSocket(SOCKET s, SOCKADDR_IN svr_addr);
	~KSocket();
	bool initSocket();
	bool connectToSvr(PCSTR ipv4_addr, u_short port);
	bool sendMsg(char *msg, int len);
	char* getMsg();
	void closeConnection();
	string getIpAddr();

private:
	int m_ret{};
	int m_sbytes{};
	WSADATA m_wsadata{};
	SOCKET m_socket{};
	SOCKADDR_IN m_svr_addr;
	// 发送数据缓冲区
	BYTE *m_sbuffer;
	// 接收数据缓冲区
	char *m_rbuffer;
	int m_rbytes = 0;
	char m_svr_ip[64] = { 0 };
};

#endif
