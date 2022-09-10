#include "kmonitorservice.h"

KMonitorService::KMonitorService(QObject *parent)
	: QObject(parent)
{}

KMonitorService::~KMonitorService()
= default;

bool KMonitorService::OpenDirectory()
{
	if (m_hDirectory)
		return true;
	// 创建文件句柄
	m_hDirectory = CreateFileA(
		m_wstrDirectory.data(),
		FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		nullptr,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
		nullptr);
	// 创建失败返回false
	if (m_hDirectory == INVALID_HANDLE_VALUE)
		return false;
	return true;
}

void KMonitorService::BeginRead()
{
	ReadDirectoryChangesW(
		m_hDirectory,
		&m_buffer[0],
		static_cast<DWORD>(m_buffer.size()),
		m_bIncludeChildren,
		m_dwFilterFlags,
		&m_dwBytes,
		&m_overlapped,
		&NotificationCompletion
	);
}
