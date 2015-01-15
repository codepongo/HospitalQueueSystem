#pragma once
#include <atlimage.h>
#include "TrackDef.h"
#include "ComputeFuncationTime.h"
#include "PrintDef.h"
//#include "TransparentHelper.h"
// CTransStatic


class CTransStatic : public CStatic
{
	DECLARE_DYNAMIC(CTransStatic)

public:
	CTransStatic(CWnd* pParentWnd,CString loadPicPath=_T(""));
	virtual ~CTransStatic();
protected:
	DECLARE_MESSAGE_MAP()
private:
	COLORREF m_bkColor;
	COLORREF m_textColor;
	UINT m_nAlpha;
	CWnd* m_pParentWnd;
	LOGFONT m_lfFont;
	
	void StaticInit();
	void DrawStatic(HDC hDestDC);
	
	CRect m_clientRect;
	StaticTextAlign m_enmTextAlign;
	CImage m_loadImage;//���ص�ͼƬ
	CString m_loadPicPath;//����ͼƬ·��
	BOOL m_bIsShowTime;//�Ƿ���ʾʱ��
	BOOL m_bIsShowQueNum;//�Ƿ���ʾ�Ŷ�����
	BOOL m_bIsForPrint;//�Ƿ�Ϊ��ӡ׼��
	StaticTimeFormat m_timeFormat;//ʱ���ʽ
	CString m_address;//���Ӵ���Ķ���
	CString m_forShowQueNumHead;//��ʾ�Ŷ�������ͷ�ַ���
	//�磺�Ŷ�������+����
	
	BOOL m_bIsForPrintChangeObject;//Ϊ��ӡ׼���ı�����:ҵ�����͵�
	EnumPrintObject m_printObject;//��ӡ�ı���
protected:
	virtual void PreSubclassWindow();
public:
	//
	void SetForShowQueNumHead(const CString& head){m_forShowQueNumHead = head;}
	CString GetForShowQueNumHead()const {return m_forShowQueNumHead;}
	//���ӵ�ַ����
	void SetLinkAddress(const CString& address){m_address = address;}
	CString GetLinkAddress()const {return m_address;}
	//������ʾʱ�����
	BOOL GetIsShowTime(){return m_bIsShowTime;}
	BOOL GetIsShowQueNum()const {return m_bIsShowQueNum;}
	void SetShowTime(BOOL isShow){m_bIsShowTime=isShow;}
	void SetShowQueNum(BOOL isShow){m_bIsShowQueNum=isShow;}
	StaticTimeFormat GetTimeFormat()const {return m_timeFormat;}
	void SetTimeFormat(StaticTimeFormat timeFormat){m_timeFormat=timeFormat;}
	//�����ı���ɫ���屳����ɫ͸�����Լ����뷽ʽ
	void SetBkColor(const COLORREF color);
	void SetTextColor(const COLORREF color);
	void SetAlpha(const UINT alpha);
	void SetFont(const LOGFONT lfFont);
	void SetStaticTextAlign(StaticTextAlign textAlign);

	COLORREF GetBkColor()const {return m_bkColor;}
	COLORREF GetTextColor()const {return m_textColor;}
	LOGFONT GetTextFont()const {return m_lfFont;}
	UINT GetAlpha()const {return m_nAlpha;}
	StaticTextAlign GetStaticTextAlign()const {return m_enmTextAlign;}
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void ShowText(HDC hDC,CRect& rc);
	BOOL IsForImage();
	void SetLoadImagePath(const CString& path){m_loadPicPath = path;}
	CString GetLoadImagePath(){return m_loadPicPath;}
	BOOL LoadPathImage();//����ͼƬ
	void DrawPathImageToDC(HDC hDC);
private:
	CComputeFuncationTime m_Time;
public:
	void SetStaticForPrint(BOOL isForPrint){m_bIsForPrint = isForPrint;}
	BOOL GetStaticForPrint(){return m_bIsForPrint;}
	void SetStaForPrintChangeObject(BOOL isForChangeObject){
		m_bIsForPrintChangeObject = isForChangeObject;
	}
	BOOL GetStaForPrintChangeObject(){return m_bIsForPrintChangeObject;}
	void SetStaForPrintObject(EnumPrintObject printObject){m_printObject = printObject;}
	EnumPrintObject GetStaPrintObject(){return m_printObject;}
};


