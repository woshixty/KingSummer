// -------------------------------------------------------
// koptscommand.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/19
// ���������� OPTS����ִ����
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

