// -------------------------------------------------------
// klistcommand.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/19
// ���������� LIST����ִ����
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef __K_LIST_COMMAND_H_
#define __K_LIST_COMMAND_H_

#include "kabstractcommand.h"

class KListCommand : public KAbstractCommand
{
public:
	KListCommand();
	~KListCommand();

	VOID makeOptUtf8OnPacket(string& packet, list_str& cmdArgs) override;
	BOOL executeCommand(KSocket* ptcpSocket, list_str& cmdArgs) override;
	BOOL waitForServerReply(KSocket* ptcpSocket, string& reply) override;

private:
	unsigned m_dataPort;
};
#endif
