// -------------------------------------------------------
// kpasscommand.h
// 创建者： xie tingyu
// 创建时间： 2022/7/19
// 功能描述： PASS命令执行器
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_PASS_COMMAND_H_
#define _K_PASS_COMMAND_H_

#include "kabstractcommand.h"
class KPassCommand final : public KAbstractCommand
{
public:
	explicit KPassCommand(KSender* pSender);
	~KPassCommand() override;

	bool execute(list_str& cmdArgs) override;
};

#endif