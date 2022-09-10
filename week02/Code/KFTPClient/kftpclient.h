// -------------------------------------------------------
// kftpclient.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/19
// ���������� �ͻ��˷�װ�࣬����ͻ��˵�һϵ�в���
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef __K_FTP_CLIENT_H_
#define __K_FTP_CLIENT_H_

#include "ksocket.h"
#include "kftpcommandhandle.h"


class KFtpClient
{
	using string = std::string;
public:
	constexpr static unsigned FTP_PORT = 21;

	KFtpClient(string ip);
	~KFtpClient();

	// ��¼ ftp ������
	void ftpLogin();
	// ftp �ͻ�����ѭ��,�������ִ��
	void runLoop();

	// ���� ftp ������
	BOOL connectToFtpServer();
	// �ȴ� ������Ӧ��
	void waitForConnectServerReply() const;

private:
	KSocket* m_tcpControlSocket;
	KFtpCommandHandle* m_commandHandle;
	string m_ip;
};

#endif

