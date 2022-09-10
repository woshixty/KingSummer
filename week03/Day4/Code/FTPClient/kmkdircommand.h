// -------------------------------------------------------
// kmkdircommand.h
// 创建者： xie tingyu
// 创建时间： 2022/7/25
// 功能描述： MKD命令执行器
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_MKDIR_COMMAND_H_
#define _K_MKDIR_COMMAND_H_

#include "kabstractcommand.h"

class KMkdirCommand final : public KAbstractCommand
{
public:
	explicit KMkdirCommand(KSender* pSender);
	~KMkdirCommand() override;
	bool execute(list_str& cmdArgs) override;
};

#endif