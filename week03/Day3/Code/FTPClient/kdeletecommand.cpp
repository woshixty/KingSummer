#include "kdeletecommand.h"

KDeleteCommand::KDeleteCommand(KSender* pSender) : KAbstractCommand(pSender)
{
}

KDeleteCommand::~KDeleteCommand()
= default;

bool KDeleteCommand::execute(list_str& cmdArgs)
{
	if (cmdArgs.size() != 1)
		return KPrint::printClientError(CLIENT_ERROR::ARGS_ERROR);
	makeRequest(CMD_NAME_MAP.find(CMD_NAME::DELETE2)->second, cmdArgs);
	sendRequest();
	return true;
}
