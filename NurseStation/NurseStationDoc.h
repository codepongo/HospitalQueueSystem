// NurseStationDoc.h : CNurseStationDoc ��Ľӿ�
//


#pragma once


class CNurseStationDoc : public CDocument
{
protected: // �������л�����
	CNurseStationDoc();
	DECLARE_DYNCREATE(CNurseStationDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CNurseStationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


