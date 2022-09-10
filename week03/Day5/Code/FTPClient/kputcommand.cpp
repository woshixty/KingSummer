#include "kputcommand.h"
#include "kutils.h"

KPutCommand::KPutCommand(KSender* pSender) : KAbstractCommand(pSender)
{
}

KPutCommand::~KPutCommand()
= default;

bool KPutCommand::execute(list_str& cmdArgs)
{
	if (cmdArgs.size() != 1)
		return KPrint::printClientError(CLIENT_ERROR::ARGS_ERROR);
	// 获取文件名
	KUtils::getFilename(cmdArgs.front(), m_filename);
	m_request.initialize(CMD_NAME_MAP.find(CMD_NAME::PUT)->second, m_filename);
	if (!initDataSocket())
		return false;
	sendRequest();
	if (m_response.code() != 150)
		return false;
	return sendFile(cmdArgs.front());
}
