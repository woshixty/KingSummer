#include "KGetMsgTask.h"

KGetMsgTask::KGetMsgTask(KEchoClient* client)
{
	m_client = client;
}

void KGetMsgTask::runtask()
{
	m_client->msgGetLoop();
}