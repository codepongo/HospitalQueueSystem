#pragma once
#include "afxwin.h"


// CDlgQueueChange �Ի���

class CDlgQueueChange : public CDialog
{
	DECLARE_DYNAMIC(CDlgQueueChange)

public:
	CDlgQueueChange(CString strConn, CString strDoctorId, CString strNurseId, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgQueueChange();

// �Ի�������
	enum { IDD = IDD_DIALOG_QUEUE_CHANGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CString m_strConn;
	CString m_strDoctorId;
	CString m_strNurseId;

	void RefreshQueue();
	CListBox m_lbSelectQueue;
	CListBox m_lbAllQueue;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonRemove();

	CString m_strSqlSelQueue;
	CString m_strSqlAllQueue;
	CMap<int,int,CString,LPCTSTR> m_mapSelQueue;
	CMap<int,int,CString,LPCTSTR> m_mapAllQueue;
};
