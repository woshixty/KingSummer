#include "koptscommand.h"

#define DEBUG

KOptsCommand::KOptsCommand()
{
}

KOptsCommand::~KOptsCommand()
{
}

VOID KOptsCommand::makeOptUtf8OnPacket(string& packet, list_str& cmdArgs)
{
	packet += "OPTS ";
	makePacket(packet, cmdArgs);
}

BOOL KOptsCommand::executeCommand(KSocket* ptcpSocket, list_str& cmdArgs)
{
	string packet;
	return createPacketSend(packet, cmdArgs, ptcpSocket);
}

BOOL KOptsCommand::waitForServerReply(KSocket *ptcpSocket, string& reply)
{
	// 等待服务器发送数据,进行接收
	return ptcpSocket->recvCommandMsg(reply);
}
