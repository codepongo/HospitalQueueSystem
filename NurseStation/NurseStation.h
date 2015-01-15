// NurseStation.h : NurseStation Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "stdafx.h"
#include "resource.h"		// ������
#include "ConnectToBase.h"
#include "MainFrm.h"
#include "Doc_NurseDlg.h"
#include "DocInfoView.h"
#include "JttsAPI.h"
#include "PoolManage.h"
#include "UserSetting.h"
#include "OfficeQueView.h"
#include "PaientView.h"
#include "PropQueSettting.h"
#include "NurseController.h"


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

// CNurseStationApp:
// �йش����ʵ�֣������ NurseStation.cpp
//

class CNurseStationApp : public CWinApp
{
public:
	CNurseStationApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:

	CNurseController* GetController()
	{
		return m_pNurseController;
	}

public:
	CMainFrame* m_pNurseWnd;
	CDocInfoView* m_pDocInfoView;
	COfficeQueView* m_pOfficeQueView;
	CPaientView*   m_pPaientView;
	CNurseView*    m_pNurseView;
	//CJttsAPI* m_pJttsAPI;

//	BOOL m_IsFront;
	CString m_loadNurseID;//��¼��ʿid
	CString m_loadNursePassword;//����
	CString m_loadNurseName;//��ʿ����
	CArray<CString> m_canDoOfficeIDList;
	int m_power;//Ȩ��
	CString m_strIP;//��¼ip
	int GetUserPower(){return m_power;}
	CString GetLoginID(){return m_loadNurseID;}
	CString GetLoginNursename(){return m_loadNurseName;}

	//CDoctorCallerDlg* m_pChatDlg;
	CUserSetting* m_pUserSetting;
	CPropQueSettting* m_pPropQueSetting;
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
	CPropSetting* m_pPropSetting;

	//BOOL VerifySerialNo();
	//BOOL ReadSerialNo(CString& strSerialNo);
	BOOL m_backSet;

	virtual BOOL PreTranslateMessage(MSG* pMsg);


public:
	//BOOL OpenDB(CADODatabase &db);
	//BOOL AddAutoRun(CString strValueName);

private:
	CNurseController* m_pNurseController;
};

extern CNurseStationApp theApp;

#ifdef _DEBUG

extern void MyWriteConsole(CString str);

#endif
//extern int g_nDataDays;