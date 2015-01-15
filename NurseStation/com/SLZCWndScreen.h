#pragma once
#include "HardWareDef.h"
#include <afxmt.h>
#include <list>
using namespace std;
class SLZCWndScreen
{
private:
	SLZCWndScreen(void);
//	static SLZCWndScreen* m_pInstance;
public:
	~SLZCWndScreen(void);
	static SLZCWndScreen* GetInstance(){
		static SLZCWndScreen instance;
		return &instance;
	}
private:
	typedef struct  
	{
		unsigned char address;//ͨ����ַ
		unsigned char channel;//ͨ����
		unsigned short width;//ͨ����
		unsigned short height;//ͨ����
		unsigned char fone;//�����С
	}ThrScreenBasicMsg;
	typedef struct  
	{
		CString msg;
		int address;
		int channel;
		CString IP;
		USHORT port;
	}SendThrScreenMsg;
	int DoScreenMsg(CString& msg,int address,
		char* buf);
	void AssicToHex(char *param);
	void StrToHexes(char *pc,int nsize,char *puc);
	int InitScreen(char *buf,const int address);
	BOOL IsResaved(const char* buf);//�жϷ��͸����������Ƿ���յ�
	CList<WNDSCREENMSG,WNDSCREENMSG&> m_listScreenMsg;//������
	HANDLE m_hDoWndScreenMsgThread;//�����������߳�
	static DWORD WINAPI DoWndScreenMsgThread(LPVOID pParm);//�����������߳�
	HANDLE m_hDoThrWndMsgThread;//����ͨ�������߳̾��
	static DWORD WINAPI DoThrWndMsgThread(LPVOID pParam);//
	CMutex m_WndScreenMutex;//������
	CMutex m_ThrWndMutex;//ͨ����
	void StartHardScreen();//���������������߳�
	std::list<ThrScreenBasicMsg> m_list_thrBasicMsg;//ͨ��ͨ��������Ϣ
	std::string m_recvThroughInitStr;//���ܳ�ʼ��ͨ������
	std::list<string> m_list_recvString;//�ֽ���ܵ�ͨ������
	std::list<SendThrScreenMsg> m_list_sendThrMsg;//ͨ�����ݻ�����
	CString FlushCstringToFitWndScreen(const CString& str,const int length,int height);//����ͨ��ʱ��ʽ���ַ���
	BOOL SendDataToThroughScreen(const CString& str,int address,int channel,const CString& IP=_T(""),USHORT port=0);
	int  FindChannelWidth(int address,int channel,int& height);//�����ͨ������ʾ���ٸ���
	void AddThrBasicMsg(ThrScreenBasicMsg msg);
public:
	void AddScreenMsg(const CString& msg,const int address);//�򻺳������������
	void InitThroughScreen(const int address);//��ʼ��ͨ������ģʽ
	void InitThroughScreen(const CString& IP,USHORT port,int address);//��ʼ��ͨ��TCPģʽ
	BOOL DoThroughInitMsg();
	void AddThroughInitStr(const char* buf,const DWORD count);
	void AddThroughScreenMsg(const CString& msg,int address,int channel,const CString& IP=_T(""),USHORT port=0);//�򻺳��������ͨ������
};
