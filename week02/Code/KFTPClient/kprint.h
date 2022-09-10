// -------------------------------------------------------
// kprint.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/15
// ���������� ��װ��ӡ��
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef __K_PRINT_H_
#define __K_PRINT_H_

#include "kcommandresponse.h"
#include <map>

enum class FILE_ERROR
{
	DIR_EXIST,
	DIR_NOT_FOUNT
};

static const std::map<FILE_ERROR, string> FILE_ERROR_MAP = 
{
	{FILE_ERROR::DIR_EXIST, "Ŀ¼�Ѵ���"},
	{FILE_ERROR::DIR_NOT_FOUNT, "Ŀ¼�Ҳ���"},
};

class KPrint
{
public:
	static void printCommandRes(KCommandResponse &res);
	static void printFileError(FILE_ERROR error);
	static bool printFailError(const string& function, int errorcode);
};

#endif
