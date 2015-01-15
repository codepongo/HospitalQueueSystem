// SetDataBaseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NurseStation.h"
#include "SetDataBaseDlg.h"
#include "MyString.h"
#include "MyCommon.h"

// CSetDataBaseDlg �Ի���

IMPLEMENT_DYNAMIC(CSetDataBaseDlg, CDialog)

CSetDataBaseDlg::CSetDataBaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDataBaseDlg::IDD, pParent)
	, m_set_account(_T(""))
	, m_set_pass(_T(""))
	, m_set_serverip(_T(""))
	//, m_selectbase(0)
{

}

CSetDataBaseDlg::~CSetDataBaseDlg()
{
}

void CSetDataBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ED_SETACCOUNT, m_set_account);
	DDX_Text(pDX, IDC_ED_SETPASS, m_set_pass);
	DDX_Text(pDX, IDC_ED_SETSERVERIP, m_set_serverip);
	//DDX_Radio(pDX, IDC_RADIO_ORACLE, m_selectbase);
}


BEGIN_MESSAGE_MAP(CSetDataBaseDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CSetDataBaseDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_INIT_DB, &CSetDataBaseDlg::OnBnClickedButtonInitDb)
END_MESSAGE_MAP()


// CSetDataBaseDlg ��Ϣ�������

BOOL CSetDataBaseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_set_account=m_baseconfig.GetServerAcount();
	m_set_pass=m_baseconfig.GetServerPassword();
	m_set_serverip=m_baseconfig.GetServerIP();
	//m_set_database=m_baseconfig.GetDataDrive();
	//if(m_set_database==_T("SQL Server"))
	//{
	//	m_selectbase=1;
	//}
	//if(m_set_database==_T("Oracle"))
	//{
	//	m_selectbase=0;
	//}
	//if(m_set_database==_T("MySQL"))
	//{
	//	m_selectbase=2;
	//}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSetDataBaseDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	m_baseconfig.SetServerAcount(m_set_account);
	m_baseconfig.SetServerIP(m_set_serverip);
	m_baseconfig.SetServerPassword(m_set_pass);
	//CString name=_T("");
	//if(m_selectbase==0)
	//{
	//	name=_T("Oracle");
	//}
	//else if(m_selectbase==1)
	//{
	//	name=_T("SQL Server");
	//}
	//else if(m_selectbase==2)
	//{
	//	name=_T("MySQL");
	//}
	//m_baseconfig.SetDataDrive(name);
	m_baseconfig.SetDataDrive(_T("SQL Server"));
	m_baseconfig.Save();
	OnOK();
}

void CSetDataBaseDlg::OnBnClickedButtonInitDb()
{
	int nRet = MessageBox(_T("ȷ�ϳ�ʼ�����ݿ���"), _T("���ݿ��ʼ��"), MB_OKCANCEL|MB_ICONWARNING|MB_DEFBUTTON2);
	if(nRet != IDOK) return;

	UpdateData(TRUE);

	CString strFilePath = MyCommon::GetModuleDir();
	strFilePath += _T("db.sql");
	if(!MyCommon::PathFileExist(strFilePath))
	{
		MessageBox(_T("���ݿ�ű��ļ�db.sqlȱʧ��"), _T("���ݿ��ʼ��"), MB_ICONERROR);
		return;
	}

	CString strParam;
	strParam.Format(_T("-S %s -U %s -P %s  -i \"%s\""), 
		m_set_serverip, m_set_account, m_set_pass, strFilePath);

	HINSTANCE hInst = ::ShellExecute(NULL, _T("open"), _T("osql"), strParam, NULL, SW_HIDE);

	if((int)hInst <= 32)
	{
		MessageBox(_T("����ȱ�� SQL SERVER �ͻ���������޷�ִ��osql���"), 
			_T("���ݿ��ʼ��"), MB_ICONERROR);
		return;
	}

	MessageBox(_T("���ݿ��ʼ����ɣ�"), 
		_T("���ݿ��ʼ��"));
}
