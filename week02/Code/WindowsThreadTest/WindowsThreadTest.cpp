#include <iostream>
#include <Windows.h>

UINT MyThreadProc(LPVOID pParam)
{
    std::cout << "Hello World! in thread " << GetCurrentThreadId() << std::endl;
    return 0;   // thread completed successfully
}

int main()
{
    int t = 0;
    HANDLE htd0, htd1, htd2;
    DWORD thrdID0, thrdID2;
    htd0 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyThreadProc, (void*)&t, 0, &thrdID0);
    std::cout << "Hello World! in main thread" << std::endl;
    Sleep(1000);
}
