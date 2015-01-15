#pragma once

#include "MySocketUDP.h"
//#include "SockDef.h"
#include "ado2.h"
#include "MyTimer.h"
//#include "NurseDef.h"

/***********���廤ʿվ��ҽ��������ͨ������Э��************/

//�����ֶγ���
#define MAX_ID_LENGTH				32			//�û�ID����
#define MAX_NAME_LENGTH				32			//�û���������
//#define USERSIGN_LENGTH			256			//�û�ǩ������
#define MAX_CHATMSG_LENGTH			1024		//������Ϣ����
//#define MAX_PACKEGEDATA_LENGTH	((MAX_ID_LENGTH+MAX_NAME_LENGTH+MAX_CHATMSG_LENGTH)*3)
//���ݰ���Ϣ����
#define MAX_IP_LENGTH				32			//IP��ַ�ַ�������
#define MAX_PASSWORD_LENGTH			32			//IP��ַ�ַ�������
#define MAX_PATIENTS_SHOW			10			//ҽ������ʾ�Ļ��������
#define MAX_STR_LENGTH				256


////////////////////////////////////////////////////////////////////////////////

typedef enum _tagNetTypeIDEnum
{
	ntiNotDefined		= 0,				//δ����
	ntiReqLogin			= 1,				//��¼����
	ntiLoginVerify			= 2,				//��¼��֤���
	ntiLogin					= 3,				//��¼
	ntiQuit						= 4,				//�˳�
	ntiHeartBeat			= 5,				//������
	ntiDoctorCmd			= 6,				//ҽ��ָ��
	ntiCmdResult			= 7,				//ҽ��ָ��ִ�н��
	//ntiDoctorEvaluate	= 8,				//ҽ����������
	ntiChatMsg				= 8				//��������
} NetTypeIDEnum;

/*������Ϣ���*/
typedef enum _tagChatTypeIDEnum
{
	ctPublicChat		= 0,		//Ⱥ����Ϣ
	ctPrivateChat		= 1		//˽����Ϣ
} ChatTypeIDEnum;

/*ҽ��ָ�����ö��*/
typedef enum _tagDoctorCmdEnum
{
	dcCmdNotDefined	= 0,		//δ����
	//dcCmdLogin		= 1,		//��¼
	//dcCmdQuit			= 2,		//�˳�
	dcCmdCall				= 1,		//����
	dcCmdRecall			= 2,		//�غ�
	dcCmdDiscard		= 3,		//����
	dcCmdWait				= 4,		//������һλ׼��
	dcCmdEva				= 5,		//��������
	dcCmdPause			= 6,		//ҽ����ͣ����
	dcCmdResume		= 7		//ҽ���ָ�����
	//dcCmdChangeStatus	= 10		//��ͣ��ָ�����״̬
} DoctorCmdEnum;

/*���۵ȼ�ö��*/
typedef enum _tagEvaluateLevelEnum
{
	evlNone			= 0,		//δ����
	evlLevel1			= 1,		//�ȼ�1
	evlLevel2			= 2,		//�ȼ�2
	evlLevel3			= 3,		//�ȼ�3
	evlLevel4			= 4		//�ȼ�4
} EvaluateLevelEnum;

/*�����л��ߵ�״̬*/
typedef enum _tagQueueStatusEnum
{
	qsDoing				= 0,		//����/����
	qsPrepare			= 1,		//׼��
	qsInLine				= 2,		//�Ŷ�
	qsSuspend			= 3,		//����
	qsDone				= 4,		//��ɾ���
	qsDiscard			= 5,		//����
	qsNotDefined		= 6		//δ����
} QueueStatusEnum;

/*��֤���*/
typedef enum _tagVerifyResultEnum
{
	vrNotDefine			= 0,		//δ����
	vrPass						= 1,		//��֤ͨ��
	vrNotPass				= 2,		//��֤��ͨ��
	vrLogined				= 3,		//���ʺ��ѵ�¼
	vrDBError				= 4,		//���ݿ����
	vrNotFoundOffice	= 5,		//�û�ʿվ������ҽ�����ڿ���
	vrFoundOffice			= 6		//�����¼�Ļ�ʿ�ʺ���ĳ�ѵ�¼�Ļ�ʿ�ʺŵĿɴ�����Ҵ����ظ�
} VerifyResultEnum;

/*�û�����*/
typedef enum _tagUserTypeEnum
{
	utNotDefine		= 0,		//δ����
	utDoctor				= 1,		//ҽ��
	utNurse				= 2		//��ʿ
} UserTypeEnum;

