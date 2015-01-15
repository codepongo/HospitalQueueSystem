// TextModifyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NurseStation.h"
#include "TextModifyDlg.h"


// CTextModifyDlg �Ի���

IMPLEMENT_DYNAMIC(CTextModifyDlg, CDialog)

CTextModifyDlg::CTextModifyDlg(CString& strTextRef, CWnd* pParent /*=NULL*/)
	: CDialog(CTextModifyDlg::IDD, pParent)
	, m_rstrText(strTextRef)
	, m_strText(_T(""))
{
}

CTextModifyDlg::~CTextModifyDlg()
{
}

void CTextModifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_strText);
}


BEGIN_MESSAGE_MAP(CTextModifyDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CTextModifyDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CTextModifyDlg ��Ϣ�������

void CTextModifyDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	m_rstrText = m_strText;
	OnOK();
}

BOOL CTextModifyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_strText = m_rstrText;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
