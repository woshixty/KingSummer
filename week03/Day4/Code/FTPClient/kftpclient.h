// -------------------------------------------------------
// kftpclient.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/19
// ���������� �ͻ��˷�װ�࣬����ͻ��˵�һϵ�в���
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_FTP_CLIENT_H_
#define _K_FTP_CLIENT_H_

#include "khandle.h"

class KFtpClient
{
public:
	constexpr static u_short s_ftp_port = 21;
	constexpr static unsigned s_buffer_len = 1024;

	KFtpClient();
	~KFtpClient();

	bool ftpConnect();
	bool ftpLogin();
	bool handleCmd();
	void runLoop();

private:
	bool m_ret;
	bool m_flag = true;
	bool m_type = false;
	char m_buffer[s_buffer_len] = { 0 };

	string m_ipv4addr;
	string m_cmdline;
	KHandle* m_pHandle;
	KSender* m_pSender;
	KResponse m_response;
	KRequest m_request;
};

#endif