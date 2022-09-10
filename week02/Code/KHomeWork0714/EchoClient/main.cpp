#include <iostream>
#include "KEchoClient.h"
#include "KGetMsgTask.h"
#include "KSendMsgTask.h"
#include  "KThread.h"

int main()
{
	KEchoClient* client = new KEchoClient("127.0.0.1", 6000);
	auto task_s = new KSendMsgTask(client);
	KThread t1(task_s);
	t1.run();

	auto task_g = new KGetMsgTask(client);
	KThread t2(task_g);
	t2.run();


	Sleep(1000000);

	WaitForSingleObject(t1.getHandle(), INFINITE);
	WaitForSingleObject(t2.getHandle(), INFINITE);
}
