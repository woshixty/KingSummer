// -------------------------------------------------------
// kdeletecommand.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/25
// ���������� DELE����ִ����
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