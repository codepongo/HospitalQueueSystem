// IniFile.cpp: implementation of the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IniFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define MAX_ALLSECTIONS   2048      //ȫ���Ķ���
#define MAX_SECTION       260       //һ����������
#define MAX_ALLKEYS       6000      //ȫ���ļ���
#define MAX_KEY           260       //һ����������

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIniFile::~CIniFile()
{

}

BOOL CIniFile::SetFileName(LPCTSTR lpFileName)
{
	CFile file;
	CFileStatus status;
	if (!file.GetStatus(lpFileName, status))
	{
		return TRUE;
	}
	m_strFileName = lpFileName;
	
	return FALSE;
}

CString CIniFile::GetFileName()
{
	return m_strFileName;
}

BOOL CIniFile::SetValue(LPCTSTR lpSection, LPCTSTR lpKey, LPCTSTR lpValue, bool bCreate /* = true */)
{
	TCHAR lpTemp[MAX_PATH] = {0};
	
	//����if����ʾ�������bCreateΪfalseʱ����û���������ʱ�򷵻�TRUE����ʾ����
	//!*&*none-value*&!* ���Ǹ������ַ�û���ر����壬������д�Ƿ�ֹ������ͬ��
	if (!bCreate)
	{
		GetPrivateProfileString(lpSection, lpKey, _T("!*&*none-value*&!*"), lpTemp, MAX_PATH, m_strFileName);
		if (_tcscmp(lpTemp, _T("!*&*none-value*&!*")) == 0)
		{
			return TRUE;
		}
	}

	if (WritePrivateProfileString(lpSection, lpKey, lpValue, m_strFileName))
	{
		return FALSE;
	}
	else
	{
		return GetLastError();
	}
}

CString CIniFile::GetValue(LPCTSTR lpSection, LPCTSTR lpKey)
{
	DWORD dValue;
	TCHAR lpValue[MAX_PATH] = {0};

	dValue = GetPrivateProfileString(lpSection, lpKey, _T(""), lpValue, MAX_PATH, m_strFileName);

	return lpValue;
}

BOOL CIniFile::DelSection(LPCTSTR lpSection)
{
	if (WritePrivateProfileString(lpSection, NULL, NULL, m_strFileName))
	{
		return FALSE;
	}
	else
	{
		return GetLastError();
	}
}

BOOL CIniFile::DelKey(LPCTSTR lpSection, LPCTSTR lpKey)
{
	if (WritePrivateProfileString(lpSection, lpKey, NULL, m_strFileName))
	{
		return FALSE;
	}
	else
	{
		return GetLastError();
	}
}

/*
GetPrivateProfileSectionNames - �� ini �ļ��л�� Section ������
��� ini �������� Section: [sec1] �� [sec2]���򷵻ص��� 'sec1',0,'sec2',0,0 ��
���㲻֪�� ini ������Щ section ��ʱ���������� api ����ȡ���� 
*/
int CIniFile::GetSections(CStringArray& arrSection)
{
	int i, iPos=0, iMaxCount;
	TCHAR chSectionNames[MAX_ALLSECTIONS] = {0};    //�ܵ���������ַ���
	TCHAR chSection[MAX_SECTION] = {0};         //���һ������
	GetPrivateProfileSectionNames(chSectionNames, MAX_ALLSECTIONS, m_strFileName);
	
	//ѭ���ض�����������0
	for (i=0; i<MAX_ALLSECTIONS; ++i)
	{
		if (chSectionNames[i] == 0)
		if (chSectionNames[i] == chSectionNames[i+1])
			break;
	}

	iMaxCount = i+1; //Ҫ��һ��0��Ԫ�ء����ҳ�ȫ���ַ����Ľ������֡�
	arrSection.RemoveAll();   //���ԭ����

	for (i=0; i<iMaxCount; i++)
	{
		chSection[iPos++] = chSectionNames[i];
		if (chSectionNames[i] == 0)
		{
			arrSection.Add(chSection);
			memset(chSection, 0, MAX_SECTION);
			iPos = 0;
		}
	}

	return (int)arrSection.GetSize();
}

