// -------------------------------------------------------
// kquitcommand.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/25
// ���������� QUIT����ִ����
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