#include "kabstractcommand.h"

#include "kutils.h"

KAbstractCommand::KAbstractCommand()
{
}

KAbstractCommand::~KAbstractCommand()
{
}

void KAbstractCommand::makePacket(string& packet, list_str& cmdArgs)
{
	for (auto cmd_arg : cmdArgs)
		packet += (cmd_arg + " ");
	packet.erase(packet.length() - 1);
	packet += "\r\n";
}

unsigned KAbstractCommand::sendPASV(KSocket* ptcpSocket)
{
	string packet = "PASV\r\n";
	ptcpSocket->sendCommand(packet.c_str(), packet.length());
	ptcpSocket->recvCommandMsg(m_reply);
	m_commandRes.initialization(m_reply);
	KPrint::printCommandRes(m_commandRes);
	return KUtils::getPortFromPasvRes(m_commandRes);
}

BOOL KAbstractCommand::createSocketRecvS(CHAR* pipAddr, unsigned dataPort)
{
	auto data_socket = new KSocket(pipAddr, dataPort);
	data_socket->connectToHost();
	string msg;
	data_socket->recvLongMsg(msg);
	std::cout << "recv data：\n" << msg << std::endl;
	data_socket->closeConnection();
	delete data_socket;
	return TRUE;
}

BOOL KAbstractCommand::createSocketRecvF(CHAR* pipAddr, unsigned dataPort, const string& filename)
{
	FILE* file = KUtils::createFile("", filename);
	if (file == nullptr)
		return FALSE;
 	auto data_socket = new KSocket(pipAddr, dataPort);
	data_socket->connectToHost();
	data_socket->recvFile(file);
	fclose(file);
	std::cout << "recv file：" << filename << std::endl;
	data_socket->closeConnection();
	delete data_socket;
	fclose(file);
	return TRUE;
}

BOOL KAbstractCommand::createSocketUploadF(CHAR* pipAddr, unsigned dataPort, FILE* file)
{
	auto data_socket = new KSocket(pipAddr, dataPort);
	data_socket->connectToHost();
	data_socket->sendFile(file);
	data_socket->closeConnection();
	delete data_socket;
	fclose(file);
	return TRUE;
}

BOOL KAbstractCommand::createPacketSend(string& packet, list_str& cmdArgs, KSocket * ptcpSocket)
{
	makeOptUtf8OnPacket(packet, cmdArgs);
	// 将数据通过 socket 发送给服务器
	return ptcpSocket->sendCommand(const_cast<char*>(packet.c_str()), packet.length());
}
