// -------------------------------------------------------
// kmsgfilter.h
// 创建者： xie tingyu
// 创建时间： 2022/08/12
// 功能描述： 消息过滤
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_MSGFILTER_H_
#define _K_MSGFILTER_H_

#include "kmessage.h"

#include <Windows.h>

class KMsgFilter
{
public:
	static bool filter(const KMessage& msg);
	static bool STDAPICALLTYPE wildcmp(LPCTSTR string, LPCTSTR wild);
};

#endif
