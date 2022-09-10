#include "krequest.h"

#include <utility>
#include "kutils.h"

KRequest::KRequest()
= default;

KRequest::~KRequest()
= default;

void KRequest::initialize(const string& line)
{
	clear();
	KUtils::parseLine(line, m_cmdName, m_cmdArgs);
}

void KRequest::initialize(string cmdName, list_str cmdArgs)
{
	m_cmdName = std::move(cmdName);
	m_cmdArgs = std::move(cmdArgs);
}

void KRequest::initialize(string cmdName, const string cmdArg)
{
	m_cmdName = std::move(cmdName);
	m_cmdArgs.push_back(cmdArg);
}

void KRequest::clear()
{
	m_cmdArgs.clear();
	m_cmdName.clear();
}

void KRequest::getRequestStr(string& requestStr) const
{
	requestStr.clear();
	requestStr.append(m_cmdName);
	for (const auto& cmd_arg : m_cmdArgs)
		requestStr.append(" " + cmd_arg);
	requestStr.append("\r\n");
}

string KRequest::getRequestStr() const
{
	string requestStr;
	requestStr.append(m_cmdName);
	for (const auto& cmd_arg : m_cmdArgs)
		requestStr.append(" " + cmd_arg);
	return requestStr;
}
