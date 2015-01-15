// MySocketUDP.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "NurseStation.h"
#include "MySocketUDP.h"
#include "MyCommon.h"
#include "MyString.h"


// MySocketUDP

MySocketUDP::MySocketUDP()
: m_uPort(0)
, m_bIsCreate(FALSE)
, m_bPeekRecvThreadProc(FALSE)
,m_pPeekRecvThreadProc(NULL)
{
	m_strLogFilePath = MyCommon::GetModuleDir() + _T("log/");
}

MySocketUDP::~MySocketUDP()
{
	CloseSocket();
}

// MySocketUDP ��Ա����

BOOL MySocketUDP::StartSocket(USHORT uPort)
{
	if(m_bIsCreate)
	{
		return FALSE;
	}
	if(!Startup())
	{
		AfxMessageBox(_T("��ʼ��Socketʧ��"));
		//ShowSocketError();
		return FALSE;
	}

	if(!CreateSocket())
	{
		AfxMessageBox(_T("����Socket�׽���ʧ��"));
		return FALSE;
	}

	if(uPort > 0)
	{
		m_uPort = uPort;
		if(!Bind())
		{
			CString str;
			str.Format(_T("%d�˿ڰ�ʧ��,��������һ���˿ں�"), m_uPort);
			AfxMessageBox(str);
			CloseSocket();
			return FALSE;
		}

		if(!StartPeekRecvThread())
		{
			CloseSocket();
			return FALSE;
		}
	}

	m_bIsCreate = TRUE;

	return TRUE;
}

BOOL MySocketUDP::ReBind(USHORT uPort)
{
	if(!_CloseSocket())
	{
		return FALSE;
	}
	if(!CreateSocket())
	{
		return FALSE;
	}
	USHORT uPortTemp = m_uPort;
	m_uPort = uPort;
	if(!Bind())
	{
		m_uPort = uPortTemp;
		return FALSE;
	}
	return TRUE;
}

BOOL MySocketUDP::CloseSocket()
{
	if(!m_bIsCreate)
	{
		return FALSE;
	}

	KillPeekRecvThread();

	if(!_CloseSocket())
	{
		return FALSE;
	}
	if(!Cleanup())
	{
		return FALSE;
	}
	m_bIsCreate = FALSE;

	return TRUE;
}

BOOL MySocketUDP::SendTo( CHAR * pData, UINT nLen, CString wszIP)
{
	return SendTo(pData, nLen, wszIP, m_uPort);
}

BOOL MySocketUDP::SendTo( CHAR * pData, UINT nLen, CString wszIP, USHORT uPort)
{
	CHAR szIP[_MY_MAX_IP_LENGTH] = {0};
	MyString::WChar2Char(szIP, _MY_MAX_IP_LENGTH, wszIP);
	SOCKADDR_IN addrin = {0};
	addrin.sin_family = AF_INET;
	addrin.sin_port = htons(uPort);
	addrin.sin_addr.S_un.S_addr = inet_addr(szIP);

	return SendTo(pData, nLen, &addrin);
}

