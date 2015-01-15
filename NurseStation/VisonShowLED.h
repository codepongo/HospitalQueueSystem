#pragma once
#include "LEDApi.h"
#define WM_LED_NOTIFY WM_USER+1001

class CVisonShowLED
{
public:
	CVisonShowLED();
	CVisonShowLED(HWND hWnd);
	~CVisonShowLED(void);
private:
	//��̬���ӿ��ʼ��
	long (_stdcall *LED_Startup)(void);

	//��̬���ӿ�����
	long (_stdcall *LED_Cleanup)(void);
	//�������ƿ����߼�������
	//  serverindex ���ƿ����߼���������(�����ڶ��socket udp�˿ڼ���)
	//  localport ���ض˿�
	long (_stdcall *LED_Report_CreateServer)(long serverindex, long localport);

	//ɾ�����ƿ����߼�������
	//  serverindex ���ƿ����߼���������
	void (_stdcall *LED_Report_RemoveServer)(long serverindex);

	//ɾ��ȫ�����ƿ����߼�������
	void (_stdcall *LED_Report_RemoveAllServer)(void);

	//��ÿ��ƿ������б�
	//�����ȴ������ƿ����߼������񣬼�����LED_Report_CreateServer��ʹ�ã����򷵻�ֵ��Ч
	//  serverindex ���ƿ����߼���������
	//  plist ��������б���û��ⲿ��������
	//        ��������(NULL/0)�����������̬���ӿ��ڲ��Ļ�������������������Ľӿ�ȡ����ϸ��Ϣ
	//  count ����ȡ����
	//--����ֵ-- С��0��ʾʧ��(δ���������߼�������)�����ڵ���0��ʾ���ߵĿ��ƿ�����
	long (_stdcall *LED_Report_GetOnlineList)(long serverindex, void* plist, long count);

	//���ĳ�����߿��ƿ����ϱ����ƿ�����
	//�����ȴ������ƿ����߼������񣬼�����LED_Report_CreateServer��ʹ�ã����򷵻�ֵ��Ч
	//  serverindex ���ƿ����߼���������
	//  itemindex �ü�������������б��У����߿��ƿ��ı��
	//--����ֵ-- ���߿��ƿ����ϱ����ƿ�����
	char* (_stdcall *LED_Report_GetOnlineItemName)(long serverindex, long itemindex);

	//���ĳ�����߿��ƿ����ϱ����ƿ�IP��ַ
	//�����ȴ������ƿ����߼������񣬼�����LED_Report_CreateServer��ʹ�ã����򷵻�ֵ��Ч
	//  serverindex ���ƿ����߼���������
	//  itemindex �ü�������������б��У����߿��ƿ��ı��
	//--����ֵ-- ���߿��ƿ���IP��ַ
	char* (_stdcall *LED_Report_GetOnlineItemHost)(long serverindex, long itemindex);

	//���ĳ�����߿��ƿ����ϱ����ƿ�Զ��UDP�˿ں�
	//�����ȴ������ƿ����߼������񣬼�����LED_Report_CreateServer��ʹ�ã����򷵻�ֵ��Ч
	//  serverindex ���ƿ����߼���������
	//  itemindex �ü�������������б��У����߿��ƿ��ı��
	//--����ֵ-- ���߿��ƿ���Զ��UDP�˿ں�
	long (_stdcall *LED_Report_GetOnlineItemPort)(long serverindex, long itemindex);

	//���ĳ�����߿��ƿ����ϱ����ƿ���ַ
	//�����ȴ������ƿ����߼������񣬼�����LED_Report_CreateServer��ʹ�ã����򷵻�ֵ��Ч
	//  serverindex ���ƿ����߼���������
	//  itemindex �ü�������������б��У����߿��ƿ��ı��
	//--����ֵ-- ���߿��ƿ���Ӳ����ַ
	long (_stdcall *LED_Report_GetOnlineItemAddr)(long serverindex, long itemindex);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/************************************************************************/
	/* ��дͨѶ�����ӿں���������һЩ�޷����ݽṹ���ָ��Ŀ�������������   */
	/************************************************************************/

