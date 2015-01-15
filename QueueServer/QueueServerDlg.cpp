// QueueServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QueueServer.h"
#include "QueueServerDlg.h"
#include "PropSetting.h"
#include "../NurseStation/MyCommon.h"
#include "../NurseStation/MyString.h"
#include "WriteLog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_MY_TRAYICON		(WM_USER+1)

#define IDEVENT_HIDEWINDOW	1
#define IDEVENT_RUNSERVICE	2


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CQueueServerDlg �Ի���




CQueueServerDlg::CQueueServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQueueServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQueueServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CQueueServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CONF, &CQueueServerDlg::OnBnClickedButtonConf)
	ON_BN_CLICKED(IDC_BUTTON_RESTART, &CQueueServerDlg::OnBnClickedButtonRestart)
	ON_COMMAND(ID_MENUITEM_SHOW, &CQueueServerDlg::OnMenuitemShow)
	ON_COMMAND(ID_MENUITEM_CONF, &CQueueServerDlg::OnMenuitemConf)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_MY_TRAYICON, OnTrayIcon)
	ON_COMMAND(ID_MENUITEM_RESTART, &CQueueServerDlg::OnMenuitemRestart)
	ON_COMMAND(ID_MENUITEM_QUIT, &CQueueServerDlg::OnMenuitemQuit)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_HIDE, &CQueueServerDlg::OnBnClickedButtonHide)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &CQueueServerDlg::OnBnClickedButtonQuit)
	ON_WM_TIMER()
	ON_WM_NCPAINT()
END_MESSAGE_MAP()


// CQueueServerDlg ��Ϣ�������

