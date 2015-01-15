// PropPageDoctorPassword.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DoctorCaller.h"
#include "PropPageDoctorPassword.h"


// CPropPageDoctorPassword �Ի���

IMPLEMENT_DYNAMIC(CPropPageDoctorPassword, CPropertyPage)

CPropPageDoctorPassword::CPropPageDoctorPassword(CString strDoctorId, CString strDbConn)
	: CPropertyPage(CPropPageDoctorPassword::IDD)
	, m_strId(strDoctorId)
	, m_strDbConn(strDbConn)
	, m_strOldPassword(_T(""))
	, m_strNewPassword(_T(""))
	, m_strConfirm(_T(""))
	, m_bChanged(FALSE)
{

}

CPropPageDoctorPassword::~CPropPageDoctorPassword()
{
}

void CPropPageDoctorPassword::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OLD_PASSWORD, m_strOldPassword);
	DDX_Text(pDX, IDC_EDIT_NEW_PASSWORD, m_strNewPassword);
	DDX_Text(pDX, IDC_EDIT_NEW_PASSWORD_COMFIRM, m_strConfirm);
}


BEGIN_MESSAGE_MAP(CPropPageDoctorPassword, CPropertyPage)
	ON_EN_CHANGE(IDC_EDIT_NEW_PASSWORD, &CPropPageDoctorPassword::OnEnChangeEditNewPassword)
END_MESSAGE_MAP()


// CPropPageDoctorPassword ��Ϣ�������

BOOL CPropPageDoctorPassword::OnApply()
{
	if(m_bChanged)
	{
		m_bChanged = FALSE;

		UpdateData(TRUE);

		try
		{
			CADODatabase db;
			db.SetConnectionString(m_strDbConn);
			db.Open();
			CString strSelect;
			strSelect.Format(_T("SELECT password FROM Doctor WHERE doctor_id='%s';"), 
				m_strId);
			CADORecordset rset(&db);
			rset.Open(strSelect, CADORecordset::openQuery);
			if(rset.IsBOF())
			{
				MessageBox(_T("��ǰ�ʺ��ѱ�ɾ��!"), _T("����"));
				return FALSE;
			}
			CString strPasswd;
			rset.GetFieldValue(0, strPasswd);
			rset.Close();
			if(strPasswd != m_strOldPassword)
			{
				MessageBox(_T("ԭ���벻��ȷ!"), _T("����"));
				return FALSE;
			}
			if(m_strNewPassword.IsEmpty())
			{
				MessageBox(_T("���벻��Ϊ�գ�"),_T("����"));
				return FALSE;
			}
			if(m_strConfirm != m_strNewPassword)
			{
				MessageBox(_T("������ȷ�ϲ�һ��!"), _T("����"));
				return FALSE;
			}
			CString strUpdate;
			strUpdate.Format(_T("UPDATE Doctor SET password='%s' WHERE doctor_id='%s';"), 
				m_strNewPassword, m_strId);
			db.Execute(strUpdate);
			db.Close();
		}
		catch (_com_error& e)
		{
			MessageBox(_T("���ݿ����!"), _T("����"));
			return FALSE;
		}

		m_strOldPassword = m_strNewPassword;
		UpdateData(FALSE);
	}

	return CPropertyPage::OnApply();
}

void CPropPageDoctorPassword::OnEnChangeEditNewPassword()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	SetModified();
	m_bChanged = TRUE;
}
