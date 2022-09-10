// -------------------------------------------------------
// kusercommand.h
// 创建者： xie tingyu
// 创建时间： 2022/7/19
// 功能描述： USER命令执行器
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_USER_COMMAND_H_
#define _K_USER_COMMAND_H_

#include "kabstractcommand.h"

class KUserCommand final : public KAbstractCommand
{
public:
	explicit KUserCommand(KSender* pSender);
	~KUserCommand() override;

	bool execute(list_str& cmdArgs) override;
};

#endif