BOOL CQueueServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	//�������߳�����
	//m_readHisData.StartReadDataThread();
	//��office�߳�����
	//m_readHisOffice.StartReadHisOfficeThread();
	//��doctor�߳�����
	//m_readHisDoctor.StartReadHisDoctorThread();

	//m_ServerController.StartControl();
	//m_ReadHis.Start();

	AddTrayIcon();

	//ModifyStyleEx(WS_EX_APPWINDOW, 0);
	//ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);

	//ShowWindow(SW_HIDE);
	//SetTimer(IDEVENT_HIDEWINDOW, 20, NULL);
	SetTimer(IDEVENT_RUNSERVICE, 10, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CQueueServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CQueueServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CQueueServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CQueueServerDlg::OnBnClickedButtonConf()
{
	/*
	if(m_bProSheet == FALSE)
	{
		m_bProSheet = TRUE;
		m_pProSheet = new CPropSetting(_T("�Ŷ�ϵͳ����������������"), this);
		m_pProSheet->DoModal();
		m_bProSheet = FALSE;
	}
	else
	{
		m_pProSheet->ShowWindow(SW_SHOW);
		m_pProSheet->ShowWindow(SW_NORMAL);
		m_pProSheet->UpdateWindow();
	}
	*/
//	m_pProSheet = new CPropSetting(_T("�Ŷ�ϵͳ����������������"), this);
	CPropSetting propSheet(_T("�������--�Ŷӽк�ϵͳ������������"), this);
	if(IDOK == propSheet.DoModal())
	{
		m_ReadHis.LoadConf();
	}
}

void CQueueServerDlg::OnBnClickedButtonRestart()
{
	//char strPath[100]; 
	//::GetModuleFileName(NULL,strPath,100);

	CString strPath = MyCommon::GetModuleFileName();

	//�����ػ����̣��������½��̳ɹ�����WM_QUIT��Ϣ����ԭ���Ľ��̣�
	STARTUPINFO startInfo;
	PROCESS_INFORMATION processInfo;
	ZeroMemory(&startInfo, sizeof(STARTUPINFO));
	startInfo.cb = sizeof(STARTUPINFO);
	if(::CreateProcess(NULL,(LPTSTR)(LPCTSTR)strPath, 
		NULL, NULL,FALSE, 0, NULL, NULL, &startInfo, &processInfo))
	{
		::CloseHandle( processInfo.hProcess );
		::CloseHandle( processInfo.hThread );
		PostQuitMessage(WM_DESTROY);
	}
}

void CQueueServerDlg::OnBnClickedButtonHide()
{
	ShowWindow(SW_HIDE);
}

void CQueueServerDlg::OnBnClickedButtonQuit()
{
	if(IDCANCEL == MessageBox(_T("ȷ���˳���"), _T("�Ŷӽк�ϵͳ������������"), MB_OKCANCEL)) return;
	DestroyWindow();
}

void CQueueServerDlg::OnClose()
{
	ShowWindow(SW_HIDE);

	//CDialog::OnClose();
}

void CQueueServerDlg::OnDestroy()
{
	//m_ServerController.EndControl();
	WriteLog::WriteLogWithTime(_T("�����������˳�"));
	RemoveTrayIcon();

	CDialog::OnDestroy();
}


BOOL CQueueServerDlg::TaskBarAddIcon(HWND hwnd, 
									  UINT uID, 
									  HICON hIcon, 
									  LPCWSTR lpszTip)
{
	BOOL res;
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hwnd;
	nid.uID = uID;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_INFO;
	nid.uCallbackMessage = WM_MY_TRAYICON;
	nid.hIcon = hIcon;
	if (lpszTip)
	{
		lstrcpyn(nid.szTip, lpszTip, sizeof(nid.szTip));
	}
	else
	{
		nid.szTip[0] = '\0';
	}
	res = Shell_NotifyIcon(NIM_ADD, &nid);

	if (hIcon)
	{
		DestroyIcon(hIcon);
	}
	return res;
}

void CQueueServerDlg::AddTrayIcon(void)
{
	HICON hIcon = LoadIcon(AfxGetApp()->m_hInstance, 
		MAKEINTRESOURCE(IDR_MAINFRAME));
	wchar_t tip[128] = {0};
	wsprintf(tip, _T("�Ŷӽк�ϵͳ������������"));
	TaskBarAddIcon(this->m_hWnd, IDR_MAINFRAME, hIcon, tip);
}

LRESULT CQueueServerDlg::OnTrayIcon(WPARAM wParam, LPARAM lParam)
{
	if(wParam != IDR_MAINFRAME)
	{
		return 1;
	}
	switch(lParam)
	{
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
		{
			this->ShowWindow(SW_NORMAL);
			//this->ShowWindow(SW_SHOW);
		}
		break;
	case WM_RBUTTONUP:
		{
			SetForegroundWindow();//�����������λ�����½ǵ����˵���ʧ
			CPoint pt;
			::GetCursorPos(&pt);
			CMenu menu;
			menu.LoadMenu(IDR_MENU_ICON);
			CMenu* subMenu = menu.GetSubMenu(0);
			subMenu->TrackPopupMenu(TPM_CENTERALIGN, pt.x, pt.y, this);
			subMenu->Detach();
			subMenu->DestroyMenu();
			menu.Detach();
			menu.DestroyMenu();
		}
		break;
	}
	return 0;
}

BOOL CQueueServerDlg::TaskBarDeleteIcon(HWND hwnd, UINT uID)
{
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hwnd;
	nid.uID = uID;
	return Shell_NotifyIcon(NIM_DELETE, &nid);
}

void CQueueServerDlg::RemoveTrayIcon()
{
	TaskBarDeleteIcon(this->m_hWnd, IDR_MAINFRAME);
}

void CQueueServerDlg::OnMenuitemShow()
{
	ShowWindow(SW_SHOWNORMAL);
}

void CQueueServerDlg::OnMenuitemConf()
{
	OnBnClickedButtonConf();
}

void CQueueServerDlg::OnMenuitemRestart()
{
	OnBnClickedButtonRestart();
}

void CQueueServerDlg::OnMenuitemQuit()
{
	OnBnClickedButtonQuit();
}



void CQueueServerDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case IDEVENT_HIDEWINDOW:
		{
			KillTimer(IDEVENT_HIDEWINDOW);
			ShowWindow(SW_HIDE);
		}
		break;
	case IDEVENT_RUNSERVICE:
		{
			//m_ServerController.StartControl();
			KillTimer(IDEVENT_RUNSERVICE);
			if(m_ReadHis.Start())
			{
				WriteLog::WriteLogWithTime(_T("HIS���ݶ�ȡ����������"));
			}
			else
			{
				WriteLog::WriteLogWithTime(_T("HIS���ݶ�ȡ��������ʧ��"));
			}
		}
		break;
	}

	CDialog::OnTimer(nIDEvent);
}

void CQueueServerDlg::OnNcPaint()
{
	static int i = 2;
	if(i > 0)
	{
		ShowWindow(SW_HIDE);
		i--;
	}
	else
	{
		CDialog::OnNcPaint();
	}
}
