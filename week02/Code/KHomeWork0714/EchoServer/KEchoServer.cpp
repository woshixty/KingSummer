#include "KEchoServer.h"

#include "KThread.h"

class KGetMsgTask;
// 子线程执行函数
DWORD WINAPI getClientThread(LPVOID lpThreadParameter)
{
	KSocket* csocket = (KSocket*)lpThreadParameter;
	// 服务器 接收 数据，在重新将这个数据返回给客户端
	for (;;)
	{
		std::string msg = csocket->getMsg();
		if (!msg.empty())
			std::cout << "recv :" << msg << std::endl;
	}
}

// 子线程执行函数
DWORD WINAPI sendClientThread(LPVOID lpThreadParameter)
{
	KSocket* csocket = (KSocket*)lpThreadParameter;
	// 服务器 接收 数据，在重新将这个数据返回给客户端
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
		throw "初始化KSocketServer失败";
	m_ret = m_socket->bindPort(port);
	if (!m_ret)
		throw "绑定端口号失败";
	m_ret = m_socket->listenSocket();
	if (!m_ret)
		throw "监听端口失败";
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
			// 每连接一个客户端,创建一个子线程
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
	std::cout << "socket循环发送消息结束" << std::endl;
}
