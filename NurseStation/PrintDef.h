#ifndef  PRINTDEF_H
#define PRINTDEF_H

typedef enum _tagEnumPrintObjectEnum
{
	enumPrintType = 0,//(����)
	enumPrintWaitNum = 1,//�Ŷ�����
	enumPrintClientNum = 2,//�ͻ�����
	enumPrintClientName = 3,//�ͻ�����
	enumPrintClientLevel  = 4,//�ͻ��Ǽ�
	enumPrintConsultName = 5,//��������
	enumPrintDoctorName = 6,//ҽ������
	enumPrintSerialID = 7 //��ˮ��
}EnumPrintObject;

typedef enum _tagEnumPrintStatus
{
	enumPrintErr = -1,//��ӡ����
	enumPrintPaperOut = -2,//ȱֽ
	enumPrintOffline = -3,//����
	enumPrintPrinting = 0,//���ڴ�ӡ�����ܴ�ӡ�����ֹ���
	enumPrintNormal = 1,//��ӡ������
	enumPrintNoDefPrinter = -4,//û��Ĭ�ϴ�ӡ��
	enumPrintFailedJob = -5//��ȡjobʧ��
}EnumPrintStaus;

const CString CS_printType = _T("��������");
const CString CS_printWaitNum = _T("�Ⱥ�����");
const CString CS_printClientNum = _T("�ŶӺ���");
const CString CS_printClientName = _T("��������");
const CString CS_printClientLevel = _T("�Ǽ�");
const CString CS_printConsultName =_T("��������");
const CString CS_printDoctorName = _T("ҽ������");
const CString CS_printSerialID = _T("��ˮ��");

const double PI = 3.14159265359;

typedef struct _tagPrintRectInfo
{
	POINT pt[2];
	BOOL isUsePrint;
}PRINTRECTINFO,*LPPRINTRECTINFO;
#endif