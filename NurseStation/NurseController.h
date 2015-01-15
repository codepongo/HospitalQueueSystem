#pragma once

#include "QueueController.h"
#include "ado2.h"
#include "NurseDef.h"
//#include "SockDef.h"
#include "afxmt.h"
//#include "MySocketUDP.h"
//#include "afxsock.h"
#include "JttsAPI.h"

/*ҽ������ʱ������Ϣ*/
typedef struct _tagDoctorBasicInfo
{
	CString			strDoctorID;
	CString			strDoctorName;
	CString			strOfficeID;
	CString			strOfficeName;
	CString			strConsultID;
	CString			strConsultName;
	CString			strSoundCall;
	CString			strSoundWait;
	CString			strDisplayCall;
	CString			strDisplayWait;
	int				iMaxRecallTimes;
	int				iWndScreenId;
	int				iEvaluatorId;
	CString			strConsultStbId;
	BOOL			bExpertFlag;
	CString			strTitle;
	int				iWaitNum;
	BOOL			bWaitWhenCall;
	int				iCompLED;
	int				iThroughLED;
	int				iCallerId;
}DOCTORBASICINFO, *LPDOCTORBASICINFO;

/*���ﻼ����Ϣ*/
typedef struct _tagCallPatientInfo
{
	CString			strSerialID;
	CString			strQueueID;
	CString			strPatientName;
	GenderEnum	eGender;
	CString			strBirth;
	int					iStatus;
	DOCTORBASICINFO sDoctorBasicInfo;
}CALLPATIENTINFO, *LPCALLPATIENTINFO;

typedef struct {
	CString strSerialID;
	CString strPatientName;
	CString strOfficeID;
	CString strDoctorID;
	CString strDoctorName;
	CString strConsultName;
} VIEWUPDATEINFO, *LPVIEWUPDATEINFO;

typedef struct {
	CString strQueueId;
	CString strPatientName;
	CString strDoctorName;
	CString strConsultName;
} STBINFO, *LPSTBINFO;

typedef struct {
	CString strStbId;
	CString strDepartName;
	CString strConsultName;
	CString strDoctorName;
	CString strDoctorId;
	CString strDoctorTitle;
	CString strCallPatient;
	CString strWaitPatient;
} CONSULTSTB, *LPCONSULTSTB;

/**/
typedef enum _tagCoverTypeEnum
{
	covtSoundCall		= 0,			//ת�����������ַ���
	covtSoundWait		= 1,			//ת��׼�������ַ���
	covtDisplayCall		= 2,			//ת��������ʾ�ַ���
	covtDisplayWait		= 3				//ת��׼����ʾ�ַ���
}CoverTypeEnum;

class CNurseController : public CQueueController
{
public:
	CNurseController(void);
	virtual ~CNurseController(void);

	BOOL SendCmd(CString strDoctorID, CString strSerialID, DoctorCmdEnum eDoctorCmdEnum);

private:

	virtual BOOL OnStartControl();
	virtual BOOL OnEndControl();

	virtual void OnRecvCmdResult(LPCMDRESULT pCmdResult, LPSOCKADDR_IN psockddr);
	virtual void OnRecvReqLogin(LPREQLOGIN pReqLogin, LPSOCKADDR_IN psockddr);
	virtual void OnRecvDoctorCmd(LPDOCTORCMD pDoctorCmd, LPSOCKADDR_IN psockddr);

	virtual void OnDoctorLogin(CDoctor* pDoctor, BOOL bLogin);
	virtual void OnDoctorOutLine(CDoctor* pDoctor, int nExitCode);

