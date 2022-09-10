// -------------------------------------------------------
// kcommandresponse.h
// 创建者： xie tingyu
// 创建时间： 2022/7/19
// 功能描述： 对命令返回结果进行封装
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_RESPONSEPACKET_H_
#define _K_RESPONSEPACKET_H_

#include "kconstants.h"

class KResponse
{
public:
	explicit KResponse();
	void initialize(const string& resmsg);
	int code() const { return m_code; }
	string resmsg() const { return m_resmsg; }

private:
	int m_code{};
	string m_resmsg;
};

#endif