// SuspendPatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NurseStation.h"
#include "SuspendPatDlg.h"

// CSuspendPatDlg �Ի���

IMPLEMENT_DYNAMIC(CSuspendPatDlg, CDialog)

CSuspendPatDlg::CSuspendPatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSuspendPatDlg::IDD, pParent)
{

}

CSuspendPatDlg::~CSuspendPatDlg()
{
}

void CSuspendPatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_last_datetime);
	DDX_Control(pDX, IDC_EDIT_CURENTTIME, m_ed_currenttime);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_suspend_time);
}


BEGIN_MESSAGE_MAP(CSuspendPatDlg, CDialog)
	//ON_BN_CLICKED(IDOK, &CSuspendPatDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSuspendPatDlg ��Ϣ�������

BOOL CSuspendPatDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_current_time=CTime::GetCurrentTime();
	CString c_time=m_current_time.Format("%H:%M:%S");
	m_ed_currenttime.SetWindowText(c_time);
	m_ed_currenttime.SetReadOnly();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSuspendPatDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*
	SUSPENDTIME suspendtime;
	m_suspend_time.GetTime(m_settime);
	CMainFrame* pMainFrame=((CNurseStationApp*)AfxGetApp())->m_pNurseWnd;
	POSITION pos=pMainFrame->GetPatientView()->m_view_paient.GetFirstSelectedItemPosition();
	if(!pos)
	{
		return;
	}
	else
	{
		while(pos)
		{
			int nItem=pMainFrame->GetPatientView()->m_view_paient.GetNextSelectedItem(pos);
			CString logid=pMainFrame->GetPatientView()->GetSelectLogidFromItem(nItem);

			if(logid!=_T(""))
			{
				try
				{
					CADODatabase db;
					db.SetConnectionString(pMainFrame->m_strConn);
					db.Open();

					CString sql=_T("");
					sql.Format(_T("update queue set status='%d' where log_id='%s'"),qsSuspend,logid);
					db.Execute(sql);

					wcscpy(suspendtime.logid,logid.GetBuffer(0));
					suspendtime.suspendtime=m_settime;
					pMainFrame->m_timeMenutex.Lock();
					pMainFrame->m_list_suspendtime.AddTail(suspendtime);
					pMainFrame->m_timeMenutex.Unlock();
					pMainFrame->GetPatientView()->ReviseListCtrPatStatus(logid,qsSuspend);
				}
				catch(_com_error& e)
				{

				}
			}
		}
	}
	*/
	OnOK();
}

void CSuspendPatDlg::WriteFile()
{

}
