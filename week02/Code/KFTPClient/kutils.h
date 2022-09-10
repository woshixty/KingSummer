// -------------------------------------------------------
// kutils.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/22
// ���������� ����������װ
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_KUTILS_H_
#define _K_KUTILS_H_

#include "kcommandresponse.h"
#include "krequestpacket.h"
#include "kconstats.h"
#include "kprint.h"

class KUtils
{
public:
	static unsigned getPortFromPasvRes(const KCommandResponse& response);
	static FILE* createFile(string dir, const string& filename);
	static bool parseLine(string& name, list_str& args, const string& line);
};

#endif