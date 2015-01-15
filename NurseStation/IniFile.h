// IniFile.h: interface for the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__61921152_E664_4427_80BA_9C1B580D7A4B__INCLUDED_)
#define AFX_INIFILE_H__61921152_E664_4427_80BA_9C1B580D7A4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIniFile  
{
public:
	CIniFile(CString strFileName):m_strFileName(strFileName)
	{
	}
	virtual ~CIniFile();

public:
	BOOL SetFileName(LPCTSTR lpFileName);   //�����ļ���
	CString GetFileName();     //��ȡ�ļ���
	BOOL SetValue(LPCTSTR lpSection, LPCTSTR lpKey, LPCTSTR lpValue, bool bCreate = true);  //���ü�ֵ��bCreate��ָ����������δ����ʱ���Ƿ񴴽���ֵ
	CString GetValue(LPCTSTR lpSection, LPCTSTR lpKey);   //�õ���ֵ
	BOOL DelSection(LPCTSTR lpSection);    //ɾ������
	BOOL DelKey(LPCTSTR lpSection, LPCTSTR lpKey);   //ɾ������

	int GetSections(CStringArray& arrSection);   //ö��ȫ���Ķ���
	int GetKeys(CStringArray& arrKey, LPCTSTR lpSection);      //ö��ȫ���ļ�ֵ
	int GetKeyValues(CStringArray& arrKey, CStringArray& arrValue, LPCTSTR lpSection);   //ö�ٳ�һ���ڵ�ȫ��������ֵ

	BOOL DelAllSections();  //ɾ�����еĶ��� 
//	CString GetExeFullFilePath();//
private:
	CString m_strFileName;
};

#endif // !defined(AFX_INIFILE_H__61921152_E664_4427_80BA_9C1B580D7A4B__INCLUDED_)
