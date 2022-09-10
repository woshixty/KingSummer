#include "kpasscommand.h"

#define DEBUG

KPassCommand::KPassCommand()
{
}

KPassCommand::~KPassCommand()
{
}

VOID KPassCommand::makeOptUtf8OnPacket(string& packet, list_str& cmdArgs)
{
	packet += "PASS ";
	makePacket(packet, cmdArgs);
}

BOOL KPassCommand::executeCommand(KSocket* ptcpSocket, list_str& cmdArgs)
{
	string packet;
	return createPacketSend(packet, cmdArgs, ptcpSocket);
}

BOOL KPassCommand::waitForServerReply(KSocket* ptcpSocket, string& reply)
{
	return ptcpSocket->recvCommandMsg(reply);
}
