// -------------------------------------------------------
// kmonitorservice.h
// 创建者： xie tingyu
// 创建时间： 2022/08/12
// 功能描述： 监控服务类，管理监控Server线程
// Copyright 2013 Kingsoft
// -------------------------------------------------------- 

#ifndef _K_MONITORSERVICE_H_
#define _K_MONITORSERVICE_H_

#include "kmonitorserver.h"
#include "kprofile.h"

class KMonitorService final : public QObject
{
	Q_OBJECT

public:
	KMonitorService(QObject *parent);
	~KMonitorService() override;

	bool startServerThread() const;
	bool stopServerThread() const;
	void addDirectory(QString directory);
	void startMonitor(KProfile profile);
	void pauseServer() const;
	void startServer();

	void setKMessageQueue(KMessageQueue* queue);

signals:
	void addFileToWatch(LPCTSTR szDirectory, BOOL bWatchSubtree, DWORD dwNotifyFilter, DWORD dwBufferSize);

private:
	DWORD m_dwNotificationFlags = 0;
	DWORD m_dwBufferSize = 16384;

	KMonitorServer* m_pServerThread;
	KMessageQueue* m_pMessageQueue{};

	KGlobalData* m_pGlobalData = KGlobalData::getGlobalDataInstance();

	// 控制server线程的相关锁与条件变量
	QWaitCondition* m_pServerCondition;
	QMutex* m_pServerLock;
	bool m_subtree{};
};

#endif