// -------------------------------------------------------
// kiputils.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/25
// ���������� ip������
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_IPUTILS_H_
#define _K_IPUTILS_H_

#include "krequest.h"

#include <WinSock2.h>

#pragma comment(lib, "WS2_32.lib")

class KIpUtils
{
public:
    static bool generatePortRequest(KRequest& request, u_short port, bool type);
};

#endif