	void OnCall(LPDOCTORCMD pDoctorCmd, LPSOCKADDR_IN psockddr);
	void OnRecall(LPDOCTORCMD pDoctorCmd, LPSOCKADDR_IN psockddr);
	void OnDiscard(LPDOCTORCMD pDoctorCmd, LPSOCKADDR_IN psockddr);
	void OnWait(LPDOCTORCMD pDoctorCmd, LPSOCKADDR_IN psockddr);
	void OnEva(LPDOCTORCMD pDoctorCmd, LPSOCKADDR_IN psockddr);
	void OnPause(LPDOCTORCMD pDoctorCmd, LPSOCKADDR_IN psockddr);
	void OnResume(LPDOCTORCMD pDoctorCmd, LPSOCKADDR_IN psockddr);
	//void OnDocLogin(LPDOCTORCMD pDoctorCmd, LPSOCKADDR_IN psockddr);
	//void OnDocLogOut(LPDOCTORCMD pDoctorCmd, LPSOCKADDR_IN psockddr);

	BOOL SendCmdResult(LPBASEINFO lpBaseInfo, const LPSOCKADDR_IN sockddr, BOOL bSucceed = TRUE);

private:
	CStringArray m_arrstrOfficeId;

private:

	VerifyResultEnum VerifyDoctor(
		CString strDoctorID, 
		CString strPassword, 
		LPCMDRESULT pCmdResult);

	BOOL SqlGetNurseFromDB();

	BOOL SqlQueryDoctorBaseInfo(DOCTORBASICINFO& rDoctorBasicInfo, CString strDoctorID);
	BOOL SqlUpdateCallToDone(CString strDoctorID);
	BOOL SqlUpdateCallToDiscard(CString strDoctorID);
	BOOL SqlUpdateWaitToInLine(CString strDoctorID);
	BOOL SqlQueryPatients(CString strDoctorId, LPCMDRESULT pCmdResult);

	BOOL SqlUpdateToCall(CString strDoctorID, CString strQueSerialID);
	BOOL SqlUpdateToWait(CString strDoctorID, CString strQueSerialID);

	BOOL SqlQueryPatientBySerialID(CString strSerialID, LPCALLPATIENTINFO pCallPatientInfo);

	BOOL SqlQueryWaitPatientByDoctorId(CString strDoctorId, LPCALLPATIENTINFO pCallPatientInfo);

	BOOL SqlQueryCallingPatient(CString strDoctorID, LPVIEWUPDATEINFO sViewUpdateInfo);

	//void AddToSoundAndDisplay(CString& strDoctorID, CString& strQueSerialID, BOOL bCall);
	void AddToSoundAndDisplay(DOCTORBASICINFO& rDoctorBasicInfo, CString strQueSerialID, BOOL bCall);

private:
	void PlayVoice(VOICEDISPLAYSTR vdstr);

	//CString StringReplace(CString strSrc, CString strFrom, CString strTo);

	CString CovertVarStr(CALLPATIENTINFO& cpiCall, CoverTypeEnum nType);
	CString CovertVarStr2(CString strSrc, CALLPATIENTINFO& cpiCall);

	//������Һ����ʾ���̺߳���
	static UINT DisplayThreadProc(LPVOID pParam);
	//void OnResumeDisplay(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
	//void OnUpdateQueListRset(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
	//void UpdateQueListData();
	////�����Ŷ��б����ݵ��̺߳���
	static UINT UpdateQueListThreadProc(LPVOID pParam);
	BOOL m_bUpdateQueListThread;
	CWinThread* m_pUpdateQueListThread;
	//����ָ�����ҵ��Ŷ��б�����
	BOOL UpdateQueListData(CString strOfficeId);
	//��������ʾ���Ŷ��б�����
	//void UpdateQueListDataRowType();

	//typedef struct {
	//	CString strQueueId;
	//	CString strPatientName;
	//	CString strOfficeName;
	//	CString strConsultName;
	//	CString strDoctorName;
	//	int iStatus;
	//} STBPATIENT, *LPSTBPATIENT;

	class StbPatient
	{
	public:
		StbPatient()
			:strQueueId(_T("")),strPatientName(_T("")),strOfficeName(_T("")),
			strConsultName(_T("")),strDoctorName(_T("")){}
		~StbPatient(){}

	public:
		CString strQueueId;
		CString strPatientName;
		CString strOfficeName;
		CString strConsultName;
		CString strDoctorName;
		QueueStatusEnum eStatus;
		CString strComment;
	};

