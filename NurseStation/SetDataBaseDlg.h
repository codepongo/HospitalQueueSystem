#pragma once

#include "BaseConfig.h"
// CSetDataBaseDlg �Ի���
//#include "ConnectToBase.h"
class CSetDataBaseDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetDataBaseDlg)

public:
	CSetDataBaseDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetDataBaseDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SETDATABASE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_set_account;
	CString m_set_pass;
	CString m_set_serverip;
	//CString m_set_database;
	CBaseConfig m_baseconfig;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
//	CConnectToBase m_connecttobase;
	//int m_selectbase;
	afx_msg void OnBnClickedButtonInitDb();
};
