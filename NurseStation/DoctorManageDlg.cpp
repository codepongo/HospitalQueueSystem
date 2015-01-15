// DoctorManageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DoctorManageDlg.h"
#include "BaseConfig.h"
#include "PropSheet.h"
#include "atlimage.h"
#include "stdlib.h"
#include "fstream"
#include "iostream"
#include "DoctorCallConfDlg.h"
#include "MyCommon.h"
#include "MyString.h"
#include "OpenDatabase.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
/*
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()
*/

// CDoctorManageDlg �Ի���

CDoctorManageDlg::CDoctorManageDlg(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CDoctorManageDlg::IDD)
	, m_strName(_T(""))
	, m_strId(_T(""))
	, m_strGender(_T(""))
	, m_strPosition(_T(""))
	, m_strPassword(_T(""))
	, m_nCurSel(-1)
	
	, m_strCallerID(_T(""))
	, m_strEvaluatorID(_T(""))
	, m_strSoundCall(_T(""))
	, m_strSoundWait(_T(""))
	, m_strDisplayCall(_T(""))
	, m_strDisplayWait(_T(""))
	, m_iRecallTimes(0)
	, m_strLoginId(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strPhotoDir = MyCommon::GetModuleDir() + _T("photoTemp\\");
	MyCommon::CreatePath(m_strPhotoDir);
}

CDoctorManageDlg::~CDoctorManageDlg()
{
	//m_db.Close();

	POSITION pos = m_mapOfficeConsults.GetStartPosition();
	CList<CONSULT>* pList;
	CString strKey;
	for(; pos; )
	{
		//CList<CONSULT>* pTemp = pList;
		m_mapOfficeConsults.GetNextAssoc(pos, strKey, pList);
		delete pList;
	}
}

void CDoctorManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_DEL, m_btnDel);
	DDX_Control(pDX, IDC_BUTTON_SET_PHOTO, m_btnSetPhoto);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_ID, m_editId);
	DDX_Control(pDX, IDC_COMBO_GENDER, m_cbGender);
	DDX_Control(pDX, IDC_EDIT_POSITION, m_editPosition);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_editPassword);
	DDX_Control(pDX, IDC_STATIC_PHOTO, m_picPhoto);
	DDX_Control(pDX, IDC_LIST_DOC_LIST, m_listDocList);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_ID, m_strId);
	DDX_Text(pDX, IDC_COMBO_GENDER, m_strGender);
	DDX_Text(pDX, IDC_EDIT_POSITION, m_strPosition);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_BUTTON_EXPORT, m_btnExport);
	DDX_Control(pDX, IDC_BUTTON_IMPORT, m_btnImport);
	DDX_Control(pDX, IDC_COMBO_OFFICE, m_cbOffice);
	DDX_Control(pDX, IDC_COMBO_CONSULT, m_cbConsult);
	DDX_Text(pDX, IDC_EDIT_CALLERID, m_strCallerID);
	DDX_Text(pDX, IDC_EDIT_EVALUATORID, m_strEvaluatorID);
	DDX_Control(pDX, IDC_COMBO_EXPERT, m_cbExpert);
	DDX_Text(pDX, IDC_EDIT_LOGIN_ID, m_strLoginId);
}

BEGIN_MESSAGE_MAP(CDoctorManageDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP

	ON_BN_CLICKED(IDC_BUTTON_SET_PHOTO, &CDoctorManageDlg::OnBnClickedButtonSetPhoto)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDoctorManageDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CDoctorManageDlg::OnBnClickedButtonExport)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_DOC_LIST, &CDoctorManageDlg::OnLvnItemchangedListDocList)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CDoctorManageDlg::OnBnClickedButtonDel)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CDoctorManageDlg::OnEnChangeEditName)
	ON_EN_CHANGE(IDC_EDIT_ID, &CDoctorManageDlg::OnEnChangeEditId)
	ON_CBN_SELCHANGE(IDC_COMBO_GENDER, &CDoctorManageDlg::OnCbnSelchangeComboGender)
	ON_EN_CHANGE(IDC_EDIT_POSITION, &CDoctorManageDlg::OnEnChangeEditPosition)
	ON_EN_CHANGE(IDC_EDIT_PASSWORD, &CDoctorManageDlg::OnEnChangeEditPassword)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_DOC_LIST, &CDoctorManageDlg::OnNMCustomdrawListDocList)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CDoctorManageDlg::OnBnClickedButtonImport)
	ON_CBN_SELCHANGE(IDC_COMBO_OFFICE, &CDoctorManageDlg::OnCbnSelchangeComboOffice)
	ON_CBN_SELCHANGE(IDC_COMBO_CONSULT, &CDoctorManageDlg::OnCbnSelchangeComboConsult)
	ON_EN_CHANGE(IDC_EDIT_CALLERID, &CDoctorManageDlg::OnEnChangeEditCallerid)
	ON_EN_CHANGE(IDC_EDIT_EVALUATORID, &CDoctorManageDlg::OnEnChangeEditEvaluatorid)
	ON_BN_CLICKED(IDC_BUTTON_CALL_CONF, &CDoctorManageDlg::OnBnClickedButtonCallConf)
	ON_CBN_SELCHANGE(IDC_COMBO_EXPERT, &CDoctorManageDlg::OnCbnSelchangeComboExpert)
	ON_EN_CHANGE(IDC_EDIT_LOGIN_ID, &CDoctorManageDlg::OnEnChangeEditLoginId)
END_MESSAGE_MAP()


// CDoctorManageDlg ��Ϣ�������

BOOL CDoctorManageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	/*
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	*/
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//�ļ��Ի���ͼƬ�����ִ�
	//m_strPicFilter = _T("Image files(*.jpg,*.jpeg,*.bmp)|*.jpg;*.jpeg;*.bmp||");
	m_strPicFilter = _T("Image files(*.jpg,*.jpeg)|*.jpg;*.jpeg||");
	m_strFileFilter = _T("Microsoft Excel CSV file(*.csv)|*.csv||");

	//�������ݿ������ַ���
	CBaseConfig config;

	m_strSqlConn = _T("Driver={")+config.GetDataDrive()+_T("};Server=")
		+config.GetServerIP()+_T(";Database=Nurse;Uid=")
		+config.GetServerAcount()+_T(";Pwd=")+config.GetServerPassword()+_T(";");
	m_db.SetConnectionString(m_strSqlConn);
	//m_strSqlQuerry = _T("select D.serial_id,D.name,doctor_id,gender,title,D.office_id,O.name office_name,password,photo,sound_call,display_call from Doctor D left join Office O on D.office_id = O.office_id;");
	//m_strSqlQuerry = _T("select serial_id,doctor_id,name,gender,title,password,photo,sound_call,sound_wait,display_call,display_wait,office_id,consult_id,caller_id,evaluator_id from Doctor order by office_id, name;");
	//m_strSqlQuerry = _T("select serial_id,doctor_id,name,gender,title,password,photo,sound_call,sound_wait,display_call,display_wait,office_id,consult_id,caller_id,evaluator_id from Doctor;");
	//m_strSqlQuerry = _T("select D.*,O.name office_name from Doctor D left join Office O on D.office_id=O.office_id order by office_name,name;");
	m_strSqlQuerry = _T("select * from Doctor order by office_id,name;");
	//m_set.SetQuery(m_strSqlQuerry);

	//�������ݿ�
	OpenDatabase odb;
	if(!odb.OpenDB(m_db))
	{
		m_btnAdd.EnableWindow(FALSE);
		m_btnExport.EnableWindow(FALSE);
		m_btnImport.EnableWindow(FALSE);
	}

	//m_db.BeginTransaction();

	//��ʼ���б�ؼ�
	InitControls();

	//��ʾ����
	ShowList();
	
	//////////////////////////////////////////////////////////////////////////

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDoctorManageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
//	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
//	{
//		CAboutDlg dlgAbout;
//		dlgAbout.DoModal();
//	}
//	else
//	{
		CDialog::OnSysCommand(nID, lParam);
