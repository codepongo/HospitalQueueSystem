#pragma once
#include "afxwin.h"
#include "PoolManage.h"
#include "BaseConfig.h"
#include "com/ComInit.h"
// CReadCardDlg �Ի���


class CReadCardDlg : public CDialog
{
	DECLARE_DYNAMIC(CReadCardDlg)

public:
	CReadCardDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReadCardDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_READCARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_com_comnum;
	CComboBox m_com_baudrate;
//	CEdit m_test_countex;
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboComnum();
//	long InitReadCard(const int ncom,const int baudRate);

	
	
	CPoolManage m_pool;
//	int m_selectCom;//ˢ��������
//	int m_selectBaudRate;//������
//	int m_selectWndCom;//������
//	int GetSelectCom(){return m_selectCom;}
//	int GetSelectBaudRate(){return m_selectBaudRate;}

	afx_msg void OnCbnSelchangeComboBaudrate();
	
	
	CBaseConfig m_baseconfig;
	
	
	CComboBox m_com_wndscrren;
	afx_msg void OnCbnSelchangeComWndscreen();
	CString m_ed_wndaddress;
	afx_msg void OnBnClickedBnSend();
	CString m_cs_msg;
private:
	CComInit* m_pComInit;
};
