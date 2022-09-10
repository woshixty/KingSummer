#include "KAcceptTask.h"

KAcceptThread::KAcceptThread(KEchoServer* server)
{
	m_server = server;
}

void KAcceptThread::runtask()
{
	m_server->acceptLoop();
}