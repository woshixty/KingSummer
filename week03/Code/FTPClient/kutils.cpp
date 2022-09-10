#include "kutils.h"
#include "io.h"
#include "kprint.h"

unsigned KUtils::getPortFromPasvRes(const KResponse& response)
{
	unsigned int v[6];
	sscanf_s(response.resmsg().data(), "%*[^(](%u,%u,%u,%u,%u,%u", &v[2], &v[3], &v[4], &v[5], &v[0], &v[1]);
	return v[0] * 256 + v[1];
}

void KUtils::getPortFromPasvRes(const string& responseStr, u_short& port)
{
	unsigned int v[6];
	sscanf_s(responseStr.c_str(), "%*[^(](%u,%u,%u,%u,%u,%u", &v[2], &v[3], &v[4], &v[5], &v[0], &v[1]);
	port =  v[0] * 256 + v[1];
}

FILE* KUtils::createFile(string dir, const string& filename)
{
	if (dir.empty())
		dir = "D:\\0-ftp-client\\";
	// 文件夹不存在就创建
	if (_access(dir.c_str(), 0) == -1)
	{
		errno = _mkdir(dir.c_str());
		switch (errno)
		{
		case EEXIST:
			// 未创建目录，因为 dirname 为现有文件、目录或设备的名称
			KPrint::printFileError(FILE_ERROR::DIR_EXIST);
			return nullptr;
		case ENOENT:
			// 找不到路径
			KPrint::printFileError(FILE_ERROR::DIR_NOT_FOUNT);
			return nullptr;
		default:
			;
		}
	}
	FILE* file = fopen((dir + filename).c_str(), "wb");
	return file;
}

FILE* KUtils::openFile(const string& filename)
{
	FILE* file = fopen(filename.c_str(), "rb");
	if (file == nullptr)
		KPrint::printFileError(FILE_ERROR::FILE_NOT_FOUNT);
	return file;
}

bool KUtils::parseLine(const string& line, string& name, list_str& args)
{
	char* pSplitStr = const_cast<char*>(line.c_str());
	// 查找用户输入命令字符串空格索引
	const size_type index = line.find(' ');
	// 找到空格
	if (index != string::npos)
	{
		char* pTemp = nullptr;
		char* pOther = nullptr;
		// 分割出命令名称
		char* pFirst = strtok_s(pSplitStr, " ", &pTemp);
		name = string(pFirst);
		// 分割出命令参数
		while ((pOther = strtok_s(nullptr, " ", &pTemp)) != nullptr)
			args.emplace_back(pOther);
	}
	else
		// 命令没有参数
		name = line;
	return true;
}

void KUtils::getFilename(const string& line, string& filename)
{
	const string::size_type iPos = line.find_last_of('\\') + 1;
	filename = line.substr(iPos, line.length() - iPos);
}
