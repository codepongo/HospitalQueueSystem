#pragma once
#include "TransButton.h"
#include "TrackDef.h"
#include "TransStatic.h"
/*
CControlRect�̳�CWnd��CRectTrackerʹ�伴����CWnd�����־���
CRectTracker
*/
class CControlRect : public CWnd,public CRectTracker
{
	friend class CTrackContrl;
public:
	CControlRect(void);
	CControlRect(CRect& rect);
	CControlRect(int l,int t,int r,int b);
	virtual ~CControlRect(void);

public:
	//�������ƶ��Ĵ��ڿؼ�
	BOOL Create(WindowType windtype,LPCTSTR lpszWindowName,CWnd* pParentWnd,
		DWORD dwStyle=WS_DISABLED | WS_CLIPCHILDREN,const CRect& rect=CRect(0,0,0,0),UINT nID=0,
		CCreateContext* pContext=NULL,CString loadPicPath=_T(""));

	//��ȡ����ע������
	LPCTSTR GetWndClassName(WindowType type);
	//����CRectTracker���е�Track����
	BOOL Track(CWnd* pWnd,CPoint point,BOOL bAllowInvert = FALSE,
		CWnd* pWndClipTo = NULL);
	//���ô��ڴ�С��λ��
	void SetRect( int x1, int y1, int x2, int y2 );
	void SetRect( const CRect & rect );
	//���ô���ʹ��״̬
	void ModifyWindowAble();
	//���ô��ڱ༭״̬
	void ModifyWindowDisable();
	//��ȡ���ڿؼ�ID
	UINT GetCtrWindowID(){return m_WindowID;}
	//��ȡ�����Ƿ��ڱ༭״̬/ʹ��״̬
	BOOL GetCtrWindowIsable(){return m_Isable;}
	//��ȡ�Ƿ�ѡ��
	BOOL GetCtrWindowSelected(){return m_bSelected;}
	//��д��͸����ť
	CTransButton *m_pTransButton;
	//��д��͸��static �ؼ�
	CTransStatic *m_pTransStatic;
	WindowType GetWindowType(){return m_windType;}
	//�ؼ�����
	void MiddleCtr();
private:
	//��ʼ��CRectTracker
	void Initialize();
	//�Ƿ�ѡ��
	BOOL m_bSelected;
	//���ڿؼ�ID
	UINT m_WindowID;
	//�ؼ��Ƿ���ã������л�ʹ�úͱ༭״̬
	BOOL m_Isable;
	//�ؼ�����
	WindowType m_windType;
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
