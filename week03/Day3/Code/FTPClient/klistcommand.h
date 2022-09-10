// -------------------------------------------------------
// klistcommand.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/19
// ���������� LIST����ִ����
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_LIST_COMMAND_H_
#define _K_LIST_COMMAND_H_

#include "kabstractcommand.h"
class KListCommand : public KAbstractCommand
{
public:
	explicit KListCommand(KSender* pSender);
	~KListCommand() override;
	bool execute(list_str& cmdArgs) override;

private:
	string m_longmsg;
};

#endif