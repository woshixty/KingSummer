// -------------------------------------------------------
// kpasscommand.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/19
// ���������� PASS����ִ����
// Copyright 2013 Kingsoft
// --------------------------------------------------------
#ifndef __K_PASS_COMMAND_H_
#define __K_PASS_COMMAND_H_

#include "kabstractcommand.h"

class KPassCommand : public KAbstractCommand
{
public:
	KPassCommand();
	~KPassCommand();

	VOID makeOptUtf8OnPacket(string& packet, list_str& cmdArgs) override;
	BOOL executeCommand(KSocket* ptcpSocket, list_str& cmdArgs) override;
	BOOL waitForServerReply(KSocket* ptcpSocket, string& reply) override;
};

#endif
