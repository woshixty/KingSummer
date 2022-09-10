// -------------------------------------------------------
// kputcommand.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/15
// ���������� STOR����ִ����
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_PUT_COMMAND_H_
#define _K_PUT_COMMAND_H_

#include "kabstractcommand.h"

class KPutCommand : public KAbstractCommand
{
public:
	explicit KPutCommand(KSender* pSender);
	~KPutCommand() override;
	bool execute(list_str& cmdArgs) override;

private:
	FILE* m_pFile{};
	string m_filename;
};

#endif