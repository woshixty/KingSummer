// -------------------------------------------------------
// kmessagequeue.h
// 创建者： xie tingyu
// 创建时间： 2022/08/14
// 功能描述： 消息队列
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_MESSAGEQUEUE_H_
#define _K_MESSAGEQUEUE_H_

#include "kmessage.h"

#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include <QList>

class KMessageQueue final : public QObject
{
	Q_OBJECT

public:
	KMessageQueue(QObject* parent);
	~KMessageQueue() override;

	void push_back(const KMessage& value);
	bool pop_front(KMessage& value);
	void stopQueue();
	void startQueue();

private:
	bool m_bTerminate;
	QList<KMessage> m_messageList;
	QMutex m_lock;
	QWaitCondition m_condition;
};

#endif