//	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDoctorManageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		ShowPhoto(m_strPhotoPath);
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDoctorManageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDoctorManageDlg::OnBnClickedButtonDel()
{
	if(-1 == m_nCurSel)
	{
		MessageBox(_T("δѡ��ҽ��"));
		return;
	}
	if(IDOK == MessageBox(_T("ȷ��ɾ����ҽ����"), _T("����"), MB_OKCANCEL))
	{
		try
		{
			if(m_set.GetRecordCount() > 0)
			{
				m_set.Delete();
			}
		}
		catch (_com_error& e)
		{

		}
		catch (...)
		{
		}

		RefreshList();

		SetModified();
	}
}

void CDoctorManageDlg::OnBnClickedButtonSetPhoto()
{
	if(-1 == m_nCurSel)
	{
		MessageBox(_T("δѡ��ҽ��"));
		return;
	}
	CFileDialog fdlg(TRUE, 0, 0, 4|2, m_strPicFilter);
	if(IDOK == fdlg.DoModal())
	{
		CString strFile = fdlg.GetPathName();
		CFile imageFile;
		if(!imageFile.Open(strFile, CFile::modeRead))
		{
			MessageBox(_T("��ȡ�ļ�����"), _T("����"));
			return;
		}
		ULONGLONG nlLength = imageFile.GetLength();
		BYTE* pbuf = new BYTE[nlLength];
		if(pbuf == NULL)
		{
			MessageBox(_T("����ͼ���ڴ����"), _T("����"));
			return;
		}
		UINT nReadLength = imageFile.Read(pbuf, nlLength);
		imageFile.Close();
		if(nReadLength == 0) return;

		SAFEARRAY*   psa;  
		SAFEARRAYBOUND   sab[1];  
		sab[0].lLbound = 0;
		sab[0].cElements = nReadLength;
		psa = SafeArrayCreate(VT_UI1, 1, sab);
		BYTE* p = pbuf;
		for(long i = 0; i < nReadLength; i++)
		{
			SafeArrayPutElement(psa,&i, p++);
		}
		delete[] pbuf;

		_variant_t varBLOB;
		varBLOB.vt = VT_ARRAY|VT_UI1;
		varBLOB.parray = psa;

		try
		{
			m_set.Edit();
			m_set.SetFieldValue(_T("photo"),varBLOB);
		}
		catch (_com_error& e)
		{
			MessageBox(_T("ͼ��������ݿ�ʱ����"), _T("����"));
			return;
		}

		RefreshList();
		ShowPhoto(strFile);
		SetModified();
	}
}

void CDoctorManageDlg::OnBnClickedButtonAdd()
{
	//CDoctorAddDlg dlg(this);
	//dlg.DoModal();
	//��ȡ��ǰ���ID
	/*
	CString strMaxDocID, strPrefix, strTempID, strNewID, strNewName, strNewPassword("123");
	int nMaxSerialID = 0, nMaxTemp;
	try
	{
		if(!m_set.IsBOF())
		{
			for(m_set.MoveFirst(); !m_set.IsEOF(); m_set.MoveNext())
			{
				m_set.GetFieldValue(_T("serial_id"), nMaxTemp);
				m_set.GetFieldValue(_T("doctor_id"), strTempID);
				if(nMaxTemp > nMaxSerialID)
				{
					nMaxSerialID = nMaxTemp;
				}
				if(strTempID.CompareNoCase(strMaxDocID) > 0)
				{
					strMaxDocID = strTempID;
				}
			}
		}
	}
	catch (_com_error& e)
	{

	}
	catch (...)
	{
	}

	int nStartNumIndex = strMaxDocID.FindOneOf(_T("0123456789"));
	if(nStartNumIndex == -1)
	{
		strPrefix = strMaxDocID.Left(nStartNumIndex);
		strMaxDocID = strMaxDocID.Mid(nStartNumIndex);
		if(strMaxDocID.IsEmpty())
		{
			strMaxDocID.Format(_T("%04d"), m_set.GetRecordCount());
		}
		char szbuf[32] = {0};
		MyString::WChar2Char(szbuf, 32, strMaxDocID.GetBuffer());
		int nMaxID = ::atoi(szbuf);
		CString strFormat;
		strFormat.Format(_T("%%s%%0%dd"), strMaxDocID.GetLength());
		strNewID.Format(strFormat, strPrefix, nMaxID+1);//
		strNewName.Format(_T("��ҽ��%d"), m_set.GetRecordCount() + 1);
	}
	else
	{
		strNewID.Format(_T("��ҽ��%d"), m_set.GetRecordCount() + 1);
		strNewName = strNewID;
	}
	*/

	CString strTempID, strNewID, strNewName, strNewPassword("123");

	strNewID = _T("��ҽ��1");
	strNewName = strNewID;
	try
	{
		if(!m_set.IsBOF())
		{
			strNewID.Format(_T("��ҽ��%d"), m_set.GetRecordCount() + 1);
			strNewName = strNewID;
			
			for(m_set.MoveFirst(); !m_set.IsEOF(); m_set.MoveNext())
			{
				m_set.GetFieldValue(_T("doctor_id"), strTempID);
				if(strTempID == strNewID)
				{
					SYSTEMTIME t;
					::GetLocalTime(&t);
					strNewID.Format(_T("%04d%02d%02d%02d%02d%02d%03d"),
						t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
					break;
				}
			}
		}
	}
	catch (_com_error& e)
	{

	}
	catch (...)
	{
	}

	CString strCallSound = _T("��[�ŶӺ���]��[��������]��[��������]��");
	CString strWaitSound = _T("��[�ŶӺ���]��[��������]����׼����");
	CString strCallDisplay = _T("#0#��#1#[�ŶӺ���]#0#��#1#[��������]#0#��#0#[��������]");
	CString strWaitDisplay = _T("#0#��#1#[�ŶӺ���]#0#��#1#[��������]#0#����׼�������ң�#0#[��������]");

	try
	{
		m_set.AddNew();
		m_set.SetFieldValue(_T("doctor_id"), strNewID);
		m_set.SetFieldValue(_T("name"), strNewName);
		m_set.SetFieldValue(_T("login_id"), strNewName);
		m_set.SetFieldValue(_T("gender"), genderNone);
		m_set.SetFieldValue(_T("password"), strNewPassword);
		m_set.SetFieldValue(_T("sound_call"), strCallSound);
		m_set.SetFieldValue(_T("sound_wait"), strWaitSound);
		m_set.SetFieldValue(_T("display_call"), strCallDisplay);
		m_set.SetFieldValue(_T("display_wait"), strWaitDisplay);
		m_nCurSel = m_set.GetRecordCount() - 1;
	}
	catch (_com_error& e)
	{
		MessageBox(_T("CAdoRecordset:AddNew Error"));
	}
	catch (...)
	{
	}

	RefreshList();

	SetModified();
	//m_listDocList.EnsureVisible(m_listDocList.GetItemCount()-1, TRUE);
	//m_listDocList.EnsureVisible(m_nCurSel, FALSE);
}

void CDoctorManageDlg::OnBnClickedButtonExport()
{
	CFileDialog dlg(FALSE,_T(".csv"),NULL,OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,m_strFileFilter);
	if(IDOK == dlg.DoModal())
	{
		WriteFileFromDB(dlg.GetPathName());
	}
}

void CDoctorManageDlg::OnBnClickedButtonImport()
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,m_strFileFilter);
	if(IDOK == dlg.DoModal())
	{
		ReadFileToDB(dlg.GetPathName());
		ShowList();
	}
}

