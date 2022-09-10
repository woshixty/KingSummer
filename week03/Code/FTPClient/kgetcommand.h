// -------------------------------------------------------
// kgetcommand.h
// 创建者： xie tingyu
// 创建时间： 2022/7/19
// 功能描述： RETR命令执行器
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_GET_COMMAND_H_
#define _K_GET_COMMAND_H_

#include "kabstractcommand.h"
class KGetCommand : public KAbstractCommand
{
public:
	explicit KGetCommand(KSender* pSender);
	~KGetCommand() override;
	bool execute(list_str& cmdArgs) override;

private:
	FILE* m_pFile;
};

#endif