	//��д����ͨѶ������������ʱʹ��
	//  index ����������
	//  localport ���ض˿�
	//  host ���ƿ�IP��ַ
	//  remoteport Զ�̶˿�
	//  address ���ƿ���ַ
	//  notifymode ͨѶͬ���첽ģʽ
	//  wmhandle ������Ϣ������
	//  wmmessage ������Ϣ����Ϣ��
	//--����ֵ-- С��0��ʾʧ�ܣ����ڵ���0��ʾ������id��
	long (_stdcall *LED_UDP_SenderParam)(long index, long localport, char* host, long remoteport, long address, long notifymode, long wmhandle, long wmmessage);

	//��д����ͨѶ������������ʱʹ��
	//  index ����������
	//  comport ���ں�
	//  baudrate ������
	//  address ���ƿ���ַ
	//  notifymode ͨѶͬ���첽ģʽ
	//  wmhandle ������Ϣ������
	//  wmmessage ������Ϣ����Ϣ��
	//--����ֵ-- С��0��ʾʧ�ܣ����ڵ���0��ʾ������id��
	long (_stdcall *LED_COM_SenderParam)(long index, long comport, long baudrate, long address, long notifymode, long wmhandle, long wmmessage);

	//��д����ͨѶ������������ʱʹ��
	//  index ����������
	//  localport ���ض˿�
	//  serverindex ���߼���������
	//  name ���ƿ�����(���ƿ��ϱ���������)
	//  notifymode ͨѶͬ���첽ģʽ
	//  wmhandle ������Ϣ������
	//  wmmessage ������Ϣ����Ϣ��
	//--����ֵ-- С��0��ʾʧ�ܣ����ڵ���0��ʾ������id��
	long (_stdcall *LED_UDP_SenderParam_ByReportName)(long index, long localport, long serverindex, char* name, long notifymode, long wmhandle, long wmmessage);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//��λ���ƿ���Ŀ���ţ�������ʾ���ƿ�Flash�д洢�Ľ�Ŀ
	long (_stdcall *LED_ResetDisplay)(PSenderParam param);
	long (_stdcall *LED_ResetDisplay2)(long senderparam_index);

	//У��ʱ�䣬�Ե�ǰ�������ϵͳʱ��У�����ƿ���ʱ��
	long (_stdcall *LED_AdjustTime)(PSenderParam param);
	long (_stdcall *LED_AdjustTime2)(long senderparam_index);

	//У��ʱ����չ����ָ����ʱ��У�����ƿ���ʱ��
	long (_stdcall *LED_AdjustTimeEx)(PSenderParam param, LPSYSTEMTIME time);
	long (_stdcall *LED_AdjustTimeEx2)(long senderparam_index, LPSYSTEMTIME time);

	//���õ�ǰ��ʾ�Ľ�Ŀ
	long (_stdcall *LED_SetCurChapter)(PSenderParam param, long value);
	long (_stdcall *LED_SetCurChapter2)(long senderparam_index, long value);

	//���ÿ��ƿ���Դ value=LED_POWER_ON��ʾ������Դ value=LED_POWER_OFF��ʾ�رյ�Դ
	long (_stdcall *LED_SetPower)(PSenderParam param, long value);
	long (_stdcall *LED_SetPower2)(long senderparam_index, long value);

	//����ת������
	long (_stdcall *LED_ComTransfer)(PSenderParam param, BYTE* buffer, DWORD size);
	long (_stdcall *LED_ComTransfer2)(long senderparam_index, BYTE* buffer, DWORD size);

	//��ȡ���ƿ���Դ״̬
	long (_stdcall *LED_GetPower)(PSenderParam param);
	long (_stdcall *LED_GetPower2)(long senderparam_index);

	//���ÿ��ƿ����� valueȡֵ��Χ0-7
	long (_stdcall *LED_SetBright)(PSenderParam param, long value);
	long (_stdcall *LED_SetBright2)(long senderparam_index, long value);

	//��ȡ���ƿ�����
	long (_stdcall *LED_GetBright)(PSenderParam param);
	long (_stdcall *LED_GetBright2)(long senderparam_index);

	//���ÿ��ƿ��Ķ�ʱ�������ƻ�
	long (_stdcall *LED_SetPowerSchedule)(PSenderParam param, PPowerSchedule value);
	long (_stdcall *LED_SetPowerSchedule2)(long senderparam_index, PPowerSchedule value);

	//��ȡ���ƿ��Ķ�ʱ�������ƻ�
	long (_stdcall *LED_GetPowerSchedule)(PSenderParam param);
	long (_stdcall *LED_GetPowerSchedule2)(long senderparam_index);

