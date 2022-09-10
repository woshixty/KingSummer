#include "pch.h"
#include "KSocket.h"
#include <WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

KSocket::KSocket()
{
	m_sbuffer = new BYTE[1024];
	m_rbuffer = new char[1024];
}

KSocket::KSocket(SOCKET s, SOCKADDR_IN svr_addr)
{
	m_socket = s;
	m_svr_addr = svr_addr;
	inet_ntop(AF_INET, &m_svr_addr.sin_addr, m_svr_ip, sizeof(m_svr_ip));
	m_sbuffer = new BYTE[1024];
	m_rbuffer = new char[1024];
}

KSocket::~KSocket()
{
	closesocket(m_socket);
	WSACleanup();
	delete m_sbuffer;
	delete m_rbuffer;
}

bool KSocket::initSocket()
{
	m_ret = WSAStartup(MAKEWORD(2, 3), &m_wsadata);
	if (m_ret != 0)
	{
		std::cerr << "WSAStartup failed, Error Code : " << WSAGetLastError() << std::endl;
		return false;
	}
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		std::cout << "create socket failed, Error Code : " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;
}

bool KSocket::connectToSvr(PCSTR ipv4_addr, u_short port)
{
	m_svr_addr.sin_family = AF_INET;
	m_svr_addr.sin_port = htons(port);
	inet_pton(AF_INET, ipv4_addr, &m_svr_addr.sin_addr.S_un.S_addr);
	inet_ntop(AF_INET, &m_svr_addr.sin_addr, m_svr_ip, sizeof(m_svr_ip));
	m_ret = connect(m_socket, (SOCKADDR*)&m_svr_addr, sizeof(SOCKADDR));
	if (m_ret == SOCKET_ERROR)
	{
		std::cout << "connect socket failed, Error Code : " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;
}

bool KSocket::sendMsg(char* msg, int len)
{
	//// 每次发送1024BYTE的数据
	//int sendTimes = len / 1024 + 1;
	//for (int i = 0; i < sendTimes; ++i)
	m_sbytes = send(m_socket, msg, len, 0);

	if (m_sbytes == SOCKET_ERROR)
	{
		std::cout << "send msg to socket failed, Error Code : " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;
}

char* KSocket::getMsg()
{
	// 清空缓存
	memset(m_rbuffer, 0, sizeof(m_rbuffer));
	m_rbytes = recv(m_socket, m_rbuffer, sizeof(m_rbuffer), 0);
	if (m_rbytes == SOCKET_ERROR)
	{
		std::cout << "get msg from socket failed, Error Code : " << WSAGetLastError() << std::endl;
		return nullptr;
	}
	return m_rbuffer;
}

void KSocket::closeConnection()
{
	closesocket(m_socket);
}

KSocket::string KSocket::getIpAddr()
{
	return m_svr_ip;
}
