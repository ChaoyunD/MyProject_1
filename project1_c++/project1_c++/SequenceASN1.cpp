#include "SequenceASN1.h"

SequenceASN1::SequenceASN1()
{

}

int SequenceASN1::writeHeadNode(int iValue)//此函数或下面函数只调用一次
{
	DER_ItAsn1_WriteInteger(iValue, &m_header);
	return 0;
}

int SequenceASN1::writeHeadNode(char * sValue, int len)
{
	DER_ITCAST_String_To_AnyBuf(&m_temp, (unsigned char *)sValue, len + 1);
	DER_ItAsn1_WritePrintableString(m_temp, &m_header);
	return 0;
}

int SequenceASN1::writeNextNode(int iValue)
{
	if (m_header->next == NULL)
	{
		DER_ItAsn1_WriteInteger(iValue, &m_header->next);
		m_next = m_header->next;
	}
	else
	{
		DER_ItAsn1_WriteInteger(iValue, &m_next->next);
		m_next = m_next->next;
	}
	return 0;
}

int SequenceASN1::writeNextNode(char * sValue, int len)
{
	if (m_header->next == NULL)
	{
		EncodeChar(sValue, len + 1, &m_header->next);
		m_next = m_header->next;
	}
	else
	{
		EncodeChar(sValue, len + 1, &m_next->next);
		m_next = m_next->next;
	}
	return 0;
}

int SequenceASN1::readHeadNode(char ** sValue)
{
	DER_ItAsn1_ReadPrintableString(m_header, &m_temp);
	*sValue = (char *)malloc(m_temp->dataLen);
	strcpy(*sValue, (char *)m_temp->pData);
	//printf("%s\n", sValue);
	m_next = m_header->next;
	freeSequence(m_temp);
	return 0;
}
int SequenceASN1::readHeadNode(char * sValue)
{
	DER_ItAsn1_ReadPrintableString(m_header, &m_temp);
	memcpy(sValue, m_temp->pData, m_temp->dataLen);
	m_next = m_header->next;
	freeSequence(m_temp);
	return 0;
}
int SequenceASN1::readHeadNode(int & iValue)//此函数或下面函数只调用一次
{
	DER_ItAsn1_ReadInteger(m_header, (ITCAST_UINT32 *)&iValue);
	m_next = m_header->next;
	return 0;
}

int SequenceASN1::readNextNode(int & iValue)
{
	DER_ItAsn1_ReadInteger(m_next, (ITCAST_UINT32 *)&iValue);
	m_next = m_next->next;
	return 0;
}

int SequenceASN1::readNextNode(long & iValue)
{
	DER_ItAsn1_ReadInteger(m_next, (ITCAST_UINT32 *)&iValue);
	m_next = m_next->next;
	return 0;
}

int SequenceASN1::readNextNode(char** sValue)//针对老师的内容修改了这里
{
	DER_ItAsn1_ReadPrintableString(m_next, &m_temp);
	*sValue = (char *)malloc(m_temp->dataLen);
	strcpy(*sValue, (char *)m_temp->pData);
	//printf("%s\n", sValue);
	m_next = m_next->next;
	freeSequence(m_temp);
	return 0;
}

int SequenceASN1::readNextNode(char * sValue)
{
	DER_ItAsn1_ReadPrintableString(m_next, &m_temp);
	memcpy(sValue, m_temp->pData, m_temp->dataLen);
	//printf("%s\n", sValue);
	m_next = m_next->next;
	freeSequence(m_temp);
	return 0;
	return 0;
}

int SequenceASN1::packSequence(char ** outData, int & outLen)
{
	DER_ItAsn1_WriteSequence(m_header, &m_temp);
	*outData = (char *)m_temp->pData;
	outLen = m_temp->dataLen;
	freeSequence(m_header);
	return 0;
}

int SequenceASN1::unpackSequence(char * inData, int inLen)
{
	m_header = NULL;
	m_next = NULL;
	m_temp = NULL;
	DER_ITCAST_String_To_AnyBuf(&m_temp, (unsigned char *)inData, inLen);
	DER_ItAsn1_ReadSequence(m_temp, &m_header);
	freeSequence(m_temp);
	return 0;
}

void SequenceASN1::freeSequence(ITCAST_ANYBUF * node)
{
	if (node == NULL)
	{
		DER_ITCAST_FreeQueue(m_header);
	}
	else
	{
		DER_ITCAST_FreeQueue(node);
	}
	}
	