	//���ÿ��ƿ��Ķ�ʱ���ȵ��ڼƻ�
	long (_stdcall *LED_SetBrightSchedule)(PSenderParam param, PBrightSchedule value);
	long (_stdcall *LED_SetBrightSchedule2)(long senderparam_index, PBrightSchedule value);

	//��ȡ���ƿ��Ķ�ʱ���ȵ��ڼƻ�
	long (_stdcall *LED_GetBrightSchedule)(PSenderParam param);
	long (_stdcall *LED_GetBrightSchedule2)(long senderparam_index);

	//���ͽ�Ŀ���� indexΪMakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�����ķ���ֵ
	long (_stdcall *LED_SendToScreen)(PSenderParam param, long index);
	long (_stdcall *LED_SendToScreen2)(long senderparam_index, long index);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���ڶԿ��ƿ�����һЩ��������
	// ����Ϊ����ȡ���ƿ�����--��ȡ��������--
	//                       --�޸ĸ�������--���޸ĺ�Ĳ���������ƿ�
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//��ȡ���ƿ�����
	long (_stdcall *LED_Cache_GetBoardParam)(PSenderParam param);
	long (_stdcall *LED_Cache_GetBoardParam2)(long senderparam_index);
	//��ȡ��������
	long (_stdcall *LED_Cache_GetBoardParam_SaveToFile)(char* filename);  //�����ƿ��ض��Ĳ�����д���ļ�
	char* (_stdcall *LED_Cache_GetBoardParam_IP)(void);
	char* (_stdcall *LED_Cache_GetBoardParam_Mac)(void);
	long (_stdcall *LED_Cache_GetBoardParam_Addr)(void);
	long (_stdcall *LED_Cache_GetBoardParam_Width)(void);
	long (_stdcall *LED_Cache_GetBoardParam_Height)(void);
	long (_stdcall *LED_Cache_GetBoardParam_Brightness)(void);
	//�޸ĸ�������
	long (_stdcall *LED_Cache_SetBoardParam_LoadFromFile)(char* filename);  //���ļ���ȡ���������浽��̬���ӿ��У��Թ�д�뵽���ƿ�
	void (_stdcall *LED_Cache_SetBoardParam_IP)(char* value);
	void (_stdcall *LED_Cache_SetBoardParam_Mac)(char* value);
	void (_stdcall *LED_Cache_SetBoardParam_Addr)(long value);
	void (_stdcall *LED_Cache_SetBoardParam_Width)(long value);
	void (_stdcall *LED_Cache_SetBoardParam_Height)(long value);
	void (_stdcall *LED_Cache_SetBoardParam_Brightness)(long value);
	//���޸ĺ�Ĳ���������ƿ�
	long (_stdcall *LED_Cache_SetBoardParam)(PSenderParam param);
	long (_stdcall *LED_Cache_SetBoardParam2)(long senderparam_index);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//��Ŀ������֯��ʽ
	//  ROOT
	//   |
	//   |---Chapter(��Ŀ)
	//   |      |
	//   |      |---Region(����)
	//   |      |     |
	//   |      |     |---Leaf(ҳ��)
	//   |      |     |    |
	//   |      |     |    |---Object(����[���֡�ʱ�ӡ�ͼƬ��])
	//   |      |     |    |
	//   |      |     |    |---Object(����[���֡�ʱ�ӡ�ͼƬ��])
	//   |      |     |    |
	//   |      |     |    |   ......
	//   |      |     |    |
	//   |      |     |
	//   |      |     |---Leaf(ҳ��)
	//   |      |     |
	//   |      |     |   ......
	//   |      |     |
	//   |      |
	//   |      |---Region(����)
	//   |      |
	//   |      |   ......
	//   |      |
	//   |---Chapter(��Ŀ)
	//   |
	//   |   ......

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//���ɲ������ݣ���VisionShow����༭��Vsq�ļ����룬������Ҫ�·��Ľ�Ŀ���ݣ�
	//  RootType Ϊ�������ͣ�=ROOT_PLAY��ʾ���¿��ƿ�RAM�еĽ�Ŀ(���綪ʧ)��=ROOT_DOWNLOAD��ʾ���¿��ƿ�Flash�еĽ�Ŀ(���粻��ʧ)
	//  ColorMode Ϊ��ɫģʽ��ȡֵΪCOLOR_MODE_MONO����COLOR
	//  survive ΪRAM��Ŀ����ʱ�䣬��RootType=ROOT_PLAYʱ��Ч����RAM��Ŀ���Ŵﵽʱ��󣬻ָ���ʾFLASH�еĽ�Ŀ
	//  filename ��VisionShow����༭�Ľ�Ŀ�ļ�
	long (_stdcall *MakeFromVsqFile)(char* filename, long RootType, long ColorMode, long survive );

