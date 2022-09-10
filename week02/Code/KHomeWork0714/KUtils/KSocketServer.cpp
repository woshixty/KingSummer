#include "pch.h"
#include "KSocketServer.h"

bool KSocketServer::initSocket()
{
	m_ret = WSAStartup(MAKEWORD(2, 3), &m_wsadata);
	if (m_ret != 0)
	{
		std::cerr << "WSAStartup failed." << std::endl;
		return false;
	}
	m_ssocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_ssocket == INVALID_SOCKET)
	{
		std::cout << "Error Code : " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;
}

bool KSocketServer::bindPort(u_short port)
{
	m_svr_addr.sin_family = AF_INET;
	m_svr_addr.sin_port = htons(port);
	m_svr_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	m_ret = bind(m_ssocket, (SOCKADDR*)&m_svr_addr, sizeof(m_svr_addr));
	if (m_ret == SOCKET_ERROR)
	{
		std::cout << "Error Code : " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;
}

bool KSocketServer::listenSocket()
{
	// 建立监听队列,让套接字进入被动监听状态
	m_ret = listen(m_ssocket, 10);
	if (m_ret == SOCKET_ERROR)
	{
		std::cout << "Error Code : " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;
}

KSocket* KSocketServer::acceptSocket()
{
	SOCKET m_csocket = accept(m_ssocket, (SOCKADDR*)&m_cli_addr, &m_len);
	if (m_csocket == -1)
	{
		std::cout << "Error Code : " << WSAGetLastError() << std::endl;
		return nullptr;
	}
	// 从网络中获取的数据是大端,打印就需要将大端字节序转换成小端字节序
	inet_ntop(AF_INET, &m_cli_addr.sin_addr, m_cli_ip, sizeof(m_cli_ip));
	std::cout << "client ip : " << m_cli_ip << R"(已连接)" << std::endl;
	KSocket* ksocket = new KSocket(m_csocket, m_cli_addr);
	return ksocket;
}