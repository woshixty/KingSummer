#include "KSendMsgTask.h"

KSendMsgTask::KSendMsgTask(KEchoServer* server)
{
	m_server = server;
}

void KSendMsgTask::runtask()
{
	m_server->msgSendLoop();
}

