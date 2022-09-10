// -------------------------------------------------------
// krequestpacket.h
// 创建者： xie tingyu
// 创建时间： 2022/7/19
// 功能描述： 对发送数据封装类
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_REQUESTPACKET_H_
#define _K_REQUESTPACKET_H_

#include "kconstats.h"
#include "kutils.h"

class KRequestPacket
{
public:
	explicit KRequestPacket();
	void initialization(const string& line);
	void clear();
	string getPacketStr() const;

private:
	string m_cmdName;
	list_str m_cmdArgs;
};

#endif
