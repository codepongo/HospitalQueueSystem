// NurseStationDoc.cpp : CNurseStationDoc ���ʵ��
//

#include "stdafx.h"
#include "NurseStation.h"

#include "NurseStationDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNurseStationDoc

IMPLEMENT_DYNCREATE(CNurseStationDoc, CDocument)

BEGIN_MESSAGE_MAP(CNurseStationDoc, CDocument)
END_MESSAGE_MAP()


// CNurseStationDoc ����/����

CNurseStationDoc::CNurseStationDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CNurseStationDoc::~CNurseStationDoc()
{
}

BOOL CNurseStationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CNurseStationDoc ���л�

void CNurseStationDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CNurseStationDoc ���

#ifdef _DEBUG
void CNurseStationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNurseStationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CNurseStationDoc ����
