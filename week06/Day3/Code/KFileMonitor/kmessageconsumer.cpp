#include "kmessageconsumer.h"
#include "kmsgfilter.h"

KMessageConsumer::KMessageConsumer(QObject* parent)
	: QThread(parent), m_pMessageQueue(nullptr), m_pRecordDao(nullptr), m_pRecordTableModel(nullptr)
{
	m_bTerminate = false;
}

KMessageConsumer::~KMessageConsumer()
= default;

void KMessageConsumer::stopConsumerThread()
{
	m_bTerminate = true;
	m_pMessageQueue->stopQueue();
}

void KMessageConsumer::startConsumerThread()
{
	m_bTerminate = false;
	m_pMessageQueue->startQueue();
}

void KMessageConsumer::run()
{
	while (!m_bTerminate)
	{
		KMessage message;
		if(m_pMessageQueue->pop_front(message))
		{
			// 进行数据过滤
			if(!KMsgFilter::filter(message))
				continue;
			// 如果是最小化运行则进行消息弹窗
			if (!m_pGlobalData->isVisible())
				m_pSystemTrayIcon->showMessage(message.title(), message.content(), QSystemTrayIcon::Information, 100);
			// 添加到页面上同时存进数据库
			// TODO 数据量过大会崩溃
			message.generateRow(m_pRecordTableModel);
		}
	}
}