	//typedef CArray<STBPATIENT> CStbPatientList;
	typedef CArray<StbPatient> CStbPatientList;

	CStbPatientList m_arrStbInfo;

	class Office 
	{
	public:
		Office()
			 : m_pStbPatientList(NULL)
		{
			m_pStbPatientList = new CStbPatientList;
		}
		~Office()
		{
			//if(m_pStbPatientList)
			//{
			//	for(int i = 0; i < m_pStbPatientList->GetCount(); i++)
			//	{
			//		delete m_pStbPatientList->GetAt(i);
			//	}
			//	m_pStbPatientList->RemoveAll();
			//	delete m_pStbPatientList;
			//	m_pStbPatientList = NULL;
			//}
		}
		CString GetOfficeId() const {return m_strOfficeId;}
		void SetOfficeId(CString strOfficeId) {m_strOfficeId = strOfficeId;}
		CString GetOfficeName() const {return m_strOfficeName;}
		void SetOfficeName(CString strOfficeName) {m_strOfficeName = strOfficeName;}
		CString GetStbId() const {return m_strStbId;}
		void SetStbId(CString strStbId) {m_strStbId = strStbId;}
		int GetQueueNum() const {return m_iQueueNum;}
		void SetQueueNum(int iQueNum) {m_iQueueNum = iQueNum;}
		CStbPatientList* GetStbPatientList() {return m_pStbPatientList;}
	private:
		CString m_strOfficeId;
		CString m_strOfficeName;
		int m_iQueueNum;
		CString m_strStbId;
		CStbPatientList* m_pStbPatientList;
	};
	//CArray<Office> m_arrOffice;

	void LoadDisplayConf();
	BOOL InitDisplay();
	BOOL BeginDisplayThread();
	void KillDisplayThread();

public:
	//���±���
	BOOL StbUpdateTitleHtml(CString strTitle, CString strStbId = _T(""));
	//����֪ͨ����
	BOOL StbUpdateNoticeHtml(CString strNotice, CString strStbId = _T(""));
	//���½���֪ͨ
	BOOL StbUpdateInstantMsg(CString strIMsg, CString strStbId = _T(""));
	//���º�����Ϣ
	//BOOL StbUpdateCallInfo(CString strCallInfo);
	BOOL StbUpdateCallInfo(CString strCallInfo, CString strOfficeId);
private:
	//���±������Ŷ��б�Һ����ʾ����
	BOOL StbUpdateQueueInfo(CString strStbId);
	//���Ŷ��б�����д����ָ��Һ��������
	BOOL StbUpdateQueueInfoHtml(CString strStbId);
	//��ϸ��Ϣ����ʾ
	BOOL StbUpdateQueueInfoHtmlTypeRow(CString strStbId);
	//���ҷ�����ʾ
	BOOL StbUpdateQueueInfoHtmlTypeCol(CString strStbId);
	//��������л���ʾ
	BOOL StbUpdateQueueInfoHtmlTypeSwitchCol(CString strStbId);
	//BOOL StbUpdateQueueInfoHtmlThreadProc();

	BOOL StbNoticeHtmlExist(CString strStbId);
	//������д��ָ��������
	BOOL WriteToStbHtmlFile(CString& strHtmlStr, CString strStbId, CString strHtmlFileName);

	BOOL WriteToFile(CString& strText, CString& strFilePath);

	CString GetGenderStr(int iGender);
	CString GetAgeStr(CString strBirth, BOOL bShowMonth);

	BOOL InitNetServer();

	void ReSetEvaluator(CString strEvaltorID);

	void UpdateDocView(LPVIEWUPDATEINFO pViewUpdateInfo, DoctorStatusEnum eUS);

public:
	void ReLoadConf();
	CString m_strSqlConn;
private:
	//MyTimer<CNurseController>* m_ptimerUpdateQue;
	//MyTimer<CNurseController>* m_ptimerDisplayCall;

