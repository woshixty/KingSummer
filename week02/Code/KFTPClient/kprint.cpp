#include "kprint.h"

void KPrint::printCommandRes(KCommandResponse& res)
{
	std::cout << "CODE: " << res.getCode() << "  MSG: " << res.getMsg() << std::endl;
}

void KPrint::printFileError(FILE_ERROR error)
{
	std::cout << "�ļ�ϵͳ����: " << FILE_ERROR_MAP.find(error)->second << std::endl;
}

bool KPrint::printFailError(const string& function, const int errorcode)
{
	std::cout << function << "ʧ��, Error Code : " << errorcode << std::endl;
	return false;
}
