// -------------------------------------------------------
// kabstractcommand.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/19
// ���������� ������࣬����ÿһ������Ľӿڣ���װ��������
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef __K_ABSTRACT_COMMAND_H_
#define __K_ABSTRACT_COMMAND_H_

#include "ksocket.h"
#include "kconstats.h"
#include "kcommandresponse.h"
#include "kprint.h"

class KAbstractCommand
{
public:
	KAbstractCommand();
	virtual ~KAbstractCommand();

	// ִ������
	virtual BOOL executeCommand(KSocket* ptcpSocket, list_str& cmdArgs) = 0;

	// �ȴ�������Ӧ��
	virtual BOOL waitForServerReply(KSocket *ptcpsocket, string &reply) = 0;

	// ����packet
	virtual VOID makeOptUtf8OnPacket(string& packet, list_str& cmdArgs) = 0;

	// ��װ����
	void makePacket(string& packet, list_str& cmdArgs);

	// ����pasv�����ö˿�
	unsigned sendPASV(KSocket* ptcpSocket);

	// ����socket���Ӳ���ȡ��������
	BOOL createSocketRecvS(CHAR* pipAddr, unsigned dataPort);
	BOOL createSocketRecvF(CHAR* pipAddr, unsigned dataPort, const string& filename);

	// ����socket���Ӳ��ϴ�����
	BOOL createSocketUploadF(CHAR* pipAddr, unsigned dataPort, FILE *file);

	// ��װ���ݰ�������
	BOOL createPacketSend(string& packet, list_str& cmdArgs, KSocket* ptcpSocket);

protected:
	KCommandResponse m_commandRes;
	string m_reply;
};

#endif