void CDoctorManageDlg::OnLvnItemchangedListDocList(NMHDR *pNMHDR, LRESULT *pResult)
{//�ؼ��б���з����ı�ʱ���Ҳ���Ϣ����
	//m_btnSave.EnableWindow(FALSE);
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	LONG iItem = pNMLV->iItem;
	//if(m_nCurSel == iItem) return;
	m_nCurSel = iItem;
	if(iItem >= 0)
	{
		//m_set.m_pRecordset->Move(iItem,(LONG)adBookmarkFirst);
		try
		{
			m_set.MoveTo(iItem);
			
			m_set.GetFieldValue(_T("name"), m_strName);
			m_set.GetFieldValue(_T("doctor_id"), m_strId);
			int nValue;
			m_set.GetFieldValue(_T("gender"), nValue);
			//m_cbGender.SetCurSel(GetGenderCbItem(nValue));
			//m_cbGender.SelectString(-1, GetGenderName(nValue));
			m_cbGender.SetCurSel(-1);
			for (int i = 0; i < m_cbGender.GetCount(); i++)
			{
				if(m_cbGender.GetItemData(i) == nValue)
				{
					m_cbGender.SetCurSel(i);
				}
			}
			m_set.GetFieldValue(_T("expert_flag"), nValue);
			m_cbExpert.SetCurSel(-1);
			for (int i = 0; i < m_cbExpert.GetCount(); i++)
			{
				if(m_cbExpert.GetItemData(i) == nValue)
				{
					m_cbExpert.SetCurSel(i);
				}
			}
			//m_cbGender.SetCurSel(nValue);
			m_set.GetFieldValue(_T("title"), m_strPosition);
			m_set.GetFieldValue(_T("login_id"), m_strLoginId);
			m_set.GetFieldValue(_T("password"), m_strPassword);
			CString strValue;
			m_set.GetFieldValue(_T("office_id"), strValue);
			m_cbOffice.SetCurSel(GetOfficeCbItem(strValue));
			//���¿����б�
			UpdateConsultList();
			m_set.GetFieldValue(_T("consult_id"), strValue);
			m_cbConsult.SetCurSel(GetConsultCbItem(strValue));

			//m_set.GetFieldValue(_T("photo"), m_strPhotoPath);
			//��ʾͷ��
			//ShowPhoto(m_strPhotoPath);
			m_strPhotoPath= m_strPhotoDir + m_strId + _T(".jpg");
			if(!m_set.IsFieldNull(_T("photo")))
			{
				CADOFieldInfo fi;
				m_set.GetFieldInfo(_T("photo"), &fi);
				if(fi.m_lSize > 0)
				{
					_variant_t var;
					m_set.GetFieldValue(_T("photo"), var);
					if(var.vt == VT_BYREF|VT_UI1 && var.vt != VT_NULL && var.vt != VT_EMPTY)
					{
						//m_strPhotoPath= m_strPhotoDir + m_strId + _T(".jpg");
						CFile imageFile;
						if(imageFile.Open(m_strPhotoPath, CFile::modeCreate|CFile::modeWrite))
						{
							BYTE* pbuf = new BYTE[fi.m_lSize];
							if(pbuf == NULL) return;
							BYTE* pbufTemp = pbuf;
							SafeArrayAccessData(var.parray, (void**)&pbuf);
							imageFile.Write(pbuf, fi.m_lSize);
							imageFile.Close();
							SafeArrayUnaccessData(var.parray);
							delete[] pbufTemp;
						}
					}
				}
			}

			m_set.GetFieldValue(_T("caller_id"), m_strCallerID);
			m_set.GetFieldValue(_T("evaluator_id"), m_strEvaluatorID);

			m_set.GetFieldValue(_T("sound_call"), m_strSoundCall);
			m_set.GetFieldValue(_T("sound_wait"), m_strSoundWait);
			m_set.GetFieldValue(_T("display_call"), m_strDisplayCall);
			m_set.GetFieldValue(_T("display_wait"), m_strDisplayWait);
			m_set.GetFieldValue(_T("max_recall_times"), m_iRecallTimes);
			m_set.GetFieldValue(_T("call_special_flag"), m_bCallSpecial);
			m_set.GetFieldValue(_T("wait_num"), m_nWaitNum);
			if(m_nWaitNum < 1) m_nWaitNum = 1;
			m_set.GetFieldValue(_T("wait_when_call_flag"), m_bWaitWhenCall);

			int nHisFlag = 0;
			m_set.GetFieldValue(_T("his_flag"), nHisFlag);
			if(nHisFlag == 1)
			{
				m_editId.EnableWindow(FALSE);
				m_editName.EnableWindow(FALSE);
				m_cbGender.EnableWindow(FALSE);
				m_editPosition.EnableWindow(FALSE);
				//m_cbOffice.EnableWindow(FALSE);
			}
			else
			{
				m_editId.EnableWindow(TRUE);
				m_editName.EnableWindow(TRUE);
				m_cbGender.EnableWindow(TRUE);
				m_editPosition.EnableWindow(TRUE);
				//m_cbOffice.EnableWindow(TRUE);
			}

			UpdateData(FALSE);
			//��ʾͷ��
			ShowPhoto(m_strPhotoPath);
		}
		catch (_com_error& e)
		{

		}
		catch (...)
		{
		}
	}
	*pResult = 0;
}

void CDoctorManageDlg::ShowList(void)
{
	QueryDB();
	RefreshList();
}

BOOL CDoctorManageDlg::QueryDB(void)
{
	try
	{
		BOOL isQuerry = m_set.Open(m_db.m_pConnection, m_strSqlQuerry);
	}catch(_com_error&)
	{
		MessageBox(_T("���ݿ����������"));
		return FALSE; 
	}

	return TRUE;
}

