// QueueServer.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "QueueServer.h"
#include "QueueServerDlg.h"
#include "../NurseStation/MyCommon.h"
#include "../NurseStation/MyString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
///////////����ڴ�й©�Ŀ�
//#pragma comment(lib,"C:/Program Files/Visual Leak Detector/lib/Win32/vld.lib")
//#include "C:\Program Files\Visual Leak Detector\include\vld.h"

#endif


// CQueueServerApp

BEGIN_MESSAGE_MAP(CQueueServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CQueueServerApp ����

CQueueServerApp::CQueueServerApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CQueueServerApp ����

CQueueServerApp theApp;


// CQueueServerApp ��ʼ��

BOOL CQueueServerApp::InitInstance()
{
	HWND hWnd = ::FindWindow(NULL, _T("�Ŷ�ϵͳ������������"));
	if(hWnd)
	{
		//::ShowWindow(hWnd, SW_MINIMIZE);
		//::ShowWindow(hWnd, SW_SHOWMAXIMIZED);
		::ShowWindow(hWnd, SW_NORMAL);
		::SetForegroundWindow(hWnd);
		return FALSE;
	}

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
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	MyCommon::AddAutoRun(_T("QueueServer"));

	CQueueServerDlg dlg;
	m_pMainWnd = &dlg;
	//m_pControl = new CServerController;
	//m_pControl->OnStartControl();
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
