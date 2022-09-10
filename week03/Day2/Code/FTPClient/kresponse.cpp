#include "KResponse.h"

KResponse::KResponse()
= default;

void KResponse::initialize(const string& resmsg)
{
	const size_type index = resmsg.find(' ');
	if (index != string::npos)
	{
		m_code = std::stoi(resmsg.substr(0, 3));
		m_resmsg = resmsg.substr(4);
	}
	else
	{
		m_code = -1;
		m_resmsg = resmsg;
	}
}
