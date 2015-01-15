// NurseStation.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "NurseStation.h"
#include "MainFrm.h"
#include "NurseStationDoc.h"
#include "NurseStationView.h"
#include "MyString.h"
#include "MyCommon.h"
#include "LicenseMaker.h"

#pragma comment(lib, "QueSystemLicense.lib")


#ifdef _DEBUG
#define new DEBUG_NEW

//#pragma comment(lib,"C:/Program Files/Visual Leak Detector/lib/Win32/vld.lib")
//#include "C:\Program Files\Visual Leak Detector\include\vld.h"

HANDLE g_hStdOutput;
void MyWriteConsole(CString str)
{
	::WriteConsole(g_hStdOutput, str, str.GetLength(), NULL, NULL);
	::WriteConsole(g_hStdOutput, "\n", 1, NULL, NULL);
}
#endif


// CNurseStationApp

BEGIN_MESSAGE_MAP(CNurseStationApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CNurseStationApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CNurseStationApp ����

CNurseStationApp::CNurseStationApp()
	: m_pNurseWnd(NULL)
	//, m_pJttsAPI(NULL)
	, m_pNurseController(NULL)
{
	m_backSet=FALSE;
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CNurseStationApp ����

CNurseStationApp theApp;
//int g_nDataDays;

// CNurseStationApp ��ʼ��

BOOL CNurseStationApp::InitInstance()
{

#ifdef _DEBUG
	::AllocConsole();
	g_hStdOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
#endif


	HWND hWnd = ::FindWindow(NULL, _T("�Ŷӽк�ϵͳ��ʿվ"));
	if(hWnd)
	{
		::ShowWindow(hWnd, SW_SHOWMAXIMIZED);
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

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Lingbhc"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)

	///////////////////////////////////////////////////////////////////////////
	////////////////////	���ע����Ϣ	///////////////////////////////////
	BOOL bGo = FALSE;
	int a = 1, b = 1;
	if(a == b)
	{
		bGo = TRUE;
	}
	if(!bGo) return FALSE;

	if(!VerifyLicense())
	{
		AfxMessageBox(_T("�����δע�ᣬ��������ע��������ע��"));
		return FALSE;
	}
	//////////////////		End ���ע����Ϣ	///////////////////////////////

	//�ó��򿪻�����
	MyCommon::AddAutoRun(_T("NurseStation"));

	//CPoolManage pool;
	//m_strIP=pool.GetComputerIP();
	m_strIP = MyCommon::GetLocalIP();

	////////////////////////////////////////////////////
	/////////////////	������¼����	////////////////
	CDoc_NurseDlg dlg;
	if(IDOK != dlg.DoModal())
	{
		return FALSE;
	}
	dlg.EndControl();
	if(m_backSet)
	{
		CPropSetting prop(_T("��̨����"));
		m_pPropSetting = &prop;
		prop.DoModal();
		//delete pdlg;
		return TRUE;
	}
	////////////////////////////////////////////////////

	m_pNurseController = new CNurseController;
	m_pNurseController->SetUserId(dlg.GetUserId());
	//delete pdlg;
	if(!m_pNurseController->StartControl())
	{
		AfxMessageBox(_T("���Ʒ�������ʧ��!"));
		return FALSE;
	}

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CNurseStationDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		NULL);
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	//m_pNurseWnd = (CMainFrame*)m_pMainWnd;



	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���

	m_pMainWnd->SetWindowText(_T("�Ŷӽк�ϵͳ��ʿվ"));
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
	return TRUE;
}

int CNurseStationApp::ExitInstance()
{
	if(m_pNurseController)
	{
		m_pNurseController->EndControl();
		delete m_pNurseController;
		m_pNurseController = NULL;
	}

	return CWinApp::ExitInstance();
}
/*
BOOL CNurseStationApp::VerifySerialNo()
{
	CString strSerialNoFromReg;
	NurseLicense lic;
	if(!ReadSerialNo(strSerialNoFromReg))
	{
		return FALSE;
	}
	if(licerrNone != lic.VerifyLicense(strSerialNoFromReg))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CNurseStationApp::ReadSerialNo(CString& strSerialNo)
{
	HKEY hKey;
	LONG ret = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
		_T("SOFTWARE\\QueueSystem\\"), 0, KEY_READ, &hKey);
	if(ERROR_SUCCESS != ret)
	{
		return FALSE;
	}
	WCHAR wszSerialNo[128] = {0};
	DWORD dType = REG_SZ;
	DWORD dLength = 128;
	ret = ::RegQueryValueEx(hKey, _T("SerialNo"), NULL, &dType, (LPBYTE)wszSerialNo, &dLength);
	//ret = ::RegGetValue(hKey, NULL, _T("SerialNo"), REG_SZ, NULL, wszSerialNo, NULL);
	::RegCloseKey(hKey);
	//AfxMessageBox(wszSerialNo);
	if(ERROR_SUCCESS != ret)
	{
		return FALSE;
	}
	strSerialNo.Format(_T("%s"), wszSerialNo);

	return TRUE;
}
*/
/*
BOOL CNurseStationApp::AddAutoRun(CString strValueName)
{
	HKEY hKey;
	LONG ret = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
		_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_READ, &hKey);
	if(ERROR_SUCCESS != ret)
	{
		return FALSE;
	}
	WCHAR wszPathGet[MAX_PATH] = {0};
	DWORD dType = REG_SZ;
	DWORD dLength = MAX_PATH;
	ret = ::RegQueryValueEx(hKey, strValueName, NULL, &dType, (LPBYTE)wszPathGet, &dLength);

	//CString strPath = MyCommon::GetModuleFileName();
	WCHAR wszPath[MAX_PATH] = {0};
	::GetModuleFileName(NULL, wszPath, MAX_PATH);

	if(ERROR_SUCCESS == ret && 
		::wcscmp(::wcslwr(wszPathGet), ::wcslwr(wszPath)) == 0)
	{
		::RegCloseKey(hKey);
		return TRUE;
	}

	ret = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
		_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_WRITE, &hKey);
	if(ERROR_SUCCESS != ret)
	{

		LPCTSTR lpSubKey = _T("Software\\");
		ret = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_WRITE, &hKey);
		if(ERROR_SUCCESS != ret)
		{
			ret = ::RegCreateKey(HKEY_LOCAL_MACHINE, lpSubKey, &hKey);
		}
		if(ERROR_SUCCESS != ret)
		{
			return FALSE;
		}
		lpSubKey = _T("Microsoft\\");
		ret = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_WRITE, &hKey);
		if(ERROR_SUCCESS != ret)
		{
			ret = ::RegCreateKey(HKEY_LOCAL_MACHINE, lpSubKey, &hKey);
		}
		if(ERROR_SUCCESS != ret)
		{
			return FALSE;
		}
		lpSubKey = _T("Windows\\");
		ret = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_WRITE, &hKey);
		if(ERROR_SUCCESS != ret)
		{
			ret = ::RegCreateKey(HKEY_LOCAL_MACHINE, lpSubKey, &hKey);
		}
		if(ERROR_SUCCESS != ret)
		{
			return FALSE;
		}
		lpSubKey = _T("CurrentVersion\\");
		ret = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_WRITE, &hKey);
		if(ERROR_SUCCESS != ret)
		{
			ret = ::RegCreateKey(HKEY_LOCAL_MACHINE, lpSubKey, &hKey);
		}
		if(ERROR_SUCCESS != ret)
		{
			return FALSE;
		}
		lpSubKey = _T("Run\\");
		ret = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_WRITE, &hKey);
		if(ERROR_SUCCESS != ret)
		{
			ret = ::RegCreateKey(HKEY_LOCAL_MACHINE, lpSubKey, &hKey);
		}
		if(ERROR_SUCCESS != ret)
		{
			return FALSE;
		}
	}

	ret = ::RegSetValueEx(hKey, strValueName, 0, REG_SZ,
		(const BYTE*)wszPath, ::wcslen(wszPath) * 2);

	if(ERROR_SUCCESS != ret)
	{
		return FALSE;
	}

	return TRUE;
}
*/

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CNurseStationApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

BOOL CNurseStationApp::PreTranslateMessage(MSG* pMsg)
{
	switch(pMsg->message)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_KEYDOWN:
	case WM_KEYUP:
		{
			if(m_pNurseWnd && m_pNurseWnd->m_wndToolBar)
			{
				int suspendState=m_pNurseWnd->
					m_wndToolBar.GetToolBarCtrl().GetState(IDI_ICON_SUSPEND);
				int recallState=m_pNurseWnd->
					m_wndToolBar.GetToolBarCtrl().GetState(IDI_ICON_RECALL);
				int queState=m_pNurseWnd->
					m_wndToolBar.GetToolBarCtrl().GetState(IDI_ICON_QUE);
				int exportState=m_pNurseWnd->
					m_wndToolBar.GetToolBarCtrl().GetState(IDI_ICON_EXPORT);
				m_pNurseWnd->m_wndToolBar.GetToolBarCtrl().SetState(IDI_ICON_EXPORT,
					exportState &= ~TBSTATE_CHECKED);
				m_pNurseWnd->m_wndToolBar.GetToolBarCtrl().SetState(IDI_ICON_SUSPEND,
					suspendState &= ~TBSTATE_CHECKED);
				m_pNurseWnd->m_wndToolBar.GetToolBarCtrl().SetState(IDI_ICON_RECALL,
					recallState &= ~TBSTATE_CHECKED);
				m_pNurseWnd->m_wndToolBar.GetToolBarCtrl().SetState(IDI_ICON_QUE,
					queState &= ~TBSTATE_CHECKED);

				m_pNurseWnd->m_iconQueCheck=FALSE;
				m_pNurseWnd->m_iconExportCheck=FALSE;
				m_pNurseWnd->m_iconSuspendCheck=FALSE;
				m_pNurseWnd->m_iconRecall=FALSE;
			}
		}
		break;
	}
	return CWinApp::PreTranslateMessage(pMsg);
}

