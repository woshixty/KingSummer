#include "kmkdircommand.h"

KMkdirCommand::KMkdirCommand(KSender* pSender): KAbstractCommand(pSender)
{
}

KMkdirCommand::~KMkdirCommand()
= default;

bool KMkdirCommand::execute(list_str& cmdArgs)
{
	if (cmdArgs.size() != 1)
		return KPrint::printClientError(CLIENT_ERROR::ARGS_ERROR);
	makeRequest(CMD_NAME_MAP.find(CMD_NAME::MKDIR)->second, cmdArgs);
	sendRequest();
	return true;
}