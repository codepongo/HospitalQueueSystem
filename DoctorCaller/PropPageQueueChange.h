#pragma once
#include "afxwin.h"


// CPropPageQueueChange �Ի���

class CPropPageQueueChange : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropPageQueueChange)

public:
	CPropPageQueueChange(CString strDoctorId, CString strConn, CString strNurseId);   // ��׼���캯��
	virtual ~CPropPageQueueChange();

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
	virtual BOOL OnApply();
};
