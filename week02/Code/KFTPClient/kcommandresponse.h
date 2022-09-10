// -------------------------------------------------------
// kcommandresponse.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/19
// ���������� ������ؽ�����з�װ
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_RESPONSEPACKET_H_
#define _K_RESPONSEPACKET_H_

#include "kconstats.h"

class KCommandResponse
{
public:
	explicit KCommandResponse();
	void initialization(int code, string resmsg);
	void initialization(const string& resmsg);
	int getCode() const { return m_code; }
	string getMsg() const { return m_resmsg; }

private:
	int m_code{};
	string m_resmsg;
};

#endif
