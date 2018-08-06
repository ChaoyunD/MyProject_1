#pragma once
#include "itcastlog.h"
#include <unistd.h>
#include <fcntl.h>
#include <cstdlib>
#include <errno.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


/* 用于通信的套接字类 */
// 超时的时间
// 错误码定义  
#define Sck_Ok             	0
#define Sck_BaseErr   		3000

#define Sck_ErrParam                	(Sck_BaseErr+1)
#define Sck_ErrTimeOut                	(Sck_BaseErr+2)
#define Sck_ErrPeerClosed               (Sck_BaseErr+3)
#define Sck_ErrMalloc			   		(Sck_BaseErr+4)

#define Sck_Err_Pool_CreateConn				(Sck_BaseErr+20)	// 创建连接池 （没有达到最大连接数）
#define Sck_Err_Pool_terminated				(Sck_BaseErr+21)	// 已终止
#define Sck_Err_Pool_GetConn_ValidIsZero	(Sck_BaseErr+22)	// 有效连接数是零
#define Sck_Err_Pool_HaveExist				(Sck_BaseErr+22)	// 连接已经在池中
#define Sck_Err_Pool_ValidBounds			(Sck_BaseErr+22)	// 有效连接数目超过了最大连接数
static const int TIMEOUT = 1000;
class TcpSocket
{
public:
	enum ErrorType {ParamError = 3001, TimeoutError, PeerCloseError, MallocError};
	TcpSocket();
	// 使用一个可以用于通信的套接字实例化套接字对象
	TcpSocket(int connfd);
	~TcpSocket();

	// 连接服务器
	int connectToHost(char* ip, unsigned short port, int timeout = TIMEOUT);
	// 发送数据
	int sendMsg(char* sendData, int dataLen, int timeout = TIMEOUT);
	// 接收数据
	int recvMsg(char** recvData, int &recvLen, int timeout = TIMEOUT);
	// 断开连接
	void disConnect();
	// 释放内存
	void freeMemory(char** buf);

private:
	// 设置I/O为非阻塞模式
	int blockIO(int fd);
	// 设置I/O为阻塞模式
	int noBlockIO(int fd);
	// 读超时检测函数，不含读操作
	int readTimeout(unsigned int wait_seconds);
	// 写超时检测函数, 不包含写操作
	int writeTimeout(unsigned int wait_seconds);
	// 带连接超时的connect函数
	int connectTimeout(struct sockaddr_in *addr, unsigned int wait_seconds);
	// 每次从缓冲区中读取n个字符
	int readn(void *buf, int count);
	// 每次往缓冲区写入n个字符
	int writen(const void *buf, int count);

private:
	int m_socket;		// 用于通信的套接字
	ItcastLog m_log;	// log对象
};

