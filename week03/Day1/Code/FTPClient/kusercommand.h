// -------------------------------------------------------
// kusercommand.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/19
// ���������� USER����ִ����
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