void CDoctorManageDlg::InitControls()
{
	//��ʼ���б�ؼ�
	ListView_SetExtendedListViewStyle(m_listDocList.m_hWnd, 
		LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES/*|LVS_EX_CHECKBOXES*/);

	//m_listDocList.SetRowHeigt(18);
	//m_listDocList.SetHeaderFontHW(14,7);
	//m_listDocList.SetFontHW(14,7);

	m_listDocList.DeleteAllItems();
	while(m_listDocList.DeleteColumn(0));
	CRect rect;
	m_listDocList.GetClientRect(&rect);
	float nColWidth = rect.Width()/100.0;
	m_listDocList.InsertColumn(0, _T("���"), LVCFMT_LEFT, nColWidth * 5);
	m_listDocList.InsertColumn(1, _T("����"), LVCFMT_LEFT, nColWidth * 12);
	m_listDocList.InsertColumn(2, _T("����"), LVCFMT_LEFT, nColWidth * 10);
	m_listDocList.InsertColumn(3, _T("����"), LVCFMT_LEFT, nColWidth * 8);
	m_listDocList.InsertColumn(4, _T("��¼��"), LVCFMT_LEFT, nColWidth * 8);
	m_listDocList.InsertColumn(5, _T("�Ա�"), LVCFMT_LEFT, nColWidth * 5);
	m_listDocList.InsertColumn(6, _T("ְ��"), LVCFMT_LEFT, nColWidth * 10);
	m_listDocList.InsertColumn(7, _T("ר��"), LVCFMT_LEFT, nColWidth * 5);
	m_listDocList.InsertColumn(8, _T("����"), LVCFMT_LEFT, nColWidth * 8);
	m_listDocList.InsertColumn(9, _T("��Ƭ"), LVCFMT_LEFT, nColWidth * 6);
	m_listDocList.InsertColumn(10, _T("������ʾ����"), LVCFMT_LEFT, nColWidth * 11);
	m_listDocList.InsertColumn(11, _T("�غ�Ȩ��"), LVCFMT_LEFT, nColWidth * 8);
	m_listDocList.InsertColumn(12, _T("׼������"), LVCFMT_LEFT, nColWidth * 8);
	m_listDocList.InsertColumn(13, _T("����ʱ׼��"), LVCFMT_LEFT, nColWidth * 10);
	m_listDocList.InsertColumn(14, _T("������"), LVCFMT_LEFT, nColWidth * 7);
	m_listDocList.InsertColumn(15, _T("������"), LVCFMT_LEFT, nColWidth * 7);

	int nItem = m_cbGender.AddString(_T("��"));
	m_cbGender.SetItemData(nItem, genderMale);
	nItem = m_cbGender.AddString(_T("Ů"));
	m_cbGender.SetItemData(nItem, genderFemale);

	nItem = m_cbExpert.AddString(_T("��"));
	m_cbExpert.SetItemData(nItem, expertYes);
	nItem = m_cbExpert.AddString(_T("��"));
	m_cbExpert.SetItemData(nItem, expertNo);

	LoadOfficeList();
	LoadConsults();
}

void CDoctorManageDlg::RefreshList()
{
	try
	{
		if(!m_set.IsOpen())
		{
			QueryDB();
		}

		if(m_set.IsBOF() || m_set.GetRecordCount() == 0)//��Ϊ��
		{
			//MessageBox(_T("��Ϊ��"));
			m_listDocList.DeleteAllItems();
			m_nCurSel = -1;
			m_strName = _T("");
			m_strId = _T("");
			m_cbGender.SetCurSel(-1);
			m_strPosition = _T("");
			m_strPassword = _T("");
			ShowPhoto(CString(_T("")));
			UpdateData(FALSE);
			return;
		}
		m_set.MoveFirst();
		m_listDocList.DeleteAllItems();
		CString strValue;
		int iValue;
		for(LONG iItem = 0;!m_set.IsEOF(); iItem++,m_set.MoveNext())
		{
			strValue.Format(_T("%d"), iItem+1);
			m_listDocList.InsertItem(iItem, strValue);
			m_set.GetFieldValue(_T("office_id"), strValue);
			m_listDocList.SetItemText(iItem, 1, GetOfficeName(strValue));
			m_set.GetFieldValue(_T("name"), strValue);
			m_listDocList.SetItemText(iItem, 2, strValue);
			//m_strPhotoPath = m_strPhotoDir + strValue + _T(".jpg");
			m_set.GetFieldValue(_T("doctor_id"), strValue);
			m_listDocList.SetItemText(iItem, 3, strValue);
			m_set.GetFieldValue(_T("login_id"), strValue);
			m_listDocList.SetItemText(iItem, 4, strValue);
			int nValue;
			m_set.GetFieldValue(_T("gender"), nValue);
			m_listDocList.SetItemText(iItem, 5, GetGenderName(nValue));
			m_set.GetFieldValue(_T("title"), strValue);
			m_listDocList.SetItemText(iItem, 6, strValue);
			m_set.GetFieldValue(_T("expert_flag"), nValue);
			if(nValue == expertYes)
			{
				strValue = _T("��");
			}
			else
			{
				strValue = _T("��");
			}
			m_listDocList.SetItemText(iItem, 7, strValue);
			m_set.GetFieldValue(_T("consult_id"), strValue);
			m_listDocList.SetItemText(iItem, 8, GetConsultName(strValue));

			if(m_set.IsFieldNull(_T("photo")))
			{
				m_listDocList.SetItemText(iItem, 9, _T("��"));
			}
			else
			{
				m_listDocList.SetItemText(iItem, 9, _T("��"));
			}

			int nCount = 0;
			m_set.GetFieldValue(_T("sound_call"), strValue);
			if(!strValue.IsEmpty()) nCount++;
			m_set.GetFieldValue(_T("sound_wait"), strValue);
			if(!strValue.IsEmpty()) nCount++;
			m_set.GetFieldValue(_T("display_call"), strValue);
			if(!strValue.IsEmpty()) nCount++;
			m_set.GetFieldValue(_T("display_wait"), strValue);
			if(!strValue.IsEmpty()) nCount++;
			if(nCount == 0) strValue = _T("δ����");
			else if(nCount < 4) strValue = _T("δ��ȫ����");
			else strValue = _T("������");
			m_listDocList.SetItemText(iItem, 10, strValue);

			m_set.GetFieldValue(_T("call_special_flag"), iValue);
			if(iValue)
			{
				strValue = _T("��");
			}
			else
			{
				strValue = _T("��");
			}
			m_listDocList.SetItemText(iItem, 11, strValue);
			//m_set.GetFieldValue(_T("max_recall_times"), iValue);
			//m_listDocList.SetItemText(iItem, 11, MyString::Int2Str(iValue));
			m_set.GetFieldValue(_T("wait_num"), iValue);
			if(iValue < 1) iValue = 1;
			m_listDocList.SetItemText(iItem, 12, MyString::Int2Str(iValue));
			m_set.GetFieldValue(_T("wait_when_call_flag"), iValue);
			if(iValue)
			{
				strValue = _T("��");
			}
			else
			{
				strValue = _T("��");
			}
			m_listDocList.SetItemText(iItem, 13, strValue);

			m_set.GetFieldValue(_T("caller_id"), strValue);
			m_listDocList.SetItemText(iItem, 14, strValue);
			m_set.GetFieldValue(_T("evaluator_id"), strValue);
			m_listDocList.SetItemText(iItem, 15, strValue);
		}
		//m_listDocList.SetCurSel(m_nCurSel);
		//m_listDocList.SetHotItem(m_nCurSel);
		if(m_nCurSel > m_set.GetRecordCount() - 1)
		{
			m_nCurSel = m_set.GetRecordCount() - 1;
		}
		//if(m_set.GetRecordCount() == 0)
		//{
		//	m_nCurSel = -1;
		//}
		m_set.MoveTo(m_nCurSel);
		m_set.GetFieldValue(_T("doctor_id"), strValue);
		m_strPhotoPath = m_strPhotoDir + strValue + _T(".jpg");
	}
	catch (_com_error& e)
	{
		if(0x80040e14 == e.Error())
		{
			MessageBox(_T("�����ظ��Ĺ��ţ�"));
			//m_editId.SetFocus();
		}
		else
		{
			CString errStr;
			_bstr_t bstrSource(e.Source());
			_bstr_t bstrDescription(e.Description());
			CString m_strErrorDescription(_T(""));
			m_strErrorDescription = (LPCSTR)bstrDescription ;
			CString str=_T("");
			str=(LPCTSTR)bstrSource;
			errStr.Format(_T("CADODataBase Error\n\tCode = %08lx\n\tCode meaning = %s\n\tSource = %s\n\tDescription = %s\n"),
				e.Error(), e.ErrorMessage(), str, m_strErrorDescription);
			MessageBox(errStr);
		}
		//QueryDB();
	}

	m_listDocList.SetItemState(m_nCurSel, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	m_listDocList.EnsureVisible(m_nCurSel, TRUE);

	//
	NMLISTVIEW nmlv;
	memset (&nmlv, 0, sizeof (nmlv));
	nmlv.hdr.hwndFrom = m_listDocList.m_hWnd;
	//nmlv.hdr.hwndFrom = this->m_hWnd;
	nmlv.hdr.idFrom = m_listDocList.GetDlgCtrlID();//GetDlgCtrlId() ;0x00190ca4
	nmlv.hdr.code = LVN_ITEMCHANGED;
	nmlv.iItem = m_nCurSel;
	nmlv.iSubItem=0;
	nmlv.uNewState = 3 ;
	nmlv.uOldState = 0;
	nmlv.uChanged = LVIF_STATE;
	nmlv.lParam = 0;
	//m_listDocList.GetParent()->SendMessage(WM_NOTIFY,nmlv.hdr.idFrom,(LPARAM)(&nmlv));
	//SendMessage(WM_NOTIFY,nmlv.hdr.idFrom,(LPARAM)(&nmlv));
}

CString CDoctorManageDlg::GetTransStr(CString strSrc)
{
	if(strSrc.IsEmpty())
	{
		return _T("��");
	}
	else
	{
		return _T("��");
	}
}

CString CDoctorManageDlg::GetOfficeName(CString strOfficeID)
{
	POSITION pos = m_mapOfficeList.GetStartPosition();
	OFFICE office;
	int nKey;
	for(; pos; )
	{
		m_mapOfficeList.GetNextAssoc(pos, nKey, office);
		if(office.strOfficeID.Compare(strOfficeID) == 0)
		{
			return office.strOfficeName;
		}
	}
	return _T("");
}

int CDoctorManageDlg::GetOfficeCbItem(CString strOfficeID)
{
	POSITION pos = m_mapOfficeList.GetStartPosition();
	OFFICE office;
	int nKey;
	for(; pos; )
	{
		m_mapOfficeList.GetNextAssoc(pos, nKey, office);
		if(office.strOfficeID.Compare(strOfficeID) == 0)
		{
			return nKey;
		}
	}
	return -1;
}

CString CDoctorManageDlg::GetConsultName(CString strConsultID)
{
	/*
	POSITION pos = m_mapConsultList.GetStartPosition();
	CONSULT consult;
	int nKey;
	for(; pos; )
	{
		m_mapConsultList.GetNextAssoc(pos, nKey, consult);
		if(consult.strConsultID.Compare(strConsultID) == 0)
		{
			return consult.strConsultName;
		}
	}
	return _T("");
	*/
	return m_mapConsultIDConsultName[strConsultID];
}

int CDoctorManageDlg::GetConsultCbItem(CString strConsultID)
{
	POSITION pos = m_mapConsultList.GetStartPosition();
	CONSULT consult;
	int nKey;
	for(; pos; )
	{
		m_mapConsultList.GetNextAssoc(pos, nKey, consult);
		if(consult.strConsultID.Compare(strConsultID) == 0)
		{
			return nKey;
		}
	}
	return -1;
}

CString CDoctorManageDlg::GetGenderName(int eGenderID)
{
	//POSITION pos = m_mapGenderList.GetStartPosition();
	//USERGENDER usergd;
	//int nKey;
	//for(; pos; )
	//{
	//	m_mapGenderList.GetNextAssoc(pos, nKey, usergd);
	//	if(usergd.eGenderID == eGenderID)
	//	{
	//		return usergd.strGenderName;
	//	}
	//}
	//return _T("");
	CString strGender;
	switch(eGenderID)
	{
	case genderMale:
		strGender = _T("��");
		break;
	case genderFemale:
		strGender = _T("Ů");
		break;
	case genderNone:
		break;
	default:
		break;
	}
	return strGender;
}

int CDoctorManageDlg::GetGenderCbItem(int eGenderID)
{
	//POSITION pos = m_mapGenderList.GetStartPosition();
	//USERGENDER usergd;
	//int nKey;
	//for(; pos; )
	//{
	//	m_mapGenderList.GetNextAssoc(pos, nKey, usergd);
	//	if(usergd.eGenderID == eGenderID)
	//	{
	//		return nKey;
	//	}
	//}
	return m_cbGender.FindString(-1, GetGenderName(eGenderID));
}

void CDoctorManageDlg::OnEnChangeEditName()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	//m_listDocList.SetItemText(m_nCurSel, 1, m_strName);
	//m_editId.SetFocus();
	UpdateData(TRUE);
	try
	{
		m_set.Edit();
		m_set.SetFieldValue(_T("name"), m_strName);
	}
	catch (_com_error& e)
	{

	}
	catch (...)
	{
	}
	RefreshList();
	SetModified();
}

