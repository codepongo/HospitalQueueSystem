#pragma once
#include "afxwin.h"


// CEditPatNameDlg �Ի���

class CEditPatNameDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditPatNameDlg)

public:
	CEditPatNameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEditPatNameDlg();

// �Ի�������
	enum { IDD = IDD_EDITNAME_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_ed_oldName;
	CEdit m_ed_newName;
	afx_msg void OnBnClickedOk();
};
