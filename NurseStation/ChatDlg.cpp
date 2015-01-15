// DoctorCallerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatDlg.h"
#include "NurseStation.h"
#include "ServiceController.h"
#include "MyString.h"
#include "MyCommon.h"

//using namespace std;
//extern CNurseStationApp theApp;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//extern void MyWriteConsole(CString str);
// CChatDlg �Ի���

CChatDlg::CChatDlg(void* pController, CWnd* pParent /*=NULL*/)
	: CDialog(CChatDlg::IDD, pParent)
	, m_pQueueController(pController)
	, m_strSendData(_T(""))
	, m_strChatRec(_T(""))
	, m_nEveryoneItem(-2)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MSG, m_editSendData);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_btnSend);
	DDX_Control(pDX, IDC_EDIT_CHATREC, m_editChatRec);
	DDX_Control(pDX, IDC_COMBO_USERLIST, m_cbUserList);
}

BEGIN_MESSAGE_MAP(CChatDlg, CDialog) 
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	//ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CChatDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CChatDlg::OnBnClickedButtonSend)
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CChatDlg ��Ϣ�������


BOOL CChatDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	//EnableButtons();
	m_nEveryoneItem = m_cbUserList.AddString(_T("������"));
	m_cbUserList.SetItemDataPtr(m_nEveryoneItem, NULL);
	m_cbUserList.SetCurSel(m_nEveryoneItem);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CChatDlg::OnClose()
{
	//if(IDOK == MessageBox(_T("ȷ���˳���"), _T("����"), MB_OKCANCEL))
	//{
	//CDialog::OnClose();
	//CDialog::OnDestroy();
	//}
	//ShowWindow(SW_HIDE);
	((CQueueController*)m_pQueueController)->HideChat();
}

void CChatDlg::OnDestroy()
{
	CDialog::OnDestroy();
}

void CChatDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
//	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
//	{
//		CAboutDlg dlgAbout;
//		dlgAbout.DoModal();
//	}
//	else
//	{
		CDialog::OnSysCommand(nID, lParam);
//	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatDlg::OnPaint()
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
HCURSOR CChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CChatDlg::OnBnClickedButtonSend()
{
	if(SendMsg())
	{
		m_editSendData.SetWindowText(_T(""));
		m_editSendData.SetFocus();
	}
}

HBRUSH CChatDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	/*
	if(pWnd->GetDlgCtrlID() == IDC_EDIT_CHATREC && nCtlColor == CTLCOLOR_EDIT )
	{
		//COLORREF clr = RGB(0, 0, 0);
		//CFont font;
		//font.CreatePointFont(20, _T("����"));
		//m_editChatRec.SetFont(&font);
		COLORREF clr = 0xCD5C5C;
		pDC->SetTextColor(clr);
		clr = RGB(255,255,255);
		pDC->SetBkColor(clr);
		hbr = CreateSolidBrush(clr);
	}else if(pWnd->GetDlgCtrlID() == IDC_STATIC_GREET && nCtlColor == CTLCOLOR_STATIC )
	{
		//COLORREF clr = RGB(0, 0, 0);
		//CFont font;
		//font.CreatePointFont(20, _T("����"));
		//m_editChatRec.SetFont(&font);
		COLORREF clr = 0x4DB34D;
		pDC->SetTextColor(clr);
	}
	*/

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
/*
void CChatDlg::EnableButtons()
{
	m_btnSend.EnableWindow(TRUE);
	m_cbUserList.EnableWindow(TRUE);
}
void CChatDlg::DisableButtons()
{
	m_btnSend.EnableWindow(FALSE);
	m_cbUserList.EnableWindow(FALSE);
}
*/
LRESULT CChatDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LONG lRes = CDialog::DefWindowProc(message, wParam, lParam);
	/*
	switch(message)
	{
	case WM_SYSCOMMAND:
		if(wParam == SC_CLOSE)
		{
			MessageBox(_T("Hide"));
			ShowWindow(SW_HIDE);
			//ShowTip();
		}
		break;
	case WM_CLOSE:
		{
			//MessageBox(_T("Hide2"));
			//ShowWindow(SW_HIDE);
		}
		break;
	}
	*/
	return lRes;
}

void CChatDlg::AddUser(void* pUser, BOOL bLogin)
{
	//CMap<void* , void*&, int, int&>::CPair* pPair;
	//pPair = m_mapUserCb.PLookup(pUser);

	//if(pPair) return;
	
	CUser* pUsr = (CUser*)pUser;
	CString strItemName = pUsr->GetName();
	if(pUsr->IsKindOf(RUNTIME_CLASS(CNurse)))
	{
		strItemName +=  _T("[��ʿ][") + ((CNurse*)pUsr)->GetOfficeNames() + _T("]");
	}
	else
	{
		strItemName += _T("[") + ((CDoctor*)pUsr)->GetOfficeName() + _T("]");
	}
	if(m_cbUserList.FindString(0, strItemName) < 1)
	{
		int iItem = m_cbUserList.AddString(strItemName);
		m_cbUserList.SetItemDataPtr(iItem, pUser);
		m_mapUserCb[pUser] = iItem;
	}
	if(bLogin)
	{
		AddLoginMsg(((CUser*)pUser)->GetName());
	}
}

void CChatDlg::DelUser(void* pUser)
{
	m_cbUserList.DeleteString(m_mapUserCb[pUser]);
	AddQuitMsg(((CUser*)pUser)->GetName());
}

