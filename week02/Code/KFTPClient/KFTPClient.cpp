// ReSharper disable All
#include "kftpclient.h"

KFtpClient::KFtpClient(string ip)
{
	m_ip = ip;
	m_tcpControlSocket = new KSocket((char*)m_ip.c_str(), FTP_PORT);
	m_commandHandle = new KFtpCommandHandle(m_tcpControlSocket);
}

KFtpClient::~KFtpClient()
{
	delete m_tcpControlSocket;
	delete m_commandHandle;
}

void KFtpClient::ftpLogin()
{
	const BOOL ret = connectToFtpServer();
	if(!ret)
	{
		std::cerr << "����FTP�������쳣" << std::endl;
		return;
	}
	waitForConnectServerReply();
	
	string cmd = "OPTS UTF8 ON";
	// ִ�� OPTS UTF8 ON ���ȴ��ظ�
	m_commandHandle->executeCommand(cmd);
	m_commandHandle->waitForCommandReply();
	// ִ�� USER h ���ȴ��ظ�
	cmd = "USER h";
	m_commandHandle->executeCommand(cmd);
	m_commandHandle->waitForCommandReply();
	// ִ�� PASS h ���ȴ��ظ�
	cmd = "PASS h";
	m_commandHandle->executeCommand(cmd);
	m_commandHandle->waitForCommandReply();
}

void KFtpClient::runLoop()
{
	string cmd;
	char buffer[32] = { 0 };
	// ���ӷ�����
	ftpLogin();
	// ftp ��ѭ��
	while (true)
	{
		cmd.clear();
		std::cout << "Ftp > ";
		std::cin.getline(buffer,32);
		cmd = string(buffer);
		// ִ������ȴ��ظ�
		BOOL ret = m_commandHandle->executeCommand(cmd);
		if(ret)
			m_commandHandle->waitForCommandReply();
	}
}

BOOL KFtpClient::connectToFtpServer()
{
	return m_tcpControlSocket->connectToHost();
}


void KFtpClient::waitForConnectServerReply() const
{
	string msg;
	int rbytes = m_tcpControlSocket->recvCommandMsg(msg);
	std::cout << "����FTP���������أ�" << msg << std::endl;
}