BOOL MySocketUDP::SendTo( CHAR * pData, UINT nLen, LPSOCKADDR_IN pSockaddr_in)
{
	StartSocket(0);
	try
	{
		int iRet = ::sendto(m_uSocket, pData, nLen, 0, (LPSOCKADDR)pSockaddr_in, sizeof(SOCKADDR_IN));
		//int iRet = ::sendto(m_uSocket, pData, nLen, MSG_DONTWAIT, (LPSOCKADDR)pSockaddr_in, sizeof(SOCKADDR_IN));
		if(iRet == SOCKET_ERROR)
		{
			return FALSE;
		}
	}
	catch (CException* e)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL MySocketUDP::Broadcast(CHAR * pData, UINT nLen)
{
	return Broadcast(pData, nLen, m_uPort);
}

BOOL MySocketUDP::Broadcast(CHAR * pData, UINT nLen, USHORT uPort)
{
	SOCKADDR_IN addrin = {0};
	addrin.sin_family = AF_INET;
	addrin.sin_port = htons(uPort);
	addrin.sin_addr.S_un.S_addr = ::htonl( INADDR_BROADCAST );

	//���ù㲥ģʽ
	BOOL bBroadcast = TRUE;
	int iRet = ::setsockopt( m_uSocket, SOL_SOCKET, SO_BROADCAST,
		(char *)&bBroadcast,sizeof( bBroadcast ) );
	if(SOCKET_ERROR == iRet)
	{
		return FALSE;
	}

	BOOL bRet = SendTo(pData, nLen, &addrin);

	//���÷ǹ㲥ģʽ
	bBroadcast = FALSE;
	iRet = ::setsockopt( m_uSocket, SOL_SOCKET, SO_BROADCAST,
		(char *)&bBroadcast,sizeof( bBroadcast ) );
	if(SOCKET_ERROR == iRet)
	{
		//Create();
	}

	return bRet;
}

BOOL MySocketUDP::RecvFrom(CHAR * buf, int iLen, LPSOCKADDR_IN from)
{
	int iAddrinLen = sizeof(SOCKADDR_IN);
	if(SOCKET_ERROR == ::recvfrom(m_uSocket, buf, iLen, 0, (LPSOCKADDR)from, &iAddrinLen))
	{
		Sleep(100);
		return FALSE;
	}

	return TRUE;
}

int MySocketUDP::GetLastError()
{
	return ::WSAGetLastError();
}

void MySocketUDP::ShowSocketError()
{
	int errCode = ::WSAGetLastError();
	switch(errCode)
	{
	case WSANOTINITIALISED:	//��ʹ�ô�API֮ǰӦ���ȳɹ��ص���WSAStartup()��
		AfxMessageBox(_T("��ʹ�ô�API֮ǰӦ���ȳɹ��ص���WSAStartup"));
		break;
	case WSAENETDOWN:		//WINDOWS�׽ӿ�ʵ�ּ�⵽������ϵͳʧЧ��
		AfxMessageBox(_T("WINDOWS�׽ӿ�ʵ�ּ�⵽������ϵͳʧЧ"));
		break;
	case WSAEFAULT:			//fromlen�����Ƿ���from��������С�޷�װ��˵�ַ��
		AfxMessageBox(_T("fromlen�����Ƿ���from��������С�޷�װ��˵�ַ"));
		break;
	case WSAEINTR:			//�������̱�WSACancelBlockingCall()ȡ����
		AfxMessageBox(_T("�������̱�WSACancelBlockingCall()ȡ��"));
		break;
	case WSAEINPROGRESS:	//һ��������WINDOWS�׽ӿڵ������������С�
		AfxMessageBox(_T("һ��������WINDOWS�׽ӿڵ�������������"));
		break;
	case WSAEINVAL:			//�׽ӿ�δ��bind()��������
		AfxMessageBox(_T("�׽ӿ�δ��bind()��������"));
		break;
	case WSAENOTCONN:		//�׽ӿ�δ���ӣ���������SOCK_STREAM���ͣ���
		AfxMessageBox(_T("�׽ӿ�δ���ӣ���������SOCK_STREAM���ͣ�"));
		break;
	case WSAENOTSOCK:		//�����ֲ���һ���׽ӿڡ�
		AfxMessageBox(_T("�����ֲ���һ���׽ӿ�"));
		break;
	case WSAEOPNOTSUPP:		//ָ����MSG_OOB�����׽ӿڲ���SOCK_STREAM���͵ġ�
		AfxMessageBox(_T("ָ����MSG_OOB�����׽ӿڲ���SOCK_STREAM���͵�"));
		break;
	case WSAESHUTDOWN:		//�׽ӿ��ѱ��رա���һ���׽ӿ���0��2��how��������shutdown()�رպ��޷�����recv()��������
		AfxMessageBox(_T("�׽ӿ��ѱ��رա���һ���׽ӿ���0��2��how��������shutdown()�رպ��޷�����recv()��������"));
		break;
	default:
		AfxMessageBox(_T("�׽ӿ�δ֪����"));
	}
}

USHORT MySocketUDP::NetToHostShort(USHORT uNetShort)
{
	return ::ntohs(uNetShort);
}

CString MySocketUDP::NetToHostIP(IN_ADDR& in_addrNet)
{
	CHAR * pszIP = ::inet_ntoa(in_addrNet);
	WCHAR wszIP[_MY_MAX_IP_LENGTH] = {0};
	MyString::Char2WChar(wszIP, _MY_MAX_IP_LENGTH, pszIP);
	//CString strIP(wszIP);
	//return strIP;

	return wszIP;
}

void MySocketUDP::WriteLogWithTime(CString strSockLog)
{
	CTime time = CTime::GetCurrentTime();
	CString str = time.Format(_T("%Y-%m-%d %H:%M:%S")) + _T("  \t") + strSockLog + _T("\r\n\r\n");
	CString strLogFile = time.Format(_T("log_%Y%m%d.log"));
	if(!MyCommon::PathFileExist(m_strLogFilePath))
	{
		if(!MyCommon::CreatePath(m_strLogFilePath))
		{
			return;
		}
	}
	AppendWriteFile(str, m_strLogFilePath + strLogFile);
}

void MySocketUDP::WriteErrLog(CString strSockLog)
{
	CString str = _T("Error: ") + strSockLog;
	WriteLogWithTime(str);
}

BOOL MySocketUDP::AppendWriteFile(CString strText, CString strFileName)
{
	CFile file;
	if(!file.Open(strFileName, 
		CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite))
	{
		//CString str;
		//str.Format(_T("���������־�ļ�ʧ��,����ʹ�õļ�����ʺ�û����Ӧ�Ĵ���дȨ��:\r\n\t%s"), g_pControl->m_strLogFilePath);
		//AfxMessageBox(str);
		return FALSE;
	}
	CHAR* szBuf = (CHAR*)malloc(strText.GetLength()*2 + 1);
	memset(szBuf, 0, strText.GetLength()*2 + 1);
	MyString::WChar2Char(szBuf, 
		strText.GetLength()*2 + 1, strText.GetBuffer());
	file.SeekToEnd();
	file.Write(szBuf, strlen(szBuf));
	file.Close();

	return TRUE;
}
/*
void MySocketUDP::OnRecvData()
{

}
*/

////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////	private	/////////////////////////////////////////

BOOL MySocketUDP::Startup()
{
	WSADATA wsaData;
	if(::WSAStartup(WINSOCK_VERSION, &wsaData) == SOCKET_ERROR)
	{
		return FALSE;
	}
	m_uMaxUdpDg = wsaData.iMaxUdpDg;

	return TRUE;
}

BOOL MySocketUDP::CreateSocket()
{
	m_uSocket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//m_uSocketBroadcast = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//���÷�����ģʽ
	ULONG ulMode = 1;
	::ioctlsocket(m_uSocket, FIONBIO, &ulMode);

	if(m_uSocket == INVALID_SOCKET)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL MySocketUDP::Bind()
{
	SOCKADDR_IN addrin = {0};
	addrin.sin_family = AF_INET;
	addrin.sin_port = htons(m_uPort);
	addrin.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	if(SOCKET_ERROR == ::bind(m_uSocket, (SOCKADDR*)&addrin, sizeof(SOCKADDR_IN)))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL MySocketUDP::_CloseSocket()
{
	if(::closesocket(m_uSocket) != SOCKET_ERROR)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL MySocketUDP::Cleanup()
{
	if(::WSACleanup() != SOCKET_ERROR)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL MySocketUDP::StartPeekRecvThread()
{
	if(m_pPeekRecvThreadProc) return TRUE;
	m_pPeekRecvThreadProc = AfxBeginThread(PeekRecvThreadProc, this);
	return m_pPeekRecvThreadProc != NULL;
}

BOOL MySocketUDP::KillPeekRecvThread()
{
	m_bPeekRecvThreadProc = FALSE;
	if(m_pPeekRecvThreadProc)
	{
		::WaitForSingleObject(m_pPeekRecvThreadProc->m_hThread, 100);
		delete m_pPeekRecvThreadProc;
		m_pPeekRecvThreadProc = NULL;
	}
	return TRUE;
}

UINT MySocketUDP::PeekRecvThreadProc(LPVOID pParam)
{
	MySocketUDP* pThis = (MySocketUDP*)pParam;
	TIMEVAL timeout;
	//timeout.tv_sec = 6;
	//timeout.tv_usec = 0;
	timeout.tv_sec = 0;
	timeout.tv_usec = 600;
	FD_SET fdset;
	int nRet;
	pThis->m_bPeekRecvThreadProc = TRUE;
	while(pThis->m_bPeekRecvThreadProc)
	{
		FD_ZERO(&fdset);
		FD_SET(pThis->m_uSocket, &fdset);
		nRet = ::select(0, &fdset, NULL, NULL, &timeout);
		//nRet = ::select(0, &fdset, NULL, NULL, NULL);
		//if(nRet == SOCKET_ERROR || nRet == 0)
		if(nRet <= 0)
		{
			Sleep(100);
			continue;
		}
		else
		{
			if(FD_ISSET(pThis->m_uSocket, &fdset))
			{
				pThis->OnRecvData();
			}
			else
			{
				Sleep(100);
			}
		}
	}
	::ExitThread(0);

	return 0;
}
