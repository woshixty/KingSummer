// -------------------------------------------------------
// khandle.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/19
// ���������� ����д�����
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_HANDLE_H_
#define _K_HANDLE_H_

#include "kabstractcommand.h"

class KHandle
{
public:
	KHandle(KSender* pSender);
	~KHandle();

	bool executeCommand(const string& cmdString, KResponse& response);
	void parseCommand(const string& cmdString);
	void initCommandMaps(KSender* pSender);
	void releaseCommandMaps();

private:
	string m_cmdName;
	list_str m_cmdArgs;
	KSender* m_pSender;
	KAbstractCommand* m_pCommand;
	std::map<string, KAbstractCommand*> m_commandMap;
};

#endif