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
		std::cerr << "连接FTP服务器异常" << std::endl;
		return;
	}
	waitForConnectServerReply();
	
	string cmd = "OPTS UTF8 ON";
	// 执行 OPTS UTF8 ON 并等待回复
	m_commandHandle->executeCommand(cmd);
	m_commandHandle->waitForCommandReply();
	// 执行 USER h 并等待回复
	cmd = "USER h";
	m_commandHandle->executeCommand(cmd);
	m_commandHandle->waitForCommandReply();
	// 执行 PASS h 并等待回复
	cmd = "PASS h";
	m_commandHandle->executeCommand(cmd);
	m_commandHandle->waitForCommandReply();
}

void KFtpClient::runLoop()
{
	string cmd;
	char buffer[32] = { 0 };
	// 连接服务器
	ftpLogin();
	// ftp 主循环
	while (true)
	{
		cmd.clear();
		std::cout << "Ftp > ";
		std::cin.getline(buffer,32);
		cmd = string(buffer);
		// 执行命令并等待回复
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
	std::cout << "连接FTP服务器返回：" << msg << std::endl;
}
