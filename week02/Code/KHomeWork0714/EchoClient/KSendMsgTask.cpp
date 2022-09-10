#include "KSendMsgTask.h"

KSendMsgTask::KSendMsgTask(KEchoClient* client)
{
	m_client = client;
}

void KSendMsgTask::runtask()
{
	m_client->msgSendLoop();
}