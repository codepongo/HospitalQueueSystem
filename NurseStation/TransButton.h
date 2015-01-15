#pragma once
#include <atlimage.h>
#include "TrackDef.h"
// CTransButton
#include "ComputeFuncationTime.h"


class CTransButton : public CButton
{
	DECLARE_DYNAMIC(CTransButton)

public:
	CTransButton(CWnd* pParentWnd);
	virtual ~CTransButton();

protected:
	DECLARE_MESSAGE_MAP()

public:
	////����Button�ĸ��ֱ���	
	void SetBkColor(const COLORREF color);
	void SetTextColor(const COLORREF color);
	void SetAlpha(const UINT nAlpha);
	void SetFont(const LOGFONT lfFont);
	void SetButtonType(const ButtonTypeEnum ButtonType);
	///////////////////////////////
	//��ȡButton�ĸ��ֱ���
	COLORREF GetBkColor()const {return m_bkColor;}
	COLORREF GetTextColor()const {return m_textColor;}
	UINT GetAlpha()const {return m_nAlpha;}
	LOGFONT GetFont()const {return m_lfFont;}
	ButtonTypeEnum GetButtonType()const {return m_ButtonType;}
	CString GetAttchAddress()const {return m_address;}
private:
	BOOL m_bOver;
	BOOL m_bDown;
	BOOL m_bDisable;
	BOOL m_bTracking;
	COLORREF m_bkColor;
	COLORREF m_textColor;
	UINT m_nAlpha;
	CWnd* m_pParentWnd;
	LOGFONT m_lfFont;
	ButtonTypeEnum m_ButtonType;
	CString m_address;//���Ӵ���Ķ���
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);//����ť
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEnable(BOOL bEnable);
private:
	void ButtonInit();
	void DrawButton();
	void DrawButton(HDC hDestDC);
//	CRect m_destRect;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//���ܺ�����ȷ����ť��������Ľ��,���Ӷ��л�����ҳ
	void AttachToQueue(const CString& address);
	CComputeFuncationTime m_computeTime;//����ʱ��
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};