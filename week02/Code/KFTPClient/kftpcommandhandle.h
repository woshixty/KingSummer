// -------------------------------------------------------
// kftpcommandhandle.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/19
// ���������� ftp�����û�������
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef __K_FTP_COMMAND_HANDLE_H_
#define __K_FTP_COMMAND_HANDLE_H_

#include "ksocket.h"
#include "kabstractcommand.h"
#include "krequestpacket.h"

#include "kusercommand.h"
#include "koptscommand.h"
#include "kpasscommand.h"
#include "klistcommand.h"
#include "kgetcommand.h"
#include "kputcommand.h"

#include <cstring>
#include <map>

class KFtpCommandHandle
{
public:
	KFtpCommandHandle(KSocket* ptcpsocket);
	~KFtpCommandHandle();

	BOOL executeCommand(string &cmdString);
	BOOL waitForCommandReply() const;

	void parseCommand(string &cmdString);
	
	void initCommandMaps();
	void releaseCommandMaps();

private:
	KSocket* m_ptcpSocket;
	KAbstractCommand* m_pcommand{};

	string m_cmdName;
	list_str m_cmdArgs;
	std::map<string, KAbstractCommand*> m_commandMap;
};

#endif