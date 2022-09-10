// -------------------------------------------------------
// koptscommand.h
// 创建者： xie tingyu
// 创建时间： 2022/7/19
// 功能描述： OPTS命令执行器
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_OPTS_COMMAND_H_
#define _K_OPTS_COMMAND_H_

#include "kabstractcommand.h"

class KOptsCommand final : public KAbstractCommand
{
public:
	KOptsCommand(KSender* pSender);
	~KOptsCommand() override;

	bool execute(list_str& cmdArgs) override;
};

#endif

