#include "RespondCodec.h"

RespondCodec::RespondCodec()
{
}

RespondCodec::RespondCodec(RespondMsg * msg)
{
	memcpy(&m_msg, msg, sizeof(RespondMsg));
}

RespondCodec::~RespondCodec()
{
}

int RespondCodec::msgEncode(char ** outData, int & len)
{
	writeHeadNode(m_msg.rv);
	writeNextNode(m_msg.clientId, strlen(m_msg.clientId));
	writeNextNode(m_msg.serverId, strlen(m_msg.serverId));
	writeNextNode(m_msg.r2, strlen(m_msg.r2));
	writeNextNode(m_msg.seckeyid);
	packSequence(outData, len);
	return 0;
}

void * RespondCodec::msgDecode(char * inData, int inLen)
{
	unpackSequence(inData, inLen);
	RespondMsg *msg = (RespondMsg *)malloc(sizeof(RespondMsg));
	readHeadNode(msg->rv);
	readNextNode(msg->clientId);
	readNextNode(msg->serverId);
	readNextNode(msg->r2);
	readNextNode(msg->seckeyid);
	return msg;
}
