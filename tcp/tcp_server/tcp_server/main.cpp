#include <cstdio>
#include <iostream>
#include "TcpServer.h"
#include <pthread.h>
using namespace std;
pthread_mutex_t mutex;
void* pthread_func(void* arg)
{
	TcpSocket *sockTcp = (TcpSocket *)arg;
	cout << "接受了一个客户端的连接请求..." << endl;
	int recvLen = -1;
	while (1)
	{
		pthread_mutex_lock(&mutex);
		char* recvBuf = NULL;
		sockTcp->recvMsg(&recvBuf, recvLen, 1000);//recvBuf为NULL时，会是程序异常退出，所以价格判断
		if (recvBuf == NULL)
		{

		}
		else
		{
			cout << "recvBuf: " << recvBuf << endl;//
		}
		// 发送数据
		char* p = "hello, client ...";
		sockTcp->sendMsg(p, strlen(p), 1000);
		sockTcp->freeMemory(&recvBuf);
		pthread_mutex_unlock(&mutex);
	}
	

}
int main()
{
	pthread_mutex_init(&mutex,NULL);
	TcpServer *server = new TcpServer;
	pthread_t pth[1024];
	// 设置监听
	server->setListen(9898);
	// 等待并接受连接请求
	cout << "开始accept..." << endl;
	
	for(int i=0;i<1024;i++)
	{
		TcpSocket* sockTcp = server->acceptConn(1000);
		pthread_create(&pth[i], NULL, pthread_func, sockTcp);
		// 通信
		pthread_detach(pth[i]);//线程分离
	}
	return 0;
}