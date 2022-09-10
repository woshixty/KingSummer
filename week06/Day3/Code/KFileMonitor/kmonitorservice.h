// -------------------------------------------------------
// kmonitorservice.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/12
// ���������� ��ط����࣬������Server�߳�
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

	// ����server�̵߳����������������
	QWaitCondition* m_pServerCondition;
	QMutex* m_pServerLock;
	bool m_subtree{};
};

#endif