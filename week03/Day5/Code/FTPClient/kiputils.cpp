#include "kiputils.h"
#include "kprint.h"

#include "WS2tcpip.h"
#include <algorithm>

bool KIpUtils::generatePortRequest(KRequest& request, u_short port, bool type)
{
    request.clear();
    WSADATA m_wsadata{};
    const int ret = WSAStartup(MAKEWORD(2, 3), &m_wsadata);
    if (ret != 0)
        return KPrint::printFailError("WSAStartup", WSAGetLastError());
    char pszIP[16] = { 0 };
    addrinfo* answer;
    addrinfo hint{};
    memset(&hint, 0x00, sizeof hint);
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;

    char szHostName[128] = { 0 };
    int iRet = gethostname(szHostName, sizeof(szHostName));
    if (iRet != 0)
        return KPrint::printFailError("gethostname");
    iRet = getaddrinfo(szHostName, nullptr, &hint, &answer);
    if (iRet != 0)
        return KPrint::printFailError("getaddrinfo");
    for (const addrinfo* curr = answer; curr != nullptr; curr = curr->ai_next)
        inet_ntop(AF_INET, &((sockaddr_in*)curr->ai_addr)->sin_addr, pszIP, 16);
    freeaddrinfo(answer);
    string cmdArg;
	cmdArg.append(pszIP);
    std::replace(cmdArg.begin(), cmdArg.end(), '.', ',');

    //-------
    if(type)
		cmdArg = "127,0,0,1";
    //-------

    const int num1 = port / 256;
    const int num2 = port % 256;
    cmdArg.append("," + std::to_string(num1) + "," + std::to_string(num2));
    request.initialize(CMD_STR_MAP.find(CMD_STR::PORT)->second, cmdArg);
	return true;
}
