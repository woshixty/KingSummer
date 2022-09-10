// -------------------------------------------------------
// kmonitorservice.h
// 创建者： xie tingyu
// 创建时间： 2022/08/12
// 功能描述： 
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

	// 打开一个文件句柄
	bool OpenDirectory();
	// 读取消息
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
	// 完成请求的回调函数
	static void CALLBACK NotificationCompletion(
		DWORD dwErrorCode,
		DWORD dwNumberOfBytesTransfered,
		LPOVERLAPPED lpOverlapped
	);

	// ReadDirectoryChangesW()所需属性
	DWORD		m_dwFilterFlags;
	BOOL		m_bIncludeChildren;
	std::string 	m_wstrDirectory;

	// CreateFile()创建文件句柄的结果
	HANDLE		m_hDirectory;

	// ReadDirectoryChangesW()输入输出的数据结构
	OVERLAPPED	m_overlapped{};

	// 接收数据缓冲区
	std::vector<byte> m_buffer;

	// 备份的数据缓冲区
	std::vector<byte> m_backupBuffer;

	DWORD m_dwBytes;
};

#endif