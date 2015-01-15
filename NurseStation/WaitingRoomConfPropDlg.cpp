// WaitingRoomConfPropDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NurseStation.h"
#include "WaitingRoomConfPropDlg.h"
#include "OpenDatabase.h"
#include "MyString.h"
#include "MyCommon.h"


// CWaitingRoomConfPropDlg �Ի���

IMPLEMENT_DYNAMIC(CWaitingRoomConfPropDlg, CPropertyPage)

CWaitingRoomConfPropDlg::CWaitingRoomConfPropDlg()
	: CPropertyPage(CWaitingRoomConfPropDlg::IDD)
	, m_strRoomName(_T(""))
{
	m_strSqlQuerry = _T("select room_name,stb_id from WaitingRoom;");
}

CWaitingRoomConfPropDlg::~CWaitingRoomConfPropDlg()
{
}

void CWaitingRoomConfPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ED_WAITNAME, m_strRoomName);
	DDX_Control(pDX, IDC_LIST_ROOMLIST, m_lcRoomList);
	DDX_Control(pDX, IDC_COMBO_STBLIST, m_cbStbList);
}


BEGIN_MESSAGE_MAP(CWaitingRoomConfPropDlg, CPropertyPage)
	ON_BN_CLICKED(IDC_BN_ADDWAITROOM, &CWaitingRoomConfPropDlg::OnBnClickedBnAddwaitroom)
	ON_BN_CLICKED(IDC_BN_DELETEWAITROOM, &CWaitingRoomConfPropDlg::OnBnClickedBnDeletewaitroom)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ROOMLIST, &CWaitingRoomConfPropDlg::OnLvnItemchangedListRoomlist)
	ON_CBN_SELCHANGE(IDC_COMBO_STBLIST, &CWaitingRoomConfPropDlg::OnCbnSelchangeComboStblist)
	ON_EN_CHANGE(IDC_ED_WAITNAME, &CWaitingRoomConfPropDlg::OnEnChangeEdWaitname)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_ROOMLIST, &CWaitingRoomConfPropDlg::OnNMCustomdrawListDocList)
END_MESSAGE_MAP()


// CWaitingRoomConfPropDlg ��Ϣ�������

BOOL CWaitingRoomConfPropDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	//��ʼ���б�ؼ�
	ListView_SetExtendedListViewStyle(m_lcRoomList.m_hWnd, 
		LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES/*|LVS_EX_CHECKBOXES*/);
	//m_lcRoomList.DeleteAllItems();
	//while(m_lcRoomList.DeleteColumn(0));
	CRect rect;
	m_lcRoomList.GetClientRect(&rect);
	int nColWidth = rect.Width()/10;
	m_lcRoomList.InsertColumn(0, _T("���"), LVCFMT_CENTER, nColWidth * 2);
	m_lcRoomList.InsertColumn(1, _T("�Ⱥ�������"), LVCFMT_CENTER, nColWidth * 4);
	//m_lcRoomList.InsertColumn(2, _T("�����б��"), LVCFMT_CENTER, nColWidth * 2);
	m_lcRoomList.InsertColumn(2, _T("����������"), LVCFMT_CENTER, nColWidth * 4);

	OpenDatabase odb;
	if(!odb.OpenDB(m_db))
	{
		return FALSE;
	}
	QueryDB();
	UpdateStbList();
	RefreshList();


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CWaitingRoomConfPropDlg::OnBnClickedBnAddwaitroom()
{
	CString strNewRoomName;
	strNewRoomName.Format(_T("�Ⱥ���%d"), m_set.GetRecordCount() + 1);
	m_set.AddNew();
	m_set.SetFieldValue(_T("room_name"), strNewRoomName);
	m_nCurSel = m_set.GetRecordCount() - 1;
	RefreshList();
	SetModified();
}

void CWaitingRoomConfPropDlg::OnBnClickedBnDeletewaitroom()
{
	if(m_nCurSel < 0)
	{
		//MessageBox(_T("δѡ����"), _T("��ʾ"));
		return;
	}
	m_set.Edit();
	m_set.Delete();
	RefreshList();
	SetModified();
}

BOOL CWaitingRoomConfPropDlg::QueryDB(void)
{
	try
	{
		CString strSql(_T("Update WaitingRoom set stb_id=null where stb_id not in (select stb_id from SetTopBox);"));
		m_db.Execute(strSql);
		BOOL isQuerry = m_set.Open(m_db.m_pConnection, m_strSqlQuerry);
	}catch(_com_error&)
	{
		//MessageBox(_T("���ݿ����������"));
		return FALSE; 
	}

	return TRUE;
}

