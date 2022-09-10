#include "KGetMsgTask.h"

KGetMsgTask::KGetMsgTask(KSocket* socket)
{
	m_socket = socket;
}

void KGetMsgTask::runtask()
{
	while (true)
	{
		std::string msg = m_socket->getMsg();
		if (!msg.empty())
			std::cout << "recv from " << m_socket->getIpAddr() << " : " << msg << std::endl;
	}
}


