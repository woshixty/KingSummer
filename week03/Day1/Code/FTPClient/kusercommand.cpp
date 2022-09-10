#include "kusercommand.h"

KUserCommand::KUserCommand(KSender* pSender) : KAbstractCommand(pSender)
{
}

KUserCommand::~KUserCommand()
= default;

bool KUserCommand::execute(list_str& cmdArgs)
{
	makeRequest(CMD_NAME_MAP.find(CMD_NAME::USER)->second, cmdArgs);
	sendRequest();
	return true;
}
