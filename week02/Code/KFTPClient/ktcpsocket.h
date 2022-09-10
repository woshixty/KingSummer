#ifndef __K_TCP_SOCKET_H_
#define __K_TCP_SOCKET_H_

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib")


class KTcpSocket
{
public:
	KTcpSocket(std::string _ip, WORD _port);
	~KTcpSocket();

	BOOL initTcpSocket();
	BOOL setWindowSockVersion();

	BOOL sockBind();
	BOOL sockListen(int backlog);

	BOOL waitForConnected();

	BOOL connectToHost();
	BOOL disconnectFromHost();

	int sockSend(BYTE buffer[], int len);
	int sockRecv(BYTE buffer[], int maxLen);

private:
	SOCKET m_socket;
	SOCKET m_clisocket;
	SOCKADDR_IN m_cliAddr{};
	WORD m_port;
	std::string m_ip;
};

#endif

