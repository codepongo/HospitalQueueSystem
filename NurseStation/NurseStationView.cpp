// NurseStationView.cpp : CNurseStationView ���ʵ��
//

#include "stdafx.h"
#include "NurseStation.h"

#include "NurseStationDoc.h"
#include "NurseStationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNurseStationView
////////////���汳���ڴ�DC
//CDC*         g_pBackDC = new CDC;
//HBITMAP  g_hBackMemBitmap = NULL;
//HBITMAP   g_hOldBackMemBitmap;
///////////////////////////////////

IMPLEMENT_DYNCREATE(CNurseStationView, CView)

BEGIN_MESSAGE_MAP(CNurseStationView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CNurseStationView ����/����

CNurseStationView::CNurseStationView()
{
	// TODO: �ڴ˴���ӹ������

}

CNurseStationView::~CNurseStationView()
{
}

BOOL CNurseStationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CNurseStationView ����

void CNurseStationView::OnDraw(CDC* /*pDC*/)
{
	CNurseStationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CNurseStationView ��ӡ

BOOL CNurseStationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CNurseStationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CNurseStationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CNurseStationView ���

#ifdef _DEBUG
void CNurseStationView::AssertValid() const
{
	CView::AssertValid();
}

void CNurseStationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNurseStationDoc* CNurseStationView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNurseStationDoc)));
	return (CNurseStationDoc*)m_pDocument;
}
#endif //_DEBUG


// CNurseStationView ��Ϣ�������
