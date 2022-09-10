#include "kprint.h"

void KPrint::printRequest(const KRequest& request)
{
	string str = request.getRequestStr();
	std::cout << "REQUEST: " << removeReturn(request.getRequestStr()) << std::endl;
}

void KPrint::printRequest(const string& requestStr)
{
	std::cout << "REQUEST: " << removeReturn(requestStr) << std::endl;
}

void KPrint::printResponse(const KResponse& response)
{
	std::cout << "RESPONSE: CODE:" << response.code() << "  MSG:" << removeReturn(response.resmsg()) << std::endl;
}

void KPrint::printResponse(const string& responseStr)
{
	std::cout << "RESPONSE: " << removeReturn(responseStr) << std::endl;
}

void KPrint::printLongMsg(const string& longmsg)
{
	std::cout << longmsg << std::endl;
}

void KPrint::printFileError(FILE_ERROR error)
{
	std::cout << "文件系统错误: " << FILE_ERROR_MAP.find(error)->second << std::endl;
}

bool KPrint::printClientError(CLIENT_ERROR error)
{
	std::cout << "客户端错误: " << CLIENT_ERROR_MAP.find(error)->second << std::endl;
	return false;
}

bool KPrint::printFailError(const string& function, const int errorcode)
{
	std::cout << function << " 失败, Error Code : " << errorcode << std::endl;
	return false;
}

bool KPrint::printFailError(const string& function)
{
	std::cout << function << " 失败" << std::endl;
	return false;
}

void KPrint::getPassword(string& password)
{
	std::cout << "please enter password > ";
	std::cin.clear();
	std::getline(std::cin, password);
}

void KPrint::getType(bool& type)
{
	std::cout << "被动模式请按下0、主动模式请按下其他任意按钮 > ";
	string str;
	std::getline(std::cin, str);
	if (str._Equal("0"))
		type = false;
	else
		type = true;
}

void KPrint::getNetType(bool& type)
{
	std::cout << "本机ip模式请按下0、内网或其他模式请按下其他任意按钮 > ";
	string str;
	std::getline(std::cin, str);
	if (str._Equal("0"))
		type = true;
	else
		type = false;
}
