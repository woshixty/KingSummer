// -------------------------------------------------------
// krequestpacket.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/19
// ���������� �Է������ݷ�װ��
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
