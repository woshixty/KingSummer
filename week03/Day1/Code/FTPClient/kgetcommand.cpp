#include "kgetcommand.h"

#include "kutils.h"

KGetCommand::KGetCommand(KSender* pSender) : KAbstractCommand(pSender), m_pFile(nullptr)
{
}

KGetCommand::~KGetCommand()
= default;

bool KGetCommand::execute(list_str& cmdArgs)
{
	if (cmdArgs.size() != 1)
		return KPrint::printClientError(CLIENT_ERROR::ARGS_ERROR);
	m_request.initialize(CMD_NAME_MAP.find(CMD_NAME::GET)->second, cmdArgs);
	// ∑¢ÀÕ«∞÷√–≈∫≈
	if (!initDataSocket())
		return false;
	sendRequest();
	if (m_response.code() != 150)
		return false;
	return recvFile(cmdArgs.front());
}