void CDoctorManageDlg::OnEnChangeEditId()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	CString strIdTemp = m_strId;
	UpdateData(TRUE);
	try
	{
		m_set.Edit();
		m_set.SetFieldValue(_T("doctor_id"), m_strId);
		m_set.Update();
	}
	//catch (CADOException& e)
	catch (_com_error& e)
	{
		if(0x80040e14 == e.Error())
		{
			MessageBox(_T("�����ظ��Ĺ��ţ�"));
			try
			{
				m_set.Edit();
				m_set.SetFieldValue(_T("doctor_id"), strIdTemp);
			}
			catch (_com_error& e)
			{
				
			}
			catch (...)
			{
			}
		}
	}
	catch (...)
	{
	}

	RefreshList();
	SetModified();
}

void CDoctorManageDlg::OnEnChangeEditPosition()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	UpdateData(TRUE);
	try
	{
		m_set.Edit();
		m_set.SetFieldValue(_T("title"), m_strPosition);
	}
	catch (_com_error& e)
	{

	}
	catch (...)
	{
	}

	RefreshList();
	SetModified();
}

void CDoctorManageDlg::OnEnChangeEditCallerid()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	UpdateData(TRUE);
	try
	{
		m_set.Edit();
		m_set.SetFieldValue(_T("caller_id"), m_strCallerID);
	}
	catch (_com_error& e)
	{

	}
	catch (...)
	{
	}

	RefreshList();
	SetModified();
}

void CDoctorManageDlg::OnEnChangeEditEvaluatorid()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	UpdateData(TRUE);
	try
	{
		m_set.Edit();
		m_set.SetFieldValue(_T("evaluator_id"), m_strEvaluatorID);
	}
	catch (_com_error& e)
	{

	}
	catch (...)
	{
	}

	RefreshList();
	SetModified();
}

void CDoctorManageDlg::OnEnChangeEditPassword()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	UpdateData(TRUE);
	try
	{
		m_set.Edit();
		m_set.SetFieldValue(_T("password"), m_strPassword);
	}
	catch (_com_error& e)
	{

	}
	catch (...)
	{
	}

	RefreshList();
	SetModified();
}

