#pragma once
#include "SLZCCaller.h"
#include "SLZCWndScreen.h"
#include "afxmt.h"
#include <list>
#include "DataDef.h"
using namespace std;
/*
�����ڶ�ȡ��
*/
class CDoComInOut
{
private:
	CDoComInOut(void);
//	CDoComInOut(const CDoComInOut& obj);
//	CDoComInOut& operator=(const CDoComInOut& obj);
public:
	//�ṩ��ȡΨһʵ���ӿ�
	static CDoComInOut* GetInstance()
	{
		static CDoComInOut instance;
		return &instance;
	}
	~CDoComInOut(void);
	HANDLE m_hReadCallerThread;//��Ӳ���������߳�
	HANDLE m_hWriteComThread;//д�����߳�
	void SetThroughInitDone(BOOL isDone) 
	{
		m_isDoneThroughInit = isDone;
	}
private:
	static DWORD WINAPI ReadCallerThread(LPVOID pParam);//��Ӳ���������߳�
	static DWORD WINAPI WriteComThread(LPVOID pParam);//д�����߳�
private:
	SLZCCaller* m_pSlzCaller;//������Ψһ����
//	SLZCEvaluator* m_pSlzEvaluator;//������Ψһ����
	SLZCWndScreen* m_pSlzWndScreen;//��Ψһ����
private:
	CMutex m_readComLock;
	BOOL Start();
	BOOL m_isDoneThroughInit;//ͨ���Ƿ��ʼ��
private:
	list<WriteComMsg*> m_list_writeComMsg;
public:
	void AddWriteComMsg(WriteComMsg* pMsg);
};
