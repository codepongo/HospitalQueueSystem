#pragma once

class CComInit
{
private:
	CComInit(void);
public:
	~CComInit(void);
	//�򿪴�����������������
	int OpenWndScreen(const int ncom);
	int m_canUse[10];//���汾�������еĿ��ô��ں�
	HANDLE m_hComWndScreen;//��������(������)
	HANDLE m_hComReadCard;//ˢ��������
	HANDLE OpenComm(const int ncom);//�򿪴���
	///try�������еĿ��õĴ���
	int TryCom(const int nCom);
	//��ˢ��������
	int OpenCardComm(const int ncom);
	//���浽�ļ�
	void SaveComm();
	//���ļ�
	CString GetCardComm();
	CString GetWndComm();
	int OpenWndScreen();
	int OpenCardComm();
private:
	//��ʼ������
	void InitCom();
	CString m_cCardComm;
	CString m_cWndComm;
	CString m_strPath;
public:
	//��ȡΨһʵ��
	static CComInit* GetInstance(){
		static CComInit instance;
		return &instance;
	}
};