void CDoctorManageDlg::OnCbnSelchangeComboGender()
{
	try
	{
		m_set.Edit();
		//int iGender = m_cbGender.GetItemData(m_cbGender.GetCurSel());
		m_set.SetFieldValue(_T("gender"), m_cbGender.GetItemData(m_cbGender.GetCurSel()));
	}
	catch (_com_error& e)
	{

	}
	catch (...)
	{
	}

	RefreshList();
	SetModified();
}

void CDoctorManageDlg::OnCbnSelchangeComboOffice()
{
	try
	{
		m_set.Edit();
		m_set.SetFieldValue(_T("office_id"), m_mapOfficeList[m_cbOffice.GetCurSel()].strOfficeID);
	}
	catch (_com_error& e)
	{

	}
	catch (...)
	{
	}

	UpdateConsultList();
	RefreshList();
	SetModified();
}


void CDoctorManageDlg::OnCbnSelchangeComboConsult()
{
	try
	{
		m_set.Edit();
		m_set.SetFieldValue(_T("consult_id"), m_mapConsultList[m_cbConsult.GetCurSel()].strConsultID);
	}
	catch (_com_error& e)
	{

	}
	catch (...)
	{
	}

	RefreshList();
	SetModified();
}

void CDoctorManageDlg::UpdateDocInfo()
{
	try
	{
		m_set.MoveTo(m_nCurSel);

		CString strOldID;
		m_set.GetFieldValue(_T("doctor_id"), strOldID);
		if(strOldID.Compare(m_strId) != 0)
		{
			BOOL bExistID = FALSE;
			CString strTempID;
			for(m_set.MoveFirst(); !m_set.IsEOF(); m_set.MoveNext())
			{
				m_set.GetFieldValue(_T("doctor_id"), strTempID);
				if(strTempID.Compare(m_strId) == 0)
				{
					bExistID = TRUE;
					MessageBox(_T("�ù����Ѵ��ڣ�����������"));
				}
			}
			m_set.MoveTo(m_nCurSel);
			if(!bExistID)
			{
				m_set.SetFieldValue(_T("doctor_id"), m_strId);
			}
		}
		m_set.Update();
	}
	catch (_com_error& e)
	{

	}
	catch (...)
	{
	}

	RefreshList();
}

//��save��ť��Ϊ����
/*
void CDoctorManageDlg::EnableSave(void)
{
	//m_btnSave.EnableWindow(TRUE);
	SetModified();
	//m_btnSave.SetFocus();
}
*/
/*
BOOL CDoctorManageDlg::OnSetActive(void)
{
	CPropSheet* pSheet = (CPropSheet*)GetParent();
	//pSheet->
	return 0;
}
*/


//�б�ؼ�ʧȥ����ʱ���ܱ��ֶ�Ӧ��ѡ��

void CDoctorManageDlg::OnNMCustomdrawListDocList(NMHDR *pNMHDR, LRESULT *pResult)
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
		POSITION pos = m_listDocList.GetFirstSelectedItemPosition();
		int index = m_listDocList.GetNextSelectedItem(pos);
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

BOOL CDoctorManageDlg::ShowPhoto(CString strPhotoPath, CWnd* pWnd)
{
	CStatic* picPhoto = (CStatic*)pWnd;
	CDC* pDC = picPhoto->GetWindowDC();
	CRect rect;
	picPhoto->GetClientRect(&rect);
	CImage img;
	BOOL bGo = TRUE;
	if(strPhotoPath.IsEmpty())
	{
		bGo = FALSE;
		//return FALSE;
	}
	HRESULT hResult = img.Load(strPhotoPath);
	if(FAILED(hResult))
	{
		//m_set.Edit();
		//m_set.SetFieldValue(_T("photo"), CString(_T("")));
		//m_set.Update();
		//RefreshList();
		//MessageBox(_T("ͼƬ·�����󣬵���ʧ��"));
		bGo = FALSE;
		//return FALSE;
	}
	if(bGo)
	{
		pDC->SetStretchBltMode(STRETCH_HALFTONE);
		img.Draw(pDC->m_hDC, 0, 0, rect.Width(), rect.Height(), 
			0, 0, img.GetWidth(), img.GetHeight());
	}
	else
	{
		pDC->SelectStockObject(GRAY_BRUSH);
		pDC->FillRect(
			&rect, pDC->GetCurrentBrush());
	}
	return bGo;
}

BOOL CDoctorManageDlg::SetStaticPicture(CWnd* pWnd, int iPicture)
{
	CStatic* picPhoto = (CStatic*)pWnd;
	CDC* pDC = picPhoto->GetWindowDC();
	CRect rect;
	picPhoto->GetClientRect(&rect);
	CImage img;
	//if(iBitMap)
	//{
	//	pDC->SelectStockObject(GRAY_BRUSH);
	//	pDC->FillRect(
	//		&rect, pDC->GetCurrentBrush());
	//	return FALSE;
	//}
	HRESULT hResult = img.Load(MAKEINTRESOURCE(iPicture));
	//if(FAILED(hResult))
	//{
	//	m_set.Edit();
	//	m_set.SetFieldValue(_T("photo"), CString(_T("")));
	//	m_set.Update();
	//	RefreshList();
	//	MessageBox(_T("ͼƬ·�����󣬵���ʧ��"));
	//	return FALSE;
	//}
	pDC->SetStretchBltMode(STRETCH_HALFTONE);
	img.Draw(pDC->m_hDC, 0, 0, rect.Width(), rect.Height(), 
		0, 0, img.GetWidth(), img.GetHeight());

	return TRUE;
}

/*
BOOL CDoctorManageDlg::ShowPhoto(CString& strPhotoPath, HDC* hdc)
{
	CImage img;
	if(strPhotoPath.IsEmpty())
	{
		MessageBox(_T("��Ƭδ����"));
	}
	HRESULT hResult = img.Load(strPhotoPath);
	if(FAILED(hResult))
	{
		MessageBox(_T("����ͼƬ�ļ�ʧ��"));
		return FALSE;
	}
	CRect rect;
	m_picPhoto.GetClientRect(&rect);
	CDC* pDC = m_picPhoto.GetWindowDC();
	pDC->SetStretchBltMode(STRETCH_HALFTONE);
	img.Draw(*hdc, 0, 0, rect.Width(), rect.Height(), 
		0, 0, img.GetWidth(), img.GetHeight());
	return TRUE;
}
*/
//��ʾͷ��
void CDoctorManageDlg::ShowPhoto(CString strPhotoPath)
{
	m_strPhotoPath = strPhotoPath;
	ShowPhoto(strPhotoPath, (CWnd*)&m_picPhoto);
}

