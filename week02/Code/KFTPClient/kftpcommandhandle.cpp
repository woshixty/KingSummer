#include "kftpcommandhandle.h"

#define DEBUG

KFtpCommandHandle::KFtpCommandHandle(KSocket* ptcpsocket)
{
	this->m_ptcpSocket = ptcpsocket;
	// 建立 命令名 命令处理对象 一对一 映射 map
	initCommandMaps();
}

KFtpCommandHandle::~KFtpCommandHandle()
{
	releaseCommandMaps();
}

BOOL KFtpCommandHandle::executeCommand(string& cmdString)
{
	// 解析命令与参数
	/*KRequestPacket request;
	request.initialization(cmdString);
	request.getPacketStr();*/

	parseCommand(cmdString);

	auto pair = m_commandMap.find(m_cmdName);
	// 从 map 找到这个命令所对应的处理对象
	if (pair == m_commandMap.end())
	{
		std::cout << "命令不存在！" << std::endl;
		return false;
	}
	KAbstractCommand* pcommand = pair->second;
	return pcommand->executeCommand(m_ptcpSocket, m_cmdArgs);
}

BOOL KFtpCommandHandle::waitForCommandReply() const
{
	KAbstractCommand* pcommand = nullptr;
	string reply;
	pcommand = m_commandMap.find(m_cmdName)->second;
	// 等待服务端回应
	BOOL ret = pcommand->waitForServerReply(m_ptcpSocket, reply);
	std::cout << m_cmdName << " reply：" << reply << std::endl;
	return ret;
}

void KFtpCommandHandle::parseCommand(string& cmdString)
{
	char* pfirst = NULL;
	char* pother = NULL;
	char* psplitStr = NULL;
	char* ptemp = NULL;
	// 清空cmdArgs
	m_cmdArgs.clear();
	// 获得 char * 指针
	psplitStr = const_cast<char*>(cmdString.c_str());
	// 查找用户输入命令字符串空格索引
	const size_type index = cmdString.find(' ');
	// 找到空格
	if (index != string::npos)
	{
		// 分割出命令名称
		pfirst = strtok_s(psplitStr, " ", &ptemp);
		m_cmdName = string(pfirst);
		// 分割出命令参数
		while ((pother = strtok_s(nullptr, " ", &ptemp)) != nullptr)
			m_cmdArgs.emplace_back(pother);
	}
	else
		// 命令没有参数
		m_cmdName = cmdString;
}

void KFtpCommandHandle::initCommandMaps()
{
	m_commandMap.insert(std::make_pair(string("OPTS"), new KOptsCommand()));
	m_commandMap.insert(std::make_pair(string("USER"), new KUserCommand()));
	m_commandMap.insert(std::make_pair(string("PASS"), new KPassCommand()));
	m_commandMap.insert(std::make_pair(string("ls"), new KListCommand()));
	m_commandMap.insert(std::make_pair(string("get"), new KGetCommand()));
	m_commandMap.insert(std::make_pair(string("put"), new KPutCommand()));
}

void KFtpCommandHandle::releaseCommandMaps()
{
	for (auto it = m_commandMap.begin(); it != m_commandMap.end(); ++it)
		delete it->second;  // NOLINT(clang-diagnostic-delete-abstract-non-virtual-dtor)
}
