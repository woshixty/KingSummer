// -------------------------------------------------------
// kabstractcommand.h
// 创建者： xie tingyu
// 创建时间： 2022/7/19
// 功能描述： 抽象基类，定义每一条命令的接口，封装公共操作
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef __K_ABSTRACT_COMMAND_H_
#define __K_ABSTRACT_COMMAND_H_

#include "ksocket.h"
#include "kconstats.h"
#include "kcommandresponse.h"
#include "kprint.h"

class KAbstractCommand
{
public:
	KAbstractCommand();
	virtual ~KAbstractCommand();

	// 执行命令
	virtual BOOL executeCommand(KSocket* ptcpSocket, list_str& cmdArgs) = 0;

	// 等待服务器应答
	virtual BOOL waitForServerReply(KSocket *ptcpsocket, string &reply) = 0;

	// 创建packet
	virtual VOID makeOptUtf8OnPacket(string& packet, list_str& cmdArgs) = 0;

	// 封装参数
	void makePacket(string& packet, list_str& cmdArgs);

	// 发送pasv命令获得端口
	unsigned sendPASV(KSocket* ptcpSocket);

	// 创建socket连接并获取返回数据
	BOOL createSocketRecvS(CHAR* pipAddr, unsigned dataPort);
	BOOL createSocketRecvF(CHAR* pipAddr, unsigned dataPort, const string& filename);

	// 创建socket连接并上传数据
	BOOL createSocketUploadF(CHAR* pipAddr, unsigned dataPort, FILE *file);

	// 封装数据包并发送
	BOOL createPacketSend(string& packet, list_str& cmdArgs, KSocket* ptcpSocket);

protected:
	KCommandResponse m_commandRes;
	string m_reply;
};

#endif

