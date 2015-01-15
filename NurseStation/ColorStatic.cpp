// ColorStatic.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NurseStation.h"
#include "ColorStatic.h"


// CColorStatic

IMPLEMENT_DYNAMIC(CColorStatic, CStatic)

CColorStatic::CColorStatic() : m_bkColor(RGB(255,255,255))
{
//	m_bkColor = RGB(255,255,255);
}

CColorStatic::~CColorStatic()
{
}


BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CColorStatic ��Ϣ�������

void CColorStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CStatic::OnPaint()
	HBRUSH hBrush=CreateSolidBrush(m_bkColor);
	CRect rect;
	GetClientRect(&rect);
	FillRect(dc,&rect,hBrush);
	DeleteObject(hBrush);
}

void CColorStatic::SetBkColor(COLORREF color)
{
	m_bkColor = color;
	Invalidate(TRUE);
}