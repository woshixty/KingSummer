// -------------------------------------------------------
// kputcommand.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/15
// ���������� STOR����ִ����
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