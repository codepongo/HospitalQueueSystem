#pragma once

#include "NurseView.h"
// CMainFrame ���
#include "PoolManage.h"
#include "OfficeQueView.h"
#include "DocInfoView.h"
#include "PaientView.h"
#include "ado2.h"
#include "SearchDataDlg.h"
#include "BaseConfig.h"
#include "ReadCardDlg.h"
//#include "DoctorCallerDlg.h" 
#include <afxmt.h>
#include <afxpriv.h>
//#include "SocketUDPClient.h"
//#include "SocketTCPClient.h"
//#include "SocketClient.h"
#include "ComputeFuncationTime.h"
#include "LCDShow.h"
#include "VisonShowLED.h"

#define ID_CALLNUM  0xE720
#define ID_QUITNUM  0xE721
#define ID_SUSPENDNUM 0xE722
#define ID_ALLNUM   0xE723
#define ID_WAITNUM  0xE724
#define ID_FLUSHTIME 0xE725
#define ID_LOGIN     0xE726
#define MYFLUSHTIME  201411

#define TIMERID_INITLED	0x0402

class CMainFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CMainFrame)
protected:
	CMainFrame();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMainFrame();
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
//	virtual BOOL OnInitDialog();
	
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()


protected:
	
	CMenu m_menu;
	
	CStatusBar m_StatBar;
	CRect m_Rect; 
public:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

	CDocInfoView *m_pDocview;
	CPaientView *m_pPatientview;
	COfficeQueView *m_pOfficeview;
	CNurseView *m_nurse;
	CSplitterWnd m_wndSplit;
	CSplitterWnd m_wndSplit_2;
	//CString m_baseDrive;
	//CString m_baseIP;
	//CString m_baseAccount;
	//CString m_basePassWord;
	CBaseConfig m_BaseConfig;
public:
	
	
	CDocInfoView* GetDocInfoView(){return m_pDocview;}
	CPaientView* GetPatientView(){return m_pPatientview;}
	COfficeQueView* GetOfficeQueView(){return m_pOfficeview;}
	CNurseView* GetNurseView(){return m_nurse;}
	afx_msg void OnFrShowsuspend();
	afx_msg void OnFrShowquit();
	afx_msg void OnFrFlush();
	afx_msg void OnFrShowwaitting();
	afx_msg void OnFrShowcall();

	afx_msg void OnFrCardQue();
	afx_msg void OnFrAutoQue();
//	afx_msg void OnUpdateFrAutoQue(CCmdUI* pCmdUI);

	
	
	CMap<UINT,UINT,UINT,UINT&> m_menuCheckStates;

	//CADODatabase* pbase;
	CString m_strConn;
	//CDoctorCallerDlg* m_pChatDlg;
	
	
	HANDLE m_hSuspendTime;//ʱ������߳�
	HANDLE m_hAutoQue;//�Զ��Ŷ��߳�
//	HANDLE m_hComReadCard;//������Դ
//	HANDLE m_hReadCardThread;//���ſ��߳�
//	HANDLE m_hReadCallerThread;//Ӳ���������߳�
//	HANDLE m_hDoCallerMsgThread;//���崦��Ӳ���������߳�
//	HANDLE m_hDoWndScreenMsgThread;//�����������߳�
	static DWORD WINAPI SuspendTimeThread(LPVOID pParam);//ʱ������߳�
	static DWORD WINAPI WriteDataToMyQueueThread(LPVOID pParam);//�Զ��Ŷ��߳�
//	static DWORD WINAPI ReadCardThread(LPVOID pParam);//�����߳�
//	static DWORD WINAPI ReadCallerThread(LPVOID pParam);//Ӳ���������߳�
//	static DWORD WINAPI DoWndScreenMsgThread(LPVOID pParm);//�����������߳�
//	static DWORD WINAPI DoCallerMsgThread(LPVOID pParam);//���崦��Ӳ���������̺߳���

//	HANDLE m_hComWndScreen;//��������(������)

//	BOOL SendMsgToWndScreen(CString docid,CString msg);
//	BOOL SendMsgToWndScreen(int wndaddress,CString msg);
	
	//BOOL ConnectToBase();
//	long InitReadCard(const int ncom,const int baudRate);//��������
//	long InitWndScreen(const int ncom);//����������(������)
	afx_msg void OnFrReadcard();
	
//	int m_comNum;//ˢ��com��
//	int m_WndCom;//����������
//	BOOL m_WndComNum;
//	int m_baudRate;//������
	CPoolManage m_pool;
//	BOOL m_count;//ˢ����������
	afx_msg void OnFrSearch();

//	void DoCardMsg(char str[],DWORD data_length);
	afx_msg void OnFrOutputdoc();
	afx_msg void OnFrOutputpait();
	CString m_strFileFilter;
	int WriteFileFromPat(CString strFilePath);
	int WriteFileFromDoc(CString strFilePath);

//	void AssicToHex(char *param);
//	void StrToHexes(char *pc,int nsize,char *puc);
//	void DoCallerMsg(char* buf,int size,CADODatabase &threadBase);
//	OVERLAPPED m_ReadOverlapped;

	/*����������*/
	typedef struct _tagWndScreenMsg
	{
		CString		docid;
		CString		strmsg;
	}WNDSCREENMSG,*LPWNDSCREENMSG;

//	CList<WNDSCREENMSG,WNDSCREENMSG&> m_list_wndscreenmsg;

//	CMutex m_wndscreenmutex;//������ԭ����
//	CMutex m_callermutex;

	//Ӳ����������������
