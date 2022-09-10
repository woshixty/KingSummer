class CReadDirectoryChanges;

namespace ReadDirectoryChangesPrivate
{
	class CReadChangesServer;

	// All functions in CReadChangesRequest run in the context of the worker thread.
	// One instance of this object is created for each call to AddDirectory().
	class CReadChangesRequest
	{
	public:
		CReadChangesRequest(CReadChangesServer* pServer, LPCTSTR sz, BOOL b, DWORD dw, DWORD size);
		~CReadChangesRequest();

		bool OpenDirectory();
		void BeginRead();

		// The dwSize is the actual number of bytes sent to the APC.
		// 拷贝消息空间
		void BackupBuffer(DWORD dwSize);

		// 处理通知
		void ProcessNotification();

		// 停止监听
		void RequestTermination()
		{
			CancelIo(m_hDirectory);
			CloseHandle(m_hDirectory);
			m_hDirectory = nullptr;
		}

		CReadChangesServer* m_pServer;

	protected:
		// 完成请求的回调函数
		static VOID CALLBACK NotificationCompletion(
				DWORD dwErrorCode,							// completion code
				DWORD dwNumberOfBytesTransfered,			// number of bytes transferred
				LPOVERLAPPED lpOverlapped);					// I/O information buffer

		// Parameters from the caller for ReadDirectoryChangesW().
		DWORD		m_dwFilterFlags;
		BOOL		m_bIncludeChildren;
		CStringW	m_wstrDirectory;

		// Result of calling CreateFile().
		HANDLE		m_hDirectory;

		// Required parameter for ReadDirectoryChangesW().
		OVERLAPPED	m_Overlapped{};

		// Data buffer for the request.
		// Since the memory is allocated by malloc, it will always
		// be aligned as required by ReadDirectoryChangesW().
		vector<byte> m_Buffer;

		// Double buffer strategy so that we can issue a new read
		// request before we process the current buffer.
		vector<byte> m_BackupBuffer;
	};


	// All functions in CReadChangesServer run in the context of the worker thread.
	// One instance of this object is allocated for each instance of CReadDirectoryChanges.
	// This class is responsible for thread startup, orderly thread shutdown, and shimming
	// the various C++ member functions with C-style Win32 functions.
	class CReadChangesServer
	{
	public:
		CReadChangesServer(CReadDirectoryChanges* pParent)
		{
			m_bTerminate = false;
			m_nOutstandingRequests = 0;
			m_pCReadDirectoryChanges = pParent;
		}

		static unsigned int WINAPI ThreadStartProc(LPVOID arg)
		{
			const auto pServer = static_cast<CReadChangesServer*>(arg);
			pServer->Run();
			return 0;
		}

		// Called by QueueUserAPC to start orderly shutdown.
		// 停止监听
		static void CALLBACK TerminateProc(__in  ULONG_PTR arg)
		{
			const auto pServer = reinterpret_cast<CReadChangesServer*>(arg);
			pServer->RequestTermination();
		}

		// Called by QueueUserAPC to add another directory.
		// 添加要监听的目录
		static void CALLBACK AddDirectoryProc(__in  ULONG_PTR arg)
		{
			const auto pRequest = reinterpret_cast<CReadChangesRequest*>(arg);
			pRequest->m_pServer->AddDirectory(pRequest);
		}

		CReadDirectoryChanges* m_pCReadDirectoryChanges;
		volatile DWORD m_nOutstandingRequests;

	protected:
		void Run() const
		{
			while (m_nOutstandingRequests || !m_bTerminate)
				SleepEx(INFINITE, true);
		}

		void AddDirectory(CReadChangesRequest* pRequest)
		{
			if (pRequest->OpenDirectory())
			{
				::InterlockedIncrement(&pRequest->m_pServer->m_nOutstandingRequests);
				m_pRequests.push_back(pRequest);
				pRequest->BeginRead();
			}
			else
				delete pRequest;
		}

		void RequestTermination()
		{
			m_bTerminate = true;
			for (const auto& m_pBlock : m_pRequests)
				// Each Request object will delete itself.
				m_pBlock->RequestTermination();
			m_pRequests.clear();
		}

		// 阻塞队列
		vector<CReadChangesRequest*> m_pRequests;
		bool m_bTerminate;
	};

}
