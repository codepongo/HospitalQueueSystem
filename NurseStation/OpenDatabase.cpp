#include "StdAfx.h"
#include "OpenDatabase.h"
#include "BaseConfig.h"

OpenDatabase::OpenDatabase(void)
{
}

OpenDatabase::~OpenDatabase(void)
{
}

BOOL OpenDatabase::OpenDB(CADODatabase &db)
{
	CBaseConfig config;
	CString strSqlConn = _T("Driver={")+config.GetDataDrive()+_T("};Server=")
		+config.GetServerIP()+_T(";Database=Nurse;Uid=")
		+config.GetServerAcount()+_T(";Pwd=")+config.GetServerPassword()+_T(";");
	db.SetConnectionString(strSqlConn);
	try
	{
		db.Open();
	}catch(_com_error& e)
	{
		AfxMessageBox(_T("���ݿ�����ʧ��,����������ԭ��\n\t1.���������ݿ�����������ѶϿ���\n\t2.���ݿ����δ������\n\t3.���ݿ������ļ������ڻ����ô���;\n\t4.���ݿ��û����������")
			,MB_OK|MB_ICONERROR);
		return FALSE;
	}
	return TRUE;
}
