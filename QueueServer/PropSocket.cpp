// PropSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QueueServer.h"
#include "PropSocket.h"
#include "../NurseStation/MyPort.h"
#include "../NurseStation/MyCommon.h"
#include "../NurseStation/MyString.h"


// CPropSocket �Ի���

IMPLEMENT_DYNAMIC(CPropSocket, CPropertyPage)

CPropSocket::CPropSocket()
	: CPropertyPage(CPropSocket::IDD)
	, m_strLocalIp(_T(""))
	, m_strListenPort(_T(""))
{

}

CPropSocket::~CPropSocket()
{
}

void CPropSocket::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LOCAL_IP, m_strLocalIp);
	DDX_Text(pDX, IDC_EDIT_LISTEN_PORT, m_strListenPort);
}


BEGIN_MESSAGE_MAP(CPropSocket, CPropertyPage)
	ON_EN_CHANGE(IDC_EDIT_LISTEN_PORT, &CPropSocket::OnEnChangeEditListenPort)
END_MESSAGE_MAP()


// CPropSocket ��Ϣ�������

BOOL CPropSocket::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	//
	MyPort myPort;
	m_strListenPort = MyString::Int2Str(myPort.GetOpenPort(4020));
	m_strLocalIp = MyCommon::GetLocalIP();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CPropSocket::OnEnChangeEditListenPort()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	SetModified();
}

BOOL CPropSocket::OnApply()
{
	UpdateData();

	MyPort myPort;
	myPort.SetOpenPort(m_strListenPort);

	return CPropertyPage::OnApply();
}
