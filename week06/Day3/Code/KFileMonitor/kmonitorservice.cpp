#include "kmonitorservice.h"

#include <comutil.h>
#include <Windows.h>
#include <QDebug>

KMonitorService::KMonitorService(QObject *parent)
	: QObject(parent)
{
	// 控制server线程的锁与控制条件
	m_pServerLock = new QMutex();
	m_pServerCondition = new QWaitCondition();
	// 初始化server线程
	m_pServerThread = new KMonitorServer(m_pServerCondition, m_pServerLock, this);
	connect(
		this, SIGNAL(addFileToWatch(LPCTSTR, BOOL, DWORD, DWORD)),
		m_pServerThread, SLOT(onFileDirAddToWatch(LPCTSTR, BOOL, DWORD, DWORD))
	);
}

KMonitorService::~KMonitorService()
{
	delete m_pServerCondition;
	delete m_pServerLock;
}

bool KMonitorService::startServerThread() const
{
	if (m_pServerThread->isRunning())
		return false;
	m_pServerThread->terminate(false);
	m_pServerThread->start();
	return true;
}

bool KMonitorService::stopServerThread() const
{
	m_pServerLock->lock();
	m_pServerThread->terminate(true);
	m_pServerCondition->notify_all();
	m_pServerLock->unlock();
	// 等待server线程执行完
	const HANDLE hThread = m_pServerThread->currentThreadId();
	MsgWaitForMultipleObjects(1, &hThread, FALSE, INFINITE, QS_ALLINPUT);
	return true;
}

void KMonitorService::addDirectory(QString directory)
{
	if (m_pServerThread->isRunning())
	{
		// TODO 更好的转换方法
		emit addFileToWatch(
			reinterpret_cast<LPCTSTR>(directory.data()),
			m_subtree,
			m_dwNotificationFlags,
			m_dwBufferSize
		);
	}
}

void KMonitorService::startMonitor(KProfile profile)
{
	QList<int> options = profile.profileOptionsList();
	// 根据options设置dwNotificationFlags
	m_dwNotificationFlags = 0;
	m_subtree = false;
	for (const int option : options)
		switch (option)
		{
		case 1:
			m_dwNotificationFlags |= FILE_NOTIFY_CHANGE_FILE_NAME;
			break;
		case 2:
			m_dwNotificationFlags |= FILE_NOTIFY_CHANGE_DIR_NAME;
			break;
		case 3:
			m_dwNotificationFlags |= FILE_NOTIFY_CHANGE_ATTRIBUTES;
			break;
		case 4:
			m_dwNotificationFlags |= FILE_NOTIFY_CHANGE_SIZE;
			break;
		case 5:
			m_dwNotificationFlags |= FILE_NOTIFY_CHANGE_LAST_WRITE;
			break;
		case 6:
			m_dwNotificationFlags |= FILE_NOTIFY_CHANGE_LAST_ACCESS;
			break;
		case 7:
			m_dwNotificationFlags |= FILE_NOTIFY_CHANGE_CREATION;
			break;
		case 8:
			m_dwNotificationFlags |= FILE_NOTIFY_CHANGE_SECURITY;
			break;
		case 9:
			m_subtree = true;
			break;
		default:;
		}
	// 监听的文件夹
	bool flag = startServerThread();
	QStringList directories = profile.watchDirsList();
	for (const auto& directory : directories) {
		addDirectory(directory);
	}
}

void KMonitorService::pauseServer() const
{
	m_pServerThread->pauseWatching();
	m_pServerCondition->notify_all();
}

void KMonitorService::startServer()
{
	m_pServerThread->startWatching();
	m_pServerCondition->notify_all();
	startMonitor(m_pGlobalData->activeProfile());
}

void KMonitorService::setKMessageQueue(KMessageQueue* queue)
{
	m_pMessageQueue = queue;
	m_pServerThread->setKMessageQueue(m_pMessageQueue);
}