	//typedef void (CNurseController::*MYTIMERPROC)(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
	//ACCallback<TIMERPROC, CNurseController, CNurseController::MYTIMERPROC> m_callbackResumeQue;
	//UINT_PTR m_idEventResumeQue;

	//CADODatabase m_db;

	CJttsAPI* m_pJttsAPI;

	CWinThread* m_pDisplayThread;
	BOOL m_bDisplayThread;
	BOOL m_bSleepDisplayThread;
	CString m_strWebRootDir;
	//CADORecordset m_rsetDisplayList;
	CMutex m_mutexRset;
	int m_iHtmlPageItemCount;
	int m_iHtmlPageSwitchTime, m_iHtmlShowCallTime;
	int m_nShowType;
	int m_nCurIndex;

public:
	//CString m_strNurseStbId;
private:
	CString m_strHtmlTitleBegin;
	CString m_strHtmlTitleEnd;
	CString m_strHtmlNoticeBegin;
	CString m_strHtmlNoticeEnd;
	CString m_strHtmlInstMsgBegin;
	CString m_strHtmlInstMsgEnd;
	CString m_strHtmlQueueInfoBegin;
	CString m_strHtmlQueueInfoEnd;

	CStringArray m_arrstrStbIdList;

	PROCESS_INFORMATION m_piNetServer;
/*
	class DoctorCallInfo
	{
	public:
		void SetDoctorId(CString strDoctorId){this->strDoctorId = strDoctorId;}
		CString GetDoctorId(){return strDoctorId;}
		void SetOfficeId(CString strOfficeId){this->strOfficeId = strOfficeId;}
		CString GetOfficeId(){return strOfficeId;}
		void SetOfficeName(CString strOfficeName){this->strOfficeName = strOfficeName;}
		CString GetOfficeName(){return strOfficeName;}
		void SetConsultId(CString strConsultId){this->strConsultId = strConsultId;}
		CString GetConsultId(){return strConsultId;}
		void SetConsultName(CString strConsultName){this->strConsultName = strConsultName;}
		CString GetConsultName(){return strConsultName;}
		void SetSoundCall(CString strSoundCall){this->strSoundCall = strSoundCall;}
		CString GetSoundCall(){return strSoundCall;}
		void SetSoundWait(CString strSoundWait){this->strSoundWait = strSoundWait;}
		CString GetSoundWait(){return strSoundWait;}
		void SetDisplayCall(CString strDisplayCall){this->strDisplayCall = strDisplayCall;}
		CString GetDisplayCall(){return strDisplayCall;}
		void SetDisplayWait(CString strDisplayWait){this->strDisplayWait = strDisplayWait;}
		CString GetDisplayWait(){return strDisplayWait;}
		void SetConsultStbId(CString strConsultStbId){this->strConsultStbId = strConsultStbId;}
		CString GetConsultStbId(){return strConsultStbId;}
		void SetMaxRecallTimes(int iMaxRecallTimes){this->iMaxRecallTimes = iMaxRecallTimes;}
		int GetMaxRecallTimes(){return iMaxRecallTimes;}
		void SetWndScreenId(int iWndScreenId){this->iWndScreenId = iWndScreenId;}
		int GetWndScreenId(){return iWndScreenId;}
		void SetEvaluatorId(int iEvaluatorId){this->iEvaluatorId = iEvaluatorId;}
		int GetEvaluatorId(){return iEvaluatorId;}
		void SetDoctorStatus(DoctorStatusEnum eDoctorStatus){this->eDoctorStatus = eDoctorStatus;}
		DoctorStatusEnum GetDoctorStatus(){return eDoctorStatus;}
	private:
		CString strDoctorId;
		CString	strOfficeId;
		CString	strOfficeName;
		CString	strConsultId;
		CString	strConsultName;
		CString	strSoundCall;
		CString	strSoundWait;
		CString	strDisplayCall;
		CString	strDisplayWait;
		CString	strConsultStbId;
		int	iMaxRecallTimes;
		int	iWndScreenId;
		int	iEvaluatorId;
		DoctorStatusEnum eDoctorStatus;
	};
*/
	CMap<CString, LPCTSTR, DOCTORBASICINFO, DOCTORBASICINFO&> m_mapDocIdDocInfo;
	LPDOCTORBASICINFO GetDocBasInfo(CString strDoctorId);
	CString CovertColorString(CString strSrc);

