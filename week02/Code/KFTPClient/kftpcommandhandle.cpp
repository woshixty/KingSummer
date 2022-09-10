#include "kftpcommandhandle.h"

#define DEBUG

KFtpCommandHandle::KFtpCommandHandle(KSocket* ptcpsocket)
{
	this->m_ptcpSocket = ptcpsocket;
	// ���� ������ �������� һ��һ ӳ�� map
	initCommandMaps();
}

KFtpCommandHandle::~KFtpCommandHandle()
{
	releaseCommandMaps();
}

BOOL KFtpCommandHandle::executeCommand(string& cmdString)
{
	// �������������
	/*KRequestPacket request;
	request.initialization(cmdString);
	request.getPacketStr();*/

	parseCommand(cmdString);

	auto pair = m_commandMap.find(m_cmdName);
	// �� map �ҵ������������Ӧ�Ĵ������
	if (pair == m_commandMap.end())
	{
		std::cout << "������ڣ�" << std::endl;
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
	// �ȴ�����˻�Ӧ
	BOOL ret = pcommand->waitForServerReply(m_ptcpSocket, reply);
	std::cout << m_cmdName << " reply��" << reply << std::endl;
	return ret;
}

void KFtpCommandHandle::parseCommand(string& cmdString)
{
	char* pfirst = NULL;
	char* pother = NULL;
	char* psplitStr = NULL;
	char* ptemp = NULL;
	// ���cmdArgs
	m_cmdArgs.clear();
	// ��� char * ָ��
	psplitStr = const_cast<char*>(cmdString.c_str());
	// �����û����������ַ����ո�����
	const size_type index = cmdString.find(' ');
	// �ҵ��ո�
	if (index != string::npos)
	{
		// �ָ����������
		pfirst = strtok_s(psplitStr, " ", &ptemp);
		m_cmdName = string(pfirst);
		// �ָ���������
		while ((pother = strtok_s(nullptr, " ", &ptemp)) != nullptr)
			m_cmdArgs.emplace_back(pother);
	}
	else
		// ����û�в���
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
