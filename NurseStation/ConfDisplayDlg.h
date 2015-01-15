#pragma once
#include "afxwin.h"
#include "DoctorManageDlg.h"
#include "MyListBox.h"



// CConfDisplayDlg �Ի���

class CConfDisplayDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfDisplayDlg)

public:
	CConfDisplayDlg(CString& strConf, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CConfDisplayDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_DISPLAY_CALL_CONF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editTextAdd;
	//CListBox m_lbList;
	CMyListBox m_mylbList;
	CComboBox m_combColor;
	afx_msg void OnBnClickedButtonAddText();
	afx_msg void OnBnClickedButtonQueueId();
	afx_msg void OnBnClickedButtonPatientName();
	afx_msg void OnBnClickedButtonDoctorName();
	afx_msg void OnBnClickedButtonOfficeName();
	afx_msg void OnBnClickedButtonConsultName();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonDelete();

	afx_msg void OnCbnSelchangeComboColor();
	afx_msg void OnLbnSelchangeListStrConf();

	afx_msg void OnBnClickedButtonTest();

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	int SplitColorStringToArray(CString strSrc, CArray<CString>& arrStr);
public:
	//CDoctorManageDlg* m_pParentDlg;
	//CADORecordset* m_pRset;
	CString& m_strConf;
	//afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//CArray<COLORTEXT*> m_PtrArr; 
	afx_msg void OnBnClickedButtonPatientGender();
	afx_msg void OnBnClickedButtonPatientAge();
	afx_msg void OnBnClickedButtonModify();
};
