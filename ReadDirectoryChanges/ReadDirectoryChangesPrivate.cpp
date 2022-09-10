#include "stdafx.h"
#include "ReadDirectoryChanges.h"
#include "ReadDirectoryChangesPrivate.h"


// The namespace is a convenience to emphasize that these are internals
// interfaces.  The namespace can be safely removed if you need to.
namespace ReadDirectoryChangesPrivate
{
	// CReadChangesRequest

	CReadChangesRequest::CReadChangesRequest(CReadChangesServer* pServer, LPCTSTR sz, BOOL b, DWORD dw, DWORD size)
	{
		m_pServer				= pServer;
		m_dwFilterFlags			= dw;
		m_bIncludeChildren		= b;
		m_wstrDirectory			= sz;
		m_hDirectory			= nullptr;

		::ZeroMemory(&m_Overlapped, sizeof(OVERLAPPED));

		// The hEvent member is not used when there is a completion
		// function, so it's ok to use it to point to the object.
		m_Overlapped.hEvent = this;

		m_Buffer.resize(size);
		m_BackupBuffer.resize(size);
	}


	CReadChangesRequest::~CReadChangesRequest()
	{
		// RequestTermination() must have been called successfully.
		_ASSERTE(m_hDirectory == nullptr);
	}

	bool CReadChangesRequest::OpenDirectory()
	{
		// Allow this routine to be called redundantly.
		if (m_hDirectory)
			return true;

		m_hDirectory = CreateFileW(
			m_wstrDirectory,			// pointer to the file name
			FILE_LIST_DIRECTORY,	// access (read/write) mode
			FILE_SHARE_READ			// share mode
			 | FILE_SHARE_WRITE
			 | FILE_SHARE_DELETE,
			nullptr,			// security descriptor
			OPEN_EXISTING,		// how to create
			FILE_FLAG_BACKUP_SEMANTICS		// file attributes
			 | FILE_FLAG_OVERLAPPED,
			nullptr);					//   file with attributes to copy

		if (m_hDirectory == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		return true;
	}

	void CReadChangesRequest::BeginRead()
	{
		DWORD dwBytes = 0;

		// This call needs to be reissued after every APC.
		BOOL success = ReadDirectoryChangesW(
			m_hDirectory,						// handle to directory
			&m_Buffer[0],                // read results buffer
			m_Buffer.size(),         // length of buffer
			m_bIncludeChildren,      // monitoring option
			m_dwFilterFlags,        // filter conditions
			&dwBytes,              // bytes returned
			&m_Overlapped,            // overlapped buffer
			&NotificationCompletion);		// completion routine
	}

	void CReadChangesRequest::BackupBuffer(DWORD dwSize)
	{
		// We could just swap back and forth between the two
		// buffers, but this code is easier to understand and debug.
		memcpy(&m_BackupBuffer[0], &m_Buffer[0], dwSize);
	}

	//static
	VOID CALLBACK CReadChangesRequest::NotificationCompletion(
		DWORD dwErrorCode,										// completion code
		const DWORD dwNumberOfBytesTransfered,					// number of bytes transferred
		LPOVERLAPPED lpOverlapped)								// I/O information buffer
	{
		const auto pBlock = static_cast<CReadChangesRequest*>(lpOverlapped->hEvent);
		if (dwErrorCode == ERROR_OPERATION_ABORTED)
		{
			::InterlockedDecrement(&pBlock->m_pServer->m_nOutstandingRequests);
			delete pBlock;
			return;
		}
		// Can't use sizeof(FILE_NOTIFY_INFORMATION) because
		// the structure is padded to 16 bytes.
		_ASSERTE(dwNumberOfBytesTransfered >= offsetof(FILE_NOTIFY_INFORMATION, FileName) + sizeof(WCHAR));
		// This might mean overflow? Not sure.
		if(!dwNumberOfBytesTransfered)
			return;
		// ¸´ÖÆ»º³åÇø
		pBlock->BackupBuffer(dwNumberOfBytesTransfered);
		// Get the new read issued as fast as possible. The documentation
		// says that the original OVERLAPPED structure will not be used
		// again once the completion routine is called.
		pBlock->BeginRead();
		pBlock->ProcessNotification();
	}

	void CReadChangesRequest::ProcessNotification()
	{
		BYTE* pData = m_BackupBuffer.data();
		for (;;)
		{
			auto& fni = reinterpret_cast<FILE_NOTIFY_INFORMATION&>(*pData);

			CStringW wstrFilename(fni.FileName, fni.FileNameLength/sizeof(wchar_t));
			// Handle a trailing backslash, such as for a root directory.
			if (m_wstrDirectory.Right(1) != L"\\")
				wstrFilename = m_wstrDirectory + L"\\" + wstrFilename;
			else
				wstrFilename = m_wstrDirectory + wstrFilename;

			// If it could be a short filename, expand it.
			const LPCWSTR wszFilename = PathFindFileNameW(wstrFilename);
			const int len = lstrlenW(wszFilename);
			// The maximum length of an 8.3 filename is twelve, including the dot.
			if (len <= 12 && wcschr(wszFilename, L'~'))
			{
				// Convert to the long filename form. Unfortunately, this
				// does not work for deletions, so it's an imperfect fix.
				wchar_t wbuf[MAX_PATH];
				if (GetLongPathNameW(wstrFilename, wbuf, _countof(wbuf)) > 0)
					wstrFilename = wbuf;
			}

			m_pServer->m_pCReadDirectoryChanges->Push(fni.Action, wstrFilename);

			if (!fni.NextEntryOffset)
				break;
			pData += fni.NextEntryOffset;
		}
	}

}
