#include "BaseASN1.h"
#include "ItcastLog.h"
#include "SequenceASN1.h"
#include "RequestCodec.h"
#include "RespondCodec.h"
#include "RequestFactory.h"
#include "RespondFactory.h"
#include <iostream>
using std::cout;
using std::endl;
//int		rv;				// 返回值
//char	clientId[12];	// 客户端编号
//char	serverId[12];	// 服务器编号
//char	r2[64];			// 服务器端随机数
//int		seckeyid;		// 对称密钥编号    keysn
int main(void)
{
	//RespondMsg(char* clientID, char* serverID, char* r2, int rv, int seckeyID)
	RespondMsg msg;
	msg.seckeyid = 1;
	msg.rv = 2;
	strcpy(msg.clientId, "111");
	strcpy(msg.r2, "222");
	strcpy(msg.serverId, "333");

	char *outData;
	int len;
	
	CodecFactory *factory = new RespondFactory(&msg);
	Codec* codec=factory->createCodec();
	codec->msgEncode(&outData, len);
	RespondMsg*temp=(RespondMsg*)codec->msgDecode(outData, len);
	cout << "cmdType:\t" << temp->seckeyid<< endl;
	cout << "cliendId:\t" << temp->rv << endl;
	cout << "authCode:\t" << temp->clientId << endl;
	cout << "serverId:\t" << temp->serverId << endl;
	cout << "r1:\t\t" << temp->r2 << endl;

	system("pause");
	return 0;
}