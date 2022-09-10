// -------------------------------------------------------
// koptscommand.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/19
// ���������� OPTS����ִ����
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef __K_OPS_COMMAND_H_
#define __K_OPT_COMMAND_H_

#include "kabstractcommand.h"

class KOptsCommand : public KAbstractCommand
{
public:
	KOptsCommand();
	~KOptsCommand();

	VOID makeOptUtf8OnPacket(string& packet, list_str& cmdArgs) override;
	BOOL executeCommand(KSocket* ptcpSocket, list_str& cmdArgs) override;
	BOOL waitForServerReply(KSocket *ptcpSocket, string& reply) override;

private:
};

#endif

