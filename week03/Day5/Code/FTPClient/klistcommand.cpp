#include "klistcommand.h"

KListCommand::KListCommand(KSender* pSender) : KAbstractCommand(pSender)
{
}

KListCommand::~KListCommand()
= default;

bool KListCommand::execute(list_str& cmdArgs)
{
	m_request.initialize(CMD_NAME_MAP.find(CMD_NAME::LIST)->second, cmdArgs);
	if (!initDataSocket())
		return false;
	sendRequest();
	if (m_response.code() != 150)
		return false;
	return recvLongMsg();
}
