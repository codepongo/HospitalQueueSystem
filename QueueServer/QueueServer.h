// QueueServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
//#include "Control.h"


// CQueueServerApp:
// �йش����ʵ�֣������ QueueServer.cpp
//

class CQueueServerApp : public CWinApp
{
public:
	CQueueServerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

public:
	//CServerController* GetControl()
	//{
	//	return m_pControl;
	//}

private:
	//CServerController* m_pControl;
};

extern CQueueServerApp theApp;