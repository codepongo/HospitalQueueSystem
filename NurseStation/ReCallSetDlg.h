#pragma once
#include "afxwin.h"
#include "PoolManage.h"

// CReCallSetDlg �Ի���

class CReCallSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CReCallSetDlg)

public:
	CReCallSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReCallSetDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_RECALLQUE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void SearchOffice();
	void SetName_Que();
	CEdit m_ed_paitname;
	CEdit m_ed_lastque;
	CComboBox m_com_setque;
	afx_msg void OnBnClickedOk();
	CPoolManage m_pool;
};
