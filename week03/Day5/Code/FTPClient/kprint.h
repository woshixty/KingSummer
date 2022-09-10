// -------------------------------------------------------
// kprint.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/15
// ���������� ��װ��ӡ��
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
	{FILE_ERROR::DIR_EXIST, "Ŀ¼�Ѵ���"},
	{FILE_ERROR::DIR_NOT_FOUNT, "Ŀ¼�Ҳ���"},
	{FILE_ERROR::FILE_NOT_FOUNT, "�ļ��Ҳ���"},
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
	{CLIENT_ERROR::NOT_CONNECT, "δ����FTP������"},
	{CLIENT_ERROR::FAIL_CONNECT, "����FTP������ʧ��"},
	{CLIENT_ERROR::CMD_NOT_FOUND, "����δ�ҵ�"},
	{CLIENT_ERROR::ARGS_ERROR, "��������"},
	{CLIENT_ERROR::CONNECTION_EXIST, "�Ѿ����ӵ���FTP�����������ȶϿ�����"},
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