void CChatDlg::AddChat(void* pUser, CString strChat, BOOL bPublic)
{
	if(bPublic)
	{
		if(((CUser*)pUser)->GetId() == 
			((CQueueController*)m_pQueueController)->GetUserId())
		{
			return;
		}
		AddUserMsg(((CUser*)pUser)->GetName(), strChat);
	}
	else
	{
		CString strName;
		strName.Format(_T("[˽��]���� %s"), ((CUser*)pUser)->GetName());
		AddUserMsg(strName, strChat);
	}
}

void CChatDlg::AddChat(CString strUserName, CString strChat, BOOL bPublic, int)
{
	if(bPublic)
	{
		AddUserMsg(strUserName, strChat);
	}
	else
	{
		CString strName;
		strName.Format(_T("[˽��]���� %s"), strUserName);
		AddUserMsg(strName, strChat);
	}
}

void CChatDlg::AddLoginMsg(CString strUsername)
{
	CString str;
	str.Format(_T("%s  ��¼"), strUsername);
	AddUserMsg(str, _T(""));
}

void CChatDlg::AddHeartBeatMsg(CString strUserID)
{
	CString str;
	str.Format(_T("%s  ������"), strUserID);
	AddUserMsg(str, _T(""));
}

void CChatDlg::AddQuitMsg(CString strUsername)
{
	CString str;
	str.Format(_T("%s  �˳�"), strUsername);
	AddUserMsg(str, _T(""));
}

void CChatDlg::AddUserMsg(CString strUserName, CString strMsg)
{
	CTime time = CTime::GetCurrentTime();
	//time.GetCurrentTime();
	CString strTime = time.Format(_T("%Y-%m-%d %H:%M:%S"));
	CString str;
	//if(m_strChatRec.IsEmpty())
	//{
	//	str.Format(_T("%s  %s\r\n%s\r\n"),strUserName, strTime, strMsg);
	//}
	//else
	//{
	//	str.Format(_T("\r\n%s  %s\r\n%s\r\n"),strUserName,strTime, strMsg);
	//}
	str.Format(_T("%s  %s\r\n%s\r\n\r\n"),strUserName,strTime, strMsg);
	AddMsg(str);
}

void CChatDlg::AddMsg(CString strMsg)
{
	m_mtChat.Lock(100);
	m_strChatRec += strMsg;
	m_editChatRec.SetWindowText(m_strChatRec);
	m_editChatRec.LineScroll(m_editChatRec.GetLineCount());
	m_mtChat.Unlock();
}

//������������
BOOL CChatDlg::SendMsg()
{
	int nCurSel = m_cbUserList.GetCurSel();
	if(nCurSel == -1) 
	{
		return FALSE;
	}
	m_editSendData.GetWindowText(m_strSendData);
	LPSOCKADDR_IN pSock = NULL;
	SOCKADDR_IN sock;
	CString strUsrName;
	if(nCurSel != m_nEveryoneItem)
	{
		CUser* pUser = (CUser*)m_cbUserList.GetItemDataPtr(nCurSel);
		if(!pUser) 
		{
			return FALSE;
		}
		sock = pUser->GetSockAddrIn();
		pSock = &sock;
		if(!pSock)
		{
			return FALSE;
		}
		strUsrName.Format(_T("[˽��]���� %s"), pUser->GetName());
		//AddUserMsg(strUsrName, m_strSendData);
	}
	else
	{
		strUsrName = ((CQueueController*)m_pQueueController)->GetUserName();
	}
	AddUserMsg(strUsrName, m_strSendData);

	BOOL bRes = ((CQueueController*)m_pQueueController)->SendChat(
		m_strSendData,pSock);
	//if(((CQueueController*)m_pQueueController)->GetUserType() == utDoctor)
	//{
	//	if(((CQueueController*)m_pQueueController)->GetPort() != 
	//		((CQueueController*)m_pQueueController)->GetBroadPort())
	//	{
	//		AddUserMsg(
	//			((CQueueController*)m_pQueueController)->GetUserName(),
	//			m_strSendData);
	//	}
	//}
	if(!bRes)
	{
		AddMsg(_T("[����ʧ��]\r\n"));
		return FALSE;
	}
	return TRUE;
}

void CChatDlg::MoveControls()
{
	CRect rect;
	GetClientRect(&rect);

	CRect rectControl;
	//m_editChatRec.GetWindowRect(&rectControl);
	rectControl.left = 10;
	rectControl.right = rect.right - rectControl.left;
	rectControl.top = rect.Height()*2/100;
	rectControl.bottom = rect.Height()*65/100 - rectControl.top;
	m_editChatRec.MoveWindow(&rectControl);

	//m_editChatRec.GetWindowRect(&rectControl);
	rectControl.top = rectControl.bottom + rect.Height()*2/100;
	rectControl.bottom = rectControl.bottom + rect.Height()*20/100;
	m_editSendData.MoveWindow(&rectControl);

	CRect rectCb;
	m_cbUserList.GetWindowRect(&rectCb);

	rectControl.top = rectControl.bottom + rect.Height()*4/100;
	rectControl.bottom = rectControl.bottom + rectCb.Height();
	rectControl.right = rectControl.left + rectCb.Width();
	m_cbUserList.MoveWindow(&rectControl);

	CRect rectBtn;
	m_btnSend.GetWindowRect(&rectBtn);
	rectControl.left = rectControl.right;
	rectControl.right = rect.right - 10;
	rectControl.bottom = rectControl.bottom + rectBtn.Height();
	m_btnSend.MoveWindow(&rectControl);
}

