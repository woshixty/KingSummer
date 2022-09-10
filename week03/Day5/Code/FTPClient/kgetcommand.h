// -------------------------------------------------------
// kgetcommand.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/19
// ���������� RETR����ִ����
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