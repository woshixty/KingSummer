// -------------------------------------------------------
// kcommandresponse.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/19
// ���������� ������ؽ�����з�װ
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