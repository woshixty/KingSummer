#include "kusercommand.h"

#define DEBUG


KUserCommand::KUserCommand()
{

}

KUserCommand::~KUserCommand()
{

}

VOID KUserCommand::makeOptUtf8OnPacket(string& packet, list_str& cmdArgs)
{
	packet += "USER ";
	makePacket(packet, cmdArgs);
}

BOOL KUserCommand::executeCommand(KSocket* ptcpSocket, list_str& cmdArgs)
{
	string packet;
	return createPacketSend(packet, cmdArgs, ptcpSocket);
}

BOOL KUserCommand::waitForServerReply(KSocket* ptcpSocket, std::string& reply)
{
	return ptcpSocket->recvCommandMsg(reply);
}
