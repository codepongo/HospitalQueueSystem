// TransButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "HallQueFront.h"
#include "TransButton.h"

extern CDC* g_pBackDC;
//extern void MyWriteConsole(CString str);
// CTransButton

IMPLEMENT_DYNAMIC(CTransButton, CButton)

CTransButton::CTransButton(CWnd* pParentWnd)
{
	ASSERT(pParentWnd!=NULL);
	m_pParentWnd=pParentWnd;
	ButtonInit();
}

CTransButton::~CTransButton()
{	
}


BEGIN_MESSAGE_MAP(CTransButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_WM_ENABLE()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CTransButton ��Ϣ�������

void CTransButton::SetBkColor(const COLORREF color)
{
	m_bkColor=color;
//	Invalidate();
}
void CTransButton::SetTextColor(const COLORREF color)
{
	m_textColor=color;
//	Invalidate();
}

BOOL CTransButton::PreCreateWindow(CREATESTRUCT& cs)
{
	BOOL bRet=CButton::PreCreateWindow(cs);
	return bRet;
}

void CTransButton::PreSubclassWindow()
{
	CButton::PreSubclassWindow();
	ModifyStyle(CS_VREDRAW | CS_HREDRAW,BS_OWNERDRAW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
}
void CTransButton::ButtonInit()
{
	m_ButtonType = enumRoundRectButton;
	m_bkColor=RGB(0,255,0);
	m_textColor=0x000000;
	m_nAlpha=100;
	m_bTracking=FALSE;
	m_bOver=m_bDown=FALSE;
	m_bDisable=TRUE;
	
	///�����ʼ��
	m_lfFont.lfHeight = -MulDiv(15, GetDeviceCaps(m_pParentWnd->GetDC()->GetSafeHdc(), LOGPIXELSY), 72);
	m_lfFont.lfWidth = 0;
	m_lfFont.lfEscapement = 0;
	m_lfFont.lfOrientation = 0;
	m_lfFont.lfWeight = FW_NORMAL;
	m_lfFont.lfItalic = 0;
	m_lfFont.lfUnderline = 0;
	m_lfFont.lfStrikeOut = 0;
	m_lfFont.lfCharSet = ANSI_CHARSET;
	m_lfFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	m_lfFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	m_lfFont.lfQuality = DEFAULT_QUALITY;
	m_lfFont.lfPitchAndFamily = DEFAULT_PITCH | FF_SWISS;
	
	_tcsncpy_s(m_lfFont.lfFaceName, LF_FACESIZE, _T("����"),5);
}

void CTransButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	DrawButton(lpDrawItemStruct->hDC);
}

void CTransButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bTracking)
	{
		m_bOver = TRUE;
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 50;
		m_bTracking = (BOOL)_TrackMouseEvent(&tme);
	}
	CButton::OnMouseMove(nFlags, point);
}

void CTransButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bDown=TRUE;

	CButton::OnLButtonDown(nFlags, point);
}

void CTransButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bDown=FALSE;
	CButton::OnLButtonUp(nFlags, point);
}
LRESULT CTransButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bOver = FALSE;
	m_bTracking = FALSE;
	m_bDown=FALSE;
	Invalidate(TRUE);
	return 0;
}

