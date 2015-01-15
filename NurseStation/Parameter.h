/////////////////////////////////////////////////////////////////////
//��Ȩ: �����Ӧ�����������
//����: ��̹��				
//����: ���ַ������з�������ȡ�ò���
//����: 02.10.26
/////////////////////////////////////////////////////////////////////

#ifndef _PARAMETER__H_
#define _PARAMETER__H_

// ע�⣺�� // ���� / ��������ķ���
//#include "D:\\work\\cximage\\CxImage\\ximage.h"
//#pragma comment(lib, "D:\\work\\cximage\\CxImage\\CxImageDLL\\Release\\cximage.lib" )

CString NewUrlEncode( const CString& strIn);

CString toParam( const CString& param );

// ��ʽ��/id 12
int RequestParam( const CString  &strParam, const CString  &name );
// ��ʽ /name abc 
CString RequestParamStr( const CString &strParam, const CString &name ); 

#ifndef UNDER_CE
// ��ʽ /width 3.3
float RequestParamF( const CString &strParam, const CString &name );
#endif // UNDER_CE

// ���� 0 ��ʾ��ȷ�������Ĵ��� ��ʽ 12,45,32,-1,23, 
int RequestParams( const CString& ini, CDWordArray& array, const CString &sep=_T(","));
// ���� 0 ��ʾ��ȷ�������Ĵ��� ��ʽ abc|def|dir adf|adsfasdf //bWithSpace TRUE ɾ���ո� //bSpace True �ָ���յ�Ҳ����
int RequestParamsStr( const CString& ini,CStringArray& array, const CString &sep=_T("``"),
					 BOOL bWithSpace = FALSE ); 
int RequestParamsStrofSpace( const CString& ini,CStringArray& array, const CString &sep=_T("``"),
					 BOOL bWithSpace = FALSE,BOOL bSpace=FALSE ); 
CString	logFontToString(const LOGFONT& font );
BOOL	StringTologFont(const CString& str, LOGFONT& font );

// guid to string
BOOL		StringToGuid( const CString& str, GUID &guid );
CString		GuidToString( const GUID& guid );


int GetDaysInMonth(const CTime& time );


CString DayTimeToString(const CTime& time );
CString DayTimeToStandString(const CTime& time );
CString DayToString(const CTime& time);
CString TimeToString( const CTime& time,const CString & Symbol=_T("," ));
void	DayTimeToStandStr( const CTime& time, CString& str );
//void	StandToDayTime(const CString& strtime,CTime & time);
CString	TimeStrToStandStr(const CString& str);	//20110101 ת 1011-01-01
void	OleDateTimeToStandStr(const COleDateTime& time, CString & str);
void	TimeToOleDateTime(const CTime& Time,COleDateTime & OleTime);
void	OleDateTimeToTime(const COleDateTime& oleTime, CTime& Time);
void	 TimetoOleDateTime(const CTime& Time,COleDateTime & time2);

void	SetSysTime(const CString& time);

BOOL	StringToDayTime( const CString& str, CTime& time );
BOOL	StringToDay(const CString& str, CTime& time);
BOOL	StringToDay(const CString& str, CTime& time,const CString & Symbol);
BOOL	StringToTime(const CString& str, CTime& time, const CTime& day=CTime(1977,7,7,7,7,7),const CString & Symbol=_T(","));
BOOL	StringToStandStr(const CString& str,CTime& time);

BOOL	IsSameDay( const CTime& t1, const CTime& t2 );
int		TimeCompareTime(const CTime& t1, const CTime& t2 );	//t1>t2=1,t1=t2=0,t1<t2=-1
DWORD	IpStringToDWORD( const CString& strAddr );

CString inttoCString( int a) ;

void CStringtobyte(const CString & str,BYTE * pb);
byte* intToByte(int i);			//����ת�������ֽ�
int bytesToInt(byte* bytes);	//byte �����ֽ�ת������

//С�����ӵĺ���
CString  ReturnStringW(const CString& _strSrc, const CString& _strStartFlag, const CString& _strEndFlag);
CString  ReturnStringA(const CString& _strSrc, const CString& _strStartFlag, const CString& _strEndFlag);

CSize GetStringSize(const CString& str, const LOGFONT& font ,CDC* Pdc); // xj add 
int		GetHeightFontSize(CSize & size1,const int& nwidth);

int		GetSrand(const int& Max);		//ȡ0 �� Max �����
CString		GetOnlyID();		//ȡάһ��ID��
int			GetDWORDCount(const CString& str);		//��ȡ���ֵĸ���
void ConvertUnicode(char* pUnicode);
 void ConvertAsni(char* pAsni, CString strInfo);
 //GBKת��ΪUTF8
void ConvertGBKToUtf8_(CString& strGBK);
//UTF8ת��ΪGBK
void ConvertUtf8ToGBK_(CString& strUtf8) ;
///���ַ���ת��unicode 16������ʽ
char* UnicodeToHexString(char *pSrc,int size);


/*************************************************************
*�������ƣ�Calc_CRC16CCNET
*�������ܣ�����CRCУ��ֵ
*���������DataBuf ���ݻ������׵�ַ
BufLen   ���ݳ���                             
*���������
*��    ע:
**************************************************************/
int Calc_CRC16CCNET( unsigned char *DataBuf, unsigned int BufLen );

void calc_crc(unsigned char byte,  unsigned char *inter_crc_h,  unsigned char *inter_crc_l);
 //int FindFormat( const CString& ext );
CString FindExtension( const CString& name );

BOOL IsNumber( LPCTSTR pszText );
HWND	OpenShowProcess(const CString& path, const CString& wndName );
BOOL	OpenShowProcess(const CString& path);

/*-------------------------------------------------------
//    ������Ա��G.Yin
//    ��дʱ�䣺2006-1-6
//    �������ƣ�GetCutString(CString strSource, int setLength)
//    �������ͣ�int
//    ����˵������ȡ�������ֵ��ַ����������ַ����ĳ��Ȳ������ӽ�Ԥ���setLength���ȣ�
//    ���strSource�ĳ���С��setLengthֵ��ֱ�ӷ���strSource�ĳ���
//    ����˵����
//        --��������----�������----��������----����˵��-------
//        --strSource            ����        CString                ����ȡ���ַ���        
//        --setLength            ����        int                    ����ȡ���ַ����ĳ���  
//-------------------------------------------------------
*/


int GetCutString(CString strSource, int setLength);

unsigned char Char8ToByte(CString str);

//xj ���ַ�ת������byte 
byte	char16toByte(char cdata);


//���ת��Ϊȫ��
CString DbcToSbc(CString stringText);

BOOL SetPrivilege(
                  HANDLE hToken,          // access token handle
                  LPCTSTR lpszPrivilege,  // name of privilege to enable/disable
                  BOOL bEnablePrivilege   // to enable or disable privilege
                  ) ;

HANDLE GetProcessHandle(int nID);

BOOL IsProcessExist(CString ProcessName, int& dwProcID,BOOL bKill /*= FALSE*/);
BOOL ShutDownOS_(BOOL Reboot);
#endif // _PARAMETER__H_
