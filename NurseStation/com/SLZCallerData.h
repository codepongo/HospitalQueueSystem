#pragma once
#include "DataDef.h"

class SLZCallerData
{
public:
	SLZCallerData(void) : m_iCallerId(0){}
	~SLZCallerData(void){}

	//��ȡ��������ַ
	int GetCallerId() const{return m_iCallerId;}
	//���ú�������ַ
	void SetCallerId(int iCallerId){m_iCallerId = iCallerId;}
	//��ȡָ������
	CmdType GetCmdType() const{return m_cmdtype;}
	//����ָ������
	void SetCmdType(CmdType cmdtype){m_cmdtype = cmdtype;}
	CString GetAttchMsg() const {return m_attchMsg;}
	void SetAttchMsg(const CString& msg){m_attchMsg = msg;}
private:
	int m_iCallerId;	//��������ַ
	CmdType m_cmdtype;		//ָ������
	CString m_attchMsg;//������Ϣ����У�1234��
};