	//���ɲ�������
	//  RootType Ϊ�������ͣ�=ROOT_PLAY��ʾ���¿��ƿ�RAM�еĽ�Ŀ(���綪ʧ)��=ROOT_DOWNLOAD��ʾ���¿��ƿ�Flash�еĽ�Ŀ(���粻��ʧ)
	//  ColorMode Ϊ��ɫģʽ��ȡֵΪCOLOR_MODE_MONO����COLOR
	//  survive ΪRAM��Ŀ����ʱ�䣬��RootType=ROOT_PLAYʱ��Ч����RAM��Ŀ���Ŵﵽʱ��󣬻ָ���ʾFLASH�еĽ�Ŀ
	long (_stdcall *MakeRoot)(long RootType, long ColorMode, long survive );

	//���ɽ�Ŀ���ݣ�������Ҫ����[AddRegion]->[AddLeaf]->[AddObject]->[AddWindows/AddDateTime��]
	//  RootType ������ΪROOT_PLAY_CHAPTER
	//  ActionMode ������Ϊ0
	//  ChapterIndex Ҫ���µĽ�Ŀ���
	//  ColorMode ͬMakeRoot�еĶ���
	//  time ���ŵ�ʱ�䳤��
	//  wait �ȴ�ģʽ��=WAIT_CHILD����ʾ���ﵽ����ʱ�䳤��ʱ����Ҫ�ȴ��ӽ�Ŀ����������л���
	//                 =WAIT_USE_TIME����ʾ���ﵽ����ʱ�䳤��ʱ�����ȴ��ӽ�Ŀ������ɣ�ֱ���л���һ��Ŀ
	long (_stdcall *MakeChapter)(long RootType, long ActionMode, long ChapterIndex, long ColorMode, DWORD time, WORD wait);

	//���ɷ�����������Ҫ����[AddLeaf]->[AddObject]->[AddWindows/AddDateTime��]
	//  RootType ������ΪROOT_PLAY_REGION
	//  ActionMode ������Ϊ0
	//  ChapterIndex Ҫ���µĽ�Ŀ���
	//  RegionIndex Ҫ���µķ������
	//  ColorMode ͬMakeRoot�еĶ���
	//  left��top��width��height ���ϡ���ȡ��߶�
	//  border ��ˮ�߿�
	long (_stdcall *MakeRegion)(long RootType, long ActionMode, long ChapterIndex, long RegionIndex, long ColorMode, long left, long top, long width, long height, long border);

	//����ҳ�棬������Ҫ����[AddObject]->[AddWindows/AddDateTime��]
	//  RootType ������ΪROOT_PLAY_LEAF
	//  ActionMode ������Ϊ0
	//  ChapterIndex Ҫ���µĽ�Ŀ���
	//  RegionIndex Ҫ���µķ������
	//  LeafIndex Ҫ���µ�ҳ�����
	//  ColorMode ͬMakeRoot�еĶ���
	//  time ���ŵ�ʱ�䳤��
	//  wait �ȴ�ģʽ��=WAIT_CHILD����ʾ���ﵽ����ʱ�䳤��ʱ����Ҫ�ȴ��ӽ�Ŀ����������л���
	//                 =WAIT_USE_TIME����ʾ���ﵽ����ʱ�䳤��ʱ�����ȴ��ӽ�Ŀ������ɣ�ֱ���л���һҳ��
	long (_stdcall *MakeLeaf)(long RootType, long ActionMode, long ChapterIndex, long RegionIndex, long LeafIndex, long ColorMode, DWORD time, WORD wait);

