#ifndef TRACKDEF_H
#define TRACKDEF_H
#include "PrintDef.h"
/*
�ṹ�幦��:
���ڴ���ؼ�������/�Ҽ�����
*/
typedef enum _tagPressTypeEnum
{	
	enmLeftPress = 0,
	enmRightPress = 1
}PressTypeEnum;

/*
�ṹ�幦��:
����Ӧ��Button����״
*/
typedef enum _tagButtonTypeEnum
{
	enumRectButton = 0,
	enumRoundRectButton = 1,
	enumEllipseButton = 2
}ButtonTypeEnum;
/*
�ؼ�������
*/
typedef enum _tagWindowType
{
	enmScrollBar = 1,
	enmStatic = 2,
	enmButton = 3,
	enmEdit = 4,
	enmListBox = 5,
	enmComboBox = 6
}WindowType;
/*
static �ؼ����ֶ��뷽ʽ
*/
typedef enum _tagStaticTextAlign
{
	enumLeft = 0,
	enumCenter = 1,
	enumRight  = 2
}StaticTextAlign;

#define  textNum 2048 //�������������
#define  addNum 256   //���Ӵ�����е�����

//ʱ���ʽ
typedef enum _tagStaticTimeFormat
{
	enumTimeChinese = 0,
	enumTimeYearMonthDay = 1,
	enumTimeHourMinSec  = 2,
	enumTimeYMDHMS = 3
}StaticTimeFormat;
/*
����д��/��ȡ �ؼ���Ϣ�Ľṹ��
*/
typedef struct _tagWindowCtrInfo
{
	WindowType windowType;//�ؼ�����
	COLORREF bkColor;//������ɫ
	COLORREF textColor;//������ɫ
	UINT nAlpha;//͸����
	LOGFONT lfFont;//����
	ButtonTypeEnum ButtonType;//��ť��״
	WCHAR address[addNum];//���Ӵ���Ķ���
	UINT   rectLeft;//����
	UINT   rectRight;
	UINT   rectTop;
	UINT   rectBottom;
	StaticTextAlign textAlign;//���ֶ��뷽ʽ
	BOOL   IsForImage;//��̬���Ƿ�ΪͼƬ��ʽ
	BOOL   IsShowTime;//��̬���Ƿ�Ϊ��ʾʱ��
	BOOL   IsShowQueNum;//��̬���Ƿ�Ϊ��ʾ�Ŷ�����
	BOOL   IsForPrint;//��̬���Ƿ�Ϊ��ӡ׼��
	BOOL   IsForPrintChangeObjec;//��̬���Ƿ�Ϊ��ӡ����
	StaticTimeFormat timeFormat;//��ʾʱ��ĸ�ʽ
	EnumPrintObject printObject;//��ӡ����
	WCHAR  staticPicPath[MAX_PATH];//��̬ͼƬ���ص�·��
	WCHAR  ctrTextContent[textNum];//�ؼ�����������
	WCHAR  forShowQueNumHead[addNum];//��ʾ�Ŷ������̶�ͷ
	//�磺�Ŷ�����:123 ǰ����Ŷ������ǹ̶�ͷ
}WINDOWCTRINFO,*LPWINDOWCTRINFO;	

#define  TRACK_CTR_ABLE					-3//trackʱ�ؼ�����
#define  TRACK_CTR_CTRL					 3//trackʱ��סctrl
#define  TRACK_CTR_SHIFT					 4//trackʱ��סshift
#define  TRACK_CTR_MIDORHANDLE  5 
//trackʱ��סhandle�м���߱�
#define  TRACK_CTR_RUBBERBAND   6//
#define  TRACK_CTR_OTHER				2  //��������
#define  TRACK_CTR_LBUTTON           7 //���
#define  TRACK_CTR_RBUTTON          8 //�Ҽ�
#define  TRACK_CTR_LDOUBLE           9//���˫��

#define  toolLeftText    _T("�����")
#define  toolMiddleText  _T("����")
#define  toolRightText   _T("�Ҷ���")
#define  toolTopText     _T("���˶���")
#define  toolBottomText  _T("�׶˶���")
#define  toolWidthText   _T("���һ��")
#define  toolHeightText  _T("�߶�һ��")
#define  toolSameSizeText    _T("����һ��")
#define  toolHorText     _T("����")
#define  toolVerText     _T("����")


#endif