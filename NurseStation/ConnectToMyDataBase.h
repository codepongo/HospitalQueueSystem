#pragma once
#include "../NurseStation/ado2.h"
class CConnectToMyDataBase
{
public:
	CConnectToMyDataBase(void);
	~CConnectToMyDataBase(void);
public:
	CString m_connectString;
	CADODatabase m_myDataBase;
	void SetConnectString(int dataBaseType/*���ݿ�����0ΪOrcle,1ΪSQL Server*/,
		CString hisIP,CString hisPort,CString hisBaseName/*���ݿ���*/,
		CString hisAccount/*�û���*/,CString hisPass/*����*/);
	BOOL OpenMyDataBase();
	BOOL IsMyDataBaseOpen();
	CADORecordset* m_pMyRecordset;
};
