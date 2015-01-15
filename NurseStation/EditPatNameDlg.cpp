// EditPatNameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NurseStation.h"
#include "EditPatNameDlg.h"
#include "WriteLog.h"


// CEditPatNameDlg �Ի���

IMPLEMENT_DYNAMIC(CEditPatNameDlg, CDialog)

CEditPatNameDlg::CEditPatNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditPatNameDlg::IDD, pParent)
{

}

CEditPatNameDlg::~CEditPatNameDlg()
{
}

void CEditPatNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ED_OLDNAME, m_ed_oldName);
	DDX_Control(pDX, IDC_ED_NEWNAME, m_ed_newName);
}


BEGIN_MESSAGE_MAP(CEditPatNameDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CEditPatNameDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CEditPatNameDlg ��Ϣ�������

BOOL CEditPatNameDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ASSERT(GetParent());
	CString name = theApp.m_pPaientView->GetSelectPaitname();
	m_ed_oldName.SetWindowText(name);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CEditPatNameDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString logid = theApp.m_pPaientView->GetSelectLogid();
	CString newName;
	m_ed_newName.GetWindowText(newName);
	CString updateSql;
	updateSql.Format(_T("update queue set patient_name='%s' where log_id='%s'"),newName,logid);
	try
	{
		CADODatabase db;
		db.SetConnectionString(theApp.m_pNurseWnd->m_strConn);
		db.Open();
		db.Execute(updateSql);
		theApp.m_pPaientView->ReviseListCtrPatName(logid,newName);
		db.Close();
	}
	catch(_com_error& e)
	{
		WriteLog::WriteDbErrLog(_T("CEditPatNameDlg::OnBnClickedOk()"));
	}
	OnOK();
}