	//���ɲ��Ŷ��󣬺�����Ҫ����[AddWindows/AddDateTime��]
	//  RootType ������ΪROOT_PLAY_OBJECT
	//  ActionMode ������Ϊ0
	//  ChapterIndex Ҫ���µĽ�Ŀ���
	//  RegionIndex Ҫ���µķ������
	//  LeafIndex Ҫ���µ�ҳ�����
	//  ObjectIndex Ҫ���µĶ������
	//  ColorMode ͬMakeRoot�еĶ���
	long (_stdcall *MakeObject)(long RootType, long ActionMode, long ChapterIndex, long RegionIndex, long LeafIndex, long ObjectIndex, long ColorMode);

	//��ӽ�Ŀ
	//  num ��Ŀ���ݻ�������ţ���MakeRoot�ķ���ֵ
	//  time ���ŵ�ʱ�䳤��
	//  wait �ȴ�ģʽ��=WAIT_CHILD����ʾ���ﵽ����ʱ�䳤��ʱ����Ҫ�ȴ��ӽ�Ŀ����������л���
	//                 =WAIT_USE_TIME����ʾ���ﵽ����ʱ�䳤��ʱ�����ȴ��ӽ�Ŀ������ɣ�ֱ���л���һ��Ŀ
	long (_stdcall *AddChapter)(WORD num, DWORD time, WORD wait); //timeΪ����

	//��ӷ���
	//  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter�ķ���ֵ
	//  left��top��width��height ���ϡ���ȡ��߶�
	//  border ��ˮ�߿�
	long (_stdcall *AddRegion)(WORD num, long left, long top, long width, long height, long border);

	//���ҳ��
	//  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion�ķ���ֵ
	//  time ���ŵ�ʱ�䳤��
	//  wait �ȴ�ģʽ��=WAIT_CHILD����ʾ���ﵽ����ʱ�䳤��ʱ����Ҫ�ȴ��ӽ�Ŀ����������л���
	//                 =WAIT_USE_TIME����ʾ���ﵽ����ʱ�䳤��ʱ�����ȴ��ӽ�Ŀ������ɣ�ֱ���л���һҳ��
	long (_stdcall *AddLeaf)(WORD num, DWORD time, WORD wait); //timeΪ����

	//�������ʱ����ʾ
	//  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
	//  left��top��width��height ���ϡ���ȡ��߶�
	//  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
	//  border ��ˮ�߿�(δʵ��)
	//  fontname ��������
	//  fontsize �����С
	//  fontcolor ������ɫ
	//  fontstyle ������ʽ ������=WFS_BOLD��ʾ���壻=WFS_ITALIC��ʾб�壻=WFS_BOLD+WFS_ITALIC��ʾ��б��
	//  year_offset ��ƫ����
	//  month_offset ��ƫ����
	//  day_offset ��ƫ����
	//  sec_offset ��ƫ����
	//  format ��ʾ��ʽ 
	//      #y��ʾ�� #m��ʾ�� #d��ʾ�� #h��ʾʱ #n��ʾ�� #s��ʾ�� #w��ʾ���� #c��ʾũ��
	//      ������ format="#y��#m��#d�� #hʱ#n��#s�� ����#w ũ��#c"ʱ����ʾΪ"2009��06��27�� 12ʱ38��45�� ������ ũ�����³���"
	long (_stdcall *AddDateTime)(WORD num, long left, long top, long width, long height, long transparent, long border,
		char* fontname, long fontsize, long fontcolor, long fontstyle, 
		long year_offset, long month_offset, long day_offset, long sec_offset, char* format);

	//�����սʱ����ʾ
	//  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
	//  left��top��width��height ���ϡ���ȡ��߶�
	//  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
	//  border ��ˮ�߿�(δʵ��)
	//  fontname ��������
	//  fontsize �����С
	//  fontcolor ������ɫ
	//  fontstyle ������ʽ ������=WFS_BOLD��ʾ���壻=WFS_ITALIC��ʾб�壻=WFS_BOLD+WFS_ITALIC��ʾ��б��
	//  format ��ʾ��ʽ 
	//      #y��ʾ�� #m��ʾ�� #d��ʾ�� #h��ʾʱ #n��ʾ�� #s��ʾ��
	//  basetime ��սʱ��
	//  fromtime ��ʼʱ��
	//  totime ����ʱ��
	//  step ��ʱ����ʱ�䲽�������ٺ�����һ�룩
	long (_stdcall *AddCampaignEx)(WORD num, long left, long top, long width, long height, long transparent, long border, 
		char* fontname, long fontsize, long fontcolor, long fontstyle, 
		char* format, PTimeStamp basetime, PTimeStamp fromtime, PTimeStamp totime, long step);

