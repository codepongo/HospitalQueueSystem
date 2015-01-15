#pragma once

// CConsult ����Ŀ��

class CConsult : public CObject
{
public:
	CConsult();
	virtual ~CConsult();
	CConsult(const CConsult& obj);
	
	//	CConsult(const CConsult& obj);
	//	Base& operator=(Base& obj);
	CConsult& operator=(CConsult& obj);
	
	///��������
	CString GetConsultName(){return m_ConsultName;}
	void SetConsultName(CString name){m_ConsultName=name;}
	///��������
	CString GetCallName(){return m_CallName;}
	void SetCallName(CString name){m_CallName=name;}
	///����ַ
	int GetShowAddress(){return m_ShowAddress;}
	void SetShowAddress(int address){m_ShowAddress=address;}
	///��������ַ
	int GetCallAddress(){return m_CallAddress;}
	void SetCallAddress(int address){m_CallAddress=address;}
	////�ۺ�����ַ
	int GetComprehAddress(){return m_ComprehAddress;}
	void SetComprehAddress(int address){m_ComprehAddress=address;}
	////ͨ����ַ
	int GetTroughAddress(){return m_TroughAddress;}
	void SetTroughAddress(int address){m_TroughAddress=address;}
	////ͨ��IP
//	CString GetThroughIP(){return m_TroughIP;}
//	void SetTroughIp(CString IP){m_TroughIP=IP;}
	////����ID
	CString GetConsultID(){return m_ConsultID;}
	void SetConsultID(CString consultid){m_ConsultID=consultid;}
	////������ID
	void SetstdId(CString strStbId){m_stdId=strStbId;}
	CString GetstdId(){return m_stdId;}
	////
	void SetHisFlag(const BOOL flag){m_bHisFlag = flag;}
	BOOL GetHisFlag(){return m_bHisFlag;}
private:
	CString m_ConsultName;
	int m_CallAddress;
	CString m_CallName;
	int m_ShowAddress;
	int m_ComprehAddress;
//	CString m_TroughIP;
	int m_TroughAddress;
	CString m_ConsultID;
	///������ID
	CString m_stdId;
	BOOL m_bHisFlag;//��ʶ���Ƿ��HIS����������
};


