#pragma once
#include "afxwin.h"


// CAddCommentDlg �Ի���

class CAddCommentDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddCommentDlg)

public:
	CAddCommentDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddCommentDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_ADD_COMMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CString GetComment(){return m_strComment;}
private:
	CString m_strComment;
public:
	//int m_nRdSelectComment;
	CComboBox m_cbComment;
	//CString m_strSelfComment;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
