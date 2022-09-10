// -------------------------------------------------------
// koptscommand.h
// 创建者： xie tingyu
// 创建时间： 2022/7/19
// 功能描述： OPTS命令执行器
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

