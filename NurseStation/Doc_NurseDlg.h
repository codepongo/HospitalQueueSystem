// Doc_NurseDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "PropSetting.h"
#include "ConnectToBase.h"
#include "PoolManage.h"
#include "NurseView.h"
#include "MainFrm.h"
#include "SetDataBaseDlg.h"
#include "Account.h"
#include "MyGetFile.h"
//#include "NurseDef.h"
#include "afxcmn.h"
#include "LoginController.h"

#define MYLOGINTIMEID			2013

// CDoc_NurseDlg �Ի���
class CDoc_NurseDlg : public CDialog, public CLoginController
{
// ����
public:
	CDoc_NurseDlg(CWnd* pParent = NULL);	// ��׼���캯��
	
// �Ի�������
	enum { IDD = IDD_DOC_NURSE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_checkBack;
	afx_msg void OnBnClickedOk();

	
	//CADODatabase* pbase;
	CBaseConfig m_baseconfig;
	CString m_loadNurseID;
	CString m_loadNursePassword;
	CString m_loadNurseName;
	CPoolManage m_pool;

//	CString m_strIP;
	CMainFrame* pWnd;
	BOOL ConnectToBase();
	CString m_baseIp;
	CString m_basePassword;
	CString m_baseDrive;
	CString m_baseAccount;
	
	CButton m_checkReque;
	afx_msg void OnBnClickedBnBaseset();
//	CString GetLoginID(){return m_loadNurseID;}
//	CString GetLoginNursename(){return m_loadNurseName;}
	afx_msg void OnDestroy();
	//std::vector<CString> m_canDoOfficeIDList;
	void GetNurseCandoOfficeID();
	void DeleteDayData();//ɾ�������Ŷӵ�����
	
	CComboBoxEx m_combo_userlogin;
	BOOL WriteUserIdToFile();
	CMyGetFile m_mygetfile;

	/*�û�����Ϣ*/
	typedef struct _tagLoginUserInfo
	{
		WCHAR       loginID[MAX_ID_LENGTH];
		CTime       loginTime;
		int			status;
		WCHAR       password[MAX_PASSWORD_LENGTH];
		int         power;
	}LOGINUSERINFO,*LPLOGINUSERINFO;

	CList<LOGINUSERINFO,LOGINUSERINFO&> m_login_info;
	BOOL ReadUserIdFromFile();
	BOOL AddStringToComBo();
	CButton m_check_rempass;
	CButton m_check_autologin;
	void SetLastLoginShow();
	CImageList *m_pImageList;
	afx_msg void OnCbnEditchangeComboUsername();
	afx_msg void OnCbnSelchangeComboUsername();
	CProgressCtrl m_progress_login;
	CButton m_bn_baseset;
	void LoginToNurse();
	CEdit m_edit_password;
	CStatic m_static_userid;
	CStatic m_static_password;
	CButton m_bn_login;
	BOOL m_bShow;
	CStatic m_show_static_userid;
	CFont m_font;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void MySetLoginText(CString str);
	int m_range;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	BOOL MyInitLoginInfoDataBase();
	BOOL MyInitSetLoginText();
	BOOL MyInitLoginPictrue();
	HANDLE m_hCheckDataBase;//�������ݿ��߳�
	static DWORD WINAPI CheckDataBase(LPVOID pParam);//�������ݿ��߳�

	BOOL m_bIsConnect;
	BOOL m_bIsCreate;
	BOOL m_bSetShowText;
	CStatic m_show_picture;
	BOOL ShowLoginBitmap();
	BOOL m_bshowpicture;
	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	BOOL DrawBack(CDC* pDC,CRect& destRect);
	CRect m_rect;
	afx_msg void OnSize(UINT nType, int cx, int cy);

private:
	virtual void OnRecvLoginResult(LPCMDRESULT pLoginResult, LPSOCKADDR_IN psockddr);
	virtual void OnSendVerify();

	BOOL m_bCanLogin;
	CString m_strConn;


	//����HIS���ݿ����
//	CADODatabase* m_phisDataBase;
	/***********************����HIS���ݿ�******************/
//	BOOL ConnectToHis();
	/******************************************************/
//	HANDLE m_hCheckHisDataBase;//����HIS���ݿ��߳�
//	static DWORD WINAPI CheckHisDataBase(LPVOID pParam);//����HIS���ݿ��߳�
};


//////// End Modify ////////////////////////////