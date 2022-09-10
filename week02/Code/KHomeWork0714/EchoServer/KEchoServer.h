// -------------------------------------------------------
// KEchoServer.h
// 创建者： xie tingyu
// 创建时间： 2022/7/15
// 功能描述： 服务端类-接受连接并向客户端发送数据
// Copyright 2013 Kingsoft
// --------------------------------------------------------
#ifndef _KECHOSERVER_H_
#define _KECHOSERVER_H_

#include <list>
#include "KSocket.h"
#include "KSocketServer.h"
#include "KGetMsgTask.h"

class KEchoServer
{
	using string = std::string;
	using list = std::list<KSocket*>;

public:
	KEchoServer(u_short port);
	void acceptLoop();
	void msgSendLoop();
	void closeserver() { m_loop_tag = false; }

private:
	KSocketServer* m_socket;
	list m_clients_list_;
	BOOL m_loop_tag = true;
	INT m_ret;
	string m_msg;
};

#endif
