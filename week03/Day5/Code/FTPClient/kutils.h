// -------------------------------------------------------
// kutils.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/22
// ���������� ����������װ
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_UTILS_H_
#define _K_UTILS_H_

#include <WinSock2.h>
#include "kresponse.h"
#include "kconstants.h"

class KUtils
{
public:
	static unsigned getPortFromPasvRes(const KResponse& response);
	static void getPortFromPasvRes(const string& responseStr, u_short& port);
	static FILE* createFile(string dir, const string& filename);
	static FILE* openFile(const string& filename);
	static bool parseLine(const string& line, string& name, list_str& args);
	static void getFilename(const string& line, string& filename);
};

#endif