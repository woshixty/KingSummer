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
	// �����״̬����״̬��Ϣ
	const size_type index = resmsg.find(' ');
	if(index != string::npos)
	{
		// �ҵ��ո� - �����״̬����״̬��Ϣ
		int spacepos = resmsg.find(' ');
		m_code = std::stoi(resmsg.substr(0, 3));
		m_resmsg = resmsg.substr(4);
	}
	else
	{
		// δ�ҵ��ո�
		m_code = -1;
		m_resmsg = resmsg;
	}
}
