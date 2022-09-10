// -------------------------------------------------------
// kmonitorserver.h
// 创建者： xie tingyu
// 创建时间： 2022/08/14
// 功能描述： 管理监控请求类-线程-消息生产者
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_MONITORSERVER_H_
#define _K_MONITORSERVER_H_

#include "kmessagequeue.h"
#include "kmonitorrequest.h"

#include <QThread>
#include <atlstr.h>

// ReSharper disable once CppInconsistentNaming
class KMonitorServer final : public QThread
{
	Q_OBJECT

public:
	KMonitorServer(QWaitCondition* condition, QMutex* lock, QObject *parent);
	~KMonitorServer() override;

	void setKMessageQueue(KMessageQueue* queue);

	void terminate(bool flag);
	void requestTermination();
	void parsingData(FILE_NOTIFY_INFORMATION& information, const CStringW& m_wstrDirectory) const;
	void pauseWatching();
	void startWatching();

	static KOperationFlag explainOperation(DWORD dwAction);

private slots:
	void onFileDirAddToWatch(LPCTSTR szDirectory, BOOL bWatchSubtree, DWORD dwNotifyFilter, DWORD dwBufferSize);
	void onFileChangeData(QVector<byte> data, const CStringW& wstrDirectory) const;

protected:
	void run() override;

private:
	QVector<KMonitorRequest*> m_pRequests;
	KMessageQueue* m_messageQueue{};
	bool m_bTerminate;
	bool m_bPause;

	QWaitCondition* m_condition;
	QMutex* m_lock;
};

#endif