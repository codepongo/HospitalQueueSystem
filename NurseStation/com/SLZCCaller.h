#pragma once

#include "SLZCallerData.h"
#include "afxmt.h"


// SLZCCaller ����Ŀ��
/*
Ӳ��������������
*/
class SLZCCaller : public CObject
{
	friend class CDoComInOut;
private:
	SLZCCaller();
public:
	//���дdata
	BOOL AddWriteCallerData(SLZCallerData callerData);
	////////////////////��ȡ���������ݽӿ�
	BOOL HasData();
	SLZCallerData GetData();
	~SLZCCaller();
	////////////////////////////
	static SLZCCaller*  GetInstance();
private:
	////////////////�ⲿ��ȡ���������ݽӿڵĻ�����
	///�����Ժ����Ϣ
	CList<SLZCallerData> m_callDataList;
	CMutex m_callerLock;
	///////////////
private:
	HANDLE m_hDoCallerMsgThread;//���崦��Ӳ���������߳�
	static DWORD WINAPI DoCallerMsgThread(LPVOID pParam);
	//���崦��������߳�
	/////////////////��������Ϣ�����ⲿ�ӿڵ���
	CMutex m_callerReadMutex;
	//���������յ�����Ϣ����
	CList<CString,CString&> m_listCallerMsg;//������
	//������������͵����ݣ�������Ϣ)
	void DoCallerMsg(char *buf,int size);
	//����
	int AlarmToSystem(const int CallerAddress,char* addbuf);
	////��ʾ�ɹ����
	int ShowSuccFail(const int address,char* buf,const int conntext);
	//��ʾʣ������
	int ShowLastPaintCount(const int CallerAddress,int WaitCount,char *addbuf);
	//������������
	int SepaMsgNum(const char* buf,char* result,int size);
	//���������յ�����Ϣ
	CList<CString,LPCWSTR> m_ReciveMsg;
	//�ϴ�û�������Ϣ
	CString m_lastMsg;
	//�����ϴ�û������Ϣ
	void ExTransmission();
	//////////////////д���ֵ�������
	int ShowSystemNum(int CallerAddress,char* buf,
		const int num[],const int count);
	/////////////////��ʾ��ǰ���к����ʣ������
	int ShowSysCallLeftNum(int callerAddress,char* buf,int leftNum,const CString& callNum);
private:
	HANDLE m_hWriteCallerThread;//дӲ���������߳�
	static DWORD WINAPI WriteCallerThread(LPVOID pParam);//дӲ���������߳�
	//дӲ������������
	CList<SLZCallerData> m_writeCallerData;
	//д��������Ϣ��
	CMutex m_writeCallerLock;
private:
	//��ʼ����������
	void InitHardWareCaller();
	///�����ȡ��Ϣ
	void DoReadMsg(const DWORD dwReaded,char* buf);
};


