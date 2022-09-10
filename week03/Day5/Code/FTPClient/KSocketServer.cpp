#include "ksocketserver.h"
#include "kprint.h"

KSocketServer::KSocketServer()
{
	m_ret = WSAStartup(MAKEWORD(2, 3), &m_wsadata);
	if (m_ret != 0)
		KPrint::printFailError("WSAStartup", WSAGetLastError());
}

KSocketServer::~KSocketServer()
{
	closeconnection();
}

bool KSocketServer::createSocket()
{
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
		return KPrint::printFailError("Create Socket", WSAGetLastError());
	return true;
}

u_short KSocketServer::bindPort()
{
	m_svr_addr.sin_family = AF_INET;
	m_svr_addr.sin_port = htons(0);
	m_svr_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	m_ret = bind(m_socket, (SOCKADDR*)&m_svr_addr, sizeof(m_svr_addr));
	if (m_ret == SOCKET_ERROR)
		return KPrint::printFailError("Bind Port", WSAGetLastError());
	m_ret = getsockname(m_socket, (sockaddr*)&m_svr_addr, &m_len);
	m_port = ntohs(m_svr_addr.sin_port);
	return m_port;
}

bool KSocketServer::listenSocket()
{
	m_ret = listen(m_socket, 10);
	if (m_ret == SOCKET_ERROR)
		return KPrint::printFailError("Listen Port", WSAGetLastError());
	return true;
}

SOCKET KSocketServer::acceptSocket()
{
	const SOCKET csocket = accept(m_socket, (SOCKADDR*)&m_cli_addr, &m_len);
	if (csocket == INVALID_SOCKET)
	{
		KPrint::printFailError("Accept Connection", WSAGetLastError());
		return 0;
	}
	m_isConnected = false;
	return csocket;
}

bool KSocketServer::closeconnection()
{
	if (!m_isConnected)
		return true;
	m_ret = closesocket(m_socket);
	if (m_ret)
		return KPrint::printFailError("Close Connection", WSAGetLastError());
	m_isConnected = false;
	return  true;
}
