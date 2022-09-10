// -------------------------------------------------------
// kftpclient.h
// 创建者： xie tingyu
// 创建时间： 2022/7/19
// 功能描述： 客户端封装类，定义客户端的一系列操作
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

	// 登录 ftp 服务器
	void ftpLogin();
	// ftp 客户端主循环,接收命令，执行
	void runLoop();

	// 连接 ftp 服务器
	BOOL connectToFtpServer();
	// 等待 服务器应答
	void waitForConnectServerReply() const;

private:
	KSocket* m_tcpControlSocket;
	KFtpCommandHandle* m_commandHandle;
	string m_ip;
};

#endif

