#pragma once


// CPropSocket �Ի���

class CPropSocket : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropSocket)

public:
	CPropSocket();
	virtual ~CPropSocket();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_SOCKET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CString m_strLocalIp;
	CString m_strListenPort;
	afx_msg void OnEnChangeEditListenPort();
	virtual BOOL OnInitDialog();
	virtual BOOL OnApply();
};
