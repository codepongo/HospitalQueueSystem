#pragma once


// CPropPageDoctorPassword �Ի���

class CPropPageDoctorPassword : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropPageDoctorPassword)

public:
	CPropPageDoctorPassword(CString strDoctorId, CString strDbConn);
	virtual ~CPropPageDoctorPassword();

// �Ի�������
	enum { IDD = IDD_DIALOG_MODIFY_DOCTOR_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CString m_strOldPassword;
	CString m_strNewPassword;
	CString m_strConfirm;

	CString m_strId;
	CString m_strDbConn;
	virtual BOOL OnApply();
	afx_msg void OnEnChangeEditNewPassword();

	BOOL m_bChanged;
};