//�Ŷ�ϵͳ���ݿ����
typedef struct _tagDbParam
{
	WCHAR				wszDriver[32];
	WCHAR				wszHost[32];
	USHORT				m_uPort;
	WCHAR				wszUID[32];
	WCHAR				wszPID[32];
	WCHAR				wszDbName[32];
	INT						m_nDataDays;
	INT						m_nCallSeconds;
} DBPARAM, *LPDBPARAM;

////////////////////////////////////////////////////////////////////////
//////////////////////////	Socket ���ݰ�����	////////////////////////

typedef struct _tagUserInfo
{
	UserTypeEnum		eUserType;
	WCHAR				wszUserID[MAX_ID_LENGTH];
	WCHAR				wszUserName[MAX_NAME_LENGTH];
	WCHAR				wszOffices[MAX_STR_LENGTH];// _T("OfficeId1,OfficeName1|OfficeId2,OfficeName2|OfficeId3,OfficeName3")
} USERINFO, *LPUSERINFO;

/*Socket���ݰ���ͷ*/
typedef struct _tagNetHeader
{
	NetTypeIDEnum		eTypeID;		//ͨ���������
	DWORD					nDataLength;	//���ݳ���
	SOCKADDR_IN		sSockAddrIn;	//���ݰ���תʱ����Դ��ַ
	USERINFO				sUserInfo;
} NETHEADER, *LPNETHEADER;

typedef struct _tagBaseInfo
{
	NETHEADER				header;
} *LPBASEINFO;

//�ͻ��˵�¼��������
typedef struct _tagReqLogin
{
	NETHEADER			header;
	//USERINFO			sUserInfo;
	WCHAR					wszPassword[MAX_PASSWORD_LENGTH];
} REQLOGIN, *LPREQLOGIN;

//��������Ӧ�ͻ��˵�¼��������
//typedef struct _tagLoginResult
//{
//	NETHEADER				header;
//	//USERINFO				sUserInfo;
//	BOOL						bCallSpecial;
//	VerifyResultEnum		eRes;
//	DBPARAM				dbParam;
//} LOGINRESULT, *LPLOGINRESULT;

//�û��㲥����
typedef struct _tagBroadcast
{
	NETHEADER			header;
	//USERINFO			sUserInfo;
} BROADCAST, *LPBROADCAST, LOGIN, *LPLOGIN, HEARTBEAT, *LPHEARTBEAT;

//�û��˳�����
typedef struct _tagQuit
{
	NETHEADER			header;
	//USERINFO			sUserInfo;
	int							nExitCode;
} QUIT, *LPQUIT;

/*ҽ�����������͵���ʿվ��ָ������ݽṹ*/
typedef struct _tagDoctorCmd
{
	NETHEADER				header;
	//USERINFO				sUserInfo;
	DoctorCmdEnum		eDoctorCmd;
	WCHAR						szQueSerialID[MAX_ID_LENGTH];
	int								iCode;
} DOCTORCMD, *LPDOCTORCMD;

/*��ʿվ���͸�ҽ���˵Ļ�����Ϣ�ṹ*/
typedef struct _tagPatientToDoctor
{
	WCHAR						wszSerialID[MAX_ID_LENGTH];
	WCHAR						wszQueueID[MAX_ID_LENGTH];
	WCHAR						wszPatientName[MAX_NAME_LENGTH];
	WCHAR						wszPatientGender[8];
	WCHAR						wszPatientAge[16];
	QueueStatusEnum		eStatus;			
}PATIENTTODOCTOR, *LPPATIENTTODOCTOR;

/*��ʿվ���͸�ҽ���˵Ļ�����Ϣ�ṹ*/
typedef struct _tagCmdResult
{
	NETHEADER				header;
	NetTypeIDEnum			eTypeIDFrom;
	DoctorCmdEnum		eDoctorCmd;
	USERINFO					sUserInfoFrom;
	BOOL							bSucceed;
	BOOL							bCallSpecial;
	VerifyResultEnum		eRes;
	int								nPatientCount;
	//int								nSentCount;
	//PATIENTTODOCTOR		patientsArray[MAX_PATIENTS_SHOW];
	BOOL							bExpertFlag;
	DBPARAM					sDbParam;
}CMDRESULT, *LPCMDRESULT;


/*�������ݵ����ݽṹ*/
typedef struct _tagChatMsg
{
	NETHEADER				header;
	//USERINFO				sUserInfo;
	ChatTypeIDEnum		eChatTypeID;
	WCHAR						wszMsg[MAX_CHATMSG_LENGTH + 2];
} CHATMSG, *LPCHATMSG;

