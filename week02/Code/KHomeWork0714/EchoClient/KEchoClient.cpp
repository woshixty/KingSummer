#include "KEchoClient.h"

KEchoClient::KEchoClient(std::string ipv4_addr, u_short port)
{
	m_socket = new KSocket();
	m_ret = m_socket->initSocket();
	if(!m_ret)
		throw "��ʼ��KSocketʧ��";
	m_ret =  m_socket->connectToSvr(ipv4_addr.data(), port);
	if (!m_ret)
		throw "���ӷ�����ʧ��";
}

void KEchoClient::msgSendLoop()
{
	while (m_loop_tag)
	{
		std::cin >> m_msg;
		char* msg_char = (char*)m_msg.c_str();
		m_ret = m_socket->sendMsg(msg_char, strlen(msg_char));
		if(!m_ret)
			break;
	}
	std::cout << "socketѭ��������Ϣ����" << std::endl;
}

void KEchoClient::msgGetLoop()
{
	while (m_loop_tag)
	{
		std::string msg = m_socket->getMsg();
		if (!msg.empty())
			std::cout << "recv from " << m_socket->getIpAddr() << " : " << msg << std::endl;
		else
			break;
		if (!m_ret)
			break;
	}
	std::cout << "socketѭ��������Ϣ����" << std::endl;
}

KEchoClient::~KEchoClient()
{
	m_socket->closeConnection();
	delete m_socket;
}
