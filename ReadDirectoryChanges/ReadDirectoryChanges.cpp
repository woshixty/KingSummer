#include "stdafx.h"
#include "ReadDirectoryChanges.h"
#include "ReadDirectoryChangesPrivate.h"

using namespace ReadDirectoryChangesPrivate;

CReadDirectoryChanges::CReadDirectoryChanges(int nMaxCount)
	: m_Notifications(nMaxCount)
{
	m_hThread	= nullptr;
	m_pServer	= new CReadChangesServer(this);
	m_dwThreadId = 0;
}

CReadDirectoryChanges::~CReadDirectoryChanges()
{
	Terminate();
	delete m_pServer;
}

void CReadDirectoryChanges::Init()
{
	// Kick off the worker thread, which will be
	// managed by CReadChangesServer.
	// �����߳�����ִ��
	// ��CReadChangesServer������߳�
	m_hThread = reinterpret_cast<HANDLE>(
		_beginthreadex(
			nullptr,
			0,
			CReadChangesServer::ThreadStartProc,
			m_pServer,
			0,
			&m_dwThreadId
		));
}

void CReadDirectoryChanges::Terminate()
{
	// ֹͣ�߳�
	if (m_hThread)
	{
		// ���һ���û�ģʽ�µ�APC���̵߳�APC����
		QueueUserAPC(CReadChangesServer::TerminateProc, m_hThread, reinterpret_cast<ULONG_PTR>(m_pServer));
		WaitForSingleObjectEx(m_hThread, 10000, true);
		CloseHandle(m_hThread);
		// ������
		m_hThread = nullptr;
		m_dwThreadId = 0;
	}
}

void CReadDirectoryChanges::AddDirectory( LPCTSTR szDirectory, BOOL bWatchSubtree, DWORD dwNotifyFilter, DWORD dwBufferSize )
{
	// TODO ʵ���ϲ�û�д����̴߳������ɹ������
	// ����߳�Ϊ�գ��򴴽��̲߳�����ִ��
	if (!m_hThread)
		Init();
	if (m_hThread)
	{
		auto pRequest = new CReadChangesRequest(m_pServer, szDirectory, bWatchSubtree, dwNotifyFilter, dwBufferSize);
		QueueUserAPC(CReadChangesServer::AddDirectoryProc, m_hThread, reinterpret_cast<ULONG_PTR>(pRequest));
	}
}

void CReadDirectoryChanges::Push(DWORD dwAction, CStringW& wstrFilename)
{
	m_Notifications.push( TDirectoryChangeNotification(dwAction, wstrFilename) );
}

bool CReadDirectoryChanges::Pop(DWORD& dwAction, CStringW& wstrFilename)
{
	TDirectoryChangeNotification pair;
	if (!m_Notifications.pop(pair))
		return false;
	dwAction = pair.first;
	wstrFilename = pair.second;
	return true;
}

bool CReadDirectoryChanges::CheckOverflow()
{
	const bool b = m_Notifications.overflow();
	if (b)
		m_Notifications.clear();
	return b;
}
