// -------------------------------------------------------
// kconstants.h
// 创建者： xie tingyu
// 创建时间： 2022/7/19
// 功能描述： 常量和命名空间
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_CONSTANTS_H_
#define _K_CONSTANTS_H_

#include <direct.h>
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>

constexpr static unsigned gs_buffer_len = 32;

using string = std::string;
using list_str = std::list<string>;
using vector_str = std::vector<string>;
using size_type = string::size_type;

enum class ResponseType
{
	COMMAND_R,
	FILE_R,
	LONGMSG_R
};

enum class CMD_NAME
{
	OPTS,
	USER,
	PASS,
	LIST,
	GET,
	PUT,
	MKDIR,
	DELETE2,
	QUIT,
	OPEN,
	LOGIN_N,
	LOGIN_P,
	EXIT,
};

static const std::map<CMD_NAME, string> CMD_NAME_MAP =
{
	{CMD_NAME::OPTS, "OPTS"},
	{CMD_NAME::USER, "USER"},
	{CMD_NAME::PASS, "PASS"},
	{CMD_NAME::LIST, "LIST"},
	{CMD_NAME::GET, "RETR"},
	{CMD_NAME::PUT, "STOR"},
	{CMD_NAME::MKDIR, "MKD"},
	{CMD_NAME::DELETE2, "DELE"},
	{CMD_NAME::QUIT, "QUIT"},
	{CMD_NAME::OPEN, "open "},
	{CMD_NAME::LOGIN_N, "user "},
	{CMD_NAME::EXIT, "quit"},
};

enum class CMD_STR
{
	OPTS_UTF8,
	PASV,
	PORT,
};

static const std::map<CMD_STR, string> CMD_STR_MAP =
{
	{CMD_STR::OPTS_UTF8, "OPTS UTF8 ON"},
	{CMD_STR::PASV, "PASV"},
	{CMD_STR::PORT, "PORT"},
};


enum class STATUS_CODE
{
	NOT_LOGIN = 530,
	REQUIRE_PASS = 331,
	LOGIN_SUCCESS = 230,
};

#endif