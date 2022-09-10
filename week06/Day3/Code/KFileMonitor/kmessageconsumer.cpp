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
			// �������ݹ���
			if(!KMsgFilter::filter(message))
				continue;
			// �������С�������������Ϣ����
			if (!m_pGlobalData->isVisible())
				m_pSystemTrayIcon->showMessage(message.title(), message.content(), QSystemTrayIcon::Information, 100);
			// ��ӵ�ҳ����ͬʱ������ݿ�
			// TODO ��������������
			message.generateRow(m_pRecordTableModel);
		}
	}
}