//	BOOL AlarmToSystem(int CallerAddress);
	//Ӳ����������ʾʣ������
//	BOOL ShowLastPaintCount(int CallerAddress,int WaitCount);
//	BOOL ShowCallerNum(int CallerAddress,const CString& msg);
	void SqlQueryWait(CADORecordset& rset, WCHAR* wszDoctorID);
	void SqlQueryInLine(CADORecordset& rset, WCHAR* wszDoctorID);

	//��ʾӲ����������ַ
//	void ShowCallerAddress(int CallerAddress);

//	CList<CString,CString&> m_callerMsg;

	BOOL WriteSuspendTimeData();
	CMyGetFile m_getfullfile;
	BOOL ReadSuspendTimeData();
public:
	CList<SUSPENDTIME,SUSPENDTIME&> m_list_suspendtime;
	CMutex m_timeMenutex;

public:
	void AddTrayIcon();
	void RemoveTrayIcon();
	BOOL TaskBarAddIcon(HWND hwnd, UINT uID, HICON hicon, CString strTip);
	BOOL TaskBarDeleteIcon(HWND hwnd, UINT uID);
	afx_msg LRESULT OnTrayIcon(WPARAM wParam, LPARAM lParam);

	afx_msg void OnSubmenuDisplay();
	afx_msg void OnSubmenuQuit();


	void SetWndStausText();
	void FlushStaDataToMemory(CString allnum,
	CString callnum,
	CString quitnum,
	CString suspendnum,
	CString waitnum);

	typedef struct _tagStatusData
	{
		CString allString;
		CString waitString;
		CString suspendString;
		CString callString;
		CString quitString;   
	}STATUSDATA,*LPSTATUSDATA;

	STATUSDATA m_statusData;
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	int m_fushsec;

	CToolBar m_wndToolBar;
	CImageList m_imageList;
	afx_msg void OnToolbarDropDown(NMHDR* pnmtb, LRESULT* plRes);
	afx_msg void OnIconexportDoc();
	afx_msg void OnIconexportPat();
	afx_msg void OnIconqueCard();
	afx_msg void OnIconqueAuto();
	BOOL m_iconCardSelect;
	BOOL m_iconAutoSelect;
	afx_msg void OnIconsusTime();
	afx_msg void OnIconsusNotime();
	afx_msg void OnRecalliconReconsult();
//	afx_msg void OnRecalliconToque();
	afx_msg void OnBnFlush();
	afx_msg void OnBnQue();
	afx_msg void OnBnExport();
	afx_msg void OnBnActive();
	afx_msg void OnBnSuspend();
	afx_msg void OnBnInsert();
	afx_msg void OnBnRecall();
	afx_msg void OnBnQuit();
	afx_msg void OnBnRepeat();
	afx_msg void OnBnSetdoc();
	afx_msg void OnBnSearch();
	afx_msg void OnBnMessage();
	afx_msg void OnBnExchange();
	afx_msg void OnBnShow();
	BOOL m_iconQueCheck;
	BOOL m_iconExportCheck;
	BOOL m_iconSuspendCheck;
	BOOL m_iconRecall;
	void SearchDoNum();


	/***********************�Ŷ��߼�********************/
	BOOL WriteDataToMyQueue();
//	CADORecordset* m_pre;
	/***************************************************/
	
	//����HIS���ݿ����
//	CADODatabase* m_phisDataBase;
	/***********************����HIS���ݿ�******************/
//	BOOL ConnectToHis();
	/******************************************************/
	/*******��his���ݿ��HisForBjlb_Patient�ж����ݷ���HisForBjlb_Patient****/
//	HANDLE m_hFlushHis;
//	static DWORD WINAPI FlushHisToMyTable(LPVOID pParam);
	/***************************************************************************/

	afx_msg void OnItemAbout();

//	CDoWndScreen m_doWndScreen;
	//����ͨ��udp
	//SocketClient *m_pDoThroughScreenUDP;
	//SocketTCPClient *m_pDoThroughScreenTCP;

	typedef struct _tagDocToAdd
	{
		int address;
		int comprehAddress;
		CString through_screen_ip;
		int through_screen_id;
	}DOCTOADD,*LPDOCTOADD;

	CMap<CString,LPCWSTR,DOCTOADD,DOCTOADD&> m_map_doctoadd;
	void SearchDocToadd();

	CMutex m_prePreLock;
	//�Խ�û��office_idֻ���ĳ��
	CString m_officeId;
	void SearChFirstOffice();

public:
	afx_msg LRESULT OnRevReRunMsg(WPARAM wParam, LPARAM lParam);

	CComputeFuncationTime m_computeTime;

//	CList<CString,LPCWSTR> m_ReciveMsg;

//	CString m_lastMsg;//�������ϴ�û�������Ϣ����
	afx_msg void OnFrUiflush();
	int m_originFlushTime;

	CLCDShow *m_pLCDShowDlg;
	afx_msg void OnFrPrint();
	afx_msg void OnFrCompset();
	afx_msg void OnItemExit();
	afx_msg void OnIconMenuShow();
	afx_msg void OnIconMenuExit();
	afx_msg void OnTakeNumConf();

//	BOOL ReturnToHCaller(CString strDoctorId);
	void InitThroughWnd();//��ʼ��ͨ������ȡͨ������
	afx_msg void OnConfig();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL DestroyWindow();
public:
	CVisonShowLED* m_pVisonShowLED;
	afx_msg LRESULT OnLedNotfiyMessage(WPARAM wParam,LPARAM lParam);

	static UINT InitLEDThreadProc(LPVOID pParam);
};

//