int CDoctorManageDlg::ReadFileToDB(CString strFilePath)
{
	ifstream file(strFilePath);
	CHAR buf[2048] = {0};
	WCHAR wbuf[2048] = {0};
	if(!file.is_open())
	{
		MessageBox(_T("�ļ���ʧ��"));
		return -1;
	}
	if(!file.eof())
	{
		file.getline(buf, 2048);
	}
	WCHAR* pArr[15] = {0};
	for(int i = 0; i < 15; i++)
	{
		pArr[i] = (WCHAR*)malloc(512);
	}
	int errRows = 0;
	CString errfilePath(_T("c:/doctor_import_failed.log"));
	CFile file_err(errfilePath,CFile::modeCreate|CFile::modeWrite);
	CHAR* strErr = "������Ϣ�޷����룬�����ǹ����ظ���\r\n";
	file_err.Write(strErr, strlen(strErr));
	for(;!file.eof()/*&&file.good()*/;)
	{
		memset(buf, 0, 2048);
		file.getline(buf, 2048);
		MyString::Char2WChar(wbuf, 4096, buf);
		SplitWStrToWStrArray(wbuf, pArr);
#ifdef _DEBUG
		//CString str;
		//str.Format(_T("source:%s"), buf);
		//MessageBox(str);
		//str.Format(_T("dest:%s,%s,%s,%s,%s,%s,%s,%s,%s"),
		//	pArr[0],pArr[1],pArr[2],pArr[3],pArr[4],
		//	pArr[5],pArr[6],pArr[7],pArr[8]);
		//MessageBox(str);
#endif
		if(strlen(buf) > 0)
		{
			//CString strLines(_T("����,����,�Ա�,ְ��,����,��Ƭ,����,��ʾ,����ID,����ID,������,������,\r\n"));
			CString strSql;
			strSql.Format(_T("insert into Doctor(doctor_id,name,gender,title,password,photo,sound_call,sound_wait,display_call,display_wait,office_id,consult_id,caller_id,evaluator_id) values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s');"),
				pArr[0],pArr[1],pArr[2],pArr[3],pArr[4],pArr[5],pArr[6],pArr[7],pArr[8],pArr[9],pArr[10],pArr[11],pArr[12],pArr[13]);
			try
			{
				m_db.Execute(strSql);
			}catch(_com_error&)
			{
				errRows++;
				file_err.Write(buf, strlen(buf));
				file_err.Write("\r\n",2);
			}
		}
	}
	file.close();
	for(int i = 0; i < 10; i++)
	{
		free(pArr[i]);
		pArr[i] = 0;
	}
	if(errRows)
	{
		CString err;
		err.Format(_T("�� %d �����ݵ���ʧ�ܣ�����������鿴\n%s"),errRows,errfilePath);
		MessageBox(err);
	}

	return errRows;
}

int CDoctorManageDlg::WriteFileFromDB(CString strFilePath)
{
	//select serial_id,doctor_id,name,gender,title,password,photo,sound_call,display_call,office_id,consult_id,caller_id,evaluator_id from Doctor order by office_id, name
	m_set.MoveFirst();
	CFile file(strFilePath, CFile::modeCreate|CFile::modeWrite);
	CString strLines(_T("����,����,�Ա�,ְ��,����,��Ƭ,��������,׼������,������ʾ,׼����ʾ,����ID,����ID,������,������,\r\n"));
	CString strCol;
	LONG lColumn = m_set.GetFieldCount();
	for(; !m_set.IsEOF(); m_set.MoveNext())
	{
		LONG i = 1;
		for(; i < lColumn; i++)
		{
			m_set.GetFieldValue(i,strCol);
			strLines += strCol;
			strLines += ",";
		}
		strLines += "\r\n";
	}
	m_set.MoveTo(m_nCurSel);
	int nBytes = WideCharToMultiByte(0, 0,strLines, strLines.GetLength(), 
		NULL, 0, NULL, NULL);
	CHAR *buf = (CHAR*)malloc((sizeof(CHAR))*2*(nBytes + 1));
	memset(buf, 0, (sizeof(CHAR))*2*(nBytes + 1));
	WideCharToMultiByte(0, 0, strLines, strLines.GetLength(), 
		buf, nBytes, NULL, NULL);
	file.Write(buf, strlen(buf));
	free(buf);
	file.Close();
	return 0;
}

int CDoctorManageDlg::SplitWStrToWStrArray(WCHAR* strSrc, WCHAR** outArray)
{
	if(!outArray)
	{
		return -1;
	}
	WCHAR ch;
	for(int i = 0; (ch = *(strSrc++)); )
	{
		if(ch != ',')
		{
			(*outArray)[i++] = ch;
		}
		else
		{
			(*outArray)[i] = 0;
			i = 0;
			outArray++;
		}
	}
	(*outArray)[0] = 0;
	return 0;
}

BOOL CDoctorManageDlg::LoadOfficeList()
{
	CString strSql("Select office_id, name from Office order by name;");
	CADORecordset rset;
	try
	{
		BOOL res = rset.Open(m_db.m_pConnection, strSql);
		if(!rset.IsBOF())
		{
			m_mapOfficeList.RemoveAll();
			m_cbOffice.ResetContent();
			int nItem = -1;
			OFFICE lst;
			for(; !rset.IsEOF(); rset.MoveNext())
			{
				rset.GetFieldValue(_T("office_id"), lst.strOfficeID);
				rset.GetFieldValue(_T("name"), lst.strOfficeName);
				nItem = m_cbOffice.AddString(lst.strOfficeName);
				m_mapOfficeList[nItem] = lst;
			}
		}
		return TRUE;
	}
	catch(_com_error& e)
	{
		MessageBox(_T("���ݿ��ѯ����")
			,_T("����"), MB_OK|MB_ICONERROR);
		return FALSE;
	}
}

BOOL CDoctorManageDlg::LoadConsults()
{
	CString strSql;
	CADORecordset rset;
	POSITION pos = m_mapOfficeList.GetStartPosition();
	int nKey;
	OFFICE office;
	try
	{
		for(; pos; )
		{
			m_mapOfficeList.GetNextAssoc(pos, nKey, office);
			if(!office.strOfficeID.IsEmpty())
			{
				strSql.Format(_T("select consult_id, name from Consult where office_id='%s' order by name;"), office.strOfficeID);
				rset.Open(m_db.m_pConnection, strSql);
				if(!rset.IsBOF())
				{
					CList<CONSULT>* lstConsultList = new CList<CONSULT>;
					for(; !rset.IsEOF(); rset.MoveNext())
					{
						CONSULT lst;
						rset.GetFieldValue(_T("consult_id"), lst.strConsultID);
						rset.GetFieldValue(_T("name"), lst.strConsultName);
						lstConsultList->AddTail(lst);
						m_mapConsultIDConsultName[lst.strConsultID] = lst.strConsultName;
					}
					m_mapOfficeConsults[office.strOfficeID] = lstConsultList;
				}
			}
		}
		return TRUE;
	}
	catch (_com_error& e)
	{

	}
	catch (...)
	{
	}

	return FALSE;
}
/*
BOOL CDoctorManageDlg::LoadGenderList()
{
	int nItem = m_cbGender.AddString(_T("��"));
	m_cbGender.SetItemData(nItem, genderMale);
	nItem = m_cbGender.AddString(_T("Ů"));
	m_cbGender.SetItemData(nItem, genderFemale);

	return TRUE;
}

void CDoctorManageDlg::LoadExpertList()
{
	int nItem = m_cbExpert.AddString(_T("��"));
	m_cbExpert.SetItemData(nItem, expertYes);
	nItem = m_cbExpert.AddString(_T("��"));
	m_cbExpert.SetItemData(nItem, expertNo);
}
*/

