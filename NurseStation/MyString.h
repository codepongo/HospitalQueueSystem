#pragma once

class MyString
{
public:
	MyString(void);
	~MyString(void);

	/**
	desc:		���ֽ��ַ��� ת ���ֽ��ַ���

	dstBuf:		Ŀ���ַ���������
	src:		Դ�ַ���

	return:		�ɹ������� TRUE;���򣬷��� FALSE
	*/
	static BOOL WChar2Char(char* dstBuf, size_t len, const wchar_t* src);

	/**
	desc:		���ֽ��ַ��� ת ���ֽ��ַ���

	dstBuf:		Ŀ���ַ���������
	src:		Դ�ַ���

	return:		�ɹ������� TRUE;���򣬷��� FALSE
	*/
	static BOOL Char2WChar(wchar_t* dstBuf,size_t len,const char *src);

	/**
	desc:		���ַ����в������ַ�����һ�γ��ֵ��±�
	strSrc:		Դ�ַ���
	strFind:	Ҫ���ҵ��ַ���

	return:		���ҳɹ��������������ַ�����һ�γ��ֵ��±ꣻ
	���򣬷��� -1
	*/
	static int Find(CString strSrc, CString strFind);

	/**
	desc:		���ַ����в������ַ�����һ�γ��ֵ��±�, �����ִ�Сд
	strSrc:		Դ�ַ���
	strFind:	Ҫ���ҵ��ַ���

	return:		���ҳɹ��������������ַ�����һ�γ��ֵ��±ꣻ
	���򣬷��� -1
	*/
	static int FindNoCase(CString strSrc, CString strFind);

	static int ReverseFind(CString strSrc, CString strFind);

	static int ReverseFindNoCase(CString strSrc, CString strFind);

	/**
	desc:		��Դ�ַ����е��ַ����滻�����ַ���

	strSrc:		Դ�ַ���
	strFrom:	Ҫ�滻���ַ���
	strTo:		�����滻�����ַ���

	return:		�����滻������ַ���
	*/
	static CString Replace(CString strSrc, CString strFrom, CString strTo);

	/**
	desc:			���ַ������ݷָ����ָ���ַ�������, 
	�ָ���������һ���ַ���Ҳ�����Ƕ���ַ���
	���磬_T("\n") �� _T(" ") �� _T(" \n,.��")

	strSrc:			Դ�ַ���
	arrStrDest:		�ַ������飬����ָ�õ��ַ���
	strDivisionSet:	�ָ�����

	return:			�ɹ������� TRUE�����򣬷��� FALSE
	*/
	static BOOL Split(CString strSrc, CStringArray& arrStrDest, CString strDivisionSet);

	static int FindCharNoCase(CString& strSrc, wchar_t chFind);

	static int ReverseFindCharNoCase(CString& strSrc, wchar_t chFind);

	/**
	desc:		�Ƚ��������ַ��Ƿ����, �����ִ�Сд
	return:		��ȣ����� TRUE�����򣬷��� FALSE
	*/
	static BOOL CompareCharNoCase(wchar_t ch1, wchar_t ch2);

	/**
	desc:				���ַ����л�ȡ����ֵ

	strSrc:				Դ�ַ���
	strProfileName:		Ҫ��ȡ��������
	strProfileValue:	�����ȡ��������ֵ

	return:				�ɹ������� TRUE�����򣬷��� FALSE
	*/
	static BOOL GetProfileFromString(CString strSrc, CString strProfileName, 
		CString& strProfileValue, wchar_t wchSplitNameValue, wchar_t wchSplitProfile);

	/**
	desc:				���ַ����л�ȡ����ֵ����������������Сд

	strSrc:				Դ�ַ���
	strProfileName:		Ҫ��ȡ��������
	strProfileValue:	�����ȡ��������ֵ

	return:				�ɹ������� TRUE�����򣬷��� FALSE
	*/
	static BOOL GetProfileFromStringNoCase(CString strSrc, CString strProfileName, 
		CString& strProfileValue, wchar_t wchSplitNameValue, wchar_t wchSplitProfile);

	/**
	desc:		���������ַ��� ת�� ��������

	strNum:		�����ַ���

	return:		���� ת���õ���������
	*/
	static int Str2Int(CString strNum);

	/**
	desc:		�������� ת�� ���������ַ��� 

	iNum:		��������

	return:		���� ת���õ����������ַ���
	*/
	static CString Int2Str(int iNum);
};
