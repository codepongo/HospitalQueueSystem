// PropConnectToHisSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "NurseStation.h"
#include "MyDbPropDlg.h"
#include "../NurseStation/MyCommon.h"
#include "../NurseStation/MyString.h"
#include "InitLocalDbDlg.h"


// CMyDbPropDlg �Ի���

IMPLEMENT_DYNAMIC(CMyDbPropDlg, CPropertyPage)

CMyDbPropDlg::CMyDbPropDlg()
	: CPropertyPage(CMyDbPropDlg::IDD)
	, m_strUID(_T(""))
	, m_strPWD(_T(""))
	, m_strHostIP(_T(""))
{

}

CMyDbPropDlg::~CMyDbPropDlg()
{
}

void CMyDbPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UID, m_strUID);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPWD);
	DDX_Text(pDX, IDC_EDIT_HOST, m_strHostIP);
}


BEGIN_MESSAGE_MAP(CMyDbPropDlg, CPropertyPage)
	ON_EN_CHANGE(IDC_EDIT_UID, &CMyDbPropDlg::OnEnChangeEditMyaccount)
	ON_EN_CHANGE(IDC_EDIT_PWD, &CMyDbPropDlg::OnEnChangeEditMypass)
	ON_EN_CHANGE(IDC_EDIT_HOST, &CMyDbPropDlg::OnEnChangeEditMyip)
	ON_BN_CLICKED(IDC_BUTTON_INIT_DB, &CMyDbPropDlg::OnBnClickedButtonInitDb)
END_MESSAGE_MAP()


// CMyDbPropDlg ��Ϣ�������

BOOL CMyDbPropDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	//
	m_strUID = MyCommon::GetProfileString(
		_T("conn"), _T("UID"), _T("sa"), _T("\\SYS\\mydb.ini"));
	m_strPWD = MyCommon::GetProfileString(
		_T("conn"), _T("PWD"), _T("123456"), _T("\\SYS\\mydb.ini"));
	m_strHostIP = MyCommon::GetProfileString(
		_T("conn"), _T("SERVER"), _T("127.0.0.1"), _T("\\SYS\\mydb.ini"));

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CMyDbPropDlg::OnEnChangeEditMyaccount()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	SetModified();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CMyDbPropDlg::OnEnChangeEditMypass()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	SetModified();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CMyDbPropDlg::OnEnChangeEditMyip()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	SetModified();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

BOOL CMyDbPropDlg::OnApply()
{
	// TODO: �ڴ����ר�ô����/����û���
	UpdateData();

	MyCommon::WriteProfileString(
		_T("conn"), _T("UID"), m_strUID, _T("\\SYS\\mydb.ini"));
	MyCommon::WriteProfileString(
		_T("conn"), _T("SERVER"), m_strHostIP, _T("\\SYS\\mydb.ini"));
	MyCommon::WriteProfileString(
		_T("conn"), _T("PWD"), m_strPWD, _T("\\SYS\\mydb.ini"));

	return CPropertyPage::OnApply();
}

void CMyDbPropDlg::OnBnClickedButtonInitDb()
{
	//CInitLocalDbDlg dlg;
	//dlg.DoModal();
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
		m_strHostIP, m_strUID, m_strPWD, strFilePath);

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

