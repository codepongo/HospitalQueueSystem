// DoctorCaller.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#include "DoctorCallerDlg.h"
#include "LoginDlg.h"


// CDoctorCallerApp:
// �йش����ʵ�֣������ DoctorCaller.cpp
//

class CDoctorCallerApp : public CWinApp
{
public:
	CDoctorCallerApp();

	CDoctorCallerDlg* GetDoctorCallerDlg()
	{
		return m_pDoctorCallerDlg;
	}
	CLoginDlg* GetLoginDlg()
	{
		return m_pLoginDlg;
	}

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
public:

private:
	//CDoctorController* m_pDoctorController;
	CDoctorCallerDlg* m_pDoctorCallerDlg;
	CLoginDlg* m_pLoginDlg;

public:
	virtual int ExitInstance();
};

extern CDoctorCallerApp theApp;