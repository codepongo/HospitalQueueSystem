#pragma once


// CInitLocalDbDlg �Ի���

class CInitLocalDbDlg : public CDialog
{
	DECLARE_DYNAMIC(CInitLocalDbDlg)

public:
	CInitLocalDbDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInitLocalDbDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_INIT_LOCAL_DB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strUID;
	CString m_strPWD;
	CString m_strHostIP;
	afx_msg void OnEnChangeEditUid();
	afx_msg void OnEnChangeEditPwd();
	afx_msg void OnEnChangeEditHost();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
