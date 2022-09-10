// -------------------------------------------------------
// ksender.h
// 创建者： xie tingyu
// 创建时间： 2022/7/22
// 功能描述： 命令发送中心，负责向服务器发送消息并接收回送
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_SENDER_H_
#define _K_SENDER_H_

#include "ksocket.h"
#include "kconstants.h"
#include "krequest.h"
#include "kresponse.h"
#include "ksocketserver.h"

#include <memory>

class KSender
{
public:
	explicit KSender();
	~KSender();
	bool initializeCommandSocket(string ipv4addr, u_short port);
	bool connect(KResponse& response);
	bool initializeDataSocket(string ipv4addr, u_short port);
	u_short serverBindPort();

	bool sendCommand(const KRequest& request, KResponse& response);
	bool sendCommand();
	bool recvFile(FILE* file, KResponse& response);
	bool sendFile(FILE* file, KResponse& response);
	bool recvDataMsg(KResponse& response, string& longmsg);

	bool prepareForData() const;
	bool shutdownCommandSocket();
	bool closeCommandSocket();

	bool isConnected() const { return m_isConnected; }
	string ipv4addr() const { return m_commandSocket->ipv4addr(); }
	bool type() const { return m_type; }
	bool netType() const { return m_net_type; }
	void setType(bool type) { m_type = type; }
	bool serverListenSocket() const;
	void setNetType(bool type) { m_net_type = type; }

private:
	bool m_ret;
	bool m_isConnected;
	bool m_type = false;
	bool m_net_type = false;
	u_short m_port;
	u_short m_port_data;
	std::unique_ptr<KSocket> m_commandSocket;
	std::unique_ptr<KSocket> m_dataSocket;
	std::unique_ptr<KSocketServer> m_dataServer;
	string m_requestStr;
	string m_responseStr;
	string m_ipv4addr;
	string m_ipv4addr_data;
};

#endif