LRESULT CTransButton::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	m_bOver = TRUE;
	Invalidate(TRUE);
	return 0;
}
void CTransButton::DrawButton()
{
	HDC hDC=::GetDC(m_hWnd);
	DrawButton(hDC);
	::ReleaseDC(m_hWnd,hDC);
}
void CTransButton::DrawButton(HDC hDestDC)
{
	CRect rc;
	GetClientRect(rc);
	
	int nWindth=rc.Width();
	int nHeight=rc.Height();
	
	HDC hDC=CreateCompatibleDC(hDestDC);//��������DC,����˫���廭��	
	HBITMAP hBitmap=CreateCompatibleBitmap(hDestDC,nWindth,nHeight);
	HBITMAP hOldBitmap=(HBITMAP)SelectObject(hDC,hBitmap);

	SetBkMode(hDC,TRANSPARENT);
	//�Ѹ����ڵı���ͼ���Ƶ���ť��DC��,ʵ���Ӿ�͸��----------------
	CPoint pt(0,0);
	MapWindowPoints(m_pParentWnd,&pt,1);
	if(g_pBackDC)
	{
		BitBlt(hDC,0,0,nWindth,nHeight,g_pBackDC->GetSafeHdc(),
			pt.x,pt.y,SRCCOPY);
	}
	//-------------------------------------------------------------
	HDC hMaskDC=CreateCompatibleDC(hDestDC);
	HBITMAP hMaskBitmap=CreateCompatibleBitmap(hDestDC,nWindth,nHeight);
	HBITMAP hOldMaskBitmap=(HBITMAP)SelectObject(hMaskDC,hMaskBitmap);
	int nAlpha=100;//0--255
	int nOffset=0;
	HBRUSH hbr=CreateSolidBrush(m_bkColor);
	FillRect(hMaskDC,&rc,hbr);
	DeleteObject(hbr);

	if(m_bDisable){
		nAlpha=m_nAlpha;
	}else if(m_bDown){
		nAlpha=180;
		nOffset=1;
	}else if(m_bOver){
		nAlpha=150;
	}else{
		nAlpha=m_nAlpha;
	}

	BLENDFUNCTION blend;
	memset( &blend, 0, sizeof( blend) );
	blend.BlendOp= AC_SRC_OVER;
	blend.SourceConstantAlpha= nAlpha; // ͸���� ���255

	HRGN hRgn;
	switch(m_ButtonType)
	{
	case enumRoundRectButton:
		hRgn=CreateRoundRectRgn(0,0,nWindth,nHeight,5,5);
		break;
	case enumRectButton:
		hRgn=CreateRectRgn(0,0,nWindth,nHeight);
		break;
	case enumEllipseButton:
		hRgn=CreateEllipticRgn(0,0,nWindth,nHeight);
		break;
	default:
		break;
	}
	SelectClipRgn (hDC,hRgn);
	//ʵ��͸��
	AlphaBlend (hDC,0,0,nWindth,nHeight,hMaskDC,0,0,nWindth,nHeight,blend);
	/////////////
	SelectObject(hMaskDC,hOldMaskBitmap);
	DeleteObject(hMaskBitmap);
	DeleteDC(hMaskDC);
	//////////////��ʾ����
	CString strText;
	GetWindowText(strText);
	if(strText!=_T(""))
	{
		rc.InflateRect(-2,-2);
		rc.OffsetRect(nOffset,nOffset);
		CFont font;
		font.CreateFontIndirect(&m_lfFont);
		HFONT hOldFont=(HFONT)SelectObject(hDC,font);
		::SetTextColor(hDC,m_textColor);
		::DrawText(hDC,strText,-1,&rc,DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_WORD_ELLIPSIS);
		::SelectObject(hDC,hOldFont);
	}
	SelectClipRgn (hDC,NULL);
	DeleteObject(hRgn);
	//���Ƶ��ؼ���DC��------------------------
	BitBlt(hDestDC,0,0,nWindth,nHeight,hDC,0,0,SRCCOPY);
	//������Դ
	SelectObject(hDC,hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hDC);
}
void CTransButton::OnEnable(BOOL bEnable)
{
	CButton::OnEnable(bEnable);
	m_bDisable=IsWindowEnabled()?FALSE:TRUE;
}

BOOL CTransButton::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	return CButton::OnEraseBkgnd(pDC);
	return TRUE;
}

void CTransButton::SetAlpha(const UINT nAlpha)
{
	m_nAlpha=nAlpha;
//	Invalidate();
}

void CTransButton::SetFont(const LOGFONT lfFont)
{
	m_lfFont = lfFont;
//	Invalidate();
}

void CTransButton::SetButtonType(const ButtonTypeEnum ButtonType)
{
	m_ButtonType = ButtonType;
	Invalidate();
}

void CTransButton::AttachToQueue(const CString& address)
{
	if(address.IsEmpty())
	{
		return;
	}
	m_address=address;
}

void CTransButton::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nChar)
	{
	case VK_ESCAPE:
	case VK_F1:
	case VK_UP:
	case VK_DOWN:
	case VK_LEFT:
	case VK_RIGHT:
		::PostMessage(m_pParentWnd->m_hWnd,WM_KEYDOWN,nChar,nChar);
		break;
	}
	CButton::OnKeyDown(nChar, nRepCnt, nFlags);
}
