#include "kmonitorserver.h"

#include <atlstr.h>
#include <comdef.h>
#include <QDebug>

KMonitorServer::KMonitorServer(QWaitCondition* condition, QMutex* lock, QObject *parent)
	: QThread(parent)
{
	m_bTerminate = false;
	m_bPause = false;
	m_condition = condition;
	m_lock = lock;
}

KMonitorServer::~KMonitorServer()
= default;

void KMonitorServer::setKMessageQueue(KMessageQueue* queue)
{
	m_messageQueue = queue;
}

void KMonitorServer::onFileDirAddToWatch(LPCTSTR szDirectory, BOOL bWatchSubtree, DWORD dwNotifyFilter, DWORD dwBufferSize)
{
	qDebug() << "KMonitorServer::onFileDirAddToWatch";
	// �����µ� KMonitorRequest ����
	const auto pRequest = new KMonitorRequest(szDirectory, bWatchSubtree, dwNotifyFilter, dwBufferSize, nullptr);

	connect(
		pRequest, SIGNAL(fileChangeData(QVector<byte>, CStringW)),
		this, SLOT(onFileChangeData(QVector<byte>, CStringW))
	);
	if (pRequest->openDirectory())
	{
		m_pRequests.push_back(pRequest);
		pRequest->beginRead();
	}
	else
		delete pRequest;
}

void KMonitorServer::onFileChangeData(QVector<byte> data, const CStringW& wstrDirectory) const
{
	qDebug() << "KMonitorServer::onFileChangeData";
	byte* pData = data.data();
	while (true)
	{
		auto& information = reinterpret_cast<FILE_NOTIFY_INFORMATION&>(*pData);
		// ��������
		parsingData(information, wstrDirectory);
		// ��������ѽ�����ͷ���
		if (!information.NextEntryOffset)
			break;
		pData += information.NextEntryOffset;
	}
}

void KMonitorServer::parsingData(FILE_NOTIFY_INFORMATION& information, const CStringW& m_wstrDirectory) const
{
	CStringW wstrFilename(information.FileName, information.FileNameLength / sizeof(wchar_t));
	// ����б�ܸ�Ŀ¼
	if (m_wstrDirectory.Right(1) != L"\\")
		wstrFilename = m_wstrDirectory + L"\\" + wstrFilename;
	else
		wstrFilename = m_wstrDirectory + wstrFilename;
	// ����Ƕ��ļ���������չ
	const LPCWSTR wszFilename = PathFindFileNameW(wstrFilename);
	const int len = lstrlenW(wszFilename);
	if (len <= 12 && wcschr(wszFilename, L'~'))
	{
		wchar_t wbuf[MAX_PATH];
		if (GetLongPathNameW(wstrFilename, wbuf, _countof(wbuf)) > 0)
			wstrFilename = wbuf;
	}
	// TODO ��װ����Ϣ��ӵ���Ϣ����
	// ����ļ�������CStringWת��ΪQString
	const QString fileName = QString::fromWCharArray(wstrFilename);
	// ��ò�������
	const KOperationFlag operation = explainOperation(information.Action);
	// TODO ��ȡ�ļ���С�������ߵ���Ϣ
	const KMessage message(operation, fileName, 0, "");
	m_messageQueue->push_back(message);
}

void KMonitorServer::pauseWatching()
{
	m_bPause = true;
}

void KMonitorServer::startWatching()
{
	m_bPause = false;
}

void KMonitorServer::terminate(bool flag)
{
	m_bTerminate = flag;
}

void KMonitorServer::requestTermination()
{
	for (const auto& m_pRequest : m_pRequests)
		m_pRequest->requestTermination();
	for (const auto& m_pRequest : m_pRequests)
		delete m_pRequest;
	m_pRequests.clear();
}

KOperationFlag KMonitorServer::explainOperation(DWORD dwAction)
{
	switch (dwAction)
	{
	case FILE_ACTION_ADDED:
		return KOperationFlag::Added;
	case FILE_ACTION_REMOVED:
		return KOperationFlag::Deleted;
	case FILE_ACTION_MODIFIED:
		return KOperationFlag::Modified;
	case FILE_ACTION_RENAMED_OLD_NAME:
		return KOperationFlag::RenamedFrom;
	case FILE_ACTION_RENAMED_NEW_NAME:
		return KOperationFlag::RenamedTo;
	default:
		return KOperationFlag::BadData;
	}
}

void KMonitorServer::run()
{
	m_lock->lock();
	while (!m_bTerminate)
	{
		m_condition->wait(m_lock);
		if(m_bPause)
			requestTermination();
	}
	// �����������ٴ���
	requestTermination();
	m_lock->unlock();
}
