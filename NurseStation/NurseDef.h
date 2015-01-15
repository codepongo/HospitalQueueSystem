#ifndef _NURSESYSTEMDEF_H
#define _NURSESYSTEMDEF_H


////////////////////////////////////////////////////////////////////////////////
/////////////////////////	�����ļ�ʹ�õ����ݶ���	////////////////////////


//�û����
#define USERTYPE_SYSADMIN			0			//ϵͳ����Ա
#define USERTYPE_MANAGER			1			//��̨����Ա
#define USERTYPE_NURSE				2			//ǰ̨��ʿ
#define USERTYPE_DOCTOR				-1			//ҽ��

/*��������ʾ���õı�������*/
#define STRING_QUEUEID_CALL			(_T("[�ŶӺ���]"))			//�����ŶӺ���
#define STRING_PATIENTNAME_CALL		(_T("[��������]"))			//���л�������
#define STRING_QUEUEID_WAIT			(_T("[׼���ŶӺ���]"))		//׼���ŶӺ���
#define STRING_PATIENTNAME_WAIT		(_T("[׼����������]"))		//׼����������
#define STRING_DOCTORNAME			(_T("[ҽ������]"))			//ҽ������
#define STRING_OFFICENAME			(_T("[��������]"))			//��������
#define STRING_CONSULTNAME			(_T("[��������]"))			//��������
#define STRING_PATIENT_GENDER		(_T("[�����Ա�]"))			//�����Ա�
#define STRING_PATIENT_AGE			(_T("[��������]"))			//��������

#define COLORREF_RED				0x0000FF			//��ɫ
#define COLORREF_GREEN				0x00FF00			//��ɫ
#define COLORREF_YELLOW				0x00FFFF			//��ɫ

#define COLORCODE_RED				(_T("#0#"))			//��ɫ
#define COLORCODE_GREEN				(_T("#1#"))			//��ɫ
#define COLORCODE_YELLOW			(_T("#2#"))			//��ɫ



////////////////////////////////////////////////////////////////////////////
////////////////////	

/*����ҽ����״̬*/
typedef enum _tagDoctorStatusEnum
{
	dsWorking		= 0,		//����״̬
	dsPause			= 1,		//��ͣ״̬
	usOutLine		= 2			//����״̬
} DoctorStatusEnum;

/*�����л������ȼ�*/
typedef enum _tagPatientPriorityEnum
{
	priMinusTwo		= -2,		//���ȼ�-2		[���]	//Ԥ��ֵ
	priMinusOne		= -1,		//���ȼ�-1		[�ϵ�]	//Ԥ��ֵ
	priZero			= 0,		//���ȼ�0��Ĭ��	[��ͨ]
	priOne			= 1,		//���ȼ�1		[�е�]
	priTwo			= 2,		//���ȼ�2		[�ϸ�]
	priThree		= 3,		//���ȼ�3		[���]
	priFour			= 4,		//���ȼ�4				//Ԥ��ֵ
	priFive			= 5			//���ȼ�5				//Ԥ��ֵ
} PatientPriorityEnum;

/*������Ϣ���*/
typedef enum _tagGenderEnum
{
	genderFemale	= 0,		//Ů��
	genderMale		= 1,		//����
	genderNeuter	= 2,		//����
	genderNone		= -1		//��ָ��
} GenderEnum;

/*������Ϣ���*/
typedef enum _tagExpertEnum
{
	expertNo		= 0,		//��ר��
	expertYes		= 1,		//ר��
} ExpertEnum;


/////////////////////////////////////////////////////////////////////////////
////////////////////////


/*�����û�״̬��Ϣ*/
/*
typedef struct _tagUserStatus
{
	WCHAR				wszUserID[MAX_ID_LENGTH];
	WCHAR				wszUserName[MAX_NAME_LENGTH];
	WCHAR				wszUserIP[MAX_IP_LENGTH];
	USHORT				iPort;
	SOCKADDR_IN			sSockAddrIn;
	DoctorStatusEnum		eUserStatus;
	short				nOnlineFlag;	//�������ж��Ƿ���������
	WCHAR               wszPatientName[MAX_NAME_LENGTH];//�û�Ϊҽ��ʱ���������/���ﻼ��
	WCHAR				wszOfficeID[MAX_ID_LENGTH];
}USERSTATUS, *LPUSERSTATUS;
*/
typedef struct _tagUserStatus
{
	CString				strUserID;
	CString				strUserName;
	CString				strUserIP;
	USHORT				iPort;
	SOCKADDR_IN			sSockAddrIn;
	DoctorStatusEnum	eUserStatus;
	short				nOnlineFlag;	//�������ж��Ƿ���������
	CString             strPatientName;//�û�Ϊҽ��ʱ���������/���ﻼ��
	CString				strOfficeID;
}USERSTATUS, *LPUSERSTATUS;

/*ʱ�������Ϣ*/
typedef struct _tagSuspendTime
{
	WCHAR		logid[255];
	CTime       suspendtime;
}SUSPENDTIME,*LPSUSPENDTIME;


#define  statusWaitLine   _T("�Ŷ�")
#define  statusQuitQue    _T("����")
#define  statusSuspend    _T("����")
#define  statusDone       _T("��ɾ���")
#define  statusDoing      _T("����/����")
#define  statusPre        _T("׼��")


#define  priMinTwoText    _T("���")
#define  priMinOneText    _T("�ϵ�")
#define	 priZeroText      _T("��ͨ")
#define  priOneText       _T("�е�")
#define  priTwoText       _T("�ϸ�")
#define  priThreeText     _T("���")

#define  callNumText      _T("��ɾ���:")
#define  quitNumText      _T("����:")
#define  suspendNumText   _T("����:")
#define  allNumText       _T("������:")
#define  waitNumText      _T("�Ŷ�:")
#define  flushTimeText    _T("ˢ��ʱ��:")
#define  loginText        _T("��ǰ��¼:")


#define  toolFulshText		_T("ˢ��")
#define  toolQueText		_T("�Ŷӷ�ʽ")
#define  toolExportText		_T("����")
#define  toolQuitText		_T("����")
#define  toolInsertText		_T("����")
#define  toolSuspendText	_T("����")
#define  toolActiveText		_T("����")
#define  toolReconsultText  _T("����")
#define  toolRecallText     _T("�ٻ�")
#define  toolSetDocText     _T("ָ��ҽ��")
#define  toolSearchText     _T("����")
#define  toolMessageText    _T("��Ϣ")
#define  toolShowText       _T("Һ����ʾ")
#define  toolExchangeText   _T("ת�ƿ���")


#define  docStaOnlineText   _T("����")
#define  docStaOutlineText  _T("����")
#define  docStaSuspendText  _T("��ͣ")


typedef struct _tagDocToComBoInfo
{
	CString docid;
	CString docname;
}DOCTOCOMBOINFO,*LPDOCTOCOMBOINFO;

/************************************************/


#endif		//_NURSESYSTEMDEF_H