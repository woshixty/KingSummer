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
	// 创建新的 KMonitorRequest 对象
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
		// 解析数据
		parsingData(information, wstrDirectory);
		// 如果数据已解析完就返回
		if (!information.NextEntryOffset)
			break;
		pData += information.NextEntryOffset;
	}
}

void KMonitorServer::parsingData(FILE_NOTIFY_INFORMATION& information, const CStringW& m_wstrDirectory) const
{
	CStringW wstrFilename(information.FileName, information.FileNameLength / sizeof(wchar_t));
	// 处理反斜杠根目录
	if (m_wstrDirectory.Right(1) != L"\\")
		wstrFilename = m_wstrDirectory + L"\\" + wstrFilename;
	else
		wstrFilename = m_wstrDirectory + wstrFilename;
	// 如果是短文件名，就拓展
	const LPCWSTR wszFilename = PathFindFileNameW(wstrFilename);
	const int len = lstrlenW(wszFilename);
	if (len <= 12 && wcschr(wszFilename, L'~'))
	{
		wchar_t wbuf[MAX_PATH];
		if (GetLongPathNameW(wstrFilename, wbuf, _countof(wbuf)) > 0)
			wstrFilename = wbuf;
	}
	// TODO 封装成消息添加到消息队列
	// 获得文件名：将CStringW转换为QString
	const QString fileName = QString::fromWCharArray(wstrFilename);
	// 获得操作类型
	const KOperationFlag operation = explainOperation(information.Action);
	// TODO 获取文件大小和所属者等信息
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
	// 进行数据销毁处理
	requestTermination();
	m_lock->unlock();
}
