#pragma once
#include "ConnectToHis.h"
#include "ConnectToMyDataBase.h"
#include "../NurseStation/BaseConfig.h"
#include "QueueServerDef.h"
class CReadHisData
{
public:
	CReadHisData(void);
	~CReadHisData(void);
public:
	CConnectToHis          m_connectToHis;
	CConnectToMyDataBase   m_connectToMyDataBase;
	void FlushHisDataToMyTable(int typeDataDrive);

	void SetHisDataBaseString(int dataBaseType/*���ݿ�����0ΪOrcle,1ΪSQL Server*/,
		CString hisIP,CString hisPort,CString hisBaseName/*���ݿ���*/,
		CString hisAccount/*�û���*/,CString hisPass/*����*/);

	void SetMyDataBaseString(int dataBaseType/*���ݿ�����0ΪOrcle,1ΪSQL Server*/,
		CString hisIP,CString hisPort,CString hisBaseName/*���ݿ���*/,
		CString hisAccount/*�û���*/,CString hisPass/*����*/);
	
	BOOL OpenHisDataBase();
	BOOL OpenMyDataBase();
	BOOL IsHisDataBaseOpen();
	BOOL IsMyDataBaseOpen();

	HANDLE m_hReadHisData;
	static DWORD WINAPI ThreadReadData(LPVOID pParam);

	BOOL StartReadDataThread();
	CBaseConfig m_baseConfig;
	int m_typeDataDrive;
};
