#include "kftpclient.h"

#include <sstream>

KFtpClient::KFtpClient()
{
	m_ret = false;
	m_pSender = new KSender();
	m_pHandle = new KHandle(m_pSender);
}

KFtpClient::~KFtpClient()
{
	delete m_pSender;
	delete m_pHandle;
}

bool KFtpClient::ftpConnect()
{
	// 判断是否处于已连接状态
	if (m_pSender->isConnected())
		KPrint::printClientError(CLIENT_ERROR::CONNECTION_EXIST);
	// 获取输入的ip地址
	std::stringstream input(m_cmdline);
	input >> m_ipv4addr;
	input >> m_ipv4addr;
	// 连接FTP服务器
	m_ret = m_pSender->initializeCommandSocket(m_ipv4addr, s_ftp_port);
	m_ret = m_pSender->connect(m_response);
	if (!m_ret)
		return KPrint::printClientError(CLIENT_ERROR::FAIL_CONNECT);
	return m_pHandle->executeCommand(CMD_STR_MAP.find(CMD_STR::OPTS_UTF8)->second, m_response);
}

bool KFtpClient::ftpLogin()
{
	// 登录
	string username;
	string password;
	std::stringstream input(m_cmdline);
	input >> username;
	input >> username;
	KPrint::getPassword(password);
	m_ret = m_pHandle->executeCommand("user " + username, m_response);
	m_ret = m_pHandle->executeCommand("pass " + password, m_response);
	return true;
}

bool KFtpClient::handleCmd()
{
	// 离开程序
	if (m_cmdline._Equal(CMD_NAME_MAP.find(CMD_NAME::EXIT)->second))
	{
		if (m_pSender->isConnected())
			return KPrint::printClientError(CLIENT_ERROR::CONNECTION_EXIST);
		m_flag = false;
		return true;
	}
	// 连接FTP服务器
	if (m_cmdline.rfind(CMD_NAME_MAP.find(CMD_NAME::OPEN)->second, 0) == 0)
		return ftpConnect();
	// 未连接FTP服务器
	if (!m_pSender->isConnected())
		return KPrint::printClientError(CLIENT_ERROR::NOT_CONNECT);
	// 用户登录
	if (m_cmdline.rfind(CMD_NAME_MAP.find(CMD_NAME::LOGIN_N)->second, 0) == 0)
		return ftpLogin();
	// 执行命令
	return m_pHandle->executeCommand(m_cmdline, m_response);
}

void KFtpClient::runLoop()
{
	// 设置主被动模式
	KPrint::getType(m_type);
	m_pSender->setType(m_type);
	// 设置网络连接模式
	KPrint::getNetType(m_type);
	m_pSender->setNetType(m_type);
	// ftp 主循环
	while (m_flag)
	{
		m_cmdline.clear();
		memset(m_buffer, '\0', s_buffer_len);
		std::cin.clear();
		std::cout << "Ftp > ";
		std::cin.getline(m_buffer, s_buffer_len);
		m_cmdline = string(m_buffer);
		handleCmd();
	}
}

