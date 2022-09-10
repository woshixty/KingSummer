// -------------------------------------------------------
// kmonitorrequest.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/12
// ���������� ���������
// Copyright 2013 Kingsoft
// -------------------------------------------------------- 

#ifndef _K_MONITORREQUEST_H_
#define _K_MONITORREQUEST_H_

#include <QObject>
#include <QVector>

#include <sdkddkver.h>
#include <Windows.h>
#include <atlbase.h>
#include <atlstr.h>

class KMonitorRequest final : public QObject
{
	Q_OBJECT

public:
	KMonitorRequest(LPCTSTR sz, BOOL b, DWORD dw, DWORD size, QObject *parent);
	~KMonitorRequest() override;

	bool openDirectory();
	void beginRead();
	void sendFileChangeData();
	void requestTermination();

protected:
	// �������Ļص�����
	static VOID CALLBACK notificationCompletion(
		DWORD dwErrorCode,
		DWORD dwNumberOfBytesTransfered,
		LPOVERLAPPED lpOverlapped);

	// ReadDirectoryChangesW()�������
	DWORD		m_dwFilterFlags;
	BOOL		m_bIncludeChildren;
	CStringW	m_wstrDirectory;

	// CreateFile()�������ļ����
	HANDLE		m_hDirectory;

	// ReadDirectoryChangesW()����Ҫ�Ĳ���
	OVERLAPPED	m_overlapped{};

	// �������ݻ�����
	QVector<byte> m_Buffer;

signals:
	void fileChangeData(QVector<byte> m_data, CStringW m_wstrDirectory);
};

#endif