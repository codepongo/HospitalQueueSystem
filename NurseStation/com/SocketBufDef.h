#ifndef _SOCKETBUFDEF_H
#define _SOCKETBUFDEF_H

#define  MAXRECVBUF 512
typedef enum _tagSendDataType
{
	getNumData = 0,//ȡ������
	callNumData = 1,//��������
	discardNumData = 2,//��������
	evateNumData = 3   //��������(�������)
}SendDataType;
#endif