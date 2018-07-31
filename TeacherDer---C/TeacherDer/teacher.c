#include "teacher.h"
#include "itcast_asn1_der.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	typedef struct _Teacher
	{
		char name[64];
		int age;
		char *p;
		long plen;
	}Teacher;
*/
int encodeTeacher(Teacher * p, char ** outData, int * outlen)
{
	ITCAST_ANYBUF* temp = NULL;
	ITCAST_ANYBUF* head = NULL;
	ITCAST_ANYBUF* next = NULL;
	// 1. 将name编码 -> char*
	// char* -> ITCAST_ANYBUF
	DER_ITCAST_String_To_AnyBuf(&temp, p->name, strlen(p->name)+1);
	DER_ItAsn1_WritePrintableString(temp, &head);
	DER_ITCAST_FreeQueue(temp);
	// 2. age编码
	DER_ItAsn1_WriteInteger(p->age, &head->next);
	// 3. p编码
	next = head->next;
	EncodeChar(p->p, strlen(p->p) + 1, &next->next);
	// 4. plen编码
	next = next->next;
	DER_ItAsn1_WriteInteger(p->plen, &next->next);
	// 5. 整个链表编码
	DER_ItAsn1_WriteSequence(head, &temp);
	// 6. 传出参数赋值
	*outData = temp->pData;
	*outlen = temp->dataLen;
	// 7. 释放内存 - 释放链表
	DER_ITCAST_FreeQueue(head);

	return 0;
}

/*
	typedef struct _Teacher
	{
		char name[64];
		int age;
		char *p;
		long plen;
	}Teacher;
*/
int decodeTeacher(char * inData, int inLen, Teacher ** p)
{
	ITCAST_ANYBUF* temp = NULL;
	ITCAST_ANYBUF* head = NULL;
	ITCAST_ANYBUF* next = NULL;

	Teacher* pt = (Teacher*)malloc(sizeof(Teacher));

	// 1. char* -> ITCAST_ANYBUF
	DER_ITCAST_String_To_AnyBuf(&temp, inData, inLen);
	// 2. ITCAST_ANYBUF -> 还原成一链表, 得到了一个操作的头结点
	DER_ItAsn1_ReadSequence(temp, &head);
	DER_ITCAST_FreeQueue(temp);
	// 3. 解码name
	DER_ItAsn1_ReadPrintableString(head, &temp);
	memcpy(pt->name, temp->pData, temp->dataLen);
	DER_ITCAST_FreeQueue(temp);

	// 4. 解码age
	next = head->next;
	DER_ItAsn1_ReadInteger(next, &pt->age);

	// 5. 解码p
	next = next->next;
	DER_ItAsn1_ReadPrintableString(next, &temp);
	pt->p = (char*)malloc(temp->dataLen);
	strcpy(pt->p, temp->pData);
	DER_ITCAST_FreeQueue(temp);

	// 6. 解码plen
	next = next->next;
	DER_ItAsn1_ReadInteger(next, &pt->plen);

	// 7. 传出参数赋值
	*p = pt;

	// 8. 释放内存
	DER_ITCAST_FreeQueue(head);

	return 0;
}

void freeTeacher(Teacher ** p)
{
	// 1. free (*p)
	// 2. (*p)->p 
	if ((*p))
	{
		if ((*p)->p)
		{
			free((*p)->p);
			(*p)->p = NULL;
		}
		free((*p));
		(*p) = NULL;
	}
}
