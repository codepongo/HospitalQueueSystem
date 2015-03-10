#include "StdAfx.h"
#include "VisonShowLED.h"
#include "CommonConvert.h"
#include "MyCommon.h"
#include "WriteLog.h"
#include "NurseStation.h"
#define DEFALT_LOCAL_PORT 9527

extern void MyWriteConsole(CString str);

CVisonShowLED::CVisonShowLED() : m_hInstance(NULL)
,m_index(-1)
,m_hDoShowWaitThread(NULL)
,m_hFlushWaitInfo(NULL)
{
	LED_Initialize();
	memset(&m_tLedParam,0,sizeof(m_tLedParam));
	m_tLedParam.devType = DEVICE_TYPE_UDP;
	m_tLedParam.locPort = DEFALT_LOCAL_PORT;
	m_tLedParam.rmtPort = 6666;
	m_tLedParam.pkpLength = DEFAULT_PKP_LENGTH;
	strcpy_s(m_tLedParam.rmtHost,16,"192.168.0.99");
	m_tLedParam.dstAddr = 0;
	memset(&m_tLedSendParam,0,sizeof(m_tLedSendParam));
	m_tLedSendParam.devParam = m_tLedParam;
	m_tLedSendParam.notifyMode = NOTIFY_EVENT;
	m_tLedSendParam.wmMessage = WM_LED_NOTIFY;
	ConnectToDB();
	Start();
}

CVisonShowLED::CVisonShowLED(HWND hWnd) : m_hInstance(NULL)
	,m_index(-1)
	,m_hDoShowWaitThread(NULL)
	,m_hFlushWaitInfo(NULL)
{
	LED_Initialize();
	memset(&m_tLedParam,0,sizeof(m_tLedParam));
	m_tLedParam.devType = DEVICE_TYPE_UDP;
	m_tLedParam.locPort = DEFALT_LOCAL_PORT;
	m_tLedParam.rmtPort = 6666;
	m_tLedParam.pkpLength = DEFAULT_PKP_LENGTH;
	strcpy_s(m_tLedParam.rmtHost,16,"192.168.0.99");
	m_tLedParam.dstAddr = 0;
	memset(&m_tLedSendParam,0,sizeof(m_tLedSendParam));
	m_tLedSendParam.devParam = m_tLedParam;
	m_tLedSendParam.notifyMode = NOTIFY_EVENT;
	m_tLedSendParam.wmMessage = WM_LED_NOTIFY;
	m_tLedSendParam.wmHandle = (long)hWnd;
	ConnectToDB();
	Start();
}

CVisonShowLED::~CVisonShowLED(void)
{
	if(m_hDoShowWaitThread)
	{
		TerminateThread(m_hDoShowWaitThread,0);
	}
	if(m_hFlushWaitInfo)
	{
		TerminateThread(m_hFlushWaitInfo,0);
	}
	Destory();
}

