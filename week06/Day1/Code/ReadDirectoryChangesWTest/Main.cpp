#include <iostream>
#include <Windows.h>

int main()
{
	const DWORD dwNotificationFlags =
		FILE_NOTIFY_CHANGE_LAST_WRITE | 
		FILE_NOTIFY_CHANGE_CREATION | 
		FILE_NOTIFY_CHANGE_FILE_NAME;
}