#pragma once

//#define MY_DEFAULT_LOCAL_PORT		4020		//ȱʡϵͳ�ڶ˿�
//#define MY_DEFAULT_OPEN_PORT		8888		//ȱʡ��������˿�

class MyPort
{
public:
	MyPort(void);
	~MyPort(void);

	USHORT GetLocalPort(USHORT uDefaultPort);
	USHORT GetOpenPort(USHORT uDefaultPort);
	BOOL SetLocalPort(CString strPort);
	BOOL SetOpenPort(CString strPort);
private:
	USHORT GetPort(CString strKeyName, USHORT uDefaultPort);
	BOOL SetPort(CString strKeyName, USHORT uPort);
};
