// -------------------------------------------------------
// kpasscommand.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/19
// ���������� PASS����ִ����
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