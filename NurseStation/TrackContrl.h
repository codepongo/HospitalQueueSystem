#pragma once
#include "afxext.h"
#include "ControlRect.h"
#include "TrackDef.h"
class CTrackContrl : public CRectTracker
{
public:
	CTrackContrl(void);
	virtual ~CTrackContrl(void);
	//��ȾCRectTracker���θ���CRectTracker��Draw
	void Draw(CDC* pDC)const; 
	//���һ��CControlRect�ؼ�
	void Add( CControlRect* pObject );
	//�ı�������໥�ص��Ŀؼ�˳��
	void CorrectZOrders( CWnd* pWndInsertAfter );
	//�жϿؼ��Ƿ�ѡ��
	BOOL IsSelected( CControlRect* pObject ) const;
	//���ؼ�ѡ��
	BOOL Select( CControlRect* pObject );
	//�л��ؼ�ѡ��״̬
	BOOL Toggle( CControlRect* pObject );
	//ɾ����ѡ�еĿؼ�
	BOOL DeSelect( CControlRect* pObject );
	//ɾ�����б�ѡ�пؼ�,���ر�ѡ�еİ�ť����
	int DeSelectAll();
	//����Track
	int Track(const CPoint & point, UINT nFlags = 0,BOOL bTrackRubberBand = TRUE );
	//����CRectTracker����
	void Create(CWnd* pWnd);
	//��ȡѡ�пؼ���
	CRect GetBoundsRect() const;//�����޸ĳ�Ա������ֵ
	//SetCursor��ʾ�����״
	BOOL SetCursor( UINT nHitTest, UINT message );
	//�ı����пؼ���ʹ��״̬
	void SetAllCtrContralEnable();
	//�ı����пؼ�Ϊ�༭״̬
	void SetAllCtrContralDisable();
	//�����ػ��Ĳ���
	void ReDrawRect(CRect &rect,int handleSize);
	//������Ӧ�����μ�CRectTracker
	void OnChangedRect(const CRect& rectOld );
	void AdjustRect(int nHandle,LPRECT lpRect );
	//����Ҽ�ѡ�еĿؼ�(��ǰ�����ڿؼ����ĵĿؼ�)
	CControlRect* m_pRightBnSelect;
	
	//ɾ������Ҽ�ѡ�еĿؼ�
	BOOL DeleteRightBnSelectCtr();
	//ʹ�ؼ�����
	void DoMiddleCtr();
	//�ؼ������
	void AlignLeftCtr();
	//�ؼ��Ҷ���
	void AlignRightCtr();
	//�ؼ����һ��
	void SameWidthCtr();
	//�ؼ��߶�һ��
	void SameHeightCtr();
	//�ؼ���Сһ��
	void SameSizeCtr();
	//������
	void AlignTopCtr();
	//�׶���
	void AlignBottomCtr();
	//����
	void DivideHorCtr();
	//����
	void DivideVerCtr();
	//���༭���˳��༭״̬ʱ�����пؼ�����λ�õ���
	void AlterAllCtrTop(int nAlterTop);
	//�������������ƶ�
	void KeyUpMove();
	void KeyDownMove();
	void KeyLeftMove();
	void KeyRightMove();
	//
	void SetForAdjustMaxRect(BOOL isForAdjustMaxRect){m_bIsForMaxRect = isForAdjustMaxRect;}
	//��������������
	void SetMaxRect(const CRect& maxRect){m_maxMoveRect = maxRect;}
	//������������ʱ������ȷ��
	void ReAdjustMaxRect(CRect& rect,BOOL isSameSize = FALSE/*��С����*/);
private:
	CWnd* m_pwndParent;//������
	//�ͷ�
	void DeleteAllCtrPtr();
	int FindRate(int coor[],const int size);//�ҳ����ִ�����������
	void AlterRectLeft(const int nAlterLeft );//�޸Ŀؼ�λ��,�����
	void AlterRectRight(const  int nAlterRight );//�Ҷ���
	void AlterRectWidth(const int nWidth );//���һ��
	void AlterRectHeight(const int nHeight );//�߶�һ��
	void AlterRectSameSize(const int nWidth,const int nHeight );//��Сһ��
	void AlterRectTop(const int nAlterTop);//������
	void AlterRectBottom(const int nAlterBottom);//�׶���
	//�������ƽ��
	void AlterDivideTop(const int nAlterDivideTop,int coor[],const int nSize);
	//�������ƽ��
	void AlterDivideLeft(const int nAlterDivideWid,int coor[],const int nSize);
	//�鲢���򣬲��ı�ؼ����Ⱥ�˳��
	void Merge(int *SR, int *TR, int i, int m, int n);
	void Msort( int *SR, int *TR1, int s, int t );
	//���ľ��ο�,���������ƶ���������
	CRect m_maxMoveRect;
	//�Ƿ���������ƶ� ���ο�
	BOOL m_bIsForMaxRect;
public:
	CArray<CControlRect*,CControlRect*> m_selectRectTracker;//��ѡ�е�CRectTracker�ؼ�
	CArray<CControlRect*,CControlRect*> m_selTrackerAll;//���е�CRectTracker�ؼ�
};
