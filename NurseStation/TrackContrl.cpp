#include "StdAfx.h"
#include "TrackContrl.h"

extern UINT g_WindowID;
void MyWriteConsole(CString str);

CTrackContrl::CTrackContrl(void) : m_pwndParent( NULL )
,m_pRightBnSelect(NULL),m_bIsForMaxRect(FALSE)
{
	
}

CTrackContrl::~CTrackContrl(void)
{
	DeleteAllCtrPtr();
}

void CTrackContrl::Draw(CDC* pDC) const
{
	for(int i=0;i<m_selectRectTracker.GetSize();i++)
	{
		if(m_selectRectTracker[i]->m_bSelected &&
			!m_selectRectTracker[i]->GetCtrWindowIsable())
		{
			m_selectRectTracker[i]->Invalidate(TRUE);//�ػ�����
			m_selectRectTracker[i]->Draw(pDC);//�ػ�
		}
	}
	
	for(int i=0;i<m_selTrackerAll.GetSize();i++)
	{
		if(!m_selTrackerAll[i]->m_bSelected)
			m_selTrackerAll[i]->Invalidate(TRUE);
	}
	
}

void CTrackContrl::Add( CControlRect* pObject )
{
	m_selTrackerAll.Add(pObject);
//	CorrectZOrders(pObject);//���ô���z_order˳��
}

void CTrackContrl::CorrectZOrders( CWnd* pWndInsertAfter )
{
	for( int i=0; i < m_selTrackerAll.GetSize(); i++ )	
	{
		//�μ�SetWindowPos
		m_selTrackerAll.GetAt( i )->SetWindowPos( pWndInsertAfter , 0,0,0,0,
			SWP_NOMOVE   | SWP_NOSIZE   | SWP_SHOWWINDOW   );
	}
}

