#pragma once


// CTextModifyDlg �Ի���

class CTextModifyDlg : public CDialog
{
	DECLARE_DYNAMIC(CTextModifyDlg)

public:
	CTextModifyDlg(CString& strTextRef, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTextModifyDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_TEXT_MODIFY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strText;
	CString& m_rstrText;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