	CString m_strQueHtml;

	//void AutoClearData();

	//int m_nDataDays;//��ȡ�ŶӲ������ݵ�ʱ�䷶Χ����ȡǰm_nDataDays���ڵ����ݣ�0��ʾֻ��ȡ����
	CString m_strSqlDate;

public:
	void SetDataDays(int nDays);
	int GetDataDays(){return m_DbParam.GetDataDays();}

private:
	class StbData
	{
	public:
		StbData():nShowMsg(0),nSwitch(0),nIndex(0){}
		~StbData(){}
		StbData(const StbData& stbData)
		{
			this->strStbId = stbData.strStbId;
			this->arrOffice.Copy(stbData.arrOffice);
			this->strHtmlTemp = stbData.strHtmlTemp;
			this->nShowMsg = stbData.nShowMsg;
			this->nSwitch = stbData.nSwitch;
			this->nIndex = stbData.nIndex;
		}
		StbData& operator= (const StbData& stbData)
		{
			if(this != &stbData)
			{
				this->strStbId = stbData.strStbId;
				this->arrOffice.Copy(stbData.arrOffice);
				this->strHtmlTemp = stbData.strHtmlTemp;
				this->nShowMsg = stbData.nShowMsg;
				this->nSwitch = stbData.nSwitch;
				this->nIndex = stbData.nIndex;
			}
			return *this;
		}
		CString strStbId;
		CStringArray arrOffice;
		CString strHtmlTemp;
		UINT nShowMsg;
		UINT nSwitch;
		UINT nIndex;
	};
	CMap<CString, LPCTSTR, StbData, StbData&> m_mapStb;
	CMap<CString, LPCTSTR, Office, Office&> m_mapOffice;

public:
	BOOL AddVoiceDisplay(CString strVoice, CString strStbId);
	BOOL ResetStbShowMsgFlag(CString strStbId);

	CString m_strConsultHtml;
	BOOL UpdateConsultStb(CONSULTSTB& consultStb);
	CString m_strModuleDir;

	CString SqlQueryWaitPatient(CString& strDoctorID);
	CString SqlQueryCallPatient(CString& strDoctorID);
	
	CString m_strHospitalName;

	BOOL CallWait(DOCTORBASICINFO& docInfo);
	CString m_strSeparator;
	BOOL m_bConsultShowNum;
	BOOL m_bReadInPatient;

	BOOL GetReadInFlag() {return m_bReadInPatient;}

	BOOL DeleteDbData();

	BOOL SendToThroughLED(int nId, CString strMsg);

	CString m_strColorCall;
	CString m_strColorWait;
	CString m_strColorInLine;
	CString m_strColorHead;
	CString m_strColorLineNum;

	BOOL m_bShowSum;
	BOOL m_bShowOffice;
	BOOL m_bShowDoctor;
	BOOL m_bShowConsult;
	BOOL m_bShowQueueNum;//�Ƿ���ʾ�ŶӺ�
	BOOL m_bSwitchPage;//�Ƿ�ҳ
	int m_nPageColCount;//ÿҳ��ʾ�Ŀ�������
	BOOL m_bShowLineNum;//�Ƿ���ʾ�к�

	//int m_nTimeCall;
	void SetCallSeconds(int nSecond);
	CString GetFirstInLinePatientSelectString(CString strDoctorId, BOOL isExpert);

public:
	//BOOL SendCmd(const int nCallerId, const DoctorCmdEnum eDocCmd, CString& strRetData);
	BOOL SendCmd(const int nCallerId, const DoctorCmdEnum eDocCmd);

	//CMap<int,int,CString, LPCTSTR> m_mapCallerId_DoctorId;
};