void CWaitingRoomConfPropDlg::RefreshList()
{
	if(m_set.IsBOF())//��Ϊ��
	{
		//MessageBox(_T("��Ϊ��"));
		m_nCurSel = -1;
		return;
	}
	m_lcRoomList.DeleteAllItems();
	CString strValue;
	m_set.MoveFirst();
	for(LONG iItem = 0;!m_set.IsEOF(); iItem++,m_set.MoveNext())
	{
		strValue.Format(_T("%d"), iItem+1);
		m_lcRoomList.InsertItem(iItem, strValue);
		m_set.GetFieldValue(_T("room_name"), strValue);
		m_lcRoomList.SetItemText(iItem, 1, strValue);
		m_set.GetFieldValue(_T("stb_id"), strValue);
		int iStbId = MyString::Str2Int(strValue);
		//m_lcRoomList.SetItemText(iItem, 2, strValue);
		m_lcRoomList.SetItemText(iItem, 2, m_mapStbId_Name[iStbId]);

	}

	//m_lcRoomList.SetCurSel(m_nCurSel);
	//m_lcRoomList.SetHotItem(m_nCurSel);
	if(m_nCurSel > (int)(m_set.GetRecordCount() - 1))
	{
		m_nCurSel = m_set.GetRecordCount() - 1;
	}
	if(m_set.GetRecordCount() == 0)
	{
		m_nCurSel = -1;
	}
	m_lcRoomList.SetItemState(m_nCurSel, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	m_lcRoomList.EnsureVisible(m_nCurSel, TRUE);
}

void CWaitingRoomConfPropDlg::UpdateStbList()
{
	CADORecordset rset;
	if(rset.Open(m_db.m_pConnection, _T("select stb_id, stb_name from SetTopBox where 1=1;"), CADORecordset::openQuery))
	{
		if(!rset.IsBOF())
		{
			int iStbId;
			CString strStbName;
			m_cbStbList.ResetContent();
			m_mapStbId_Name.RemoveAll();
			for(int iItem = 0; !rset.IsEOF(); iItem++, rset.MoveNext())
			{
				rset.GetFieldValue(_T("stb_id"), iStbId);
				rset.GetFieldValue(_T("stb_name"), strStbName);
				m_mapStbId_Name[iStbId] = strStbName;
				int icbItem = m_cbStbList.AddString(strStbName);
				m_cbStbList.SetItemData(icbItem, iStbId);
			}
		}
	}
}


void CWaitingRoomConfPropDlg::OnLvnItemchangedListRoomlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	LONG iItem = pNMLV->iItem;
	m_nCurSel = iItem;
	if(iItem >= 0)
	{
		//m_set.m_pRecordset->Move(iItem,(LONG)adBookmarkFirst);
		m_set.MoveTo(iItem);
		CString strValue;
		m_set.GetFieldValue(_T("room_name"), strValue);
		m_strRoomName = strValue;
		
		//int iStbId;
		//m_set.GetFieldValue(_T("stb_id"), iStbId);
		m_set.GetFieldValue(_T("stb_id"), strValue);
		int iStbId = MyString::Str2Int(strValue);
		int iCbItem = -1;
		for(int i = 0; i < m_cbStbList.GetCount(); i++)
		{
			if(iStbId == m_cbStbList.GetItemData(i))
			{
				iCbItem = i;
				break;
			}
		}
		m_cbStbList.SetCurSel(iCbItem);

		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CWaitingRoomConfPropDlg::OnCbnSelchangeComboStblist()
{
	int iStbId = m_cbStbList.GetItemData(m_cbStbList.GetCurSel());
	m_set.Edit();
	m_set.SetFieldValue(_T("stb_id"), iStbId);
	RefreshList();
	SetModified();
}

void CWaitingRoomConfPropDlg::OnEnChangeEdWaitname()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	UpdateData();
	m_set.Edit();
	m_set.SetFieldValue(_T("room_name"), m_strRoomName);
	RefreshList();
	SetModified();
}

BOOL CWaitingRoomConfPropDlg::OnApply()
{
	//if(m_set.IsConnectionOpen())
	//{
	//	m_set.Update();
	//}

	return CPropertyPage::OnApply();
}

//�б�ؼ�ʧȥ����ʱ���ܱ��ֶ�Ӧ��ѡ��

void CWaitingRoomConfPropDlg::OnNMCustomdrawListDocList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
	*pResult = CDRF_DODEFAULT;
	if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{   
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
	{           
		COLORREF clrNewTextColor, clrNewBkColor;
		int nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec );
		POSITION pos = m_lcRoomList.GetFirstSelectedItemPosition();
		int index = m_lcRoomList.GetNextSelectedItem(pos);
		if (index == nItem)//���Ҫˢ�µ���Ϊ��ǰѡ������������Ϊ��ɫ������ɫ��Ϊ��ɫ
		{             
			clrNewTextColor = RGB(255,255,255);//Set the text to white 
			clrNewBkColor = RGB(49,106,197);        //Set the background color to blue 
		}else{
			clrNewTextColor = RGB(0,0,0);        //set the text black
			clrNewBkColor = RGB(255,255,255);    //leave the background color white
		}
		pLVCD->clrText = clrNewTextColor;
		pLVCD->clrTextBk = clrNewBkColor; 
		*pResult = CDRF_DODEFAULT; 
	}
}

void CWaitingRoomConfPropDlg::UpdateFromDB()
{
	QueryDB();
	UpdateStbList();
	RefreshList();
}
