// -------------------------------------------------------
// kputcommand.h
// 创建者： xie tingyu
// 创建时间： 2022/7/15
// 功能描述： STOR命令执行器
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_PUT_COMMAND_H_
#define _K_PUT_COMMAND_H_

#include "kabstractcommand.h"
class KPutCommand : public KAbstractCommand
{
public:
	KPutCommand();
	~KPutCommand();

	VOID makeOptUtf8OnPacket(string& packet, list_str& cmdArgs) override;
	BOOL executeCommand(KSocket* ptcpSocket, list_str& cmdArgs) override;
	BOOL waitForServerReply(KSocket* ptcpSocket, string& reply) override;

private:
	string m_filename;
	unsigned m_dataPort;
};

#endif