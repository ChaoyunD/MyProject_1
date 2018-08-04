﻿#pragma once
#include "SequenceASN1.h"

class Codec : public SequenceASN1
{
public:
	Codec() {}
	virtual ~Codec() {}
	
	// 数据编码
	virtual int msgEncode(char** outData, int &len)=0;
	// 数据解码
	virtual void* msgDecode(char *inData, int inLen)=0;
};
