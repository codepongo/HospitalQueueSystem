#pragma once

#include "../NurseStation/ado2.h"
#include "../NurseStation/MyTimer.h"

// CReadHis ����Ŀ��

class CReadHis : public CObject
{
public:
	CReadHis();
	virtual ~CReadHis();
	BOOL Start();
	void Close();

private:
	BOOL StartPatientThread();
	void EndPatientThread();
	static UINT ReadPatientThreadProc(LPVOID pParam);//��HIS�ŶӲ��������̺߳���
	void ReadOtherDataTimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);//��HIS���ŵȻ������ݶ�ʱ������
	void AutoDeletePatientTimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);//�Զ�ɾ����ϵͳ�������ݶ�ʱ������
	static UINT ReadOtherDataThreadProc(LPVOID pParam);//��HIS���ŵȻ��������̺߳���
	static UINT AutoDeleteThreadProc(LPVOID pParam);//�Զ�ɾ����ϵͳ���������̺߳���

	BOOL OpenHisDb(CADODatabase& hisDb);
	BOOL OpenMyDb(CADODatabase& myDb);

	BOOL ReadPatient();
	BOOL ReadDepart();
	BOOL ReadItem();
	BOOL ReadClinic();
	BOOL ReadDoctor();
	BOOL AutoDeletePatient();
	//int GetHisDays(int nDef);
	BOOL StringExistInStringArray(CString str, CStringArray& arr);

private:

	CString m_strMyDbConnStr;//��ϵͳ���ݿ������ַ���
	//CString m_strHisDbConnStr;//HIS���ݿ������ַ���
	int m_nHisDays;//HIS�ṩ���Ŷ������ڸ�����������֮��
	CWinThread* m_pReadPatientThread;//��HIS�ŶӲ��������߳�
	BOOL m_bReadPatientThread;
	MyTimer<CReadHis> m_timerReadOtherData;//��HIS���ŵȻ������ݶ�ʱ��������ʱ����һ�� ��HIS���ŵȻ��������߳�
	MyTimer<CReadHis> m_timerAutoDeletePatient;//�Զ�ɾ����ϵͳ�������ݶ�ʱ��������ʱ����һ�� �Զ�ɾ����ϵͳ���������߳�
	CWinThread* m_pReadOtherDataThread;//��HIS���ŵȻ��������߳�
	CWinThread* m_pAutoDeleteThread;//�Զ�ɾ����ϵͳ���������߳�

	BOOL m_bHisDbErr;
	BOOL m_bMyDbErr;

	CString m_strHisDbConn;

public:
	void LoadConf();

	CMap<CString, LPCTSTR, CString, LPCTSTR> m_mapItemDepart;
	void LoadMap();

	int m_nDataReadMode;

	int m_nDbType;

	CString m_strQueryPatient;

};

