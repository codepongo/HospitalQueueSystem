#ifndef HARDWAREDEF_H
#define HARDWAREDEF_H

/*�������ݷ���*/
#define WNDSCREEN_HEAD_FIRST      0xA0//����ͷ
#define WNDSCREEN_HEAD_SCEND      0x90//����ͷ
#define WNDSCREEN_SHOW_ROM        0xA1//��ʾ����ROM����
#define WNDSCREEN_SET_ROM         0xA2//����ROM
#define WNDSCREEN_SHOW_INFOR      0xA5//��ʾ��Ϣ

/*Ӳ������������*/
#define HARDWARE_CALLER_START     0x0A//��ʼ
#define HARDWARE_CALLER_WAIT	  0x0B//�Ⱥ�
#define HARDWARE_CALLER_CALL      0x0C//����
#define HARDWARE_CALLER_RECALL    0x0D//�غ�
#define HARDWARE_CALLER_CANCEL    0x0E//ȡ��
#define HARDWARE_CALLER_FUNCATION 0x0F//����
#define HARDWARE_CALLER_SHOW      0x02//������02
#define HARDWARE_CALLER_SYSTEM    0x03//ϵͳ���к�����
#define HARDWARE_CALLER_HEAD	  0xFF
#define HARDWARE_CALLER_CONST     0x68
#define HARDWARE_CALLER_TAIL      0x16

/*Ӳ������������*/
#define HARDWARE_EVALTOR_HEAD       0xFF//ͷ
#define HARDWARE_EVALTOR_CONST      0x68
#define HARDWARE_EVALTOR_TAIL       0x16//β
#define HARDWARE_EVALTOR_TOSYS   0x11//���������ݵ�ϵͳ
#define HARDWARE_EVALTOR_TOEVA      0x01//ϵͳ�����ݵ�������
#define HARDWARE_EVALTOR_TOSTAR     0x02//��ʾ�Ǽ�
#define HARDWARE_EVALTOR_TOSTART    0x01//��������������������
#define HARDWARE_EVALTOR_NOLEVEL    0x00//0��
#define HARDWARE_EVALTOR_LEVELONE   0x01//1��
#define HARDWARE_EVALTOR_LEVELTWO   0x02//2��
#define HARDWARE_EVALTOR_LEVELTHREE 0x03//3��
#define HARDWARE_EVALTOR_LEVELFOUR  0x04//4��
#define HARDWARE_EVALTOR_LEVELFIVE  0x05//5��
#define HARDWARE_EVALTOR_GRADEZERO  0x00//��
#define HARDWARE_EVALTOR_GRADEONE   0x01//һ��
#define HARDWARE_EVALTOR_GRADETWO   0x02//�Ϻ�
#define HARDWARE_EVALTOR_GRADETHREE 0x03//��
#define HARDWARE_EVALTOR_GRADFOUR   0x04//�ܺ�

#define HARDWARE_THROUGH_FLAG1 0xAA
#define HARDWARE_THROUGH_FLAG2 0xBB
//////���۳�ʱ���ݽṹ
typedef struct _tagEvaltOutTime
{
	int address;
	BOOL IsEvalt;
	UINT time;
}EvaltOutTime,*LPEVALTOUTTIME;

/****** ���۵ȼ� ***********/
typedef enum _tagEvaLevelEum
{
	elNone				= 0,		//δ����
	elGood				= 3,		//��
	elMid				= 2,		//��
	elBad				= 1,		//��
	elBest              = 4         //�ǳ�����
} EvaLevelEum;

typedef struct _tagWndScreenMsg
{
	int         address;
	CString		strmsg;
	int         color;
}WNDSCREENMSG,*LPWNDSCREENMSG;

/*******ͨ�����ݰ�ͷ**************/
typedef struct _tagThroughScreenHead
{
	unsigned char flagFirst;	//0xAA
	unsigned char address;	//��ַ	��0-255��������255Ϊ�㲥��ַ
	//TCPͨѶʱ���ù㲥��ַͨѶ
	unsigned char flagSecond;	//0xBB
	unsigned char type;		//���ݰ�����	��4λ��0-�����࣬1-�����ࣻ
	//��4λ��0-��У�飬1-CRCУ��
	unsigned char index;	//���	����0
	unsigned short int length;	//���ݳ���	ע��(���� = ����+[CRCУ���ֽ�])
	//���ȸ��ֽ���ǰ ���ȵ��ֽ��ں�
}ThroughScreenHead,*pThroughScreenHead;

/******ͨ����Ӧͨ��������ϢList**********/
typedef struct//	(34�ֽ�)
{
	unsigned char   TongDaoHao;     //ͨ����
	unsigned char   PlayType;       //���� 0-�ı�,1ͼƬ
	unsigned char   ShowTitle;      //�Ƿ����ñ�����
	unsigned char   ShowFlag;       //���º���������ʾ
	unsigned short  Width;          //���ڿ�
	unsigned short  Height;         //���ڸ�
	unsigned char   Font;           //����	16��,24��
	unsigned char   IsSameColor;    //�Ƿ���ɫ��ͬ
	unsigned int    Color;          //��ɫ
	unsigned char   Name[20];       //��ʶ����
}TQtList,*pTQtList;

/*****ͨ��������Ϣ************/
typedef struct//		(32�ֽ�)
{
	unsigned char   Flag1;          //�Ƿ���Ч��־   0xE9
	unsigned char   Flag2;          //�Ƿ���Ч��־   0x5A
	unsigned char   LedType;        //����0-����,1-����,2-˫ɫ
	unsigned char   GrayScale;      //�Ҷȵȼ� ����Ϊ0
	unsigned short  Width;          //����
	unsigned short  Height;         //����
	unsigned char   TXSelect;       //ͨѶ���� 0-RS232,1-TCPIP,2-UDP
	unsigned char   IP[16];         //IP
	unsigned short  Port;           //�˿�
	unsigned char   Com;            //����
	unsigned char   Baud;           //������0~7(1200,2400,4800,9600,19200,38400,57600,115200)
	unsigned char   LedAddr;        //��ַ	0~255,�㲥��ַ:255
	unsigned char   CheckLevel;     //У��ȼ�0-��У��,1-CRCУ��
	unsigned char   TXDelay;        //ͨѶ��ʱ
}TLedInfo,*pTLedInfo;
#endif