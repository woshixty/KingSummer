// -------------------------------------------------------
// kprint.h
// 创建者： xie tingyu
// 创建时间： 2022/7/15
// 功能描述： 封装打印类
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
	{FILE_ERROR::DIR_EXIST, "目录已存在"},
	{FILE_ERROR::DIR_NOT_FOUNT, "目录找不到"},
};

class KPrint
{
public:
	static void printCommandRes(KCommandResponse &res);
	static void printFileError(FILE_ERROR error);
	static bool printFailError(const string& function, int errorcode);
};

#endif
