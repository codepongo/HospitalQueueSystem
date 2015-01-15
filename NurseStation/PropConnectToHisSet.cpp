// PropConnectToHisSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NurseStation.h"
#include "PropConnectToHisSet.h"
#include "MyString.h"
#include "MyCommon.h"
#include "MyPort.h"


// CPropConnectToHisSet �Ի���

IMPLEMENT_DYNAMIC(CPropConnectToHisSet, CPropertyPage)

CPropConnectToHisSet::CPropConnectToHisSet()
	: CPropertyPage(CPropConnectToHisSet::IDD)
	, m_his_port(_T(""))
	, m_his_ip(_T(""))
	, m_his_pass(_T(""))
	, m_his_account(_T(""))
	, m_his_selectbase(0)
	, m_his_basename(_T(""))
	, m_strLocalIp(_T(""))
	, m_strListenPort(_T(""))
{

}

CPropConnectToHisSet::~CPropConnectToHisSet()
{
}

void CPropConnectToHisSet::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HISPORT, m_his_port);
	DDX_Text(pDX, IDC_EDIT_HISIP, m_his_ip);
	DDX_Text(pDX, IDC_EDIT_HISPASS, m_his_pass);
	DDX_Text(pDX, IDC_EDIT_HISACCOUNT, m_his_account);
	//DDX_Control(pDX, IDC_RADIO_HISORACLE, m_his_selectbase);
	DDX_Radio(pDX, IDC_RADIO_HISORACLE, m_his_selectbase);
	DDX_Text(pDX, IDC_EDIT_BASENAME, m_his_basename);
	DDX_Text(pDX, IDC_EDIT_LOCAL_IP, m_strLocalIp);
	DDX_Text(pDX, IDC_EDIT_LISTEN_PORT, m_strListenPort);
}


BEGIN_MESSAGE_MAP(CPropConnectToHisSet, CPropertyPage)
	ON_EN_CHANGE(IDC_EDIT_HISACCOUNT,&CPropConnectToHisSet::OnEnChangeEdAccount)
	ON_EN_CHANGE(IDC_EDIT_HISPASS,&CPropConnectToHisSet::OnEnChangeEdPass)
	ON_EN_CHANGE(IDC_EDIT_HISPORT,&CPropConnectToHisSet::OnEnChangeEdPort)
	ON_EN_CHANGE(IDC_EDIT_HISIP,&CPropConnectToHisSet::OnEnChangeEdIP)
	ON_BN_CLICKED(IDC_RADIO_HISORACLE, &CPropConnectToHisSet::OnBnClickedRadioHisoracle)
	ON_BN_CLICKED(IDC_RADIO_HISSQL, &CPropConnectToHisSet::OnBnClickedRadioHissql)
	ON_BN_CLICKED(IDC_RADIO_HISMYSQL, &CPropConnectToHisSet::OnBnClickedRadioHismysql)
	ON_EN_CHANGE(IDC_EDIT_BASENAME, &CPropConnectToHisSet::OnEnChangeEditBasename)
END_MESSAGE_MAP()


// CPropConnectToHisSet ��Ϣ�������

BOOL CPropConnectToHisSet::OnApply()
{
	// TODO: �ڴ����ר�ô����/����û���
	UpdateData();
	m_baseConfig.SetHisAcount(m_his_account);
	m_baseConfig.SetHisPass(m_his_pass);
	m_baseConfig.SetHisServerIP(m_his_ip);
	m_baseConfig.SetHisPort(m_his_port);
	m_baseConfig.SetHisBaseName(m_his_basename);
	if(m_his_selectbase==0)
	{
		m_hisDataDrive=_T("Oracle");
	}
	else if(m_his_selectbase==1)
	{
		m_hisDataDrive=_T("SQL Server");
	}
	else if(m_his_selectbase==2)
	{
		m_hisDataDrive=_T("MySQL");
	}
	m_baseConfig.SetHisDataDrive(m_hisDataDrive);
	m_baseConfig.SaveHisData();
	return CPropertyPage::OnApply();
}

BOOL CPropConnectToHisSet::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_his_account=m_baseConfig.GetHisAcount();
	m_his_ip=m_baseConfig.GetHisServerIP();
	m_his_pass=m_baseConfig.GetHisPass();
	m_his_port=m_baseConfig.GetHisPort();
	m_hisDataDrive=m_baseConfig.GetHisDataDrive();
	m_his_basename=m_baseConfig.GetHisBaseName();

	if(m_hisDataDrive==_T("Oracle"))
	{
		m_his_selectbase=0;
	}
	else if(m_hisDataDrive==_T("SQL Server"))
	{
		m_his_selectbase=1;
	}
	else if(m_hisDataDrive==_T("MySQL"))
	{
		m_his_selectbase=2;
	}

	//
	MyPort myPort;
	m_strListenPort = MyString::Int2Str(myPort.GetOpenPort(MY_DEFAULT_OPEN_PORT));
	m_strLocalIp = MyCommon::GetLocalIP();

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CPropConnectToHisSet::OnEnChangeEdAccount()
{
	SetModified();
}

void CPropConnectToHisSet::OnEnChangeEdPass()
{
	SetModified();
}

void CPropConnectToHisSet::OnEnChangeEdPort()
{
	SetModified();
}

void CPropConnectToHisSet::OnEnChangeEdIP()
{
	SetModified();
}
void CPropConnectToHisSet::OnBnClickedRadioHisoracle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetModified();
}

void CPropConnectToHisSet::OnBnClickedRadioHissql()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetModified();
}

void CPropConnectToHisSet::OnBnClickedRadioHismysql()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetModified();
}

void CPropConnectToHisSet::OnEnChangeEditBasename()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	SetModified();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
/*
CString CPropConnectToHisSet::GetPort()
{
	CString strExePath = MyCommon::GetModuleDir();
	strExePath += _T("sys\\port.ini");
	WCHAR wszPort[11] = {0};
	//CFile file;
	//if(CommonStrMethod::PathFileExists(strExePath))
	//{
	//	if(file.Open(strExePath, CFile::modeRead))
	//	{
	//		GetPrivateProfileString(_T("sys"),_T("PORT"), NULL, wszPort, 11, strExePath);
	//	}
	//}
	//
	//CString strPort(wszPort);
	//return strPort;

	GetPrivateProfileString(_T("sys"),_T("PORT"), NULL, wszPort, 11, strExePath);
	
	return wszPort;
}
*/
