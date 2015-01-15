#pragma once
////����ת���ַ�������
#include <string>
using namespace std;
class CCommonConvert
{
public:
	CCommonConvert(void);
	~CCommonConvert(void);
	static int CStringToChar(CString str,char c_str[]);
	static int CharToCstring(CString& str,char c_str[]);
	static void intToCString(int i,CString& str);
	static void CStringToint(int& i,CString str);
	static BOOL WChar2Char(char* dstBuf, size_t len, const wchar_t* src);
	//��ȡ����IP
	CString GetComputerIP();
	//��ȡ����ִ��·��
	CString GetExeFullFilePath();
	////UTF8תstd::string
	static std::string UTF8_To_string(const std::string & str);
	////std::stringתutf8�ַ���
	static std::string string_To_UTF8(const std::string & str); 
private:
	CString m_strPath;
};
