// -------------------------------------------------------
// kdeletecommand.h
// 创建者： xie tingyu
// 创建时间： 2022/7/25
// 功能描述： DELE命令执行器
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_DELETE_COMMAND_H_
#define _K_DELETE_COMMAND_H_

#include "kabstractcommand.h"

class KDeleteCommand final : public KAbstractCommand
{
public:
	explicit KDeleteCommand(KSender* pSender);
	~KDeleteCommand() override;
	bool execute(list_str& cmdArgs) override;
};

#endif