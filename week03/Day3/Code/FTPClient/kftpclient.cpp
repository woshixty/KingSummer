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
	// �ж��Ƿ���������״̬
	if (m_pSender->isConnected())
		KPrint::printClientError(CLIENT_ERROR::CONNECTION_EXIST);
	// ��ȡ�����ip��ַ
	std::stringstream input(m_cmdline);
	input >> m_ipv4addr;
	input >> m_ipv4addr;
	// ����FTP������
	m_ret = m_pSender->initializeCommandSocket(m_ipv4addr, s_ftp_port);
	m_ret = m_pSender->connect(m_response);
	if (!m_ret)
		return KPrint::printClientError(CLIENT_ERROR::FAIL_CONNECT);
	return m_pHandle->executeCommand(CMD_STR_MAP.find(CMD_STR::OPTS_UTF8)->second, m_response);
}

bool KFtpClient::ftpLogin()
{
	// ��¼
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
	// �뿪����
	if (m_cmdline._Equal(CMD_NAME_MAP.find(CMD_NAME::EXIT)->second))
	{
		if (m_pSender->isConnected())
			return KPrint::printClientError(CLIENT_ERROR::CONNECTION_EXIST);
		m_flag = false;
		return true;
	}
	// ����FTP������
	if (m_cmdline.rfind(CMD_NAME_MAP.find(CMD_NAME::OPEN)->second, 0) == 0)
		return ftpConnect();
	// δ����FTP������
	if (!m_pSender->isConnected())
		return KPrint::printClientError(CLIENT_ERROR::NOT_CONNECT);
	// �û���¼
	if (m_cmdline.rfind(CMD_NAME_MAP.find(CMD_NAME::LOGIN_N)->second, 0) == 0)
		return ftpLogin();
	// ִ������
	return m_pHandle->executeCommand(m_cmdline, m_response);
}

void KFtpClient::runLoop()
{
	// ����������ģʽ
	KPrint::getType(m_type);
	m_pSender->setType(m_type);
	// ������������ģʽ
	KPrint::getNetType(m_type);
	m_pSender->setNetType(m_type);
	// ftp ��ѭ��
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