	//���ģ��ʱ��
	//  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
	//  left��top��width��height ���ϡ���ȡ��߶�
	//  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
	//  border ��ˮ�߿�(δʵ��)
	//  offset ��ƫ����
	//  bkcolor: ������ɫ
	//  framecolor: �����ɫ
	//  framewidth: �����ɫ
	//  frameshape: �����״ =0��ʾ�����Σ�=1��ʾԲ�Ƿ��Σ�=2��ʾԲ��
	//  dotradius: �̶Ⱦ���������İ뾶
	//  adotwidth: 0369��̶ȴ�С
	//  adotcolor: 0369��̶���ɫ
	//  bdotwidth: ������̶ȴ�С
	//  bdotcolor: ������̶���ɫ
	//  hourwidth: ʱ���ϸ
	//  hourcolor: ʱ����ɫ
	//  minutewidth: �����ϸ
	//  minutecolor: ������ɫ
	//  secondwidth: �����ϸ
	//  secondcolor: ������ɫ
	long (_stdcall *AddClock)(WORD num, long left, long top, long width, long height, long transparent, long border, long offset,
		DWORD bkcolor, DWORD framecolor, DWORD framewidth, long frameshape,
		long dotradius, long adotwidth, DWORD adotcolor, long bdotwidth, DWORD bdotcolor,
		long hourwidth, DWORD hourcolor, long minutewidth, DWORD minutecolor, long secondwidth, DWORD secondcolor);

	//��Ӷ���
	//  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
	//  left��top��width��height ���ϡ���ȡ��߶�
	//  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
	//  border ��ˮ�߿�(δʵ��)
	//  filename avi�ļ���
	//  stretch: ͼ���Ƿ���������Ӧ�����С
	long (_stdcall *AddMovie)(WORD num, long left, long top, long width, long height, long transparent, long border, char* filename, long stretch);

	//���ͼƬ�鲥��
	//  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
	//  left��top��width��height ���ϡ���ȡ��߶�
	//  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
	//  border ��ˮ�߿�(δʵ��)
	long (_stdcall *AddWindows)(WORD num, long left, long top, long width, long height, long transparent, long border);

