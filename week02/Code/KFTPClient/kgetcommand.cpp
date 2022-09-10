#include "kgetcommand.h"

KGetCommand::KGetCommand()
{
}

KGetCommand::~KGetCommand()
{
}

void KGetCommand::makeOptUtf8OnPacket(string& packet, list_str& cmdArgs)
{
	packet += "RETR ";
	makePacket(packet, cmdArgs);
}

BOOL KGetCommand::executeCommand(KSocket* ptcpSocket, list_str& cmdArgs)
{
	if(cmdArgs.size() != 1)
	{
		std::cerr << "get 指令参数有误！" << std::endl;
		return false;
	}
	m_filename = cmdArgs.front();
	m_dataPort = sendPASV(ptcpSocket);
	string packet;
	createPacketSend(packet, cmdArgs, ptcpSocket);
	ptcpSocket->recvCommandMsg(m_reply);
	m_commandRes.initialization(m_reply);
	KPrint::printCommandRes(m_commandRes);
	return createSocketRecvF(ptcpSocket->getIpv4AddrP(), m_dataPort, m_filename);
}

BOOL KGetCommand::waitForServerReply(KSocket* ptcpSocket, string& reply)
{
	return ptcpSocket->recvCommandMsg(reply);
}