BOOL CDoctorManageDlg::UpdateConsultList()
{
	m_cbConsult.ResetContent();
	CString strSql;

	CList<CONSULT>* lstConsultList = 
		m_mapOfficeConsults[m_mapOfficeList[m_cbOffice.GetCurSel()].strOfficeID];
	if(lstConsultList == NULL) return FALSE;
	if(lstConsultList->IsEmpty()) return FALSE;
	int nIndex = -1;
	POSITION pos = lstConsultList->GetHeadPosition();
	CONSULT consult = {0};
	for(; pos; )
	{
		consult = lstConsultList->GetNext(pos);
		nIndex = m_cbConsult.AddString(consult.strConsultName);
		m_mapConsultList[nIndex] = consult;
	}
	return TRUE;
}
/*
BOOL CDoctorManageDlg::OpenDB(CADODatabase &db)
{
	CBaseConfig config;
	CString strSqlConn = _T("Driver={")+config.GetDataDrive()+_T("};Server=")
		+config.GetServerIP()+_T(";Database=Nurse;Uid=")
		+config.GetServerAcount()+_T(";Pwd=")+config.GetServerPassword()+_T(";");
	db.SetConnectionString(strSqlConn);
	try
	{
		db.Open();
		return TRUE;
	}catch(_com_error& e)
	{
		MessageBox(_T("���ݿ�����ʧ��,����������ԭ��\n\t1.���������ݿ�����������ѶϿ���\n\t2.���ݿ����δ������\n\t3.���ݿ������ļ������ڻ����ô���;\n\t4.���ݿ��û����������")
			,_T("����"), MB_OK|MB_ICONERROR);
	}
	return FALSE;
}
*/


BOOL CDoctorManageDlg::DestroyWindow()
{
/*	if(m_phisDataBase)
	{
		if(m_phisDataBase->IsOpen())
		{
			m_phisDataBase->Close();
		}
		delete m_phisDataBase;
		m_phisDataBase=NULL;
	}
	*/
	return CPropertyPage::DestroyWindow();
}

BOOL CDoctorManageDlg::OnApply()
{
	//UpdateDocInfo();

	try
	{
		//UpdateDocInfo();
		//m_set.Update();
		//m_db.CommitTransaction();
		//m_db.BeginTransaction();
	}
	catch (_com_error& e)
	{
		if(0x80040e14 == e.Error())
		{
			MessageBox(_T("�����ظ��Ĺ��ţ�"));;
			//m_editId.SetFocus();
		}
		else
		{
			CString errStr;
			_bstr_t bstrSource(e.Source());
			_bstr_t bstrDescription(e.Description());
			CString m_strErrorDescription(_T(""));
			m_strErrorDescription = (LPCSTR)bstrDescription ;
			CString str=_T("");
			str=(LPCTSTR)bstrSource;
			errStr.Format(_T("CADODataBase Error\n\tCode = %08lx\n\tCode meaning = %s\n\tSource = %s\n\tDescription = %s\n"),
				e.Error(), e.ErrorMessage(), str, m_strErrorDescription);
			MessageBox(errStr);
		}
	}

	return CPropertyPage::OnApply();
}

void CDoctorManageDlg::OnCancel()
{
	try
	{
		//m_set.CancelUpdate();
		//m_db.RollbackTransaction();
	}
	catch (_com_error& e)
	{

	}
	catch (...)
	{
	}

	CPropertyPage::OnCancel();
}

void CDoctorManageDlg::OnBnClickedButtonCallConf()
{
	if(-1 == m_nCurSel)
	{
		MessageBox(_T("δѡ��ҽ��"));
		return;
	}

	CDoctorCallConfDlg dlg(this);
	if(dlg.DoModal() == IDOK)
	{
		try
		{
			m_set.Edit();
			//if(dlg.m_ckConfAll.GetCheck() == BST_CHECKED)
			if(dlg.m_nRadioConfType == 2)
			{
				for(m_set.MoveFirst(); !m_set.IsEOF(); m_set.MoveNext())
				{
					m_set.SetFieldValue(_T("sound_call"), m_strSoundCall);
					m_set.SetFieldValue(_T("sound_wait"), m_strSoundWait);
					m_set.SetFieldValue(_T("display_call"), m_strDisplayCall);
					m_set.SetFieldValue(_T("display_wait"), m_strDisplayWait);
					m_set.SetFieldValue(_T("max_recall_times"), m_iRecallTimes);
					m_set.SetFieldValue(_T("call_special_flag"), m_bCallSpecial);
					m_set.SetFieldValue(_T("wait_num"), m_nWaitNum);
					m_set.SetFieldValue(_T("wait_when_call_flag"), m_bWaitWhenCall);
				}
				m_set.MoveTo(m_nCurSel);
			}
			else if(dlg.m_nRadioConfType == 1)
			{
				CString strCurOfficeId;
				m_set.GetFieldValue(_T("office_id"), strCurOfficeId);
				for(m_set.MoveFirst(); !m_set.IsEOF(); m_set.MoveNext())
				{
					CString strOfficeId;
					m_set.GetFieldValue(_T("office_id"), strOfficeId);
					if(strOfficeId == strCurOfficeId)
					{
						m_set.SetFieldValue(_T("sound_call"), m_strSoundCall);
						m_set.SetFieldValue(_T("sound_wait"), m_strSoundWait);
						m_set.SetFieldValue(_T("display_call"), m_strDisplayCall);
						m_set.SetFieldValue(_T("display_wait"), m_strDisplayWait);
						m_set.SetFieldValue(_T("max_recall_times"), m_iRecallTimes);
						m_set.SetFieldValue(_T("call_special_flag"), m_bCallSpecial);
						m_set.SetFieldValue(_T("wait_num"), m_nWaitNum);
						m_set.SetFieldValue(_T("wait_when_call_flag"), m_bWaitWhenCall);
					}
				}
				m_set.MoveTo(m_nCurSel);
			}
			else
			{
				m_set.SetFieldValue(_T("sound_call"), m_strSoundCall);
				m_set.SetFieldValue(_T("sound_wait"), m_strSoundWait);
				m_set.SetFieldValue(_T("display_call"), m_strDisplayCall);
				m_set.SetFieldValue(_T("display_wait"), m_strDisplayWait);
				m_set.SetFieldValue(_T("max_recall_times"), m_iRecallTimes);
				m_set.SetFieldValue(_T("call_special_flag"), m_bCallSpecial);
				m_set.SetFieldValue(_T("wait_num"), m_nWaitNum);
				m_set.SetFieldValue(_T("wait_when_call_flag"), m_bWaitWhenCall);
			}
		}
		catch (_com_error& e)
		{
		}
		catch (...)
		{
		}

		RefreshList();
		SetModified();
	}
}

void CDoctorManageDlg::OnCbnSelchangeComboExpert()
{
	try
	{
		m_set.Edit();
		//int iGender = m_cbGender.GetItemData(m_cbGender.GetCurSel());
		m_set.SetFieldValue(_T("expert_flag"), m_cbExpert.GetItemData(m_cbExpert.GetCurSel()));
	}
	catch (_com_error& e)
	{

	}
	catch (...)
	{
	}

	RefreshList();
	SetModified();
}

BOOL CDoctorManageDlg::OnSetActive()
{
	LoadOfficeList();
	LoadConsults();
	UpdateConsultList();
	RefreshList();
	ShowPhoto(m_strPhotoPath);

	return CPropertyPage::OnSetActive();
}

void CDoctorManageDlg::OnOK()
{
	//m_db.CommitTransaction();

	CPropertyPage::OnOK();
}

void CDoctorManageDlg::OnEnChangeEditLoginId()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	UpdateData(TRUE);
	try
	{
		m_set.Edit();
		m_set.SetFieldValue(_T("login_id"), m_strLoginId);
	}
	catch (_com_error& e)
	{

	}
	catch (...)
	{
	}

	RefreshList();
	SetModified();
}