BOOL CTrackContrl::IsSelected( CControlRect* pObject ) const
{
	for( int i=0; i < m_selectRectTracker.GetSize(); i++ )
	{
		if( m_selectRectTracker[i] == pObject )
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CTrackContrl::Select( CControlRect* pObject )
{
	if( ! IsSelected( pObject ) )
	{
		m_selectRectTracker.Add( pObject );
		pObject->m_bSelected = TRUE;
		ReDrawRect(pObject->m_rect,pObject->m_nHandleSize);

		return TRUE;
	}

	return FALSE;
}
//�л�ѡ��״̬
BOOL CTrackContrl::Toggle( CControlRect* pObject )
{
	if( IsSelected( pObject ) )
	{
		DeSelect( pObject );
		return TRUE;
	}
	else
	{
		Select( pObject );
		return FALSE;
	}
}

BOOL CTrackContrl::DeSelect( CControlRect* pObject )
{
	if(IsSelected(pObject))
	{
		for(int i=0;i<m_selectRectTracker.GetSize();i++)
		{
			if(m_selectRectTracker[i]==pObject)
			{
				m_selectRectTracker.RemoveAt(i);
				ReDrawRect(pObject->m_rect,pObject->m_nHandleSize);
			}
		}
		pObject->m_bSelected=FALSE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CTrackContrl::DeSelectAll()
{
	int count=m_selectRectTracker.GetSize();
	for(int i=0;i<m_selTrackerAll.GetSize();i++)
	{
		m_selTrackerAll[i]->m_bSelected = FALSE;
	}
	for(int i=0;i<count;i++)
	{
		CRect rect=m_selectRectTracker[i]->m_rect;
		ReDrawRect(rect,m_selectRectTracker[i]->m_nHandleSize);
	}
	m_selectRectTracker.RemoveAll();
	return count;
}

int CTrackContrl::Track( const CPoint & point, UINT nFlags /* = 0 */,BOOL bTrackRubberBand /* = TRUE */ )
{
	ASSERT(m_pwndParent != NULL);
	CRect InitialBoundRect;
	int pX, pY;
	if(nFlags == MK_LBUTTON || nFlags== (MK_LBUTTON | MK_CONTROL)
		|| nFlags==(MK_LBUTTON | MK_SHIFT))
	{
		for(int i=0;i<m_selTrackerAll.GetSize();i++)
		{
			int Hit=m_selTrackerAll[i]->HitTest(point);//�ж��û��Ƿ�ץס��һ��handle
			if(m_selTrackerAll[i]->GetCtrWindowIsable())
			{
				return TRACK_CTR_ABLE;
			}
			if(Hit!=CRectTracker::hitNothing)
			{
				//�ж�ctrl����
				if( ( nFlags & MK_CONTROL ) != 0 )
				{
					Toggle( m_selTrackerAll[i] );
					return TRACK_CTR_CTRL;						
				}	
				//shift
				if( ( nFlags & MK_SHIFT ) != 0 )
				{
					Select( m_selTrackerAll[i] );
					return TRACK_CTR_SHIFT;
				}
				//û��ctrl shiftʱ ����ؼ�������
				if(!IsSelected(m_selTrackerAll[i]))//��ѡ������������ؼ��Ƿ��Ѿ�ѡ����
					DeSelectAll();//ɾ������������ѡ��
				Select( m_selTrackerAll[i] );//ѡ�е�ǰ�ؼ�

				InitialBoundRect = GetBoundsRect();//��ȡû���ƶ�ǰ��CRect
				///////��û���ƶ�ǰ��Rect������ǰTrackContrl��Rect
				m_rect.CopyRect( & InitialBoundRect );

				if(Hit ==  CRectTracker::hitMiddle)//�û�ץס�м�μ�MSDN  CRectTracker::HitTest
				{
					CRectTracker::Track( m_pwndParent, point);//�û��������λ��,��������m_rect��			
					pX = InitialBoundRect.left - m_rect.left;
					pY = InitialBoundRect.top - m_rect.top;
					
					// �ѿؼ��ƶ������λ��
					for( int j = 0; j < m_selectRectTracker.GetSize(); j++ )
					{
						//������ѡ�еĿؼ�
						int Hit=m_selectRectTracker[j]->HitTest(point);
						if(!m_selectRectTracker[j]->GetCtrWindowIsable() && Hit != CRectTracker::hitNothing)
						{
							m_pRightBnSelect = m_selectRectTracker[j];	
						}
						/////////////////////////////////////////
						//////////////////////////////�ƶ�
						CRect rect;
						rect.left = m_selectRectTracker[j]->m_rect.left - pX;
						rect.right = m_selectRectTracker[j]->m_rect.right - pX;
						rect.top = m_selectRectTracker[j]->m_rect.top - pY;
						rect.bottom = m_selectRectTracker[j]->m_rect.bottom - pY;
						//�������ζԱ�
						ReAdjustMaxRect(rect,TRUE);
						m_selectRectTracker[j]->SetRect(rect);
						///////////////////////////////�ػ�
						ReDrawRect(m_selectRectTracker[j]->m_rect,m_selectRectTracker[j]->m_nHandleSize);
					}
					/////�ػ�Old����
					ReDrawRect(InitialBoundRect,m_selTrackerAll[0]->m_nHandleSize);
				}
				else
				{
					/////////////////////////������С
					m_selTrackerAll[i]->Track( m_pwndParent, point );
					/////////////////////////�����������Ա�
					ReAdjustMaxRect(m_selTrackerAll[i]->m_rect);
					m_selTrackerAll[i]->SetRect(m_selTrackerAll[i]->m_rect);
					///////�ػ�
					ReDrawRect(m_selTrackerAll[i]->m_rect,m_selTrackerAll[i]->m_nHandleSize);
					ReDrawRect(InitialBoundRect,m_selTrackerAll[i]->m_nHandleSize);
				}
				return TRACK_CTR_MIDORHANDLE;
			}
		}
		//�û����û��ץס�κοؼ���handle	
		DeSelectAll();//ɾ�����������ѡ�а�ť
		//����bTrackRubberBand�����Ƿ����߿�����,�μ�TrackRubberBand����,
		//��windows������ѡ����������߿����������Ͽ����϶�һ�����߿�ѡ��n��ͼ��
		if(!bTrackRubberBand)
		{
			m_pwndParent->Invalidate();
			return TRACK_CTR_RUBBERBAND;
		}
		TrackRubberBand( m_pwndParent, point );
		//  TrackRubberBand��ʾ��Ƥ��㣨Windows������ѡ������߿򣩣�
		//	�ú���һ���ڴ���WM_LBUTTONDOWN��Ϣ�ĺ����б����ã�
		//	�����е�һ��������ӵ����Ƥ����εĴ���ָ�룬�ڶ��������ǵ�����꣬
		//	�������������ڿ����Ƿ�������ѡ�񣬼������½ǵ����Ͻǽ���ѡ��
		m_rect.NormalizeRect();//һ�������ľ��Σ�����������ϻ����ο򣬺���������top��bottom
		//ͬ����������ʱ����left��right
		CRect temp;
		for(int k=0;k<m_selTrackerAll.GetSize();k++)
		{
			//intersectRect�����������εĽ���
			temp.IntersectRect(&m_rect,&m_selTrackerAll[k]->m_rect);
			//����������ε��ڿؼ����Σ�ѡ��
			if(temp.EqualRect(&m_selTrackerAll[k]->m_rect))
				Select(m_selTrackerAll[k]);
		}
		return TRACK_CTR_LBUTTON;
	}
	else if(nFlags & MK_RBUTTON)
	{
		int flag = TRACK_CTR_OTHER;
		for(int i=0;i<m_selTrackerAll.GetSize();i++)
		{
			int Hit=m_selTrackerAll[i]->HitTest(point);//�ж��û��Ƿ�ץס��һ��handle
			if(m_selTrackerAll[i]->GetCtrWindowIsable())
			{
				flag = TRACK_CTR_ABLE;
				return flag;
			}
			if(Hit != CRectTracker::hitNothing)
			{
				if(!IsSelected(m_selTrackerAll[i]))//��ѡ������������ؼ��Ƿ��Ѿ�ѡ����
					DeSelectAll();//ɾ������������ѡ��
				Select( m_selTrackerAll[i] );//ѡ�е�ǰ�ؼ�
			
				m_pRightBnSelect = m_selTrackerAll[i];
				flag = TRACK_CTR_RBUTTON;
			}
		}
		return flag;
	}
	else 
	{
		return TRACK_CTR_OTHER;
	}
}

void CTrackContrl::Create(CWnd* pWnd)
{
	ASSERT(pWnd!=NULL);
	m_pwndParent=pWnd;
}

CRect CTrackContrl::GetBoundsRect() const
{
	int Left=0, Right=0, Top=0, Bottom=0;
	int pLeft=0, pRight=0, pTop=0, pBottom=0;

	pLeft=m_selectRectTracker[0]->m_rect.left;
	pTop=m_selectRectTracker[0]->m_rect.top;
	pRight=m_selectRectTracker[0]->m_rect.right;
	pBottom=m_selectRectTracker[0]->m_rect.bottom;
	//���ѡ���˶���ؼ���ȡ��������

	for(int i=1;i<m_selectRectTracker.GetSize();i++)
	{
		Left = m_selectRectTracker[i]->m_rect.left;
		Right = m_selectRectTracker[i]->m_rect.right;
		Top = m_selectRectTracker[i]->m_rect.top;
		Bottom = m_selectRectTracker[i]->m_rect.bottom;

		if(Left<pLeft)
			pLeft=Left;
		if(Top<pTop)
			pTop=Top;
		if(Right>pRight)
			pRight=Right;
		if(Bottom>pBottom)
			pBottom=Bottom;
	}
	return CRect(pLeft,pTop,pRight,pBottom);
}

BOOL CTrackContrl::SetCursor( UINT nHitTest, UINT message )
{
	ASSERT( m_pwndParent != NULL );

	for( int i=0; i < m_selTrackerAll.GetSize(); i++ )
	{	
		if(!m_selTrackerAll[i]->GetCtrWindowIsable())
		{
			if( m_selTrackerAll[i]->SetCursor( m_pwndParent, nHitTest ) )
				return TRUE;
		}
	}	

	return FALSE;
}

void CTrackContrl::SetAllCtrContralEnable()
{
	for(int i=0;i<m_selTrackerAll.GetSize();i++)
	{
		m_selTrackerAll[i]->ModifyWindowAble();
	}
}

void CTrackContrl::SetAllCtrContralDisable()
{
	for(int i=0;i<m_selTrackerAll.GetSize();i++)
	{
		m_selTrackerAll[i]->ModifyWindowDisable();		
	}
}

void CTrackContrl::ReDrawRect(CRect &rect,int handleSize)
{
	ASSERT(m_pwndParent!=NULL);
	CRect destRect = rect;
	destRect.left -= handleSize;
	destRect.top -= handleSize;
	destRect.right += handleSize;
	destRect.bottom += handleSize;
	m_pwndParent->InvalidateRect(destRect,TRUE);
}

void CTrackContrl::OnChangedRect(const CRect &rectOld)
{
//	m_pwndParent->Invalidate(TRUE);
	CDC* pDC = m_pwndParent->GetDC();
	Draw(pDC);
	m_pwndParent->ReleaseDC(pDC);
}

void CTrackContrl::AdjustRect(int nHandle,LPRECT lpRect )
{
//	CRect rect = *lpRect;
//	ReDrawRect(rect,6);
//	m_pwndParent->Invalidate(TRUE);
}

BOOL CTrackContrl::DeleteRightBnSelectCtr()
{
	if(m_pRightBnSelect)
	{
		CRect rect = m_pRightBnSelect->m_rect;
		int handsize = m_pRightBnSelect->m_nHandleSize; 
		for(int i=0;i<m_selTrackerAll.GetSize();i++)
		{
			if(m_pRightBnSelect == m_selTrackerAll[i])
			{
				delete m_pRightBnSelect;
				m_selTrackerAll.RemoveAt(i);
				break;
			}
		}

		for(int i=0;i<m_selectRectTracker.GetSize();i++)
		{
			if(m_pRightBnSelect == m_selectRectTracker[i])
			{
				m_selectRectTracker.RemoveAt(i);
				ReDrawRect(rect,handsize);
				break;
			}
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CTrackContrl::DoMiddleCtr()
{
	for(int i=0;i<m_selectRectTracker.GetSize();i++)
	{
		m_selectRectTracker[i]->MiddleCtr();
	}
}

void CTrackContrl::AlignLeftCtr()
{
	if(m_selectRectTracker.GetSize()<=1)
	{
		return;
	}

	int *coor = new int[m_selectRectTracker.GetSize()];

	int minLeftCoor = m_selectRectTracker[0]->m_rect.left;//������

	for(int i=0;i<m_selectRectTracker.GetSize();i++)
	{
		minLeftCoor = minLeftCoor > m_selectRectTracker[i]->m_rect.left ? 
			m_selectRectTracker[i]->m_rect.left : minLeftCoor; 
		coor[i] = m_selectRectTracker[i]->m_rect.left;		
	}

	int most = FindRate(coor,m_selectRectTracker.GetSize());//�ҳ����ִ�����������
	delete [] coor;
	
	if(most==0)
	{
		AlterRectLeft(minLeftCoor);
	}
	else
	{
		AlterRectLeft(most);
	}
}

void CTrackContrl::AlignRightCtr()
{
	if(m_selectRectTracker.GetSize()<=1)
	{
		return;
	}
	int *coor = new int[m_selectRectTracker.GetSize()];

	int maxRightCoor = m_selectRectTracker[0]->m_rect.right;//������
	for(int i=0;i<m_selectRectTracker.GetSize();i++)
	{
		maxRightCoor = maxRightCoor < m_selectRectTracker[i]->m_rect.right ? 
			m_selectRectTracker[i]->m_rect.right : maxRightCoor; 
		coor[i] = m_selectRectTracker[i]->m_rect.right;		
	}

	int most = FindRate(coor,m_selectRectTracker.GetSize());//�ҳ����ִ�����������

	delete [] coor;

	if(most==0)
	{
		AlterRectRight(maxRightCoor);
	}
	else
	{
		AlterRectRight(most);
	}
}

int CTrackContrl::FindRate(int coor[],const int size)
{
//	int *b = (int*) malloc(size * sizeof(int));
	int *b = new int[size];
	memset(b,0,size * sizeof(int));
	
	for(int i=0;i<size-1;i++)
	{
		for(int j=i+1;j<size;j++)
		{
			if(coor[i]==coor[j])
			{
				b[i]++;
			}
		}
	}
	int max = 0;
	for(int i=0;i<size;i++)
	{
		max = max>b[i]  ? max : b[i]; 	
	}

	if(max == 0)
	{
		delete [] b;
		return 0;
	}

	int most = 0;
	for(int i=0;i<size;i++)
	{
		if(max == b[i])
		{
			most = coor[i];
		}
	}
	delete [] b;

	return most;
}

void CTrackContrl::AlterRectLeft( const int nAlterLeft )
{
	for(int i=0;i<m_selectRectTracker.GetSize();i++)
	{
		CRect rect;
		rect.left = nAlterLeft;
		rect.right = m_selectRectTracker[i]->m_rect.right + 
			nAlterLeft - m_selectRectTracker[i]->m_rect.left;
		rect.top = m_selectRectTracker[i]->m_rect.top;
		rect.bottom = m_selectRectTracker[i]->m_rect.bottom;
	
		CRect oldRect;//��ȡû���ƶ�ǰ��rect
		m_selectRectTracker[i]->GetTrueRect(&oldRect);

		m_selectRectTracker[i]->m_rect = rect;//���µ�λ�ø����ؼ�
		m_selectRectTracker[i]->MoveWindow(&rect,FALSE);
		
		CRect newRect;//��ȡ�µ�rect
		m_selectRectTracker[i]->GetTrueRect(&newRect);
		
		//�ػ�
		m_selectRectTracker[i]->GetParent()->InvalidateRect(oldRect,TRUE);
		m_selectRectTracker[i]->GetParent()->InvalidateRect(newRect,TRUE);
	}
}

void CTrackContrl::AlterRectRight(const int nAlterRight )
{
	for(int i=0;i<m_selectRectTracker.GetSize();i++)
	{
		CRect rect;
		rect.right = nAlterRight;
		rect.left = m_selectRectTracker[i]->m_rect.left + 
			nAlterRight - m_selectRectTracker[i]->m_rect.right;
		rect.top = m_selectRectTracker[i]->m_rect.top;
		rect.bottom = m_selectRectTracker[i]->m_rect.bottom;

		CRect oldRect;//��ȡû���ƶ�ǰ��rect
		m_selectRectTracker[i]->GetTrueRect(&oldRect);

		m_selectRectTracker[i]->m_rect = rect;//���µ�λ�ø����ؼ�
		m_selectRectTracker[i]->MoveWindow(&rect,FALSE);

		CRect newRect;//��ȡ�µ�rect
		m_selectRectTracker[i]->GetTrueRect(&newRect);

		//�ػ�
		m_selectRectTracker[i]->GetParent()->InvalidateRect(oldRect,TRUE);
		m_selectRectTracker[i]->GetParent()->InvalidateRect(newRect,TRUE);
	}
}

void CTrackContrl::SameWidthCtr()
{
	if(m_selectRectTracker.GetSize()<=1)
	{
		return;
	}
	int *coor = new int[m_selectRectTracker.GetSize()];

	int nFirstWidth = m_selectRectTracker[0]->m_rect.Width();//��һ���ؼ��Ŀ�
	for(int i=0;i<m_selectRectTracker.GetSize();i++)
	{
		coor[i] = m_selectRectTracker[i]->m_rect.Width();		
	}

	int most = FindRate(coor,m_selectRectTracker.GetSize());//�ҳ����ִ�����������

	delete [] coor;

	if(most==0)
	{
		AlterRectWidth(nFirstWidth);
	}
	else
	{
		AlterRectWidth(most);
	}
}

void CTrackContrl::SameHeightCtr()
{
	if(m_selectRectTracker.GetSize()<=1)
	{
		return;
	}
	int *coor = new int[m_selectRectTracker.GetSize()];

	int nFirstHeight = m_selectRectTracker[0]->m_rect.Height();//��һ���ؼ��ĸ�
	for(int i=0;i<m_selectRectTracker.GetSize();i++)
	{
		coor[i] = m_selectRectTracker[i]->m_rect.Height();		
	}

	int most = FindRate(coor,m_selectRectTracker.GetSize());//�ҳ����ִ�����������

	delete [] coor;

	if(most==0)
	{
		AlterRectHeight(nFirstHeight);
	}
	else
	{
		AlterRectHeight(most);
	}
}

void CTrackContrl::SameSizeCtr()
{
	if(m_selectRectTracker.GetSize()<=1)
	{
		return;
	}
	int *coorWidth = new int[m_selectRectTracker.GetSize()];
	int *coorHeight = new int[m_selectRectTracker.GetSize()];

	int nFirstHeight = m_selectRectTracker[0]->m_rect.Height();//��һ���ؼ��ĸ�
	int nFirstWidth = m_selectRectTracker[0]->m_rect.Width();//��

	for(int i=0;i<m_selectRectTracker.GetSize();i++)
	{
		coorHeight[i] = m_selectRectTracker[i]->m_rect.Height();
		coorWidth[i] = m_selectRectTracker[i]->m_rect.Width();
	}

	int mostWidth = FindRate(coorWidth,m_selectRectTracker.GetSize());//�ҳ����ִ�����������
	int mostHeight = FindRate(coorHeight,m_selectRectTracker.GetSize());

	delete [] coorWidth;
	delete [] coorHeight;

	if(mostWidth == 0 || mostHeight == 0)
	{
		AlterRectSameSize(nFirstWidth,nFirstHeight);
	}
	else
	{
		AlterRectSameSize(mostWidth,mostHeight);
	}
}

void CTrackContrl::AlterRectWidth(const int nWidth )
{
	for(int i=0;i<m_selectRectTracker.GetSize();i++)
	{
		CRect rect;
		rect.left = m_selectRectTracker[i]->m_rect.left;
		rect.right = m_selectRectTracker[i]->m_rect.right + 
			nWidth - m_selectRectTracker[i]->m_rect.Width();

		rect.top = m_selectRectTracker[i]->m_rect.top;
		rect.bottom = m_selectRectTracker[i]->m_rect.bottom;

		CRect oldRect;//��ȡû���ƶ�ǰ��rect
		m_selectRectTracker[i]->GetTrueRect(&oldRect);

		m_selectRectTracker[i]->m_rect = rect;//���µ�λ�ø����ؼ�
		m_selectRectTracker[i]->MoveWindow(&rect,FALSE);

		CRect newRect;//��ȡ�µ�rect
		m_selectRectTracker[i]->GetTrueRect(&newRect);

		//�ػ�
		m_selectRectTracker[i]->GetParent()->InvalidateRect(oldRect,TRUE);
		m_selectRectTracker[i]->GetParent()->InvalidateRect(newRect,TRUE);
	}
}

void CTrackContrl::AlterRectHeight(const int nHeight )
{
	for(int i=0;i<m_selectRectTracker.GetSize();i++)
	{
		CRect rect;
		rect.left = m_selectRectTracker[i]->m_rect.left;
		rect.right = m_selectRectTracker[i]->m_rect.right;

		rect.top = m_selectRectTracker[i]->m_rect.top;

		rect.bottom = m_selectRectTracker[i]->m_rect.bottom +
			nHeight - m_selectRectTracker[i]->m_rect.Height();

		CRect oldRect;//��ȡû���ƶ�ǰ��rect
		m_selectRectTracker[i]->GetTrueRect(&oldRect);

		m_selectRectTracker[i]->m_rect = rect;//���µ�λ�ø����ؼ�
		m_selectRectTracker[i]->MoveWindow(&rect,FALSE);

		CRect newRect;//��ȡ�µ�rect
		m_selectRectTracker[i]->GetTrueRect(&newRect);

		//�ػ�
		m_selectRectTracker[i]->GetParent()->InvalidateRect(oldRect,TRUE);
		m_selectRectTracker[i]->GetParent()->InvalidateRect(newRect,TRUE);
	}
}

void CTrackContrl::AlterRectSameSize(const int nWidth,const int nHeight )
{
	for(int i=0;i<m_selectRectTracker.GetSize();i++)
	{
		CRect rect;
		rect.left = m_selectRectTracker[i]->m_rect.left;
		rect.right = m_selectRectTracker[i]->m_rect.right +
			nWidth - m_selectRectTracker[i]->m_rect.Width();

		rect.top = m_selectRectTracker[i]->m_rect.top;

		rect.bottom = m_selectRectTracker[i]->m_rect.bottom +
			nHeight - m_selectRectTracker[i]->m_rect.Height();

		CRect oldRect;//��ȡû���ƶ�ǰ��rect
		m_selectRectTracker[i]->GetTrueRect(&oldRect);

		m_selectRectTracker[i]->m_rect = rect;//���µ�λ�ø����ؼ�
		m_selectRectTracker[i]->MoveWindow(&rect,FALSE);

		CRect newRect;//��ȡ�µ�rect
		m_selectRectTracker[i]->GetTrueRect(&newRect);

		//�ػ�
		m_selectRectTracker[i]->GetParent()->InvalidateRect(oldRect,TRUE);
		m_selectRectTracker[i]->GetParent()->InvalidateRect(newRect,TRUE);
	}
}

void CTrackContrl::AlignTopCtr()
{
	if(m_selectRectTracker.GetSize()<=1)
	{
		return;
	}
	int *coor = new int[m_selectRectTracker.GetSize()];

	int minTopCoor = m_selectRectTracker[0]->m_rect.top;//��һ���ؼ��Ķ�
	for(int i=0;i<m_selectRectTracker.GetSize();i++)
	{
		
		minTopCoor = minTopCoor > m_selectRectTracker[i]->m_rect.top ? 
			m_selectRectTracker[i]->m_rect.top : minTopCoor; 
		coor[i] = m_selectRectTracker[i]->m_rect.top;
	}

	int most = FindRate(coor,m_selectRectTracker.GetSize());//�ҳ����ִ�����������

	delete [] coor;

	if(most==0)
	{
		AlterRectTop(minTopCoor);
	}
	else
	{
		AlterRectTop(most);
	}
}

void CTrackContrl::AlignBottomCtr()
{
	if(m_selectRectTracker.GetSize()<=1)
	{
		return;
	}
	int *coor = new int[m_selectRectTracker.GetSize()];

	int maxBottomCoor = m_selectRectTracker[0]->m_rect.bottom;//��һ���ؼ��ĵ�
	for(int i=0;i<m_selectRectTracker.GetSize();i++)
	{
		maxBottomCoor = maxBottomCoor < m_selectRectTracker[i]->m_rect.bottom ? 
			m_selectRectTracker[i]->m_rect.bottom : maxBottomCoor;

		coor[i] = m_selectRectTracker[i]->m_rect.bottom;		
	}

	int most = FindRate(coor,m_selectRectTracker.GetSize());//�ҳ����ִ�����������

	delete [] coor;

	if(most==0)
	{
		AlterRectBottom(maxBottomCoor);
	}
	else
	{
		AlterRectBottom(most);
	}
}

void CTrackContrl::AlterRectTop(const int nAlterTop)
{
	for(int i=0;i<m_selectRectTracker.GetSize();i++)
	{
		CRect rect;
		rect.left = m_selectRectTracker[i]->m_rect.left;
		rect.right = m_selectRectTracker[i]->m_rect.right;

		rect.top = nAlterTop;
		rect.bottom = m_selectRectTracker[i]->m_rect.bottom + 
			nAlterTop - m_selectRectTracker[i]->m_rect.top;

		CRect oldRect;//��ȡû���ƶ�ǰ��rect
		m_selectRectTracker[i]->GetTrueRect(&oldRect);

		m_selectRectTracker[i]->m_rect = rect;//���µ�λ�ø����ؼ�
		m_selectRectTracker[i]->MoveWindow(&rect,FALSE);

		CRect newRect;//��ȡ�µ�rect
		m_selectRectTracker[i]->GetTrueRect(&newRect);

		//�ػ�
		m_selectRectTracker[i]->GetParent()->InvalidateRect(oldRect,TRUE);
		m_selectRectTracker[i]->GetParent()->InvalidateRect(newRect,TRUE);
	}
}

void CTrackContrl::AlterRectBottom(const int nAlterBottom)
{
	for(int i=0;i<m_selectRectTracker.GetSize();i++)
	{
		CRect rect;
		rect.left = m_selectRectTracker[i]->m_rect.left;
		rect.right = m_selectRectTracker[i]->m_rect.right;

		rect.top = m_selectRectTracker[i]->m_rect.top +
			nAlterBottom - m_selectRectTracker[i]->m_rect.bottom;
		rect.bottom = nAlterBottom;

		CRect oldRect;//��ȡû���ƶ�ǰ��rect
		m_selectRectTracker[i]->GetTrueRect(&oldRect);

		m_selectRectTracker[i]->m_rect = rect;//���µ�λ�ø����ؼ�
		m_selectRectTracker[i]->MoveWindow(&rect,FALSE);

		CRect newRect;//��ȡ�µ�rect
		m_selectRectTracker[i]->GetTrueRect(&newRect);

		//�ػ�
		m_selectRectTracker[i]->GetParent()->InvalidateRect(oldRect,TRUE);
		m_selectRectTracker[i]->GetParent()->InvalidateRect(newRect,TRUE);
	}
}


void CTrackContrl::DivideHorCtr()
{
	int nSize = m_selectRectTracker.GetSize();
	if(nSize<=2)
	{
		return;
	}

	int *coor = new int[nSize];
	int nCtrWidth=0;
	int minLeft=m_selectRectTracker[0]->m_rect.left;
	int maxRight=0;
	for(int i=0;i<nSize;i++)
	{
		nCtrWidth += m_selectRectTracker[i]->m_rect.Width();
		minLeft = minLeft > m_selectRectTracker[i]->m_rect.left ? 
			m_selectRectTracker[i]->m_rect.left : minLeft;
		maxRight = maxRight < m_selectRectTracker[i]->m_rect.right ?
			m_selectRectTracker[i]->m_rect.right : maxRight;
		coor[i] = m_selectRectTracker[i]->m_rect.left;
	}

	int nDivideWidth = (maxRight - minLeft - nCtrWidth)/(nSize - 1);
	
	AlterDivideLeft(nDivideWidth,coor,nSize);
	delete [] coor;
}

void CTrackContrl::DivideVerCtr()
{

	int nSize = m_selectRectTracker.GetSize();
	if(nSize<=2)
	{
		return;
	}

	int *coor = new int[nSize];
	int nCtrHeight=0;
	int minTop=m_selectRectTracker[0]->m_rect.top;
	int maxBottom=0;
	for(int i=0;i<nSize;i++)
	{
		nCtrHeight += m_selectRectTracker[i]->m_rect.Height();
		minTop = minTop > m_selectRectTracker[i]->m_rect.top ? 
			m_selectRectTracker[i]->m_rect.top : minTop;
		maxBottom = maxBottom < m_selectRectTracker[i]->m_rect.bottom ?
			m_selectRectTracker[i]->m_rect.bottom : maxBottom;
		coor[i] = m_selectRectTracker[i]->m_rect.top;
	}

	int nDvideHor = (maxBottom - minTop - nCtrHeight)/(nSize-1);

	AlterDivideTop(nDvideHor,coor,nSize);

	delete [] coor;
}


void CTrackContrl::AlterDivideLeft(const int nAlterDivideWid,int coor[],const int nSize)
{
	//������
	Msort(coor,coor,0,nSize-1);
	CArray<CControlRect*,CControlRect*> sortTracker;
	for(int i=0;i<nSize;i++)
	{
		for(int j=0;j<m_selectRectTracker.GetSize();j++)
		{
			if(coor[i] == m_selectRectTracker[j]->m_rect.left)
			{
				sortTracker.Add(m_selectRectTracker[j]);
				break;
			}
		}
	}

	//Ȼ���ƶ�
	for(int i=1;i<sortTracker.GetSize();i++)
	{
		CRect rect;
		rect.left = sortTracker[i-1]->m_rect.right + nAlterDivideWid;
		rect.right = rect.left + sortTracker[i]->m_rect.Width();

		rect.top = sortTracker[i]->m_rect.top;
		rect.bottom = sortTracker[i]->m_rect.bottom;

		CRect oldRect;//��ȡû���ƶ�ǰ��rect
		sortTracker[i]->GetTrueRect(&oldRect);

		sortTracker[i]->m_rect = rect;//���µ�λ�ø����ؼ�
		sortTracker[i]->MoveWindow(&rect,FALSE);
		CRect newRect;//��ȡ�µ�rect
		sortTracker[i]->GetTrueRect(&newRect);

		//�ػ�
		sortTracker[i]->GetParent()->InvalidateRect(oldRect,TRUE);
		sortTracker[i]->GetParent()->InvalidateRect(newRect,TRUE);
	}
}


void CTrackContrl::AlterDivideTop(const int nAlterDivideTop,int coor[],const int nSize)
{
	Msort(coor,coor,0,nSize-1);
	CArray<CControlRect*,CControlRect*> sortTracker;
	for(int i=0;i<nSize;i++)
	{
		for(int j=0;j<m_selectRectTracker.GetSize();j++)
		{
			if(coor[i] == m_selectRectTracker[j]->m_rect.top)
			{
				sortTracker.Add(m_selectRectTracker[j]);
				break;
			}
		}
	}

	for(int i=1;i<sortTracker.GetSize();i++)
	{
		CRect rect;
		rect.left = sortTracker[i]->m_rect.left;
		rect.right = sortTracker[i]->m_rect.right;

		rect.top = sortTracker[i-1]->m_rect.bottom + 
			nAlterDivideTop;
		rect.bottom = rect.top + sortTracker[i]->m_rect.Height();

		CRect oldRect;//��ȡû���ƶ�ǰ��rect
		sortTracker[i]->GetTrueRect(&oldRect);

		sortTracker[i]->m_rect = rect;//���µ�λ�ø����ؼ�
		sortTracker[i]->MoveWindow(&rect,FALSE);
		CRect newRect;//��ȡ�µ�rect
		sortTracker[i]->GetTrueRect(&newRect);

		//�ػ�
		sortTracker[i]->GetParent()->InvalidateRect(oldRect,TRUE);
		sortTracker[i]->GetParent()->InvalidateRect(newRect,TRUE);
	}
}

void CTrackContrl::Merge(int *SR, int *TR, int i, int m, int n)
{
	// �������SR[i..m]��SR[m+1..n]�鲢Ϊ�����TR[i..n]
	int j = m+1;
	int k = i;
	for(; i<=m && j<=n; ++k)
	{
		// ��SR�м�¼���ؼ��ִ�С����ظ��Ƶ�TR��
		if (SR[i]<=SR[j])
		{
			TR[k] = SR[i++];
		}else
		{
			TR[k] = SR[j++];
		}
	}
	while (i<=m) TR[k++] = SR[i++];   // ��ʣ��� SR[i..m] ���Ƶ�TR
	while (j<=n) TR[k++] = SR[j++];   // ��ʣ��� SR[j..n] ���Ƶ�TR
}//Merge


void CTrackContrl::Msort( int *SR, int *TR1, int s, int t ){
	// ��SR[s..t]���й鲢���������ļ�¼����TR1[s..t]
	if (s==t)
	{
		TR1[s] = SR[s];
	}
	else 
	{
		int TR2[10] ;
		int m = (s+t)/2;   // �� SR[s..t] ƽ��Ϊ SR[s..m] �� SR[m+1..t]
		Msort(SR,TR2,s,m);  // �ݹ�ؽ� SR[s..m] �鲢Ϊ����� TR2[s..m]
		Msort(SR,TR2,m+1, t); // �ݹ�ؽ�SR[m+1..t]�鲢Ϊ�����TR2[m+1..t]
		Merge(TR2,TR1,s,m,t); // ��TR2[s..m]��TR2[m+1..t] �鲢�� TR1[s..t]
	}// else
} // Msort

void CTrackContrl::AlterAllCtrTop(int nAlterTop)
{
	for(int i=0;i<m_selTrackerAll.GetSize();i++)
	{
		CRect rect;
		rect.left = m_selTrackerAll[i]->m_rect.left;
		rect.right = m_selTrackerAll[i]->m_rect.right;

		rect.top = m_selTrackerAll[i]->m_rect.top + nAlterTop;
		rect.bottom = rect.top + m_selTrackerAll[i]->m_rect.Height();

		CRect oldRect;//��ȡû���ƶ�ǰ��rect
		m_selTrackerAll[i]->GetTrueRect(&oldRect);

		m_selTrackerAll[i]->m_rect = rect;//���µ�λ�ø����ؼ�
		m_selTrackerAll[i]->MoveWindow(&rect,FALSE);

		CRect newRect;//��ȡ�µ�rect
		m_selTrackerAll[i]->GetTrueRect(&newRect);

		//�ػ�
		m_selTrackerAll[i]->GetParent()->InvalidateRect(oldRect,TRUE);
		m_selTrackerAll[i]->GetParent()->InvalidateRect(newRect,TRUE);
	}
}

void CTrackContrl::KeyUpMove()
{
	int count = m_selectRectTracker.GetCount();
	for(int i=0;i<count;i++)
	{
		if(!m_selectRectTracker[i]->GetCtrWindowIsable())
		{
			CRect rect;
			rect.left = m_selectRectTracker[i]->m_rect.left;
			rect.right = m_selectRectTracker[i]->m_rect.right;

			rect.top = m_selectRectTracker[i]->m_rect.top - 1;
			rect.bottom = m_selectRectTracker[i]->m_rect.bottom - 1;
			//�����������Ƚ�
			ReAdjustMaxRect(rect,TRUE);
			/////////////////////
			CRect oldRect;//��ȡû���ƶ�ǰ��rect
			m_selectRectTracker[i]->GetTrueRect(&oldRect);

			m_selectRectTracker[i]->m_rect = rect;//���µ�λ�ø����ؼ�
			m_selectRectTracker[i]->MoveWindow(&rect,FALSE);

			CRect newRect;//��ȡ�µ�rect
			m_selectRectTracker[i]->GetTrueRect(&newRect);

			//�ػ�
			m_selectRectTracker[i]->GetParent()->InvalidateRect(oldRect,TRUE);
			m_selectRectTracker[i]->GetParent()->InvalidateRect(newRect,TRUE);
		}
	}
}

void CTrackContrl::KeyDownMove()
{
	int count = m_selectRectTracker.GetCount();
	for(int i=0;i<count;i++)
	{
		if(!m_selectRectTracker[i]->GetCtrWindowIsable())
		{
			CRect rect;
			rect.left = m_selectRectTracker[i]->m_rect.left;
			rect.right = m_selectRectTracker[i]->m_rect.right;

			rect.top = m_selectRectTracker[i]->m_rect.top + 1;
			rect.bottom = m_selectRectTracker[i]->m_rect.bottom + 1;
			
			//�����������Ƚ�
			ReAdjustMaxRect(rect,TRUE);
			/////////////////////

			CRect oldRect;//��ȡû���ƶ�ǰ��rect
			m_selectRectTracker[i]->GetTrueRect(&oldRect);

			m_selectRectTracker[i]->m_rect = rect;//���µ�λ�ø����ؼ�
			m_selectRectTracker[i]->MoveWindow(&rect,FALSE);

			CRect newRect;//��ȡ�µ�rect
			m_selectRectTracker[i]->GetTrueRect(&newRect);

			//�ػ�
			m_selectRectTracker[i]->GetParent()->InvalidateRect(oldRect,TRUE);
			m_selectRectTracker[i]->GetParent()->InvalidateRect(newRect,TRUE);
		}
	}
}

void CTrackContrl::KeyLeftMove()
{
	int count = m_selectRectTracker.GetCount();
	for(int i=0;i<count;i++)
	{
		if(!m_selectRectTracker[i]->GetCtrWindowIsable())
		{
			CRect rect;
			rect.left = m_selectRectTracker[i]->m_rect.left - 1;
			rect.right = m_selectRectTracker[i]->m_rect.right - 1;

			rect.top = m_selectRectTracker[i]->m_rect.top;
			rect.bottom = m_selectRectTracker[i]->m_rect.bottom;
			
			//�����������Ƚ�
			ReAdjustMaxRect(rect,TRUE);
			/////////////////////

			CRect oldRect;//��ȡû���ƶ�ǰ��rect
			m_selectRectTracker[i]->GetTrueRect(&oldRect);

			m_selectRectTracker[i]->m_rect = rect;//���µ�λ�ø����ؼ�
			m_selectRectTracker[i]->MoveWindow(&rect,FALSE);

			CRect newRect;//��ȡ�µ�rect
			m_selectRectTracker[i]->GetTrueRect(&newRect);

			//�ػ�
			m_selectRectTracker[i]->GetParent()->InvalidateRect(oldRect,TRUE);
			m_selectRectTracker[i]->GetParent()->InvalidateRect(newRect,TRUE);
		}
	}
}

void CTrackContrl::KeyRightMove()
{
	int count = m_selectRectTracker.GetCount();
	for(int i=0;i<count;i++)
	{
		if(!m_selectRectTracker[i]->GetCtrWindowIsable())
		{
			CRect rect;
			rect.left = m_selectRectTracker[i]->m_rect.left + 1;
			rect.right = m_selectRectTracker[i]->m_rect.right + 1;

			rect.top = m_selectRectTracker[i]->m_rect.top;
			rect.bottom = m_selectRectTracker[i]->m_rect.bottom;
			
			//�����������Ƚ�
			ReAdjustMaxRect(rect,TRUE);
			/////////////////////

			CRect oldRect;//��ȡû���ƶ�ǰ��rect
			m_selectRectTracker[i]->GetTrueRect(&oldRect);

			m_selectRectTracker[i]->m_rect = rect;//���µ�λ�ø����ؼ�
			m_selectRectTracker[i]->MoveWindow(&rect,FALSE);

			CRect newRect;//��ȡ�µ�rect
			m_selectRectTracker[i]->GetTrueRect(&newRect);

			//�ػ�
			m_selectRectTracker[i]->GetParent()->InvalidateRect(oldRect,TRUE);
			m_selectRectTracker[i]->GetParent()->InvalidateRect(newRect,TRUE);
		}
	}
}

void CTrackContrl::DeleteAllCtrPtr()
{
	int count = m_selTrackerAll.GetCount();
	for(int i=0;i<count;i++)
	{
		CControlRect* pControlRect = m_selTrackerAll[i];
		delete pControlRect;
	}
}

void CTrackContrl::ReAdjustMaxRect(CRect& rect,BOOL isSameSize)
{
	if(m_bIsForMaxRect)
	{
		if(!isSameSize)
		{
			if(rect.right>m_maxMoveRect.right)
			{
				rect.right = m_maxMoveRect.right;
			}
			if(rect.bottom>m_maxMoveRect.bottom)
			{
				rect.bottom = m_maxMoveRect.bottom;
			}
			if(rect.left<m_maxMoveRect.left)
			{
				rect.left = m_maxMoveRect.left;
			}
			if(rect.top<m_maxMoveRect.top)
			{
				rect.top = m_maxMoveRect.top;
			}
		}
		else
		{
			if(rect.right>m_maxMoveRect.right)
			{
				rect.left = rect.left - (rect.right - m_maxMoveRect.right);
				rect.right = m_maxMoveRect.right;
			}
			if(rect.bottom>m_maxMoveRect.bottom)
			{
				rect.top = rect.top - (rect.bottom - m_maxMoveRect.bottom);
				rect.bottom = m_maxMoveRect.bottom;
			}
			if(rect.left<m_maxMoveRect.left)
			{
				rect.right = rect.right + (m_maxMoveRect.left - rect.left);
				rect.left = m_maxMoveRect.left;
			}
			if(rect.top<m_maxMoveRect.top)
			{
				rect.bottom = rect.bottom + (m_maxMoveRect.top - rect.top);
				rect.top = m_maxMoveRect.top;
			}
		}
	}
}