// -------------------------------------------------------
// kprint.h
// 创建者： xie tingyu
// 创建时间： 2022/7/15
// 功能描述： 封装打印类
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef __K_PRINT_H_
#define __K_PRINT_H_

#include <algorithm>

#include "kconstants.h"
#include "kresponse.h"
#include "krequest.h"
#include <map>

enum class FILE_ERROR
{
	DIR_EXIST,
	DIR_NOT_FOUNT,
	FILE_NOT_FOUNT
};

static const std::map<FILE_ERROR, string> FILE_ERROR_MAP =
{
	{FILE_ERROR::DIR_EXIST, "目录已存在"},
	{FILE_ERROR::DIR_NOT_FOUNT, "目录找不到"},
	{FILE_ERROR::FILE_NOT_FOUNT, "文件找不到"},
};

enum class CLIENT_ERROR
{
	NOT_CONNECT,
	FAIL_CONNECT,
	CMD_NOT_FOUND,
	ARGS_ERROR,
	CONNECTION_EXIST,
};

static const std::map<CLIENT_ERROR, string> CLIENT_ERROR_MAP =
{
	{CLIENT_ERROR::NOT_CONNECT, "未连接FTP服务器"},
	{CLIENT_ERROR::FAIL_CONNECT, "连接FTP服务器失败"},
	{CLIENT_ERROR::CMD_NOT_FOUND, "命令未找到"},
	{CLIENT_ERROR::ARGS_ERROR, "参数错误"},
	{CLIENT_ERROR::CONNECTION_EXIST, "已经连接到了FTP服务器，请先断开连接"},
};

class KPrint
{
public:
	static void printRequest(const KRequest& request);
	static void printRequest(const string& requestStr);

	static void printResponse(const KResponse& response);
	static void printResponse(const string& responseStr);

	static void printLongMsg(const string& longmsg);

	static void printFileError(FILE_ERROR error);
	static bool printClientError(CLIENT_ERROR error);

	static bool printFailError(const string& function, int errorcode);
	static bool printFailError(const string& function);

	static void getPassword(string& password);
	static void getType(bool& type);
	static void getNetType(bool& type);

	static string removeReturn(string str);
};

inline string KPrint::removeReturn(string str)
{
	std::replace(str.begin(), str.end(), '\n', ' ' );
	return str;
}

#endif