/*
GetPrivateProfileSectionNames - �� ini �ļ��л�� Section ������
��� ini �������� Section: [sec1] �� [sec2]���򷵻ص��� 'sec1',0,'sec2',0,0 ��
���㲻֪�� ini ������Щ section ��ʱ���������� api ����ȡ���� 
*/
int CIniFile::GetKeys(CStringArray& arrKey, LPCTSTR lpSection)
{

	int i, iPos=0, iMaxCount;  
	CString strKey;
	TCHAR chKeyNames[MAX_ALLKEYS] = {0}; //�ܵ���������ַ���
	TCHAR chKey[MAX_KEY] = {0}; //�������һ������
	
	GetPrivateProfileSection(lpSection, chKeyNames, MAX_ALLKEYS, m_strFileName);
	
	for(i=0; i<MAX_ALLKEYS; i++)
	{
		if (chKeyNames[i] == 0)
			if (chKeyNames[i] == chKeyNames[i+1])
				break;
	}
	
	iMaxCount = i + 1; //Ҫ��һ��0��Ԫ�ء����ҳ�ȫ���ַ����Ľ������֡�
	arrKey.RemoveAll();//���ԭ����
	
	for(i=0; i<iMaxCount; i++)
	{
		chKey[iPos++] = chKeyNames[i];
		if(chKeyNames[i] == 0)
		{
			strKey = chKey;
			arrKey.Add(strKey.Left(strKey.Find(_T("="))));
			memset(chKey, 0, MAX_KEY);
			iPos = 0;
		}	
	}
	
	return (int)arrKey.GetSize();
}

/*
GetPrivateProfileSection- �� ini �ļ��л��һ��Section��ȫ��������ֵ��
���ini����һ���Σ������� "��1=ֵ1" "��2=ֵ2"���򷵻ص��� '��1=ֵ1',0,'��2=ֵ2',0,0 ��
���㲻֪��  ���һ�����е����м���ֵ����������� */
int CIniFile::GetKeyValues(CStringArray& arrKey, CStringArray& arrValue, LPCTSTR lpSection)
{

	int i, iPos=0, iMaxCount;  
	CString strKeyValue;
	TCHAR chKeyNames[MAX_ALLKEYS] = {0}; //�ܵ���������ַ���
	TCHAR chKey[MAX_KEY] = {0}; //�������һ������
	
	GetPrivateProfileSection(lpSection, chKeyNames, MAX_ALLKEYS, m_strFileName);
	
	for(i=0; i<MAX_ALLKEYS; i++)
	{
		if (chKeyNames[i] == 0)
			if (chKeyNames[i] == chKeyNames[i+1])
				break;
	}
	
	iMaxCount = i + 1; //Ҫ��һ��0��Ԫ�ء����ҳ�ȫ���ַ����Ľ������֡�
	arrKey.RemoveAll();//���ԭ����
	arrValue.RemoveAll();
	
	for(i=0; i<iMaxCount; i++)
	{
		chKey[iPos++] = chKeyNames[i];
		if(chKeyNames[i] == 0)
		{
			strKeyValue = chKey;
			arrKey.Add(strKeyValue.Left(strKeyValue.Find(_T("="))));
			arrValue.Add(strKeyValue.Mid(strKeyValue.Find(_T("="))+1));
			memset(chKey, 0, MAX_KEY);
			iPos = 0;
		}	
	}
	
	return (int)arrKey.GetSize();
}

BOOL CIniFile::DelAllSections()
{
	int i, nSection;
	CStringArray arrSection;
	nSection = GetSections(arrSection);
	for(i=0; i<nSection; i++)
	{
		if(DelSection(arrSection[i]))
			return GetLastError();
	}
	return FALSE;
}
