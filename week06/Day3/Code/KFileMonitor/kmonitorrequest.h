// -------------------------------------------------------
// kmonitorrequest.h
// 创建者： xie tingyu
// 创建时间： 2022/08/12
// 功能描述： 监控请求类
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
	// 完成请求的回调函数
	static VOID CALLBACK notificationCompletion(
		DWORD dwErrorCode,
		DWORD dwNumberOfBytesTransfered,
		LPOVERLAPPED lpOverlapped);

	// ReadDirectoryChangesW()所需参数
	DWORD		m_dwFilterFlags;
	BOOL		m_bIncludeChildren;
	CStringW	m_wstrDirectory;

	// CreateFile()创建的文件句柄
	HANDLE		m_hDirectory;

	// ReadDirectoryChangesW()所需要的参数
	OVERLAPPED	m_overlapped{};

	// 接收数据缓冲区
	QVector<byte> m_Buffer;

signals:
	void fileChangeData(QVector<byte> m_data, CStringW m_wstrDirectory);
};

#endif