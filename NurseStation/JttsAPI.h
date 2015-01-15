#pragma once

#include <afxwin.h>
#include <afxmt.h>
#include "jTTS_ML.h"
#pragma comment(lib, "jTTS_ML.lib")
//#include "NurseDef.h"

typedef struct _tagVoiceAndDisplayStr
{
	CString		strVoiceStr;
	CString		strDisplayStr;
	int				iWndScreenId;
	int				iCompLED;
	int				iThroughLED;
	CString		strOfficeStbId;
	CString		strConsultStbId;
	CString		strCallPatientID;
	CString		strCallPatientName;
	CString		strWaitPatientID;
	CString		strWaitPatientName;
	//BOOL		bScreen;
} VOICEDISPLAYSTR, *LPVOICEDISPLAYSTR;

class CJttsAPI : public CObject
{
public:
	CJttsAPI();
	~CJttsAPI();

	void SetSoundReplayTimes(int iTimes){m_iSoundReplayTimes = iTimes;}
	void LoadConf();

	BOOL InitTTS();
	BOOL EndTTS();
	BOOL SetPlay(
		UINT uDeviceID, //���ΪWAVE_MAPPER(-1)����ʾȱʡ�ķ����豸������Ϊָ���ķ����豸�� 
		HWND hwnd, //һ���Ϸ��Ĵ��ھ������ϵͳ�Ķ�ʱ����Ϻ󣬻ᷢ��һЩ�Զ�����Ϣ���˴��ڡ����ΪNULL����ʹ�ô�����Ϣ�ķ�ʽ֪ͨӦ�ó���
		JTTS_CALLBACKPROC lpfnCallback, //һ���Ϸ��Ļص�������ַ����ϵͳ�Ķ�ʱ����Ϻ󣬻���ô˺�����
		DWORD dwUserData //�û�������Զ������ݣ��ص�ʱ���ش����ص�����
		);

	BOOL AddPlayText(VOICEDISPLAYSTR vdstr);
	void ErrorMessage(ERRCODE err);
private:
	CString GetModuleDir(void);
	BOOL WriteReg(void);
	//static BOOL WChar2Char(char* dstBuf, size_t len, wchar_t* srcBuf);
	static UINT PlayVoiceThread(LPVOID pParam);
private:

	//CList<char*, char*&> m_lstPlayStrList;
	CList<VOICEDISPLAYSTR> m_lstPlayStrList;
	CWinThread* m_pPlayVoiceThread;
	BOOL m_bPlayVoiceThread;
	CMutex m_mtPlayStrList;
	int m_iSoundReplayTimes;
	//CMutex m_mtThreadPlayVoice;


	//CEvent* m_pevtKillThread;

protected:
	JTTS_CONFIG m_config;
	BOOL m_bCallbackFunc,
		 m_bCallbackHwnd;
	int  m_nFormat;
	int	 m_nFileHeadFlag;
	int  m_nInitMethod;
	char* m_szInitPath;
	char* m_szSerialNo;
	char* m_szVoiceInfo;

	int m_nSpeed;	//0~9 ����
	int m_nVolume;//0~9 ����
};