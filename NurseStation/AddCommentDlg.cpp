// AddCommentDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NurseStation.h"
#include "AddCommentDlg.h"


// CAddCommentDlg �Ի���

IMPLEMENT_DYNAMIC(CAddCommentDlg, CDialog)

CAddCommentDlg::CAddCommentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddCommentDlg::IDD, pParent)
	//, m_nRdSelectComment(0)
	//, m_strSelfComment(_T(""))
{

}

CAddCommentDlg::~CAddCommentDlg()
{
}

void CAddCommentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Radio(pDX, IDC_RADIO_COMMENT_SELECT, m_nRdSelectComment);
	DDX_Control(pDX, IDC_COMBO_COMMENT, m_cbComment);
	//DDX_Text(pDX, IDC_EDIT_COMMENT, m_strSelfComment);
}


BEGIN_MESSAGE_MAP(CAddCommentDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAddCommentDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddCommentDlg ��Ϣ�������

BOOL CAddCommentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cbComment.AddString(_T(""));
	m_cbComment.AddString(_T("����"));
	m_cbComment.AddString(_T("����"));
	m_cbComment.AddString(_T("ԤԼ"));
	m_cbComment.AddString(_T("��Լ"));
	m_cbComment.AddString(_T("סԺ"));
	//m_cbComment.AddString(_T("�����ٻ�"));
	m_cbComment.SetCurSel(0);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CAddCommentDlg::OnBnClickedOk()
{
	UpdateData();
	//m_cbComment.GetLBText(
	//	m_cbComment.GetCurSel(), m_strComment);
	m_cbComment.GetWindowText(m_strComment);
	OnOK();
}
