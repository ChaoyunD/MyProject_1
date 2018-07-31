﻿#ifndef _ITCAST_MESSAGE_DER_
#define _ITCAST_MESSAGE_DER_

#ifdef __cplusplus
extern "C" {
#endif

#define ITCASTDER_NoErr 0 

typedef int                 ITCAST_INT;
typedef unsigned char       ITCAST_UINT8;
typedef unsigned short      ITCAST_UINT16;
typedef unsigned long       ITCAST_UINT32;
typedef signed long         ITCAST_SINT32;

#define  TRUE  1
#define  FALSE 0


#define    ITDER_NoErr                    0	
#define    ITDER_MemoryErr                200
#define	   ITDER_LengthErr                201
#define	   ITDER_LengthNotEqualErr        202
#define	   ITDER_DataRangeErr             203
#define	   ITDER_InvalidTagErr            204



/* The ID's for universal tag numbers 0-31.  Tag number 0 is reserved for
	encoding the end-of-contents value when an indefinite-length encoding
	is used */
enum {//ASN.1自定义内建数据类型
	ITCAST_DER_ID_RESERVED,//保留
	ITCAST_DER_ID_BOOLEAN,//         1
	ITCAST_DER_ID_INTEGER, //全部整数（包括正数和负数）   2
	ITCAST_DER_ID_BITSTRING,//比特串  3
	ITCAST_DER_ID_OCTETSTRING,//字节串  4
	ITCAST_DER_ID_NULL,//只包含一个值NULL，用于传送一个报告或者作为CHOICE类型中某些值       5
	ITCAST_DER_ID_OBJECT_IDENTIFIER,//一个实体的标识符，它在一个全世界范围树状结构中注册   6
	ITCAST_DER_ID_OBJECT_DESCRIPTOR,//
	ITCAST_DER_ID_EXTERNAL,//表示层上下文交换类型
	ITCAST_DER_ID_REAL,//实数  9
	ITCAST_DER_ID_ENUMERATED,//标识符的枚举（实例状态机的状态）  10
	ITCAST_DER_ID_EMBEDDED_PDV,//表示层上下文交换类型
	ITCAST_DER_ID_STRING_UTF8,//各种字符串
	ITCAST_DER_ID_13,
	ITCAST_DER_ID_14,
	ITCAST_DER_ID_15,
	ITCAST_DER_ID_SEQUENCE,//由不同类型的值组成一个有序的结构(相当于C中的结构体)
	ITCAST_DER_ID_SET,//由不同类型的值组成一个无序的结构
	ITCAST_DER_ID_STRING_NUMERIC,//各种字符串
	ITCAST_DER_ID_STRING_PRINTABLE,//各种字符串
	ITCAST_DER_ID_STRING_T61,//各种字符串
	ITCAST_DER_ID_STRING_VIDEOTEX,//各种字符串
	ITCAST_DER_ID_STRING_IA5,//各种字符串
	ITCAST_DER_ID_TIME_UTC,//日期
	ITCAST_DER_ID_TIME_GENERALIZED,//日期
	ITCAST_DER_ID_STRING_GRAPHIC,//各种字符串
	ITCAST_DER_ID_STRING_ISO646,//各种字符串
	ITCAST_DER_ID_STRING_GENERAL,//各种字符串
	ITCAST_DER_ID_STRING_UNIVERSAL,//各种字符串
	ITCAST_DER_ID_29,
	ITCAST_DER_ID_STRING_BMP//各种字符串
};


/* Whether the encoding is constructed or primitive */

#define ITCAST_DER_CONSTRUCTED			    0x20
#define ITCAST_DER_PRIMITIVE			    0x00

/* The encodings for the universal(通用) types */
#define ITCAST_DER_UNIVERSAL			    0x00
#define ITCAST_DER_APPLICATION		   	    0x40
#define ITCAST_DER_CONTEXT_SPECIFIC	        0x80
#define ITCAST_DER_PRIVATE				    0xC0
							  /*等价于(                  0x00|                  0x00|                     xxx)*/
						      /*第三位是多少，或出来的结果就是多少*/
#define ITCAST_DER_RESERVED		      ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_RESERVED )
#define ITCAST_DER_BOOLEAN			  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_BOOLEAN )
#define ITCAST_DER_INTEGER			  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_INTEGER )
#define ITCAST_DER_BITSTRING		  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_BITSTRING )
#define ITCAST_DER_OCTETSTRING		  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_OCTETSTRING )
#define ITCAST_DER_NULL			      ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_NULL )
#define ITCAST_DER_OBJECT_IDENTIFIER  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_OBJECT_IDENTIFIER )
#define ITCAST_DER_OBJECT_DESCRIPTOR  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_OBJECT_DESCRIPTOR )
#define ITCAST_DER_EXTERNAL		      ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_EXTERNAL )
#define ITCAST_DER_REAL			      ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_REAL )
#define ITCAST_DER_ENUMERATED		  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_ENUMERATED )
#define ITCAST_DER_EMBEDDED_PDV	      ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_EMBEDDED_PDV )
#define ITCAST_DER_STRING_UTF8		  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_STRING_UTF8 )
#define ITCAST_DER_13				  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_13 )
#define ITCAST_DER_14				  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_14 )
#define ITCAST_DER_15				  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_15 )
#define ITCAST_DER_SEQUENCE		      ( ITCAST_DER_UNIVERSAL | ITCAST_DER_CONSTRUCTED | ITCAST_DER_ID_SEQUENCE )
#define ITCAST_DER_SET				  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_CONSTRUCTED | ITCAST_DER_ID_SET )
#define ITCAST_DER_STRING_NUMERIC	  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_STRING_NUMERIC )
#define ITCAST_DER_STRING_PRINTABLE   ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_STRING_PRINTABLE )
#define ITCAST_DER_STRING_T61		  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_STRING_T61 )
#define ITCAST_DER_STRING_VIDEOTEX	  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_STRING_VIDEOTEX )
#define ITCAST_DER_STRING_IA5		  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_STRING_IA5 )
#define ITCAST_DER_TIME_UTC		      ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_TIME_UTC )
#define ITCAST_DER_TIME_GENERALIZED   ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_TIME_GENERALIZED )
#define ITCAST_DER_STRING_GRAPHIC	  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_STRING_GRAPHIC )
#define ITCAST_DER_STRING_ISO646	  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_STRING_ISO646 )
#define ITCAST_DER_STRING_GENERAL	  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_STRING_GENERAL )
#define ITCAST_DER_STRING_UNIVERSAL   ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_STRING_UNIVERSAL )
#define ITCAST_DER_29				  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE |  ITCAST_DER_ID_29 )
															/*ITCAST_DER_ID_BER29转成ITCAST_DER_ID_29*/
#define ITCAST_DER_STRING_BMP		  ( ITCAST_DER_UNIVERSAL | ITCAST_DER_PRIMITIVE | ITCAST_DER_ID_STRING_BMP )


/* Masks to extract information from a tag number 掩码(下面)-->(作用):从标签号中提取信息*/

#define ITCAST_DER_CLASS_MASK			0xC0
#define ITCAST_DER_CONSTRUCTED_MASK	    0x20
#define ITCAST_DER_SHORT_ID_MASK		0x1F
#define ITCAST_DER_FIRST_NOT_ID_MASK    0x7F     //xia
#define ITCAST_DER_FIRST_YES_ID_MASK    0x80     //xia
#define ITCAST_DER_ALL_YES_ID_MASK      0xFF     //xia
/* The maximum size for the short tag number encoding, and the magic value
   which indicates that a long encoding of the number is being used */

#define ITASN1_MAX_SHORT_BER_ID	    30
//#define ITASN1_LONG_BER_ID		    0x1F//没用到


#define		DER_ITCAST_Free(memblock) {if(memblock) {free(memblock); memblock=NULL;}}  

#define DER_ITASN1_LOW_IDENTIFIER(cTag)      (cTag & ITCAST_DER_SHORT_ID_MASK)

#define  DER_CREATE_LOW_ITCAST_ANYBUF(point) \
	     point = (ITCAST_ANYBUF *)malloc(sizeof(ITCAST_ANYBUF)); \
         if (point==NULL) return 7002; \
		 memset(point,0,sizeof(ITCAST_ANYBUF)); \
         point->dataLen = 0; \
         point->dataType = 0; \
	     point->memoryType = DER_ITASN1_MEMORY_MALLOC; \
	     point->pData = NULL; \
	     point->unusedBits = 0; \
	     point->next = NULL; \
         point->prev = NULL

#define DER_ITASN1_LOW_CREATEUINT8(point,size) \
	    point = malloc(size); \
		if (point==NULL) return 7002; \
        //memset(point,0,size)

#define DER_ITASN1_LOW_CREATEUINT32(point) \
	    point = malloc(sizeof(ITCAST_UINT32)); \
		if (point==NULL) return 7002; \
        memset(point,0,sizeof(ITCAST_UINT32))

#define DER_ITASN1_LOW_CHECKERR(iResult,iErrNumber) \
	    if (iResult == iErrNumber) \
            return iErrNumber
#define DER_DACERT_LOW_FREE_ANYBUF(point) \
	    DER_ITCAST_Free(point->pData); \
        DER_ITCAST_Free(point)
//#define DER_ITASN1_MEMORY_STATIC     1//没用到
#define DER_ITASN1_MEMORY_MALLOC     2

typedef struct ITCAST_ANYBUF_ {

	unsigned char 	  *pData;
	ITCAST_UINT32     dataLen;

	ITCAST_UINT32     unusedBits;	/* for bit string */
	ITCAST_UINT32     memoryType;
	ITCAST_UINT32     dataType;
	struct ITCAST_ANYBUF_ *next;    /* for sequence and set */
	struct ITCAST_ANYBUF_ *prev;

}ITCAST_ANYBUF;

typedef ITCAST_UINT8     ITASN1_BOOLEAN;
typedef ITCAST_ANYBUF    ITASN1_INTEGER;
typedef ITCAST_ANYBUF    ITASN1_OCTETSTRING;
typedef ITCAST_ANYBUF    ITASN1_BITSTRING;
typedef ITCAST_ANYBUF    ITASN1_PRINTABLESTRING;
/*begin of bmpstring*/
typedef ITCAST_ANYBUF	 ITASN1_BMPSTRING;
/*end of bmpstring*/
typedef ITCAST_ANYBUF    ITASN1_ENUMERATED;
typedef ITCAST_ANYBUF    ITASN1_IA5STRING;
typedef ITCAST_ANYBUF    ITASN1_SEQUENCE;
typedef ITCAST_ANYBUF    ITASN1_SET;


ITCAST_INT DER_ItAsn1_WriteInteger(ITCAST_UINT32 integer, ITASN1_INTEGER **ppDerInteger);//编码

ITCAST_INT DER_ItAsn1_ReadInteger(ITASN1_INTEGER *pDerInteger, ITCAST_UINT32 *pInteger);//解码

ITCAST_INT DER_ItAsn1_WriteBitString(ITASN1_BITSTRING *pBitString, ITASN1_BITSTRING **ppDerBitString);//编码

ITCAST_INT DER_ItAsn1_ReadBitString(ITASN1_BITSTRING *pDerBitString, ITASN1_BITSTRING **ppBitString);//解码

ITCAST_INT DER_ItAsn1_WritePrintableString(ITASN1_PRINTABLESTRING *pPrintString, ITASN1_PRINTABLESTRING **ppDerPrintString);//编码

ITCAST_INT DER_ItAsn1_ReadPrintableString(ITASN1_PRINTABLESTRING *pDerPrintString, ITASN1_PRINTABLESTRING **ppPrintString);//解码

ITCAST_INT DER_ItAsn1_WriteSequence(ITASN1_SEQUENCE *pSequence, ITCAST_ANYBUF **ppDerSequence);

ITCAST_INT DER_ItAsn1_ReadSequence(ITCAST_ANYBUF *pDerSequence, ITASN1_SEQUENCE **ppSequence);

ITCAST_INT DER_ItAsn1_WriteNull(ITCAST_ANYBUF ** ppDerNull);

ITCAST_INT DER_ItAsn1_ReadNull(ITCAST_ANYBUF * ppDerNull, ITCAST_UINT8 * pInt);

// 释放一个序列(链表), pAnyBuf为链表的头结点
ITCAST_INT DER_ITCAST_FreeQueue(ITCAST_ANYBUF *pAnyBuf);

// 创建ITCAST_ANYBUF, 将strOrigin写入创建的ITCAST_ANYBUF内存中, 通过pOriginBuf将内存地址传出
ITCAST_INT DER_ITCAST_String_To_AnyBuf(ITCAST_ANYBUF **pOriginBuf, unsigned char * strOrigin, int strOriginLen);

int WriteNullSequence(ITCAST_ANYBUF **pOutData);

// pData编码为ITCAST_ANYBUF(有malloc动作), 将新的ITCAST_ANYBUF节点地址赋值给outBuf
int EncodeChar(char *pData, int dataLen, ITCAST_ANYBUF **outBuf);



// 同 EncodeChar 函数
int EncodeUnsignedChar(unsigned char *pData, int dataLen, ITCAST_ANYBUF **outBuf);

// 解析节点inBuf中的字符串数据, 通过第二个参数Data指针传出
int DecodeChar(ITCAST_ANYBUF *inBuf, char **Data, int *pDataLen);

#ifdef __cplusplus
}
#endif

#endif
