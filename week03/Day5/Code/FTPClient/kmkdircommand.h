// -------------------------------------------------------
// kmkdircommand.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/25
// ���������� MKD����ִ����
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