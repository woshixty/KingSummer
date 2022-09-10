// -------------------------------------------------------
// kquitcommand.h
// 创建者： xie tingyu
// 创建时间： 2022/7/25
// 功能描述： QUIT命令执行器
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_QUIT_COMMAND_H_
#define _K_QUIT_COMMAND_H_

#include "kabstractcommand.h"

class KQuitCommand : public KAbstractCommand
{
public:
	explicit KQuitCommand(KSender* pSender);
	~KQuitCommand() override;
	bool execute(list_str& cmdArgs) override;
};

#endif