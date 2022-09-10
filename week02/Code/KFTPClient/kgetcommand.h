// -------------------------------------------------------
// kgetcommand.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/19
// ���������� RETR����ִ����
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_GET_COMMAND_H_
#define _K_GET_COMMAND_H_

#include "kabstractcommand.h"

class KGetCommand : public KAbstractCommand
{
public:
	KGetCommand();
	~KGetCommand();

	VOID makeOptUtf8OnPacket(string& packet, list_str& cmdArgs) override;
	BOOL executeCommand(KSocket* ptcpSocket, list_str& cmdArgs) override;
	BOOL waitForServerReply(KSocket* ptcpSocket, string& reply) override;

private:
	unsigned m_dataPort;
	string m_filename;
};

#endif