#include "kputcommand.h"

KPutCommand::KPutCommand()
{
}

KPutCommand::~KPutCommand()
{
}

void KPutCommand::makeOptUtf8OnPacket(string& packet, list_str& cmdArgs)
{
	packet += "STOR ";
	makePacket(packet, cmdArgs);
}

BOOL KPutCommand::executeCommand(KSocket* ptcpSocket, list_str& cmdArgs)
{
	if (cmdArgs.size() != 1)
	{
		std::cerr << "put 指令参数有误！" << std::endl;
		return false;
	}
	m_filename = cmdArgs.front();
	m_dataPort = sendPASV(ptcpSocket);
	FILE* file = fopen(m_filename.c_str(), "rb");
	if(file == nullptr)
	{
		std::cerr << "put 文件为空！" << std::endl;
		return false;
	}
	string packet;

	string temp = cmdArgs.front();
	cmdArgs.pop_front();
	size_type iPos = temp.find_last_of('\\') + 1;
	temp = temp.substr(iPos, temp.length() - iPos);
	cmdArgs.push_back(temp);

	createPacketSend(packet, cmdArgs, ptcpSocket);
	ptcpSocket->recvCommandMsg(m_reply);
	m_commandRes.initialization(m_reply);
	KPrint::printCommandRes(m_commandRes);
	return createSocketUploadF(ptcpSocket->getIpv4AddrP(), m_dataPort, file);
}

BOOL KPutCommand::waitForServerReply(KSocket* ptcpSocket, string& reply)
{
	return ptcpSocket->recvCommandMsg(reply);
}
