#include <iostream>
#include <thread>
#include "ksocketserver.h"
#include "kftpclient.h"

int main()
{
	string method = "";
	string ipaddr = "127.0.0.1";
	const auto s_c = new KFtpClient(ipaddr);
    s_c->runLoop();
}