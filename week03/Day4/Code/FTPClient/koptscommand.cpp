#include "koptscommand.h"

KOptsCommand::KOptsCommand(KSender* pSender) : KAbstractCommand(pSender)
{
}

KOptsCommand::~KOptsCommand()
= default;

bool KOptsCommand::execute(list_str& cmdArgs)
{
	makeRequest(CMD_NAME_MAP.find(CMD_NAME::OPTS)->second, cmdArgs);
	sendRequest();
	return true;
}

