#pragma once


// CColorStatic
/*
�̳��Ծ�̬�ؼ���ר��������ʾ��ɫ
*/
class CColorStatic : public CStatic
{
	DECLARE_DYNAMIC(CColorStatic)

public:
	CColorStatic();
	virtual ~CColorStatic();
	afx_msg void OnPaint();
	void SetBkColor(COLORREF color);
protected:
	DECLARE_MESSAGE_MAP()
	COLORREF m_bkColor;
};


