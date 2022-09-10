#include "kabstractcommand.h"
#include "kprint.h"
#include "kutils.h"
#include "ksocketserver.h"
#include "kiputils.h"

#include <utility>


KAbstractCommand::KAbstractCommand(KSender* pSender)
{
	m_sender = pSender;
	m_ret = false;
}

KAbstractCommand::~KAbstractCommand()
= default;

bool KAbstractCommand::initDataSocket()
{
	if(m_sender->type())
	{
		const u_short port = m_sender->serverBindPort();
		// 主动
		KIpUtils::generatePortRequest(m_temp_request, port, m_sender->netType());
		sendTempRequest();
		if (m_temp_respond.code() != 200)
			return false;
		return m_sender->serverListenSocket();
	}
	// 被动
	m_temp_request.initialize(CMD_STR_MAP.find(CMD_STR::PASV)->second);
	// 初始化端口与IP
	sendTempRequest();
	if (m_temp_respond.code() != 227)
		return false;
	const u_short port = KUtils::getPortFromPasvRes(m_temp_respond);
	m_sender->initializeDataSocket(m_sender->ipv4addr(), port);
	return true;
}

void KAbstractCommand::makeRequest(string cmdName, const list_str& cmdArgs)
{
	m_request.initialize(std::move(cmdName), cmdArgs);
}

void KAbstractCommand::setPSender(KSender* pSender)
{
	m_sender = pSender;
}

bool KAbstractCommand::recvLongMsg()
{
	m_ret = m_sender->recvDataMsg(m_response, m_longmsg);
	KPrint::printLongMsg(m_longmsg);
	return true;
}

bool KAbstractCommand::recvFile(const string& filename)
{
	FILE* file = KUtils::createFile("", filename);
	if (file == nullptr)
		return false;
	m_sender->recvFile(file, m_response);
	fclose(file);
	return true;
}

bool KAbstractCommand::sendFile(const string& filename)
{
	FILE* file = KUtils::openFile(filename);
	if (file == nullptr)
		return false;
	m_sender->sendFile(file, m_response);
	fclose(file);
	return true;
}

bool KAbstractCommand::sendRequest()
{
	return m_sender->sendCommand(m_request, m_response);
}

bool KAbstractCommand::sendTempRequest()
{
	return m_sender->sendCommand(m_temp_request, m_temp_respond);
}
