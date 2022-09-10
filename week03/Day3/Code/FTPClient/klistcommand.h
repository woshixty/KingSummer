// -------------------------------------------------------
// klistcommand.h
// 创建者： xie tingyu
// 创建时间： 2022/7/19
// 功能描述： LIST命令执行器
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