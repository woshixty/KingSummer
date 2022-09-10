// -------------------------------------------------------
// kcommandsender.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/22
// ���������� ��������ģ������������������Ϣ�����ջ���
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_COMMAND_SENDER_H_
#define _K_COMMAND_SENDER_H_

#include "ksocket.h"
#include "kconstats.h"
#include "krequestpacket.h"
#include "kcommandresponse.h"
#include <memory>

class KCommandSender
{
public:
	explicit KCommandSender();
	~KCommandSender();
	bool initializeCommandSocket(string ipv4addr, u_short port) const;
	bool initializeDataSocket(string ipv4addr, u_short port) const;
	bool sendCommand(const KRequestPacket& packet, KCommandResponse& response);

private:
	std::unique_ptr<KSocket> m_commandSocket;
	std::unique_ptr<KSocket> m_dataSocket;
	string m_packetStr;
	string m_responseStr;
	int m_ret;
};

#endif