//#define MAX_PACKEGEDATA_LENGTH	(sizeof(CHATMSG) > sizeof(CMDRESULT) ? sizeof(CHATMSG) : sizeof(CMDRESULT))
#define MAX_PACKEGEDATA_LENGTH	sizeof(CHATMSG)

/*ͨ�ŵ�UDP���ݰ�,����Socket������(��ʿվ)�������ݣ�Ȼ���ٽ������������ж�*/
typedef struct _tagUDPPackege
{
	NETHEADER		header;
	CHAR					szData[MAX_PACKEGEDATA_LENGTH - sizeof(NETHEADER)];
} UDPPACKEGE, *LPUDPPACKEGE;


//////////////////////////	End Socket ���ݰ�����		////////////////////////

#define MY_DEFAULT_LOCAL_PORT		4020		//ȱʡϵͳ�ڶ˿�

class CController : public MySocketUDP
{
public:
	CController();
	virtual ~CController();

	BOOL StartControl();
	BOOL EndControl();

	CString GetUserId() const
	{
		return m_strCtlUserId;
	}
	void SetUserId(CString strUserId)
	{
		m_strCtlUserId = strUserId;
	}
	CString GetUserName() const
	{
		return m_strCtlUserName;
	}
	void SetUserName(CString strUserName)
	{
		m_strCtlUserName = strUserName;
	}
	UserTypeEnum GetUserType() const
	{
		return m_eCtlUserType;
	}
	void SetUserType(UserTypeEnum eUserType)
	{
		m_eCtlUserType = eUserType;
	}
	CString GetOffices() const
	{
		return m_strCtlOffices;
	}
	void SetOffices(CString strOffices)
	{
		m_strCtlOffices = strOffices;
	}
	BOOL GetOnline() const
	{
		return m_bOnline;
	}
	void SetOnline(BOOL bOnline)
	{
		m_bOnline = bOnline;
	}
	void SetSendBaseInfo(LPBASEINFO pBaseInfo, NetTypeIDEnum eNetType, int iStructSize)
	{
		pBaseInfo->header.eTypeID = eNetType;
		pBaseInfo->header.nDataLength = iStructSize;
		wcscpy_s(pBaseInfo->header.sUserInfo.wszUserID, MAX_ID_LENGTH, GetUserId().GetBuffer());
		wcscpy_s(pBaseInfo->header.sUserInfo.wszUserName, MAX_NAME_LENGTH, GetUserName().GetBuffer());
		wcscpy_s(pBaseInfo->header.sUserInfo.wszOffices, MAX_STR_LENGTH, GetOffices().GetBuffer());
		pBaseInfo->header.sUserInfo.eUserType = GetUserType();
	}
	USHORT GetPort(){return m_uPort;}

protected:

	virtual BOOL OnStartControl();
	virtual BOOL OnEndControl();

	virtual void DispatchCmd(LPUDPPACKEGE pUDPPackege, LPSOCKADDR_IN psockddr);

	///////		CMD dispatch function	/////////////////////////////
	virtual void OnRecvReqLogin(LPREQLOGIN pReqLogin, LPSOCKADDR_IN psockddr) = 0;
	virtual void OnRecvLogin(LPBROADCAST pLogin, LPSOCKADDR_IN psockddr) = 0;
	virtual void OnRecvQuit(LPQUIT pQuit, LPSOCKADDR_IN psockddr) = 0;
	virtual void OnRecvHeartBeat(LPBROADCAST pHeartbeat, LPSOCKADDR_IN psockddr) = 0;
	virtual void OnRecvDoctorCmd(LPDOCTORCMD pDoctorCmd, LPSOCKADDR_IN psockddr) = 0;
	virtual void OnRecvCmdResult(LPCMDRESULT pCmdResult, LPSOCKADDR_IN psockddr) = 0;
	virtual void OnRecvChatMsg(LPCHATMSG pChatMsg, LPSOCKADDR_IN psockddr) = 0;
	///////		End	CMD dispatch function	/////////////////////////

	virtual void OnSetPort();

protected:

	void SetPort(USHORT uPort);

protected:
	virtual void OnRecvData();
	//BOOL DispatchCmd(LPUDPPACKEGE pUDPPackege, LPSOCKADDR_IN psockddr);

protected:

	USHORT m_uPort;

	CString m_strCtlUserId;
	CString m_strCtlUserName;
	UserTypeEnum m_eCtlUserType;
	CString m_strCtlOffices;
	BOOL m_bOnline;
};


