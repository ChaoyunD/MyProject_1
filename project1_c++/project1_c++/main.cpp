#include "BaseASN1.h"
#include "ItcastLog.h"
#include "SequenceASN1.h"
typedef struct _Teacher
{
	char name[64];
	int age;
	char *p;
	int plen;
}Teacher;
SequenceASN1 seq;
int encodeTeacher(Teacher * p, char ** outData, int & outlen)//编码
{
	
	seq.writeNextNode(p->age);
	seq.writeNextNode(p->p, strlen(p->p));
	seq.writeNextNode(p->plen);
	seq.packSequence(outData, outlen);// 数据关联 - 整个结构体数据块,编码整个结构体
	return 0;
}
int decodeTeacher(char * inData, int inLen, Teacher ** p)//解码
{
	seq.unpackSequence(inData, inLen);
	Teacher* pt = (Teacher*)malloc(sizeof(Teacher));
	seq.readHeadNode(pt->name);
	seq.readNextNode(pt->age);
	seq.readNextNode(&pt->p);
	seq.readNextNode(pt->plen);
	*p = pt;
	return 0;
}
int main(void)
{
	Teacher tea;
	strcpy(tea.name, "路飞");
	tea.age = 20;
	tea.p = (char*)malloc(100);
	strcpy(tea.p, "我是要成为海贼王的男人");
	tea.plen = strlen(tea.p);
	//编码
	char *outData=NULL;
	int outlen;
	encodeTeacher(&tea, &outData, outlen);
	//解码
	Teacher* pt=NULL;
	decodeTeacher(outData, outlen, &pt);
	printf("name:	%s\n", pt->name);
	printf("age:	%d\n", pt->age);
	printf("p:	%s\n", pt->p);
	printf("plen:	%d\n", pt->plen);
	system("pause");
	return 0;
}