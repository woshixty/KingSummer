#include "klistcommand.h"

KListCommand::KListCommand()
{
}

KListCommand::~KListCommand()
{
}

VOID KListCommand::makeOptUtf8OnPacket(string& packet, list_str& cmdArgs)
{
	packet += "LIST ";
	makePacket(packet, cmdArgs);
}

BOOL KListCommand::executeCommand(KSocket* ptcpSocket, list_str& cmdArgs)
{
	// 发送PASV获得数据传输端口
	m_dataPort = sendPASV(ptcpSocket);
	string packet;
	createPacketSend(packet, cmdArgs, ptcpSocket);
	ptcpSocket->recvCommandMsg(m_reply);
	m_commandRes.initialization(m_reply);
	KPrint::printCommandRes(m_commandRes);
	return createSocketRecvS(ptcpSocket->getIpv4AddrP(), m_dataPort);
}

BOOL KListCommand::waitForServerReply(KSocket* ptcpSocket, string& reply)
{
	// 等待服务器发送数据,进行接收
	return ptcpSocket->recvCommandMsg(reply);
}