	//���ͼƬ�����ͼƬ �˺���Ҫ����AddWindows�������
	//  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
	//  dc ԴͼƬDC���
	//  width ͼƬ���
	//  height ͼƬ�߶�
	//  inmethod ���뷽ʽ(�������б�˵��)
	//  inspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  outmethod ������ʽ(�������б�˵��)
	//  outspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  stopmethod ͣ����ʽ(�������б�˵��)
	//  stopspeed ͣ���ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  stoptime ͣ��ʱ��(��λ����)
	long (_stdcall *AddChildWindow)(WORD num, HDC dc, long width, long height, long alignment, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime��λΪ��

	//���ͼƬ�����ͼƬ �˺���Ҫ����AddWindows�������
	//  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
	//  filename ͼƬ�ļ���
	//  inmethod ���뷽ʽ(�������б�˵��)
	//  inspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  outmethod ������ʽ(�������б�˵��)
	//  outspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  stopmethod ͣ����ʽ(�������б�˵��)
	//  stopspeed ͣ���ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  stoptime ͣ��ʱ��(��λ����)
	long (_stdcall *AddChildPicture)(WORD num, char* filename, long alignment, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime��λΪ��

	//���ͼƬ�����ͼƬ �˺���Ҫ����AddWindows�������
	//  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
	//  str �����ַ���
	//  fontname ��������
	//  fontsize �����С
	//  fontcolor ������ɫ
	//  fontstyle ������ʽ ������=WFS_BOLD��ʾ���壻=WFS_ITALIC��ʾб�壻=WFS_BOLD+WFS_ITALIC��ʾ��б��
	//  wordwrap �Ƿ��Զ����� =1�Զ����У�=0���Զ�����
	//  inmethod ���뷽ʽ(�������б�˵��)
	//  inspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  outmethod ������ʽ(�������б�˵��)
	//  outspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  stopmethod ͣ����ʽ(�������б�˵��)
	//  stopspeed ͣ���ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  stoptime ͣ��ʱ��(��λ����)
	long (_stdcall *AddChildText)(WORD num, char* str, char* fontname, long fontsize, long fontcolor, long fontstyle, long wordwrap, long alignment, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime��λΪ����

	//������������鲥��
	//  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
	//  left��top��width��height ���ϡ���ȡ��߶�
	//  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
	//  border ��ˮ�߿�(δʵ��)
	long (_stdcall *AddStrings)(WORD num, long left, long top, long width, long height, long transparent, long border);

	//���ͼƬ�����ͼƬ �˺���Ҫ����AddWindows�������
	//  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
	//  str �����ַ���
	//  fontset �ֿ� =FONTSET_16P��ʾ16�����ֿ⣻=FONTSET_24P��ʾ24�����ֿ�
	//  color ��ɫ
	//  inmethod ���뷽ʽ(�������б�˵��)
	//  inspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  outmethod ������ʽ(�������б�˵��)
	//  outspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  stopmethod ͣ����ʽ(�������б�˵��)
	//  stopspeed ͣ���ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  stoptime ͣ��ʱ��(��λ����)
	long (_stdcall *AddChildString)(WORD num, char* str, long fontset, long color, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime��λΪ����

	//���ͼƬ���󲥷�
	//  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
	//  left��top��width��height ���ϡ���ȡ��߶�
	//  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
	//  border ��ˮ�߿�(δʵ��)
	//  dc ԴͼƬDC���
	//  src_width ͼƬ���
	//  src_height ͼƬ�߶�
	//  inmethod ���뷽ʽ(�������б�˵��)
	//  inspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  outmethod ������ʽ(�������б�˵��)
	//  outspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  stopmethod ͣ����ʽ(�������б�˵��)
	//  stopspeed ͣ���ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  stoptime ͣ��ʱ��(��λ����)
	long (_stdcall *AddWindow)(WORD num, long left, long top, long width, long height, long transparent, long border,
		HDC dc, long src_width, long src_height, long alignment, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime��λΪ����

	//���ͼƬ�ļ�����
	//  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
	//  left��top��width��height ���ϡ���ȡ��߶�
	//  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
	//  border ��ˮ�߿�(δʵ��)
	//  filename ͼƬ�ļ�
	//  inmethod ���뷽ʽ(�������б�˵��)
	//  inspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  outmethod ������ʽ(�������б�˵��)
	//  outspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  stopmethod ͣ����ʽ(�������б�˵��)
	//  stopspeed ͣ���ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  stoptime ͣ��ʱ��(��λ����)
	long (_stdcall *AddPicture)(WORD num, long left, long top, long width, long height, long transparent, long border,
		char* filename, long alignment, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime��λΪ����

	//������ֲ���
	//  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
	//  left��top��width��height ���ϡ���ȡ��߶�
	//  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
	//  border ��ˮ�߿�(δʵ��)
	//  str �����ַ���
	//  fontname ��������
	//  fontsize �����С
	//  fontcolor ������ɫ
	//  fontstyle ������ʽ ������=WFS_BOLD��ʾ���壻=WFS_ITALIC��ʾб�壻=WFS_BOLD+WFS_ITALIC��ʾ��б��
	//  wordwrap �Ƿ��Զ����� =1�Զ����У�=0���Զ�����
	//  inmethod ���뷽ʽ(�������б�˵��)
	//  inspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  outmethod ������ʽ(�������б�˵��)
	//  outspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  stopmethod ͣ����ʽ(�������б�˵��)
	//  stopspeed ͣ���ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  stoptime ͣ��ʱ��(��λ����)
	long (_stdcall *AddText)(WORD num, long left, long top, long width, long height, long transparent, long border,
		char* str, char* fontname, long fontsize, long fontcolor, 
		long fontstyle, long wordwrap, long alignment, 
		long inmethod, long inspeed, long outmethod, long outspeed,
		long stopmethod, long stopspeed, long stoptime); //stoptime��λΪ����

	//����������ֲ���
	//  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
	//  left��top��width��height ���ϡ���ȡ��߶�
	//  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
	//  border ��ˮ�߿�(δʵ��)
	//  str �����ַ���
	//  fontset �ֿ� =FONTSET_16P��ʾ16�����ֿ⣻=FONTSET_24P��ʾ24�����ֿ�
	//  color ��ɫ
	//  inmethod ���뷽ʽ(�������б�˵��)
	//  inspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  outmethod ������ʽ(�������б�˵��)
	//  outspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  stopmethod ͣ����ʽ(�������б�˵��)
	//  stopspeed ͣ���ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  stoptime ͣ��ʱ��(��λ����)
	long (_stdcall *AddString)(WORD num, long left, long top, long width, long height, long transparent, long border,
		char* str, long fontset, long color, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime��λΪ����

	///////////////////////////////////////////////////////////////////////////////////////////////////
	// �����˲��г���Ŀר�Ŷ���
	//�������ֲ��Ŷ���
	//  ObjectIndex ��Ҫ�����滻���Ķ�����
	//  width ������
	//  height ����߶�
	//  str �����ַ���
	//  fontname ��������
	//  fontsize �����С
	//  fontcolor ������ɫ
	//  FontStyle ��������
	//  wordwrap �Զ�����
	//  alignment ���뷽ʽ
	//  inmethod ���뷽ʽ(�������б�˵��)
	//  inspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  outmethod ������ʽ(�������б�˵��)
	//  outspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  stopmethod ͣ����ʽ(�������б�˵��)
	//  stopspeed ͣ���ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
	//  stoptime ͣ��ʱ��(��λ����)
	//  istitle �Ƿ����
	long (_stdcall *SZRC_MakeTextObject)(long ObjectIndex, long width, long height, 
		char* str, char* fontname, long fontsize, long fontcolor, long fontstyle, long wordwrap, long alignment,
		long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime, long istitle);

	// ====���붯����ʽ�б�(��ֵ��0��ʼ)====
	//    0 = '���',
	//    1 = '������ʾ',
	//    2 = '�����ʾ',
	//    3 = '�Ϲ���ʾ',
	//    4 = '�ҹ���ʾ',
	//    5 = '�¹���ʾ',
	//    6 = '���������ʾ',
	//    7 = '�����Ϲ���ʾ',
	//    8 = '�м�������չ��',
	//    9 = '�м�������չ��',
	//   10 = '�м�������չ��',
	//   11 = '������������',
	//   12 = '������������',
	//   13 = '��������չ��',
	//   14 = '��������չ��',
	//   15 = '�����Ͻ�����',
	//   16 = '�����½�����',
	//   17 = '�����Ͻ�����',
	//   18 = '�����½�����',
	//   19 = '������������',
	//   20 = '������������',
	//   21 = '�����Ҷ��',
	//   22 = '�����Ҷ��',
	// =====================================

	// ====����������ʽ�б�(��ֵ��0��ʼ)====
	//    0 = '���',
	//    1 = '����ʧ',
	//    2 = '������ʧ',
	//    3 = '�������м��£',
	//    4 = '�������м��£',
	//    5 = '�������м��£',
	//    6 = '���������Ƴ�',
	//    7 = '���������Ƴ�',
	//    8 = '���������£',
	//    9 = '�������Һ�£',
	//   10 = '�����Ͻ��Ƴ�',
	//   11 = '�����½��Ƴ�',
	//   12 = '�����Ͻ��Ƴ�',
	//   13 = '�����½��Ƴ�',
	//   14 = '���������Ƴ�',
	//   15 = '���������Ƴ�',
	//   16 = '�����Ҷ��',
	//   17 = '�����Ҷ��'
	// =====================================

	// ====ͣ��������ʽ�б�(��ֵ��0��ʼ)====
	//    0 = '��̬��ʾ',
	//    1 = '��˸��ʾ'
	// =====================================
private:
//	long m_lDev;
	HINSTANCE m_hInstance;//��̬��ʵ��
	TDeviceParam m_tLedParam;//���ƿ�����
	TSenderParam m_tLedSendParam;//���Ͳ���
private:
	///��װ����
	void Destory();
	bool LED_Initialize();
	long CreateData(const CString& msg,const CRect& rect,
		DWORD lShowTime,int nRegion);
	long m_index;
public:
//	long VisonShowOpen(HWND hWnd);
	//�ӿں���
	void SendDataToScreen(const CString& msg,const CString& wStrIP,const CRect& rect,
		DWORD lShowTime,int nRegion/*������*/);
	void SetHWnd(HWND hWnd);
	//��ȡ���ƿ�Ӧ����������
	long (_stdcall *LED_GetNotifyParam)(PNotifyParam notify, long index);
};
