#pragma once
#include "Consult.h"

class CNurseOfficeQueue : public CObject
{
public:
	CNurseOfficeQueue(void);
	~CNurseOfficeQueue(void);
	CNurseOfficeQueue(const CNurseOfficeQueue& obj);
	CNurseOfficeQueue& operator=(CNurseOfficeQueue& obj);

	CString GetQueName(){return m_queName;}//��������
	void SetQueName(CString name){m_queName=name;}

	CString GetQueCallName(){return m_queCallName;}//��������
	void SetQueCallName(CString name){m_queCallName=name;}

	void SetQueID(CString id){m_queID=id;}//����ID������
	CString GetQueID(){return m_queID;}

	CString GetQueCallID(){return m_queIDCallName;}//idǰ׺
	void SetQueCallID(CString idName){m_queIDCallName=idName;}

	int GetQuenumStart(){return m_queNumStart;}//��ʼ����(�ŶӺ�)
	void SetQuenumStart(int numstart){m_queNumStart=numstart;}

	int GetQuenumEnd(){return m_queNumEnd;}//��������
	void SetQuenumEnd(int numend){m_queNumEnd=numend;}

	void SetAmLimitPatient(int patient);
	int GetAmLimitPatient(){return m_AmLimitPatient;}

	void SetPmLimitPatient(int patient);
	int GetPmLimitPatient(){return m_PmLimitPatient;}
	
	void SetDayLimitPatient(int patient);
	int GetDayLimitPatient(){return m_DayLimitPatient;}
	////////////////////
	void SetQueNumber(int patient);//ʵ���Ŷ�����
	int GetQueNumber(){return m_queNumber;}
	/////Һ��������ID
	void SetstdId(CString strStbId){m_stdId=strStbId;}
	CString GetstdId(){return m_stdId;}
	////////////////////////////////ΨһID
	void SetSerialId(int serial_id){m_serial_id=serial_id;}
	int GetSerialId(){return m_serial_id;}
	///////////////////////////////////////////
	////HIS��ʶ
	BOOL GetHisFlag(){return m_bHisFlag;}
	void SetHisFlag(const BOOL flag){m_bHisFlag = flag;}
	//////////
	CList<CConsult,CConsult&> m_list_officeConsult;
protected:
	CString m_queName;
	CString m_queCallName;
	CString m_queID;
	CString m_queIDCallName;
	int m_queNumStart;
	int m_queNumEnd;
	int m_AmLimitPatient;
	int m_PmLimitPatient;
	int m_DayLimitPatient;
	int m_queNumber;
	CString m_stdId;
	int m_serial_id;
	BOOL m_bHisFlag;//��ʶ�Ƿ��HIS������������
};
