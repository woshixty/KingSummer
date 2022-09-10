#include "kcommandsender.h"

#include <utility>

KCommandSender::KCommandSender()
{
	m_commandSocket.reset(new KSocket());
	m_dataSocket.reset(new KSocket());
}

KCommandSender::~KCommandSender()
{
	m_commandSocket.release();
	m_dataSocket.release();
}

bool KCommandSender::initializeCommandSocket(string ipv4addr, u_short port) const
{
	return m_commandSocket->connectToHost(std::move(ipv4addr), port);
}

bool KCommandSender::initializeDataSocket(string ipv4addr, u_short port) const
{
	return m_dataSocket->connectToHost(std::move(ipv4addr), port);
}

bool KCommandSender::sendCommand(const KRequestPacket& packet, KCommandResponse& response)
{
	m_packetStr = packet.getPacketStr();
	m_ret = m_commandSocket->sendCommand(m_packetStr.c_str(), m_packetStr.size());
	if (!m_ret)
		return false;
	m_ret = m_commandSocket->recvCommandMsg(m_responseStr);
	if (!m_ret)
		return false;
	response.initialization(m_responseStr);
	return true;
}
