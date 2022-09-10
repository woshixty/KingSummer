#include "kutils.h"

unsigned KUtils::getPortFromPasvRes(const KCommandResponse& response)
{
	unsigned int v[6];
	sscanf_s(response.getMsg().data(), "%*[^(](%u,%u,%u,%u,%u,%u", &v[2], &v[3], &v[4], &v[5], &v[0], &v[1]);
	return v[0] * 256 + v[1];
}

FILE* KUtils::createFile(string dir, const string& filename)
{
	if(dir.empty())
		dir = "D:\\0-ftp-client\\";
	// �ļ��в����ھʹ���
	if (_access(dir.c_str(), 0) == -1)
	{
		errno = _mkdir(dir.c_str());
		switch (errno)
		{
		case EEXIST:
			// δ����Ŀ¼����Ϊ dirname Ϊ�����ļ���Ŀ¼���豸������
			KPrint::printFileError(FILE_ERROR::DIR_EXIST);
			return nullptr;
		case ENOENT:
			// �Ҳ���·��
			KPrint::printFileError(FILE_ERROR::DIR_NOT_FOUNT);
			return nullptr;
		default:
			;
		}
	}
	FILE* file = fopen((dir + filename).c_str(), "wb");
	return file;
}

bool KUtils::parseLine(string& name, list_str& args, const string& line)
{
	char* pSplitStr = const_cast<char*>(line.c_str());
	// �����û����������ַ����ո�����
	const size_type index = line.find(' ');
	// �ҵ��ո�
	if (index != string::npos)
	{
		char* pTemp = nullptr;
		char* pOther = nullptr;
		// �ָ����������
		char* pFirst = strtok_s(pSplitStr, " ", &pTemp);
		name = string(pFirst);
		// �ָ���������
		while ((pOther = strtok_s(nullptr, " ", &pTemp)) != nullptr)
			args.emplace_back(pOther);
	}
	else
		// ����û�в���
		name = line;
	return true;
}
