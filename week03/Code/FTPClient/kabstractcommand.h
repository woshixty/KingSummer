// -------------------------------------------------------
// kabstractcommand.h
// 创建者： xie tingyu
// 创建时间： 2022/7/19
// 功能描述： 抽象基类，定义每一条命令的接口，封装公共操作
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_ABSTRACT_COMMAND_H_
#define _K_ABSTRACT_COMMAND_H_

#include "kconstants.h"
#include "ksender.h"
#include "krequest.h"
#include "kresponse.h"

class KAbstractCommand
{
public:
	KAbstractCommand(KSender* pSender);
	virtual ~KAbstractCommand();

	virtual bool execute(list_str& cmdArgs) = 0;

	bool initDataSocket();

	void makeRequest(string cmdName, const list_str& cmdArgs);
	void setPSender(KSender* pSender);

	bool recvLongMsg();
	bool recvFile(const string& filename);
	bool sendFile(const string& filename);

	bool sendRequest();
	bool sendTempRequest();

	int responseCode() const { return m_response.code(); }
	string responseMsg() const { return m_response.resmsg(); }

protected:
	bool m_ret;
	string m_longmsg;
	KResponse m_response;
	KRequest m_request;
	KRequest m_temp_request;
	KResponse m_temp_respond;
	KSender* m_sender;
};

#endif