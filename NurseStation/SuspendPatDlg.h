#pragma once
#include "afxdtctl.h"
#include "afxwin.h"


// CSuspendPatDlg �Ի���

class CSuspendPatDlg : public CDialog
{
	DECLARE_DYNAMIC(CSuspendPatDlg)

public:
	CSuspendPatDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSuspendPatDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SUSPEND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
//	CDateTimeCtrl m_last_datetime;
	CEdit m_ed_currenttime;
	CTime m_settime;
	CTime m_current_time;
	CDateTimeCtrl m_suspend_time;
	afx_msg void OnBnClickedOk();
	void WriteFile();
};
