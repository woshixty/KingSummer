// ReSharper disable All
#include "ktcpsocket.h"

KTcpSocket::KTcpSocket(std::string _ip, WORD _port) :
	m_ip(_ip),
	m_port(_port),
	m_socket(0),
	m_clisocket(0)
{
	
	initTcpSocket();
}

KTcpSocket::~KTcpSocket()
{
}

BOOL KTcpSocket::initTcpSocket()
{
	setWindowSockVersion();
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		WSACleanup();
		return FALSE;
	}
	return TRUE;
}

BOOL KTcpSocket::setWindowSockVersion()
{
	WSADATA wsaData;
	return WSAStartup(MAKEWORD(2, 3), &wsaData) == 0 ? (TRUE) : (FALSE);
}


BOOL KTcpSocket::sockBind()
{
	int ret;
	SOCKADDR_IN svr_addr;
	inet_pton(AF_INET, m_ip.c_str(), &svr_addr.sin_addr.S_un.S_addr);

	svr_addr.sin_family = AF_INET;
	svr_addr.sin_port = htons(m_port);

	ret = bind(m_socket, (SOCKADDR*)&svr_addr, sizeof(SOCKADDR));

	if (ret == SOCKET_ERROR)
	{
		closesocket(m_socket);
		WSACleanup();
		return FALSE;
	}

	return TRUE;
}

BOOL KTcpSocket::sockListen(int backlog)
{
	int ret;

	ret = listen(m_socket, backlog);
	if (ret == SOCKET_ERROR)
	{
		closesocket(m_socket);
		WSACleanup();
		return FALSE;
	}

	return TRUE;
}

BOOL KTcpSocket::waitForConnected()
{
	int len = sizeof(SOCKADDR);

	std::cout << "[Wait For Connect]" << std::endl;
	m_clisocket = accept(m_socket, (SOCKADDR*)&m_cliAddr, &len);
	if (m_clisocket == SOCKET_ERROR)
	{
		closesocket(m_socket);
		WSACleanup();
		return FALSE;
	}
	return TRUE;
}

BOOL KTcpSocket::connectToHost()
{
	BOOL ret;

	SOCKADDR_IN svr_addr;

	inet_pton(AF_INET, m_ip.c_str(), &svr_addr.sin_addr.S_un.S_addr);

	svr_addr.sin_family = AF_INET;
	svr_addr.sin_port = htons(m_port);
	
	ret = connect(m_socket,(const SOCKADDR *)&svr_addr,sizeof(SOCKADDR));
	if (ret == SOCKET_ERROR)
		return FALSE;

	return TRUE;
}

BOOL KTcpSocket::disconnectFromHost()
{
	if (m_socket > 0)
		closesocket(m_socket);
	return 0;
}

int KTcpSocket::sockSend(BYTE buffer[], int len)
{
	return send(m_socket, (const char*)buffer, len, 0);
}

int KTcpSocket::sockRecv(BYTE buffer[], int maxLen)
{
	return recv(m_socket,(char *)buffer,maxLen,0);
}