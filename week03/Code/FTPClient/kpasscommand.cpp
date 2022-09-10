#include "kpasscommand.h"

KPassCommand::KPassCommand(KSender* pSender) : KAbstractCommand(pSender)
{
}

KPassCommand::~KPassCommand()
= default;

bool KPassCommand::execute(list_str& cmdArgs)
{
	makeRequest(CMD_NAME_MAP.find(CMD_NAME::PASS)->second, cmdArgs);
	sendRequest();
	return true;
}
