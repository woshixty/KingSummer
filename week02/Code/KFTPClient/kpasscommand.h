// -------------------------------------------------------
// kpasscommand.h
// 创建者： xie tingyu
// 创建时间： 2022/7/19
// 功能描述： PASS命令执行器
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
