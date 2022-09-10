#include "ksocket.h"
#include <WS2tcpip.h>
#include <utility>

KSocket::KSocket()
{
	m_ret = WSAStartup(MAKEWORD(2, 3), &m_wsadata);
	if (m_ret != 0)
		KPrint::printFailError("WSAStartup", WSAGetLastError());
}

KSocket::~KSocket()
{
	WSACleanup();
	closeConnection();
}

bool KSocket::createSocket()
{
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
		return KPrint::printFailError("Create Socket", WSAGetLastError());
	return true;
}

bool KSocket::connectToHost(string ipv4addr, u_short port)
{
	m_ipv4addr = std::move(ipv4addr);
	m_port = port;
	m_svrAddr.sin_family = AF_INET;
	m_svrAddr.sin_port = htons(m_port);

	inet_pton(AF_INET, m_ipv4addr.c_str(), &m_svrAddr.sin_addr.S_un.S_addr);
	m_ret = connect(m_socket, (SOCKADDR*)&m_svrAddr, sizeof(SOCKADDR));
	if (m_ret == SOCKET_ERROR)
		return KPrint::printFailError("Connect Socket", WSAGetLastError());
	m_isConnected = true;
	return true;
}

bool KSocket::sendMsg(const char* msg, size_type size)
{
	m_ret = send(m_socket, msg, static_cast<int>(size), 0);
	if (m_ret == SOCKET_ERROR)
		return KPrint::printFailError("Send MSG To Socket", WSAGetLastError());
	return true;
}

bool KSocket::recvMsg(string& msg)
{
	msg.clear();
	memset(m_buffer, '\0', DATA_LEN);
	m_ret = recv(m_socket, m_buffer, DATA_LEN, 0);
	if (m_ret == SOCKET_ERROR)
		return KPrint::printFailError("Recv MSG", WSAGetLastError());
	msg.append(m_buffer, m_ret);
	return true;
}

bool KSocket::recvLongMsg(string& msg)
{
	msg.clear();
	do {
		memset(m_buffer, '\0', DATA_LEN);
		m_ret = recv(m_socket, m_buffer, DATA_LEN, 0);
		if (m_ret == SOCKET_ERROR)
			return KPrint::printFailError("Recv Long MSG", WSAGetLastError());
		msg.append(m_buffer, m_ret);
	} while (m_ret > 0);
	return true;
}

bool KSocket::recvFile(FILE* pFile)
{
	do {
		memset(m_buffer, '\0', DATA_LEN);
		m_ret = recv(m_socket, m_buffer, DATA_LEN, 0);
		if (m_ret == SOCKET_ERROR)
			return KPrint::printFailError("Recv File", WSAGetLastError());
		fwrite(m_buffer, m_ret, 1, pFile);
	} while (m_ret > 0);
	return true;
}

bool KSocket::sendFile(FILE* pFile)
{
	do {
		memset(m_buffer, '\0', DATA_LEN);
		const int nCounts = fread(m_buffer, 1, DATA_LEN, pFile);
		m_ret = send(m_socket, m_buffer, nCounts, 0);
		if (m_ret == SOCKET_ERROR)
			return KPrint::printFailError("Send File", WSAGetLastError());
	} while (m_ret > 0);
	return true;
}

bool KSocket::shutdownConnection()
{
	m_ret = shutdown(m_socket, SD_BOTH);
	if (m_ret)
		return KPrint::printFailError("ShutDown Connection", WSAGetLastError());
	return  true;
}

bool KSocket::closeConnection()
{
	if (!m_isConnected)
		return true;
	m_ret = closesocket(m_socket);
	if (m_ret)
		return KPrint::printFailError("Close Connection", WSAGetLastError());
	m_isConnected = false;
	return  true;
}

bool KSocket::setSocket(SOCKET otherSocket)
{
	closeConnection();
	m_socket = otherSocket;
	return true;
}
