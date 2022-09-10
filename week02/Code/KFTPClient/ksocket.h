// -------------------------------------------------------
// ksocket.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/15
// ���������� ��װSocket��
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_SOCKET_H_
#define _K_SOCKET_H_

#include <iostream>
#include <WinSock2.h>
#include <math.h>
#include "kprint.h"

#pragma comment(lib,"ws2_32.lib")

#define DATA_LEN 2048

class KSocket
{
	using string = std::string;

public:
	explicit KSocket();
	explicit KSocket(char* ipv4_addr, u_short port);
	explicit KSocket(SOCKET socket, SOCKADDR_IN svr_addr);
	~KSocket();
	BOOL initSocket();
	BOOL connectToHost();
	BOOL connectToHost(string ipv4addr, u_short port);
	BOOL sendMsg(CHAR* msg, size_t len);
	BOOL recvCommandMsg(string& msg);
	BOOL recvLongMsg(string& msg);
	BOOL recvFile(FILE* pFile);
	BOOL sendFile(FILE* pFile);
	VOID closeConnection() const;
	string getIp4AddrS();
	BOOL sendCommand(const char* pCommand, int size);
	CHAR* getIpv4AddrP();

private:
	WSADATA m_wsadata{};
	SOCKET m_socket{};
	SOCKADDR_IN m_svrAddr{};
	int m_ret{};
	// �շ����ݻ�����
	CHAR m_buffer[DATA_LEN]{};
	// ������ipv4��ַ
	char m_svrIp[64] = { 0 };
	char* m_ipv4_addr{};
	// �շ��ֽ���
	int m_bytes = 0;
	string m_ipv4addr;
	u_short m_port{};
};

#endif