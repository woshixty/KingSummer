#include "stdafx.h"

#include <string>
#include <comdef.h>
#include "ReadDirectoryChanges.h"


LPCWSTR ExplainAction( DWORD dwAction );
bool TryGetKeyboardInput( HANDLE hStdIn, bool &bTerminate, char* buf );


//
// When the application starts, it immediately starts monitoring your home
// directory, including children, as well as C:\, not including children.
// The application exits when you hit Esc.
// You can add a directory to the monitoring list by typing the directory
// name and hitting Enter. Notifications will pause while you type.
//

//int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
int _tmain()
{
	constexpr DWORD dwNotificationFlags =
		FILE_NOTIFY_CHANGE_LAST_WRITE
		| FILE_NOTIFY_CHANGE_CREATION
		| FILE_NOTIFY_CHANGE_FILE_NAME;

	// Create the monitor and add two directories.
	CReadDirectoryChanges changesService;
	// changes.AddDirectory(_tgetenv(_T("USERPROFILE")), true, dwNotificationFlags);
	changesService.AddDirectory(_T("D:\\0"), true, dwNotificationFlags);
	changesService.AddDirectory(_T("D:\\0-ftp-client"), false, dwNotificationFlags);

	const HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	const HANDLE handles[] = { hStdIn, changesService.GetWaitHandle() };

	bool bTerminate = false;

	while (!bTerminate)
	{
		char buf[MAX_PATH];
		const DWORD rc = WaitForMultipleObjectsEx(_countof(handles), handles, false, INFINITE, true);
		switch (rc)
		{
		case WAIT_OBJECT_0 + 0:
			// hStdIn was signaled. This can happen due to mouse input, focus change,
			// Shift keys, and more.  Delegate to TryGetKeyboardInput().
			// TryGetKeyboardInput sets bTerminate to true if the user hits Esc.
			if (TryGetKeyboardInput(hStdIn, bTerminate, buf))
				changesService.AddDirectory(CStringW(buf), false, dwNotificationFlags);
			break;
		case WAIT_OBJECT_0 + 1:
			// We've received a notification in the queue.
			{
				if (changesService.CheckOverflow())
					wprintf(L"Queue overflowed.\n");
				else
				{
					CStringW wstrFilename;
					DWORD dwAction;
					changesService.Pop(dwAction, wstrFilename);
					char* stdstr = CW2A(wstrFilename); // ExplainAction(dwAction),
					 
					_bstr_t b(wstrFilename);
					const char* c = b;
					printf("Output: %s\n", c); 
				}
			}
			break;
		case WAIT_IO_COMPLETION:
			// Nothing to do.
			break;
		default: ;
		}
	}

	// Just for sample purposes. The destructor will
	// call Terminate() automatically.
	changesService.Terminate();

	return EXIT_SUCCESS;
}

LPCWSTR ExplainAction( DWORD dwAction )
{
	switch (dwAction)
	{
	case FILE_ACTION_ADDED            :
		return L"Added";
	case FILE_ACTION_REMOVED          :
		return L"Deleted";
	case FILE_ACTION_MODIFIED         :
		return L"Modified";
	case FILE_ACTION_RENAMED_OLD_NAME :
		return L"Renamed From";
	case FILE_ACTION_RENAMED_NEW_NAME :
		return L"Renamed To";
	default:
		return L"BAD DATA";
	}
}

bool TryGetKeyboardInput( HANDLE hStdIn, bool &bTerminate, char* buf )
{
	DWORD dwNumberOfEventsRead=0;
	INPUT_RECORD rec = {0};

	if (!::PeekConsoleInput(hStdIn, &rec, 1, &dwNumberOfEventsRead))
		return false;

	if (rec.EventType == KEY_EVENT)
	{
		if (rec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
			bTerminate = true;
		else if (rec.Event.KeyEvent.wVirtualKeyCode > VK_HELP)
		{
			if (!gets_s(buf, 1024))	// End of file, usually Ctrl-Z
				bTerminate = true;
			else
				return true;
		}
	}

	::FlushConsoleInputBuffer(hStdIn);

	return false;
}
