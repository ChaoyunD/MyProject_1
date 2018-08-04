#include "RequestCodec.h"

RequestCodec::RequestCodec()
{
}

RequestCodec::RequestCodec(RequestMsg * msg)
{
	memcpy(&m_msg, msg, sizeof(RequestMsg));
}

RequestCodec::~RequestCodec()
{
}
int RequestCodec::msgEncode(char ** outData, int & len)//编码
{
	writeHeadNode(m_msg.cmdType);
	writeNextNode(m_msg.clientId, strlen(m_msg.clientId));
	writeNextNode(m_msg.authCode, strlen(m_msg.authCode));
	writeNextNode(m_msg.serverId, strlen(m_msg.serverId));
	writeNextNode(m_msg.r1, strlen(m_msg.r1));
	packSequence(outData, len);
	return 0;
}
void * RequestCodec::msgDecode(char * inData, int inLen)
{
	unpackSequence(inData, inLen);
	RequestMsg *msg = (RequestMsg *)malloc(sizeof(RequestMsg));
	readHeadNode(msg->cmdType);
	readNextNode(msg->clientId);
	readNextNode(msg->authCode);
	readNextNode(msg->serverId);
	readNextNode(msg->r1);
	return msg;
}
