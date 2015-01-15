// PropPrintShowTime.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NurseStation.h"
#include "PropPrintShowTime.h"
#include "PropPrintSet.h"


// CPropPrintShowTime �Ի���

IMPLEMENT_DYNAMIC(CPropPrintShowTime, CPropertyPage)

CPropPrintShowTime::CPropPrintShowTime()
	: CPropertyPage(CPropPrintShowTime::IDD)
	, m_textColor(RGB(0,0,0))
{
//	m_textColor = RGB(0,0,0);
}

CPropPrintShowTime::~CPropPrintShowTime()
{
}

void CPropPrintShowTime::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDPR_EXAMPLE, m_edpr_example);
	DDX_Control(pDX, IDC_COMPR_TIMESTYLE, m_compr_timeStyle);
	DDX_Control(pDX, IDC_STAPR_COLOR, m_stapr_color);
}


BEGIN_MESSAGE_MAP(CPropPrintShowTime, CPropertyPage)
	ON_BN_CLICKED(IDC_BNPR_FONT, &CPropPrintShowTime::OnBnClickedBnprFont)
	ON_STN_CLICKED(IDC_STAPR_COLOR, &CPropPrintShowTime::OnStnClickedStaColor)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMPR_TIMESTYLE, &CPropPrintShowTime::OnCbnSelchangeComprTimestyle)
END_MESSAGE_MAP()


// CPropPrintShowTime ��Ϣ�������

void CPropPrintShowTime::OnBnClickedBnprFont()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	CFont* pFont = m_edpr_example.GetFont();
	if(pFont != NULL)
		pFont->GetLogFont(&lf);


	CFontDialog fdlg(&lf);
	LOGFONT lplf;
	if(IDOK==fdlg.DoModal())
	{
		fdlg.GetCurrentFont(&lplf);
		m_textFont.DeleteObject();
		m_textFont.CreateFontIndirect(&lplf);
		m_edpr_example.SetFont(&m_textFont,TRUE);
	}
}

void CPropPrintShowTime::OnStnClickedStaColor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CColorDialog dlg;
	if(IDOK == dlg.DoModal())
	{
		m_textColor = dlg.GetColor();
		m_stapr_color.SetBkColor(m_textColor);
	}
}

