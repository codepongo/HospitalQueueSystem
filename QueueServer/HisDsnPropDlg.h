#pragma once

#include "resource.h"
// CHisDsnPropDlg �Ի���

class CHisDsnPropDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CHisDsnPropDlg)

public:
	CHisDsnPropDlg();
	virtual ~CHisDsnPropDlg();

// �Ի�������
	enum { IDD = IDD_PROP_HIS_DSN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL OnInitDialog();
	virtual BOOL OnApply();

	DECLARE_MESSAGE_MAP()

public:
	CString m_strHisDsn;

	afx_msg void OnEnChangeEditDsn();
};
