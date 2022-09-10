#include "KEchoServer.h"
#include "KAcceptTask.h"
#include "KSendMsgTask.h"
#include "KThread.h"

int main()
{
	//KSocketServer *socket = new KSocketServer();
	//socket->initSocket();
	//socket->bindPort(6000);
	//socket->listenSocket();
	//// 主循环
	//for (;;)
	//{
	//	KSocket* csocket = socket->acceptSocket();
	//	if (csocket != nullptr)
	//	{
	//		// 每连接一个客户端,创建一个子线程
	//		HANDLE hThread = CreateThread(NULL, 0, doClientThread, (LPVOID)csocket, 0, NULL);
	//		HANDLE h2Thread = CreateThread(NULL, 0, sendClientThread, (LPVOID)csocket, 0, NULL);
	//		if (hThread == NULL)
	//			break;
	//		if (h2Thread == NULL)
	//			break;
	//	}
	//}
	KEchoServer* server = new KEchoServer(0);

	auto task_a = new KAcceptThread(server);
	KThread t1(task_a);
	t1.run();

	auto task_s = new KSendMsgTask(server);
	KThread t2(task_s);
	t2.run();

	WaitForSingleObject(t1.getHandle(), INFINITE);
	WaitForSingleObject(t2.getHandle(), INFINITE);
}