HBRUSH CPropPrintShowTime::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if(nCtlColor==CTLCOLOR_EDIT &&
		pWnd->GetDlgCtrlID()==IDC_EDPR_EXAMPLE)//ע��˴��ģ�pWnd->��������ûЧ��
	{
		CFont * pfntOld = pDC->SelectObject(&m_textFont);
		pDC->SetTextColor(m_textColor);
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

BOOL CPropPrintShowTime::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CTime currentTime;
	currentTime = CTime::GetCurrentTime();
	CString time;
	time.Format(_T("%d��%d��%d�� %dʱ%d��%d��"),
		currentTime.GetYear(),currentTime.GetMonth(),currentTime.GetDay(),
		currentTime.GetHour(),currentTime.GetMinute(),currentTime.GetSecond());
	m_compr_timeStyle.AddString(time);
	time = currentTime.Format(_T("%Y-%m-%d"));
	m_compr_timeStyle.AddString(time);
	time = currentTime.Format(_T("%H:%M:%S"));
	m_compr_timeStyle.AddString(time);
	time = currentTime.Format(_T("%Y-%m-%d %H:%M:%S"));
	m_compr_timeStyle.AddString(time);

	InitFont();

	SetTimer(ShowPrintTime,1000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CPropPrintShowTime::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CTime currentTime;
	currentTime = CTime::GetCurrentTime();
	CString time;

	switch(nIDEvent)
	{
	case ShowPrintTime:
		{
			int index = m_compr_timeStyle.GetCurSel();
			if(index!=-1)
			{
				switch(index)
				{
				case enumTimeChinese:
					time.Format(_T("%d��%d��%d�� %dʱ%d��%d��"),
						currentTime.GetYear(),currentTime.GetMonth(),currentTime.GetDay(),
						currentTime.GetHour(),currentTime.GetMinute(),currentTime.GetSecond());
					break;
				case enumTimeYearMonthDay:
					time = currentTime.Format(_T("%Y-%m-%d"));
					break;
				case enumTimeHourMinSec:
					time = currentTime.Format(_T("%H:%M:%S"));
					break;
				case enumTimeYMDHMS:
					time = currentTime.Format(_T("%Y-%m-%d %H:%M:%S"));
					break;
				}
			}
			m_edpr_example.SetWindowText(time);
		}
		break;
	}
	CPropertyPage::OnTimer(nIDEvent);
}

void CPropPrintShowTime::OnCbnSelchangeComprTimestyle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CPropPrintShowTime::InitFont()
{
	CPropPrintSet* pPropPrintSet = (CPropPrintSet*)GetParent();
	//CPrintSetDlg* pSetDlg = pPropPrintSet->m_pPrSetDlg;
	CPropPageConfigPrint* pSetDlg = pPropPrintSet->m_pPrSetDlg;
	if(pSetDlg->m_trackContrl.m_pRightBnSelect && pSetDlg->m_bIsForEdit)
	{
		LOGFONT lfFont = pSetDlg->m_trackContrl.m_pRightBnSelect->m_pTransStatic
			->GetTextFont();
		m_textFont.DeleteObject();
		m_textFont.CreateFontIndirect(&lfFont);
		m_textColor = pSetDlg->m_trackContrl.m_pRightBnSelect->m_pTransStatic
			->GetTextColor();
		m_timeFormat = pSetDlg->m_trackContrl.m_pRightBnSelect->m_pTransStatic
			->GetTimeFormat();
		m_compr_timeStyle.SetCurSel(m_timeFormat);
	}
	else
	{
		CClientDC dc(this);
		m_textFont.CreateFont(
			-MulDiv(14, dc.GetDeviceCaps(LOGPIXELSY), 72),                        // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_BOLD,                 // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			_T("����")); 
	}

	m_edpr_example.SetFont(&m_textFont,TRUE);
	m_stapr_color.SetBkColor(m_textColor);
}
void CPropPrintShowTime::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	CPropPrintSet* pPropPrintSet = (CPropPrintSet*)GetParent();
	//CPrintSetDlg* pSetDlg = pPropPrintSet->m_pPrSetDlg;
	CPropPageConfigPrint* pSetDlg = pPropPrintSet->m_pPrSetDlg;

	//��ȡ����
	LOGFONT lfFont;
	m_textFont.GetLogFont(&lfFont);
	int index = m_compr_timeStyle.GetCurSel();
	if(index==-1)
	{
		return;
	}
	else
	{
		switch(index)
		{
		case 0:
			m_timeFormat = enumTimeChinese;
			break;
		case 1:
			m_timeFormat = enumTimeYearMonthDay;
			break;
		case 2:
			m_timeFormat = enumTimeHourMinSec;
			break;
		case 3:
			m_timeFormat = enumTimeYMDHMS;
			break;
		}
	}
	CString text;
	m_edpr_example.GetWindowText(text);
	CRect rect = pSetDlg->GetShowRect();
	CSize textSize;
	HDC hdc = ::GetDC(m_edpr_example.m_hWnd);
	HFONT hOldFont =(HFONT) ::SelectObject(hdc,m_textFont);
	GetTextExtentPoint32(hdc,text,text.GetLength(),&textSize);
	::SelectObject(hdc,hOldFont);
	::ReleaseDC(m_edpr_example.m_hWnd,hdc);
	////////////////////////////////////////
	if(pSetDlg->m_trackContrl.m_pRightBnSelect && pSetDlg->m_bIsForEdit)
	{
		rect = pSetDlg->m_trackContrl.m_pRightBnSelect->m_rect;
		//��ȡOldRect
		CRect oldRect;
		pSetDlg->m_trackContrl.m_pRightBnSelect->GetTrueRect(&oldRect);
		/////////////////////////////////////////
		rect.right = rect.left + textSize.cx;
		rect.bottom = rect.top + textSize.cy;
		pSetDlg->m_trackContrl.ReAdjustMaxRect(rect,TRUE);
		pSetDlg->m_trackContrl.m_pRightBnSelect->m_rect = rect;
		pSetDlg->m_trackContrl.m_pRightBnSelect->MoveWindow(&rect,FALSE);
		//����������ɫ
		pSetDlg->m_trackContrl.m_pRightBnSelect->m_pTransStatic->
			SetTextColor(m_textColor);
		pSetDlg->m_trackContrl.m_pRightBnSelect->m_pTransStatic->
			SetFont(lfFont);
		pSetDlg->m_trackContrl.m_pRightBnSelect->m_pTransStatic->
			SetTimeFormat(m_timeFormat);
		pSetDlg->m_trackContrl.m_pRightBnSelect->m_pTransStatic->
			SetWindowText(text);
		pSetDlg->m_trackContrl.m_pRightBnSelect->m_pTransStatic->
			SetStaticForPrint(TRUE);
		//�ػ�
		pSetDlg->m_trackContrl.m_pRightBnSelect->GetParent()->
			InvalidateRect(&oldRect);
		CRect newRect;
		pSetDlg->m_trackContrl.m_pRightBnSelect->GetTrueRect(newRect);
		pSetDlg->m_trackContrl.m_pRightBnSelect->GetParent()->
			InvalidateRect(&newRect);
	}
	else
	{
		//������ʾʱ��
		rect.right=rect.left + textSize.cx;
		rect.bottom=rect.top + textSize.cy;

		CControlRect *pStatic = new CControlRect(rect);
		pStatic->Create(enmStatic,text,pSetDlg,0,rect,0,0);
		
		pStatic->m_pTransStatic->SetShowTime(TRUE);
		//����������ɫ
		pStatic->m_pTransStatic->SetTextColor(m_textColor);
		pStatic->m_pTransStatic->SetFont(lfFont);
		pStatic->m_pTransStatic->SetTimeFormat(m_timeFormat);
		pStatic->m_pTransStatic->SetStaticForPrint(TRUE);
		pSetDlg->m_trackContrl.Add(pStatic);
	}
	CPropertyPage::OnOK();
}
