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
	std::cout << "�ļ�ϵͳ����: " << FILE_ERROR_MAP.find(error)->second << std::endl;
}

bool KPrint::printClientError(CLIENT_ERROR error)
{
	std::cout << "�ͻ��˴���: " << CLIENT_ERROR_MAP.find(error)->second << std::endl;
	return false;
}

bool KPrint::printFailError(const string& function, const int errorcode)
{
	std::cout << function << " ʧ��, Error Code : " << errorcode << std::endl;
	return false;
}

bool KPrint::printFailError(const string& function)
{
	std::cout << function << " ʧ��" << std::endl;
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
	std::cout << "����ģʽ�밴��0������ģʽ�밴���������ⰴť > ";
	string str;
	std::getline(std::cin, str);
	if (str._Equal("0"))
		type = false;
	else
		type = true;
}

void KPrint::getNetType(bool& type)
{
	std::cout << "����ipģʽ�밴��0������������ģʽ�밴���������ⰴť > ";
	string str;
	std::getline(std::cin, str);
	if (str._Equal("0"))
		type = true;
	else
		type = false;
}
