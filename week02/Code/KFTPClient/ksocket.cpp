#include "pch.h"
#include "ksocket.h"
#include <WS2tcpip.h>

#include <utility>

#pragma comment(lib,"ws2_32.lib")

KSocket::KSocket()
{
	initSocket();
}

KSocket::KSocket(char* ipv4_addr, u_short port)
{
	m_ipv4_addr = ipv4_addr;
	m_port = port;
	initSocket();
}

KSocket::KSocket(SOCKET s, SOCKADDR_IN svr_addr)
{
	m_socket = s;
	m_svrAddr = svr_addr;
	inet_ntop(AF_INET, &m_svrAddr.sin_addr, m_svrIp, sizeof(m_svrIp));
	initSocket();
}

KSocket::~KSocket()
{
	WSACleanup();
	closesocket(m_socket);
}

BOOL KSocket::initSocket()
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
		std::cerr << "create socket failed, Error Code : " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;
}

BOOL KSocket::connectToHost()
{
	m_svrAddr.sin_family = AF_INET;
	m_svrAddr.sin_port = htons(m_port);

	inet_pton(AF_INET, m_ipv4_addr, &m_svrAddr.sin_addr.S_un.S_addr);
	inet_ntop(AF_INET, &m_svrAddr.sin_addr, m_svrIp, sizeof(m_svrIp));
	m_ret = connect(m_socket, reinterpret_cast<SOCKADDR*>(&m_svrAddr), sizeof(SOCKADDR));
	if (m_ret == SOCKET_ERROR)
	{
		std::cerr << "connect socket failed, Error Code : " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;
}

BOOL KSocket::connectToHost(string ipv4addr, u_short port)
{
	m_ipv4addr = std::move(ipv4addr);
	m_port = port;
	m_svrAddr.sin_family = AF_INET;
	m_svrAddr.sin_port = htons(m_port);
	inet_pton(AF_INET, m_ipv4_addr, &m_svrAddr.sin_addr.S_un.S_addr);
	m_ret = connect(m_socket, reinterpret_cast<SOCKADDR*>(&m_svrAddr), sizeof(SOCKADDR));
	if (m_ret == SOCKET_ERROR)
		return KPrint::printFailError("Connect Socket", WSAGetLastError());
	return true;
}

BOOL KSocket::sendMsg(CHAR* msg, size_t len)
{
	// 每次发送2048BYTE的数据
	m_bytes = send(m_socket, msg, len, 0);
	if (m_bytes == SOCKET_ERROR)
	{
		std::cerr << "send msg to socket failed, Error Code : " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;
}

BOOL KSocket::recvCommandMsg(string& msg)
{
	msg.clear();
	memset(m_buffer, '\0', DATA_LEN);
	m_bytes = recv(m_socket, m_buffer, DATA_LEN, 0);
	if (m_bytes == SOCKET_ERROR)
	{
		std::cerr << "recvmsg failed, error code : " << WSAGetLastError() << std::endl;
		return false;
	}
	msg.append(m_buffer, m_bytes);
	return true;
}

BOOL KSocket::recvLongMsg(string& msg)
{
	msg.clear();
	do {
		memset(m_buffer, '\0', DATA_LEN);
		m_bytes = recv(m_socket, m_buffer, DATA_LEN, 0);
		if (m_bytes == SOCKET_ERROR)
		{
			std::cerr << "recvmsg failed, error code : " << WSAGetLastError() << std::endl;
			return false;
		}
		msg.append(m_buffer, m_bytes);
	} while (m_bytes > 0);
	return true;
}

BOOL KSocket::recvFile(FILE* pFile)
{
	do {
		memset(m_buffer, '\0', DATA_LEN);
		m_bytes = recv(m_socket, m_buffer, DATA_LEN, 0);
		if (m_bytes == SOCKET_ERROR)
		{
			std::cerr << "recvFile failed, Error Code : " << WSAGetLastError() << std::endl;
			return false;
		}
		fwrite(m_buffer, m_bytes, 1, pFile);
	} while (m_bytes > 0);
	return true;
}

BOOL KSocket::sendFile(FILE* pFile)
{
	int nCounts = 0;
	do {
		memset(m_buffer, '\0', DATA_LEN);
		nCounts = fread(m_buffer, 1, DATA_LEN, pFile);
		m_bytes = send(m_socket, m_buffer, nCounts, 0);
		if (m_bytes == SOCKET_ERROR)
		{
			std::cerr << "sendFile failed, Error Code : " << WSAGetLastError() << std::endl;
			return false;
		}
	} while (m_bytes > 0);
	return true;
}

void KSocket::closeConnection() const
{
	closesocket(m_socket);
}

KSocket::string KSocket::getIp4AddrS()
{
	return m_svrIp;
}

BOOL KSocket::sendCommand(const char* pCommand, int size)
{
	m_bytes = send(m_socket, pCommand, size, 0);
	if (m_bytes == SOCKET_ERROR)
	{
		std::cerr << "send command to socket failed, Error Code : " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;
}

CHAR* KSocket::getIpv4AddrP()
{
	return m_ipv4_addr;
}
