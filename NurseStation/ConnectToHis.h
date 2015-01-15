#pragma once
#include "../NurseStation/ado2.h"
class CConnectToHis
{
public:
	CConnectToHis(void);
	~CConnectToHis(void);
public:
	CADODatabase m_hisDataBase;
	CString m_connectString;
	void SetConnectString(int dataBaseType/*���ݿ�����0ΪOrcle,1ΪSQL Server*/,
		CString hisIP,CString hisPort,CString hisBaseName/*���ݿ���*/,
		CString hisAccount/*�û���*/,CString hisPass/*����*/);
	BOOL OpenHisDataBase();
	BOOL IsHisDataBaseOpen();
	CADORecordset* m_pHisRecordset;
};
