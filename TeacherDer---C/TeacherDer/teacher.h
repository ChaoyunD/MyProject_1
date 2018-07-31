#ifndef _TEACHER_H
#define _TEACHER_H
typedef struct _Teacher
{
	char name[64]; 
	int age;   
	char *p;
	long plen;
}Teacher;

// 编码结构体
// outData -> 传出参数, 编码之后的字符串
// outlen -> 编码之后的字符串长度
int encodeTeacher(Teacher* p, char** outData, int* outlen);

// 解码结构体
// inData -> 传入, 要解码的字符串
// inlen -> 传入, 要解码的字符串长度
// p -> 传出, 解码之后的结构体
int decodeTeacher(char* inData, int inLen, Teacher**p);

// 释放内存函数
// p指向decodeTeacher中创建的Teacher类型的内存
void freeTeacher(Teacher** p);

#endif	// _TEACHER_H