bool CVisonShowLED::LED_Initialize()
{
	if ((m_hInstance=LoadLibrary(_T("LEDSender2010.dll")))!=NULL)
	{
		LED_Startup=(long (_stdcall *)(void))GetProcAddress(m_hInstance,"LED_Startup");
		LED_Cleanup=(long (_stdcall *)(void))GetProcAddress(m_hInstance,"LED_Cleanup");

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//���߿��ƿ��б���ؽӿں���
		LED_Report_CreateServer=(long (_stdcall *)(long, long))GetProcAddress(m_hInstance,"LED_Report_CreateServer");
		LED_Report_RemoveServer=(void (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_Report_RemoveServer");
		LED_Report_RemoveAllServer=(void (_stdcall *)(void))GetProcAddress(m_hInstance,"LED_Report_RemoveAllServer");
		LED_Report_GetOnlineList=(long (_stdcall *)(long, void*, long))GetProcAddress(m_hInstance,"LED_Report_GetOnlineList");
		LED_Report_GetOnlineItemName=(char* (_stdcall *)(long, long))GetProcAddress(m_hInstance,"LED_Report_GetOnlineItemName");
		LED_Report_GetOnlineItemHost=(char* (_stdcall *)(long, long))GetProcAddress(m_hInstance,"LED_Report_GetOnlineItemHost");
		LED_Report_GetOnlineItemPort=(long (_stdcall *)(long, long))GetProcAddress(m_hInstance,"LED_Report_GetOnlineItemPort");
		LED_Report_GetOnlineItemAddr=(long (_stdcall *)(long, long))GetProcAddress(m_hInstance,"LED_Report_GetOnlineItemAddr");
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		LED_ResetDisplay=(long (_stdcall *)(PSenderParam))GetProcAddress(m_hInstance,"LED_ResetDisplay");
		LED_AdjustTime=(long (_stdcall *)(PSenderParam))GetProcAddress(m_hInstance,"LED_AdjustTime");
		LED_AdjustTimeEx=(long (_stdcall *)(PSenderParam, LPSYSTEMTIME))GetProcAddress(m_hInstance,"LED_AdjustTimeEx");
		LED_SetCurChapter=(long (_stdcall *)(PSenderParam, long))GetProcAddress(m_hInstance,"LED_SetCurChapter");
		LED_SetPower=(long (_stdcall *)(PSenderParam, long))GetProcAddress(m_hInstance,"LED_SetPower");
		LED_GetPower=(long (_stdcall *)(PSenderParam))GetProcAddress(m_hInstance,"LED_GetPower");
		LED_SetBright=(long (_stdcall *)(PSenderParam, long))GetProcAddress(m_hInstance,"LED_SetBright");
		LED_GetBright=(long (_stdcall *)(PSenderParam))GetProcAddress(m_hInstance,"LED_GetBright");
		LED_SetPowerSchedule=(long (_stdcall *)(PSenderParam, PPowerSchedule))GetProcAddress(m_hInstance,"LED_SetPowerSchedule");
		LED_GetPowerSchedule=(long (_stdcall *)(PSenderParam))GetProcAddress(m_hInstance,"LED_GetPowerSchedule");
		LED_SetBrightSchedule=(long (_stdcall *)(PSenderParam, PBrightSchedule))GetProcAddress(m_hInstance,"LED_SetBrightSchedule");
		LED_GetBrightSchedule=(long (_stdcall *)(PSenderParam))GetProcAddress(m_hInstance,"LED_GetBrightSchedule");
		LED_SendToScreen=(long (_stdcall *)(PSenderParam, long))GetProcAddress(m_hInstance,"LED_SendToScreen");
		LED_ComTransfer=(long (_stdcall *)(PSenderParam, BYTE*, DWORD))GetProcAddress(m_hInstance,"LED_ComTransfer");

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//�˴���֮ǰͬ������������ͬ��ֻ�ǽ��ṹ��ָ�������ֳɶ����������������PB��java�ȿ������Ե���
		LED_UDP_SenderParam=(long (_stdcall *)(long, long, char*, long, long, long, long, long))GetProcAddress(m_hInstance,"LED_UDP_SenderParam");
		LED_COM_SenderParam=(long (_stdcall *)(long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"LED_COM_SenderParam");
		LED_UDP_SenderParam_ByReportName=(long (_stdcall *)(long, long, long, char*, long, long, long))GetProcAddress(m_hInstance,"LED_UDP_SenderParam_ByReportName");
		LED_ResetDisplay2=(long (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_ResetDisplay2");
		LED_AdjustTime2=(long (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_AdjustTime2");
		LED_AdjustTimeEx2=(long (_stdcall *)(long, LPSYSTEMTIME))GetProcAddress(m_hInstance,"LED_AdjustTimeEx2");
		
		LED_SetCurChapter2=(long (_stdcall *)(long, long))GetProcAddress(m_hInstance,"LED_SetCurChapter2");
		LED_SetPower2=(long (_stdcall *)(long, long))GetProcAddress(m_hInstance,"LED_SetPower2");
		LED_GetPower2=(long (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_GetPower2");
		LED_SetBright2=(long (_stdcall *)(long, long))GetProcAddress(m_hInstance,"LED_SetBright2");
		LED_GetBright2=(long (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_GetBright2");
		LED_SetPowerSchedule2=(long (_stdcall *)(long, PPowerSchedule))GetProcAddress(m_hInstance,"LED_SetPowerSchedule2");
		LED_GetPowerSchedule2=(long (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_GetPowerSchedule2");
		LED_SetBrightSchedule2=(long (_stdcall *)(long, PBrightSchedule))GetProcAddress(m_hInstance,"LED_SetBrightSchedule2");
		LED_GetBrightSchedule2=(long (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_GetBrightSchedule2");
		LED_SendToScreen2=(long (_stdcall *)(long, long))GetProcAddress(m_hInstance,"LED_SendToScreen2");
		LED_ComTransfer2=(long (_stdcall *)(long, BYTE*, DWORD))GetProcAddress(m_hInstance,"LED_ComTransfer2");

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//��ȡ���ƿ�����
		LED_Cache_GetBoardParam=(long (_stdcall *)(PSenderParam))GetProcAddress(m_hInstance,"LED_Cache_GetBoardParam");
		LED_Cache_GetBoardParam2=(long (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_Cache_GetBoardParam2");
		//��ȡ��������
		LED_Cache_GetBoardParam_SaveToFile=(long (_stdcall *)(char*))GetProcAddress(m_hInstance,"LED_Cache_GetBoardParam_SaveToFile");
		LED_Cache_GetBoardParam_IP=(char* (_stdcall *)(void))GetProcAddress(m_hInstance,"LED_Cache_GetBoardParam_IP");
		LED_Cache_GetBoardParam_Mac=(char* (_stdcall *)(void))GetProcAddress(m_hInstance,"LED_Cache_GetBoardParam_Mac");
		LED_Cache_GetBoardParam_Addr=(long (_stdcall *)(void))GetProcAddress(m_hInstance,"LED_Cache_GetBoardParam_Addr");
		LED_Cache_GetBoardParam_Width=(long (_stdcall *)(void))GetProcAddress(m_hInstance,"LED_Cache_GetBoardParam_Width");
		LED_Cache_GetBoardParam_Height=(long (_stdcall *)(void))GetProcAddress(m_hInstance,"LED_Cache_GetBoardParam_Height");
		LED_Cache_GetBoardParam_Brightness=(long (_stdcall *)(void))GetProcAddress(m_hInstance,"LED_Cache_GetBoardParam_Brightness");
		//�޸ĸ�������
		LED_Cache_SetBoardParam_LoadFromFile=(long (_stdcall *)(char*))GetProcAddress(m_hInstance,"LED_Cache_SetBoardParam_LoadFromFile");
		LED_Cache_SetBoardParam_IP=(void (_stdcall *)(char*))GetProcAddress(m_hInstance,"LED_Cache_SetBoardParam_IP");
		LED_Cache_SetBoardParam_Mac=(void (_stdcall *)(char*))GetProcAddress(m_hInstance,"LED_Cache_SetBoardParam_Mac");
		LED_Cache_SetBoardParam_Addr=(void (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_Cache_SetBoardParam_Addr");
		LED_Cache_SetBoardParam_Width=(void (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_Cache_SetBoardParam_Width");
		LED_Cache_SetBoardParam_Height=(void (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_Cache_SetBoardParam_Height");
		LED_Cache_SetBoardParam_Brightness=(void (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_Cache_SetBoardParam_Brightness");
		//���޸ĺ�Ĳ���������ƿ�
		LED_Cache_SetBoardParam=(long (_stdcall *)(PSenderParam))GetProcAddress(m_hInstance,"LED_Cache_SetBoardParam");
		LED_Cache_SetBoardParam2=(long (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_Cache_SetBoardParam2");

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		LED_GetNotifyParam=(long (_stdcall *)(PNotifyParam, long))GetProcAddress(m_hInstance,"LED_GetNotifyParam");

		MakeFromVsqFile=(long (_stdcall *)(char*, long, long, long))GetProcAddress(m_hInstance,"MakeFromVsqFile");
		MakeRoot=(long (_stdcall *)(long, long, long))GetProcAddress(m_hInstance,"MakeRoot");
		MakeChapter=(long (_stdcall *)(long, long, long, long, DWORD, WORD))GetProcAddress(m_hInstance,"MakeChapter");
		MakeRegion=(long (_stdcall *)(long, long, long, long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"MakeRegion");
		MakeLeaf=(long (_stdcall *)(long, long, long, long, long, long, DWORD, WORD))GetProcAddress(m_hInstance,"MakeLeaf");
		MakeObject=(long (_stdcall *)(long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"MakeObject");

		AddChapter=(long (_stdcall *)(WORD, DWORD, WORD))GetProcAddress(m_hInstance,"AddChapter");
		AddRegion=(long (_stdcall *)(WORD, long, long, long, long, long))GetProcAddress(m_hInstance,"AddRegion");
		AddLeaf=(long (_stdcall *)(WORD, DWORD, WORD))GetProcAddress(m_hInstance,"AddLeaf");

		AddDateTime=(long (_stdcall *)(WORD, long, long, long, long, long, long, char*, long, long, long, long, long, long, long, char*))GetProcAddress(m_hInstance,"AddDateTime");
		AddCampaignEx=(long (_stdcall *)(WORD, long, long, long, long, long, long, char*, long, long, long, char*, PTimeStamp, PTimeStamp, PTimeStamp, long))GetProcAddress(m_hInstance,"AddCampaignEx");
		AddClock=(long (_stdcall *)(WORD, long, long, long, long, long, long, long, DWORD, DWORD, DWORD, long, long, long, DWORD, long, DWORD, long, DWORD, long, DWORD, long, DWORD))GetProcAddress(m_hInstance,"AddClock");
		AddMovie=(long (_stdcall *)(WORD, long, long, long, long, long, long, char*, long))GetProcAddress(m_hInstance,"AddMovie");

		AddWindows=(long (_stdcall *)(WORD, long, long, long, long, long, long))GetProcAddress(m_hInstance,"AddWindows");
		AddChildWindow=(long (_stdcall *)(WORD, HDC, long, long, long, long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"AddChildWindow");
		AddChildPicture=(long (_stdcall *)(WORD, char*, long, long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"AddChildPicture");
		AddChildText=(long (_stdcall *)(WORD, char*, char*, long, long, long, long, long, long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"AddChildWindow");
		AddStrings=(long (_stdcall *)(WORD, long, long, long, long, long, long))GetProcAddress(m_hInstance,"AddStrings");
		AddChildString=(long (_stdcall *)(WORD, char*, long, long, long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"AddChildString");

		AddWindow=(long (_stdcall *)(WORD, long, long, long, long, long, long, HDC, long, long, long, long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"AddWindow");
		AddPicture=(long (_stdcall *)(WORD, long, long, long, long, long, long, char*, long, long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"AddPicture");
		AddText=(long (_stdcall *)(WORD, long, long, long, long, long, long, char*, char*, long, long, long, long, long, long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"AddText");
		AddString=(long (_stdcall *)(WORD, long, long, long, long, long, long, char*, long, long, long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"AddString");

		if (LED_Startup) 
			LED_Startup();
		return true;
	}
	else
	{
		return false;
	}
	
}

void CVisonShowLED::Destory()
{
	if(LED_Cleanup) 
		LED_Cleanup();
 	if(m_hInstance)
 		FreeLibrary(m_hInstance);
}

void CVisonShowLED::SendDataToScreen(const CString& msg,const CString& wStrIP,const CRect& rect, DWORD lShowTime,int nRegion)
{
	if(m_strIpAdd != wStrIP)m_strIpAdd = wStrIP;
 	long index = CreateData(msg,rect,lShowTime,nRegion);//���ɷ�������
	int len = CCommonConvert::CStringToChar(wStrIP,NULL);
	char* pStrIP = new char[len+1];
	memset(pStrIP,0,len+1);
	CCommonConvert::CStringToChar(wStrIP,pStrIP);
	strcpy_s(m_tLedParam.rmtHost,16,pStrIP);//IP��ַ
	delete [] pStrIP;
	m_tLedSendParam.devParam = m_tLedParam;
	if(m_hInstance)
	{
 		LED_SendToScreen(&m_tLedSendParam,index);//����
	}
//	ReadWaitInfo();
}

void CVisonShowLED::SetHWnd(HWND hWnd)
{
	m_tLedSendParam.wmHandle = (long)hWnd;
}

long CVisonShowLED::CreateData(const CString& msg,const CRect& rect, DWORD lShowTime ,int nRegion)
{
	DWORD left,width,top,height;
	left = rect.left;width = rect.right - left;
	top = rect.top; height = rect.bottom - top;
	if(m_hInstance)
	{
//		m_index = MakeRoot(ROOT_PLAY,COLOR_MODE_DOUBLE,ROOT_SURVIVE_ALWAYS);
//		AddChapter(m_index,lShowTime,LED_WAIT_CHILD);
//		AddRegion(m_index,left,top,rigth,bottom,0);
		m_index = MakeRegion(ROOT_PLAY_REGION, ACTMODE_REPLACE, 0, nRegion, COLOR_MODE_DOUBLE,left,top,width,height,0);
		
		AddLeaf(m_index,lShowTime,LED_WAIT_CHILD);
		int len = CCommonConvert::CStringToChar(msg,NULL);
		char* pStrMsg = new char[len+1];
		memset(pStrMsg,0,len+1);                                                                       
		CCommonConvert::CStringToChar(msg,pStrMsg);
		AddText(m_index,left,top,width,height,0,0,pStrMsg,
			"����",12,RGB(255,0,0),WFS_NONE,1/*�Զ�����*/,0/*�����*/,
			1/*������ʾ*/,5/*�����ٶ�*/,2/*��������*/,2/*�����ٶ�*/,
			0/*������̬��ʾ*/,3/*�����ٶ�*/,lShowTime/*����ʱ��*/);
		delete [] pStrMsg;	
	}
	return m_index;
}

CVisonShowLED* CVisonShowLED::GetInstance(HWND hWnd)
{
	static CVisonShowLED Instance(hWnd);
	return &Instance;
}

BOOL CVisonShowLED::ReadWaitInfo()
{
	m_mMsgLock.Lock();
	m_map_visionmsg.clear();
	m_mMsgLock.Unlock();
	if(m_DataBase.IsOpen())
	{
		try
		{
			CADORecordset pRe(&m_DataBase);
			CString searchSql;
			searchSql.Format(_T("select n.office_id,o.name from Nurse m,Nurse_Office n,Office o where m.nurse_id = n.nurse_id and o.office_id=n.office_id and m.nurse_id='%s';"),theApp.GetLoginID());
			if(pRe.Open(searchSql,CADORecordset::openQuery))
			{
				if(!pRe.IsBOF())
				{
					ShowWaitInfo(&pRe);
				}
				pRe.Close();
			}
			else
			{
				return FALSE;
			}
		}
		catch(_com_error &e)
		{
			WriteLog::WriteDbErrLog(_T("CVisonShow::ReadWaitInfo"));
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CVisonShowLED::ConnectToDB()
{
	if(!m_DataBase.IsOpen())
	{
		CMainFrame* pMainFrame=((CNurseStationApp*)AfxGetApp())->m_pNurseWnd;
		try
		{
			m_DataBase.SetConnectionString(pMainFrame->m_strConn);
			return m_DataBase.Open();
		}
		catch (_com_error &e)
		{
			WriteLog::WriteDbErrLog(_T("CVisonShowLED::ConnectToDB"));
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CVisonShowLED::ShowWaitInfo(CADORecordset* pRe)
{
	if(!pRe)return FALSE;
	m_mLock.Lock();
//	CRect rect;
//	static UINT left = MyCommon::GetProfileInt(_T("sys"),_T("WAITLEFT"),0,_T("sys\\VisonShow.ini"));
//	static UINT right = MyCommon::GetProfileInt(_T("sys"),_T("WAITRIGHT"),256,_T("sys\\VisonShow.ini"));
//	static UINT top = MyCommon::GetProfileInt(_T("sys"),_T("WAITTOP"),0,_T("sys\\VisonShow.ini"));
//	static UINT bottom = MyCommon::GetProfileInt(_T("sys"),_T("WAITBOTTOM"),64,_T("sys\\VisonShow.ini"));
//	static UINT nRegion = MyCommon::GetProfileInt(_T("sys"),_T("WAITREGION"),0,_T("sys\\VisonShow.ini"));
//	static UINT nRow = MyCommon::GetProfileInt(_T("sys"),_T("WAITROW"),3,_T("sys\\VisonShow.ini"));
	static UINT nPaient = MyCommon::GetProfileInt(_T("sys"),_T("WAITPAITNUM"),6,_T("sys\\VisonShow.ini"));
//	static UINT nPage = MyCommon::GetProfileInt(_T("sys"),_T("WAITPAGE"),4,_T("sys\\VisonShow.ini"));
//	rect.left = left; rect.right = right; rect.top = top; rect.bottom = bottom;
	m_mLock.Unlock();
	try{
		m_mMsgLock.Lock();
	while(!pRe->IsEOF())
	{
		CString office_id,office_name;
		pRe->GetFieldValue(_T("office_id"),office_id);
		pRe->GetFieldValue(_T("name"),office_name);
		if(m_DataBase.IsOpen())
		{
			CADORecordset reset(&m_DataBase);
			CString sql;
			list<CString> listTemp;
			listTemp.push_back(office_name);
			sql.Format(_T("select * from queue where office_id='%s' and status=%d"),office_id,qsInLine);
			if(reset.Open(sql,CADORecordset::openQuery))
			{
				if(!reset.IsBOF())
				{
					int nNum = nPaient;
					while(!reset.IsEOF())
					{
						//д���ڴ�
						nNum--;
						if(!nNum)break;
						CString patient_name;
						reset.GetFieldValue(_T("patient_name"),patient_name);
						listTemp.push_back(patient_name);
						reset.MoveNext();
					}
					m_map_visionmsg[office_id] = listTemp;
				}
			}
		}
		pRe->MoveNext();
	}
	}
	catch (_com_error &e)
	{
		WriteLog::WriteDbErrLog(_T("CVisonShowLED::ShowWaitInfo"));
		m_mMsgLock.Unlock();
		return FALSE;
	}
	m_mMsgLock.Unlock();
	return TRUE;
}

BOOL CVisonShowLED::CreateData(DWORD lShowTime)
{
	m_mLock.Lock();
	CRect rect;
	static UINT left = MyCommon::GetProfileInt(_T("sys"),_T("WAITLEFT"),0,_T("sys\\VisonShow.ini"));
	static UINT right = MyCommon::GetProfileInt(_T("sys"),_T("WAITRIGHT"),256,_T("sys\\VisonShow.ini"));
	static UINT top = MyCommon::GetProfileInt(_T("sys"),_T("WAITTOP"),0,_T("sys\\VisonShow.ini"));
	static UINT bottom = MyCommon::GetProfileInt(_T("sys"),_T("WAITBOTTOM"),64,_T("sys\\VisonShow.ini"));
	static UINT nRegion = MyCommon::GetProfileInt(_T("sys"),_T("WAITREGION"),0,_T("sys\\VisonShow.ini"));
	static UINT nRow = MyCommon::GetProfileInt(_T("sys"),_T("WAITROW"),3,_T("sys\\VisonShow.ini"));
	static UINT nPaient = MyCommon::GetProfileInt(_T("sys"),_T("WAITPAITNUM"),5,_T("sys\\VisonShow.ini"));
	static UINT nPageShowTime = MyCommon::GetProfileInt(_T("sys"),_T("WAITPAGETIME"),4,_T("sys\\VisonShow.ini"));
	rect.left = left; rect.right = right; rect.top = top; rect.bottom = bottom;
	m_mLock.Unlock();
	DWORD width,height;
	width = rect.right - left;
	height = rect.bottom - top;
	if(m_hInstance)
	{
//		m_index = MakeRegion(ROOT_PLAY_REGION, ACTMODE_REPLACE, 0, nRegion, COLOR_MODE_DOUBLE,left,top,width,height,0);	
		m_mMsgLock.Lock();//�̰߳�ȫ
		int actiPage = m_map_visionmsg.size()/nRow;
		if(m_map_visionmsg.size() % nRow) actiPage += 1;
		for(int i=0;i<actiPage;i++)//��ʾ����ҳ
		{
			CString showMsg;//��ʾ����Ϣ
			map<CString,list<CString>>::const_iterator itera = m_map_visionmsg.begin();
			//itera += (i * nRow);
			for(int k=0;k<(int)i*nRow;k++)
			{
				itera++;
			}
			for(int m=0;m<(int)nPaient;m++)
			{
				int j = 0;
				map<CString,list<CString>>::const_iterator tempItera = itera;
				for(tempItera;tempItera != m_map_visionmsg.end();tempItera++)
				{
					if(j == nRow)break;
					list<CString> patientNameList = tempItera->second;
					CString patientName;
					if(m<(int)patientNameList.size())
						//ȡ�������ж�Ӧλ�õ��ַ���
					{
						GetListData(&patientNameList,patientName,m);
					}
					if(patientName.IsEmpty())
						showMsg+=_T("        ");
					else if(patientName.GetLength() == 1)
					{
						showMsg += patientName;
						showMsg += _T("      ");
					}
					else if(patientName.GetLength() == 2)
					{
						showMsg += patientName;
						showMsg += _T("    ");
					}
					else if(patientName.GetLength() == 3)
					{
						showMsg += patientName;
						showMsg += _T("  ");
					}
					else 
						showMsg += patientName;
					showMsg += _T("  ");
					j++;
				}
				showMsg+=_T("\n");
			}
			//��������
#ifdef _DEBUG
		MyWriteConsole(showMsg);
#endif
			SendDataToScreen(showMsg,m_strIpAdd,rect,lShowTime,nRegion);
			Sleep(nPageShowTime*1000);
		}
		m_mMsgLock.Unlock();
	}
	return TRUE;
}

BOOL CVisonShowLED::GetListData(const list<CString>* pList,CString& data,int location)
{
	if(location>=(int)pList->size())return FALSE;
	list<CString>::const_iterator itera = pList->begin();
	for(int i=0;i<location;i++)
	{
		itera++;
	}
	data = *itera;
	return TRUE;
}

DWORD WINAPI CVisonShowLED::DoShowWait(LPVOID pParam)
{
	CVisonShowLED* pThis = (CVisonShowLED*) pParam;
	while(TRUE)
	{
		pThis->CreateData(10*1000);
	}
	return 0;
}

BOOL CVisonShowLED::Start()
{
	m_hDoShowWaitThread = CreateThread(NULL,0,DoShowWait,this,0,NULL);
	if(!m_hDoShowWaitThread)return FALSE;
	m_hFlushWaitInfo = CreateThread(NULL,0,FlushWaitInfo,this,0,NULL);
	if(!m_hFlushWaitInfo)return FALSE;
	return TRUE;
}

DWORD WINAPI CVisonShowLED::FlushWaitInfo(LPVOID pParam)
{
	CVisonShowLED* pThis = (CVisonShowLED*) pParam;
	while(TRUE)
	{
		pThis->ReadWaitInfo();
		Sleep(1000);
	}
	return 0;
}