#include "kquitcommand.h"

KQuitCommand::KQuitCommand(KSender* pSender) : KAbstractCommand(pSender)
{
}

KQuitCommand::~KQuitCommand()
= default;

bool KQuitCommand::execute(list_str& cmdArgs)
{
	if (!cmdArgs.empty())
		return KPrint::printClientError(CLIENT_ERROR::ARGS_ERROR);
	makeRequest(CMD_NAME_MAP.find(CMD_NAME::QUIT)->second, cmdArgs);
	sendRequest();
	m_sender->closeCommandSocket();
	return true;
}
