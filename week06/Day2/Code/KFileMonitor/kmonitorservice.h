// -------------------------------------------------------
// kmonitorservice.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/12
// ���������� 
// Copyright 2013 Kingsoft
// -------------------------------------------------------- 

#ifndef _K_MONITORSERVICE_H_
#define _K_MONITORSERVICE_H_

#include <QObject>
#include <Windows.h>

class KReadChangesRequest;
class KReadChangesServer;

class KReadChangesRequest
{
public:
	KReadChangesRequest();
	~KReadChangesRequest();

	// ��һ���ļ����
	bool OpenDirectory();
	// ��ȡ��Ϣ
	void BeginRead();
};

class KMonitorService final : public QObject
{
	Q_OBJECT

public:
	KMonitorService(QObject *parent);
	~KMonitorService() override;

	bool OpenDirectory();

	void BeginRead();

protected:
	// �������Ļص�����
	static void CALLBACK NotificationCompletion(
		DWORD dwErrorCode,
		DWORD dwNumberOfBytesTransfered,
		LPOVERLAPPED lpOverlapped
	);

	// ReadDirectoryChangesW()��������
	DWORD		m_dwFilterFlags;
	BOOL		m_bIncludeChildren;
	std::string 	m_wstrDirectory;

	// CreateFile()�����ļ�����Ľ��
	HANDLE		m_hDirectory;

	// ReadDirectoryChangesW()������������ݽṹ
	OVERLAPPED	m_overlapped{};

	// �������ݻ�����
	std::vector<byte> m_buffer;

	// ���ݵ����ݻ�����
	std::vector<byte> m_backupBuffer;

	DWORD m_dwBytes;
};

#endif