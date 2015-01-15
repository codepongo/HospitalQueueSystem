#pragma once

#include "SLZData.h"
#include "PrintDef.h"
#include "TrackDef.h"
#include <afxmt.h>
//#include <afxwin.h>
#include "atlimage.h"
#include "DrawStars.h"
//��ӡ������winspool
#pragma comment(lib, "winspool.lib")
#include <winspool.h>

class SLZPrinter
{
public:
	SLZPrinter(void);
	~SLZPrinter(void);

	BOOL Print(const SLZData& data,const int waitNum);
	///����ӡ��״̬
	EnumPrintStaus CheckPrinterStatus();
	BOOL Start();
	///���¼�������
	BOOL ReFreshPrintInfo();
private:
	BOOL GetJobs(HANDLE hPrinter,
		JOB_INFO_2 **ppJobInfo,
		int *pcJobs,          
		DWORD *pStatus);
	EnumPrintStaus CheckPrintJobStatus(HANDLE hPrinter);
	HANDLE m_hPrinter;
	CList<SLZData> m_list_printData;
	CMutex m_printLock;
private:
	BOOL LoadPrintInofFromFile();
	CList<WINDOWCTRINFO> m_list_setPrintInfo;
	CString m_printInfoPath;
	//��ӡ�߳�
	HANDLE m_hPrintThread;
	static DWORD WINAPI OnPrint(LPVOID lpParam);
	//��ӡ
	void PrintInfo(SLZData& data);
	//׼����ӡ��Ϣ
	void OnBeginPrinting(CDC *pDC, CPrintInfo* pInfo);
	//���ô�ӡDC
	void SetPrintStyle(CDC* pDC,const WINDOWCTRINFO& info,SLZData& data);
	CImage m_picImage;
	BOOL LoadImage(const CString& path);
	void DrawImageToDC(CDC* pDC,const CRect& rect);
private:
	int m_prWaitNum;//��ӡ�Ŷ�����
	///���ݿͻ����������
	void DrawStarsForClientLev(CDC* pDC,const UINT num,const CRect& rect,
		const UINT level);
	////////////////////////
	//��ӡ������
	CRect m_printRect;
	BOOL LoadPrintRectFormFile();
public:
	BOOL m_isUsePrint;
};
