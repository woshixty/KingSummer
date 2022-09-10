// -------------------------------------------------------
// krequest.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/19
// ���������� �Է��͸�FTP�����������ݷ�װ��
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_REQUESTPACKET_H_
#define _K_REQUESTPACKET_H_

#include "kconstants.h"

class KRequest
{
public:
	explicit KRequest();
	~KRequest();
	void initialize(const string& line);
	void initialize(string&& line);

	void initialize(string cmdName, list_str cmdArgs);
	void initialize(string cmdName, string cmdArg);
	void clear();
	void getRequestStr(string& requestStr) const;
	string getRequestStr() const;

private:
	string m_cmdName;
	list_str m_cmdArgs;
};

/*
 * std::string str= "";
 * KRequest r;
 * r.initialize(str);
 *
 */

#endif
