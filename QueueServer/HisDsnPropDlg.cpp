// HisDsnPropDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QueueServer.h"
#include "HisDsnPropDlg.h"
#include "../NurseStation/MyCommon.h"
#include "../NurseStation/MyString.h"


// CHisDsnPropDlg �Ի���

IMPLEMENT_DYNAMIC(CHisDsnPropDlg, CPropertyPage)

CHisDsnPropDlg::CHisDsnPropDlg()
	: CPropertyPage(CHisDsnPropDlg::IDD)
	, m_strHisDsn(_T(""))
{

}

CHisDsnPropDlg::~CHisDsnPropDlg()
{
}

void CHisDsnPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DSN, m_strHisDsn);
}


BEGIN_MESSAGE_MAP(CHisDsnPropDlg, CPropertyPage)
	ON_EN_CHANGE(IDC_EDIT_DSN, &CHisDsnPropDlg::OnEnChangeEditDsn)
END_MESSAGE_MAP()


// CHisDsnPropDlg ��Ϣ�������


BOOL CHisDsnPropDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	//
	m_strHisDsn = MyCommon::GetProfileString(
		_T("conn"), _T("DSN"), _T("NurseHisDb"), _T("\\SYS\\hisdb.ini"));

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CHisDsnPropDlg::OnEnChangeEditDsn()
{
	SetModified();
}

BOOL CHisDsnPropDlg::OnApply()
{
	UpdateData();
	MyCommon::WriteProfileString(
		_T("conn"), _T("DSN"), m_strHisDsn, _T("\\SYS\\hisdb.ini"));

	return CPropertyPage::OnApply();
}
