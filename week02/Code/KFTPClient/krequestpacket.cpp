#include "krequestpacket.h"


KRequestPacket::KRequestPacket()
{
}

void KRequestPacket::initialization(const string& line)
{
	// Çå¿ÕÊý¾Ý
	clear();
	KUtils::parseLine(m_cmdName, m_cmdArgs, line);
}

void KRequestPacket::clear()
{
	m_cmdArgs.clear();
	m_cmdName.clear();
}

string KRequestPacket::getPacketStr() const
{
	string packetStr = m_cmdName;
	for (const auto& cmd_arg : m_cmdArgs)
		packetStr.append(" " + cmd_arg);
	packetStr += "\r\n";
	return packetStr;
}
