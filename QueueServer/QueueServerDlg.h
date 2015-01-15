// QueueServerDlg.h : ͷ�ļ�
//

#pragma once
#include "PropSetting.h"
//#include "ServerController.h"
#include "ReadHis.h"


// CQueueServerDlg �Ի���
class CQueueServerDlg : public CDialog
{
// ����
public:
	CQueueServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_QUEUESERVER_DIALOG };

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
	afx_msg void OnBnClickedButtonConf();

//	CPropSetting* m_pProSheet;
//	BOOL m_bProSheet;
	//�̴߳�����
	//CReadHisData   m_readHisData;
	//CReadHisDoctor m_readHisDoctor;
	//CReadHisOffice m_readHisOffice;

	afx_msg void OnBnClickedButtonRestart();
	afx_msg void OnClose();
	afx_msg void OnMenuitemShow();
	afx_msg void OnMenuitemConf();

	BOOL TaskBarAddIcon(HWND hwnd, UINT uID, HICON hicon, LPCWSTR lpszTip);
	void AddTrayIcon();
	//LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTrayIcon(WPARAM wParam, LPARAM lParam);
	BOOL TaskBarDeleteIcon(HWND hwnd, UINT uID);
	void RemoveTrayIcon();
	afx_msg void OnMenuitemRestart();
	afx_msg void OnMenuitemQuit();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonHide();
	afx_msg void OnBnClickedButtonQuit();

	//CServerController m_ServerController;
	CReadHis m_ReadHis;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNcPaint();
};
