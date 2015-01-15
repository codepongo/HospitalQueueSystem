#pragma once
#include "afxwin.h"
#include "BaseConfig.h"
#include "ado2.h"
#include "PoolManage.h"
// CSetDoctorDialog �Ի���

class CSetDoctorDialog : public CDialog
{
	DECLARE_DYNAMIC(CSetDoctorDialog)

public:
	CSetDoctorDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetDoctorDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_SETDOCTOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	CEdit m_ct_lastname;
//	CString m_cs_lastname;
//	CEdit m_ct_lastdoc;
//	CString m_cs_lastdoc;
	CComboBox m_com_setdoc;
	virtual BOOL OnInitDialog();

	CString m_baseDrive;
	CString m_baseIP;
	CString m_baseAccount;
	CString m_basePassWord;
	CBaseConfig m_BaseConfig;

	BOOL ConnectToBase();

	CADODatabase* pbase;
	void SearchDoctor();
	afx_msg void OnBnClickedOk();
	CPoolManage m_pool;

//	void DataSend();
	CMap<int,int,DOCTOCOMBOINFO,DOCTOCOMBOINFO&> m_map_doctor;

	CString GetSelectDoctorId();
};
