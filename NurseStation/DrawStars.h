#pragma once
#include "PrintDef.h"

class CDrawStars
{
public:
	CDrawStars(void);
	~CDrawStars(void);
	///��������ǵ��Ǹ���
	void CalculationPoint(const  DWORD lRaudis,const CPoint& startPoint);
	//�������
	void Draw(CDC* pDC,BOOL isSoid=FALSE);
private:
	//��������ǵ��Ǹ���
	POINT m_ptStar[10];
};
