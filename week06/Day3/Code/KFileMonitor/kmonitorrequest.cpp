#include "kmonitorrequest.h"

#include <QDebug>

KMonitorRequest::KMonitorRequest(LPCTSTR sz, BOOL b, DWORD dw, DWORD size, QObject* parent)
	: QObject(parent)
{
	// ��ʼ������
	m_dwFilterFlags = dw;
	m_bIncludeChildren = b;
	m_wstrDirectory = sz;
	m_hDirectory = nullptr;
	// ��ʼ��OVERLAPPED�ṹ
	::ZeroMemory(&m_overlapped, sizeof(OVERLAPPED));
	m_overlapped.hEvent = this;
	m_Buffer.resize(static_cast<int>(size));
}

KMonitorRequest::~KMonitorRequest()
= default;

bool KMonitorRequest::openDirectory()
{
	if (m_hDirectory)
		return true;
	// ���ļ����
	m_hDirectory = CreateFileW(
		m_wstrDirectory,
		FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		nullptr,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
		nullptr
	);
	if (m_hDirectory == INVALID_HANDLE_VALUE)
		return false;
	return true;
}

void KMonitorRequest::beginRead()
{
	DWORD dwBytes = 0;
	// TODO ����δ�ɹ������
	BOOL success = ReadDirectoryChangesW(
		m_hDirectory,
		&m_Buffer[0],
		m_Buffer.size(),
		m_bIncludeChildren,
		m_dwFilterFlags,
		&dwBytes,
		&m_overlapped,
		&notificationCompletion
	);
}

void KMonitorRequest::sendFileChangeData()
{
	qDebug() << "KMonitorRequest::sendFileChangeData";
	emit fileChangeData(m_Buffer, m_wstrDirectory);
}

void KMonitorRequest::requestTermination()
{
	CancelIo(m_hDirectory);
	CloseHandle(m_hDirectory);
	m_hDirectory = nullptr;
}

void KMonitorRequest::notificationCompletion(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped)
{
	const auto pRequest = static_cast<KMonitorRequest*>(lpOverlapped->hEvent);
	if (dwErrorCode == ERROR_OPERATION_ABORTED)
	{
		// TODO �������쳣���ָ��Ϊ�յ�����
		// ::InterlockedDecrement(&pBlock->m_pServer->m_nOutstandingRequests);
		// delete pRequest;
		return;
	}
	if (!dwNumberOfBytesTransfered)
		return;
	// �����ݷ��ͳ�ȥ
	pRequest->sendFileChangeData();
	pRequest->beginRead();
}
