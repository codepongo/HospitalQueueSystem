// DoctorCaller.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "DoctorCaller.h"
#include "LoginDlg.h"
#include "../NurseStation/MyCommon.h"
#include "../NurseStation/MyString.h"
//#include "../NurseStation/NurseLicense.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDoctorCallerApp

BEGIN_MESSAGE_MAP(CDoctorCallerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDoctorCallerApp ����

CDoctorCallerApp::CDoctorCallerApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CDoctorCallerApp ����

CDoctorCallerApp theApp;


// CDoctorCallerApp ��ʼ��

BOOL CDoctorCallerApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Lingbhc"));

	///////////////////////////////////////////////////////////////////////////

	m_pLoginDlg = new CLoginDlg;
	//g_pLoginDlg = &dlgLogin;
	INT_PTR nResponse = m_pLoginDlg->DoModal();
	m_pLoginDlg->EndControl();
	if (nResponse == IDOK)
	{
		m_pDoctorCallerDlg = new CDoctorCallerDlg;
		m_pMainWnd = m_pDoctorCallerDlg;
		m_pDoctorCallerDlg->DoModal();
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int CDoctorCallerApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
