// NurseStationView.h : CNurseStationView ��Ľӿ�
//


#pragma once


class CNurseStationView : public CView
{
protected: // �������л�����
	CNurseStationView();
	DECLARE_DYNCREATE(CNurseStationView)

// ����
public:
	CNurseStationDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CNurseStationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // NurseStationView.cpp �еĵ��԰汾
inline CNurseStationDoc* CNurseStationView::GetDocument() const
   { return reinterpret_cast<CNurseStationDoc*>(m_pDocument); }
#endif

