#include <cstdio>
#include <iostream>
#include "TcpSocket.h"
using namespace std;
int main()
{
    //printf("hello from tcp_client!\n");
	TcpSocket client;
	client.connectToHost("127.0.0.1", 9898);
	cout << "连接服务器成功...." << endl;
	char *outData = NULL;
	int len = -1;
	while (1)
	{
		
		cout << "发送数据hello world..." << endl;
		client.sendMsg("hello world...", strlen("hello world..."));
		cout << "接收数据:";
		client.recvMsg(&outData, len);
		cout << outData << endl;
		sleep(2);
		client.freeMemory(&outData);
	}
	client.disConnect();

    return 0;
}