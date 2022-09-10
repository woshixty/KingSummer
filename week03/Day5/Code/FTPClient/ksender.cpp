#include "ksender.h"
#include "kutils.h"

#include <utility>

KSender::KSender()
{
	m_commandSocket.reset(new KSocket());
	m_dataSocket.reset(new KSocket());
	m_dataServer.reset(new KSocketServer());
	m_ret = false;
	m_isConnected = false;
	m_port = 0;
	m_port_data = 0;
}

KSender::~KSender()
= default;

bool KSender::initializeCommandSocket(string ipv4addr, u_short port)
{
	m_ipv4addr = std::move(ipv4addr);
	m_port = port;
	return true;
}

bool KSender::connect(KResponse& response)
{
	m_ret = m_commandSocket->createSocket();
	m_ret = m_commandSocket->connectToHost(m_ipv4addr, m_port);
	if (m_ret)
		m_isConnected = true;
	else
		return false;
	m_commandSocket->recvMsg(m_responseStr);
	response.initialize(m_responseStr);
	KPrint::printResponse(response);
	return m_ret;
}

bool KSender::initializeDataSocket(string ipv4addr, u_short port)
{
	m_ipv4addr_data = std::move(ipv4addr);
	m_port_data = port;
	return true;
}

u_short KSender::serverBindPort()
{
	m_ret = m_dataServer->createSocket();
	return m_dataServer->bindPort();
}

bool KSender::sendCommand(const KRequest& request, KResponse& response)
{
	request.getRequestStr(m_requestStr);
	KPrint::printRequest(m_requestStr);
	m_ret = m_commandSocket->sendMsg(m_requestStr.c_str(), m_requestStr.size());
	m_ret = m_commandSocket->recvMsg(m_responseStr);
	response.initialize(m_responseStr);
	KPrint::printResponse(m_responseStr);
	return true;
}

bool KSender::sendCommand()
{
	KPrint::printRequest(m_requestStr);
	m_ret = m_commandSocket->sendMsg(m_requestStr.c_str(), m_requestStr.size());
	m_ret = m_commandSocket->recvMsg(m_responseStr);
	KPrint::printResponse(m_responseStr);
	return true;
}

bool KSender::recvFile(FILE* file, KResponse& response)
{
	if (!prepareForData())
		return false;
	m_ret = m_dataSocket->recvFile(file);
	m_ret = m_dataSocket->closeConnection();
	m_ret = m_commandSocket->recvMsg(m_responseStr);
	response.initialize(m_responseStr);
	KPrint::printResponse(response);
	return true;
}

bool KSender::sendFile(FILE* file, KResponse& response)
{
	if (!prepareForData())
		return false;
	m_ret = m_dataSocket->sendFile(file);
	m_ret = m_dataSocket->closeConnection();
	m_ret = m_commandSocket->recvMsg(m_responseStr);
	response.initialize(m_responseStr);
	KPrint::printResponse(response);
	return true;
}

bool KSender::recvDataMsg(KResponse& response, string& longmsg)
{
	if (!prepareForData())
		return false;
	m_ret = m_dataSocket->recvLongMsg(longmsg);
	m_ret = m_dataSocket->closeConnection();
	m_ret = m_commandSocket->recvMsg(m_responseStr);
	response.initialize(m_responseStr);
	KPrint::printResponse(response);
	return true;
}

bool KSender::prepareForData() const
{
	if(m_type)
	{
		// 主动模式
		const SOCKET socket = m_dataServer->acceptSocket();
		if (socket == 0)
			return false;
		m_dataServer->closeconnection();
		return m_dataSocket->setSocket(socket);
	}
	// 被动模式
	return m_dataSocket->createSocket() && m_dataSocket->connectToHost(m_ipv4addr_data, m_port_data);
}

bool KSender::shutdownCommandSocket()
{
	m_ret = m_commandSocket->shutdownConnection();
	if(m_ret)
		m_isConnected = false;
	return m_ret;
}

bool KSender::closeCommandSocket()
{
	m_ret = m_commandSocket->closeConnection();
	if (m_ret)
		m_isConnected = false;
	return m_ret;
}

bool KSender::serverListenSocket() const
{
	return m_dataServer->listenSocket();
}
