#pragma once



// CPropSetting
#include "PropQueSettting.h"

#include "UserSetting.h"

#include "DoctorManageDlg.h"
#include "PropConnectToHisSet.h"
//#include "CompConfPropDlg.h"
#include "WaitingRoomConfPropDlg.h"
#include "StbPropDlg.h"
#include "PropDlgThroughLED.h"


class CPropSetting : public CPropertySheet
{
	DECLARE_DYNAMIC(CPropSetting)

public:
	CPropSetting(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPropSetting(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CPropSetting();

	//	CPrintSetting m_propprint;//��ӡ
	CUserSetting m_propuser;//�û�
	CPropQueSettting m_propque;//��������
	//	CPropConsulSetting m_propconsult;//����
	CDoctorManageDlg m_DoctorManageDlg;//ҽ������
	//CPropConnectToHisSet m_propConnectToHis;
	//CCompConfPropDlg m_CompConfPropDlg;
	//	CPropWaittingRoom m_propWait;
	//CWaitingRoomConfPropDlg m_WaitingRoomConfPropDlg;
	CStbPropDlg m_StbPropDlg;//����������
//	CPropThroughWnd m_propThroughWnd;//ͬƵ����
	CPropDlgThroughLED m_PropDlgThroughLED;
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	HICON    m_hIcon;
};


