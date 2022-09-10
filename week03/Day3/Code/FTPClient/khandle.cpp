#include "khandle.h"
#include "koptscommand.h"
#include "kpasscommand.h"
#include "kusercommand.h"
#include "kgetcommand.h"
#include "klistcommand.h"
#include "kmkdircommand.h"
#include "kputcommand.h"
#include "kdeletecommand.h"
#include "kquitcommand.h"

#include <sstream>

KHandle::KHandle(KSender* pSender)
{
	m_pSender = pSender;
	m_pCommand = nullptr;
	initCommandMaps(pSender);
}

KHandle::~KHandle()
{
	releaseCommandMaps();
}

bool KHandle::executeCommand(const string& cmdString, KResponse& response)
{
	parseCommand(cmdString);
	const auto pair = m_commandMap.find(m_cmdName);
	if (pair == m_commandMap.end())
		return KPrint::printClientError(CLIENT_ERROR::CMD_NOT_FOUND);
	m_pCommand = pair->second;
	return m_pCommand->execute(m_cmdArgs);
}

void KHandle::parseCommand(const string& cmdString)
{
	m_cmdName.clear();
	m_cmdArgs.clear();
	string temp;
	std::stringstream input(cmdString);
	input >> m_cmdName;
	while (input >> temp)
		m_cmdArgs.push_back(temp);
}

void KHandle::initCommandMaps(KSender* pSender)
{
	m_commandMap.insert(std::make_pair(string("OPTS"), new KOptsCommand(pSender)));
	m_commandMap.insert(std::make_pair(string("user"), new KUserCommand(pSender)));
	m_commandMap.insert(std::make_pair(string("pass"), new KPassCommand(pSender)));
	m_commandMap.insert(std::make_pair(string("ls"), new KListCommand(pSender)));
	m_commandMap.insert(std::make_pair(string("get"), new KGetCommand(pSender)));
	m_commandMap.insert(std::make_pair(string("put"), new KPutCommand(pSender)));
	m_commandMap.insert(std::make_pair(string("mkdir"), new KMkdirCommand(pSender)));
	m_commandMap.insert(std::make_pair(string("delete"), new KDeleteCommand(pSender)));
	m_commandMap.insert(std::make_pair(string("bye"), new KQuitCommand(pSender)));
}

void KHandle::releaseCommandMaps()
{
	for (auto it = m_commandMap.begin(); it != m_commandMap.end(); ++it)
		delete it->second;
}
