#include "kcommandresponse.h"

#include <utility>

KCommandResponse::KCommandResponse()
{
}

void KCommandResponse::initialization(int code, string resmsg)
{
	m_code = code;
	m_resmsg = std::move(resmsg);
}

void KCommandResponse::initialization(const string& resmsg)
{
	// 分离出状态码与状态信息
	const size_type index = resmsg.find(' ');
	if(index != string::npos)
	{
		// 找到空格 - 分离出状态码与状态信息
		int spacepos = resmsg.find(' ');
		m_code = std::stoi(resmsg.substr(0, 3));
		m_resmsg = resmsg.substr(4);
	}
	else
	{
		// 未找到空格
		m_code = -1;
		m_resmsg = resmsg;
	}
}
