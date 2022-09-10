// -------------------------------------------------------
// kmessageconsumer.h
// 创建者： xie tingyu
// 创建时间： 2022/08/16
// 功能描述： 消息消费者
// Copyright 2013 Kingsoft
// -------------------------------------------------------- 

#ifndef _K_MESSAGECONSUMER_H_
#define _K_MESSAGECONSUMER_H_

#include "kmessagequeue.h"
#include "krecorddao.h"

#include <QThread>
#include <QSqlTableModel>
#include <QSystemTrayIcon>

class KMessageConsumer final : public QThread
{
	Q_OBJECT

public:
	KMessageConsumer(QObject *parent);
	~KMessageConsumer() override;

	void stopConsumerThread();
	void startConsumerThread();

	void setSqlTableModel(QSqlTableModel* recordTableModel) { m_pRecordTableModel = recordTableModel; }
	void setRecordDao(KRecordDao* recordDao) { m_pRecordDao = recordDao; }
	void setMessageQueue(KMessageQueue* messageQueue) { m_pMessageQueue = messageQueue; }
	void setSystemTrayIcon(QSystemTrayIcon* systemTrayIcon) { m_pSystemTrayIcon = systemTrayIcon; }

protected:
	void run() override;

private:
	bool m_bTerminate;
	KMessageQueue* m_pMessageQueue;
	KRecordDao* m_pRecordDao;
	QSqlTableModel* m_pRecordTableModel;
	QSystemTrayIcon* m_pSystemTrayIcon{};
	KGlobalData* m_pGlobalData = KGlobalData::getGlobalDataInstance();
};

#endif
