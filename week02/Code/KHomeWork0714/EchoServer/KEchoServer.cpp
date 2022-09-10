#include "KEchoServer.h"

#include "KThread.h"

class KGetMsgTask;
// ���߳�ִ�к���
DWORD WINAPI getClientThread(LPVOID lpThreadParameter)
{
	KSocket* csocket = (KSocket*)lpThreadParameter;
	// ������ ���� ���ݣ������½�������ݷ��ظ��ͻ���
	for (;;)
	{
		std::string msg = csocket->getMsg();
		if (!msg.empty())
			std::cout << "recv :" << msg << std::endl;
	}
}

// ���߳�ִ�к���
DWORD WINAPI sendClientThread(LPVOID lpThreadParameter)
{
	KSocket* csocket = (KSocket*)lpThreadParameter;
	// ������ ���� ���ݣ������½�������ݷ��ظ��ͻ���
	for (;;)
	{
		std::string msg;
		std::cin >> msg;
		char* msg_char = (char*)msg.c_str();
		csocket->sendMsg(msg_char, strlen(msg_char));
	}
}

KEchoServer::KEchoServer(u_short port)
{
	m_socket = new KSocketServer();
	m_ret = m_socket->initSocket();
	if (!m_ret)
		throw "��ʼ��KSocketServerʧ��";
	m_ret = m_socket->bindPort(port);
	if (!m_ret)
		throw "�󶨶˿ں�ʧ��";
	m_ret = m_socket->listenSocket();
	if (!m_ret)
		throw "�����˿�ʧ��";
}

void KEchoServer::acceptLoop()
{
	while (m_loop_tag)
	{
		KSocket* csocket = m_socket->acceptSocket();
		m_clients_list_.push_back(csocket);
		if (csocket != nullptr)
		{
			KGetMsgTask* task = new KGetMsgTask(csocket);
			// ÿ����һ���ͻ���,����һ�����߳�
			KThread thread(task);
			thread.run();
		}
	}
}

void KEchoServer::msgSendLoop()
{
	while (m_loop_tag)
	{
		std::cin >> m_msg;
		char* msg_char = (char*)m_msg.c_str();
		for (KSocket* m_client : m_clients_list_)
			m_ret = m_client->sendMsg(msg_char, strlen(msg_char));
	}
	std::cout << "socketѭ��������Ϣ����" << std::endl;
}
