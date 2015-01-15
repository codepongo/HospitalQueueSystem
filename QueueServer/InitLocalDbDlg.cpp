// InitLocalDbDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QueueServer.h"
#include "InitLocalDbDlg.h"
#include "../NurseStation/ado2.h"
#include "../NurseStation/MyCommon.h"
#include "../NurseStation/MyString.h"


// CInitLocalDbDlg �Ի���

IMPLEMENT_DYNAMIC(CInitLocalDbDlg, CDialog)

CInitLocalDbDlg::CInitLocalDbDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInitLocalDbDlg::IDD, pParent)
	, m_strUID(_T(""))
	, m_strPWD(_T(""))
	, m_strHostIP(_T(""))
{

}

CInitLocalDbDlg::~CInitLocalDbDlg()
{
}

void CInitLocalDbDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UID, m_strUID);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPWD);
	DDX_Text(pDX, IDC_EDIT_HOST, m_strHostIP);
}


BEGIN_MESSAGE_MAP(CInitLocalDbDlg, CDialog)

	ON_BN_CLICKED(IDOK, &CInitLocalDbDlg::OnBnClickedOk)
END_MESSAGE_MAP()



BOOL CInitLocalDbDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_strHostIP = _T("127.0.0.1");
	m_strUID = _T("sa");
	m_strPWD = _T("123456");

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
/*
void CInitLocalDbDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	CString strConn;
	strConn.Format(_T("Driver={SQL Server};Server=%s;Uid=%s;Pwd=%s;Database=master;"),
		m_strHostIP, m_strUID, m_strPWD);

	CADODatabase myDb;
	try
	{
		myDb.Open(strConn);
	}
	catch (_com_error& e)
	{
		CString strErr;
		strErr.Format(_T("��ʼ��ʧ�ܣ��޷����ӵ�SQL Server���ݿ���û����������: %s"), e.ErrorMessage());
		MessageBox(strErr, _T("��ʼ�����ݿ�"));
		return;
	}
	//CStdioFile file;
	CFile file;
	CString strFileDir = MyCommon::GetModuleDir();
	CString strFilePath = strFileDir + _T("db.sql");
	if(!file.Open(strFilePath, CFile::modeRead))
	{
		MessageBox(_T("��ʼ��ʧ�ܣ���װĿ¼��db.sql�ļ�ȱʧ"), _T("��ʼ�����ݿ�"));
		return;
	}
	//
	int nLength = file.GetLength();
	if(nLength < 1)
	{
		return;
	}
	char* buf = new char[nLength + 1];
	if(buf == NULL)
	{
		MessageBox(_T("�ڴ����ʧ��!"), _T("��ʼ�����ݿ�"));
	}
	file.Read(buf, nLength);
	file.Close();
	buf[nLength] = '\0';
	//WCHAR* pWCH = new WCHAR[nLength];
	//if(pWCH == NULL)
	//{
	//	MessageBox(_T("�ڴ����ʧ��!"), _T("��ʼ�����ݿ�"));
	//}
	//MyString::Char2WChar(pWCH, nLength, buf);
	//CString strDbInit(pWCH);
	//delete[] pWCH;
	CString strDbInit;
	strDbInit.Format(_T("%s"), buf);
	delete[] buf;
	//strDbInit.Replace('?', ' ');
	strDbInit = strDbInit.Mid(
		CommonStrMethod::StrFindNoCase(strDbInit, _T("GO")));

	strDbInit = strDbInit.Left(
		CommonStrMethod::StrReverseFindNoCase(strDbInit, _T("END")) + 3);

	//strDbInit = MyString::Replace(strDbInit, _T("GO"), _T("GO "));

	//strDbInit = MyString::Replace(strDbInit, _T("\n"), _T("\n "));

#ifdef _DEBUG
	//CString str;
	//str.Format(_T("FileLength:%d\nDataLength:%d\nData:\n%s"), 
	//	nLength, strDbInit.GetLength(), strDbInit);
	//AfxMessageBox(str);
	CStdioFile fileTemp;
	strFilePath = strFileDir + _T("db.temp.sql");
	if(fileTemp.Open(strFilePath, CFile::modeCreate|CFile::modeWrite))
	{
		ULONGLONG nLength = strDbInit.GetLength() * 2 + 2;
		char* pCh = new char[nLength];
		MyString::WChar2Char(pCh, nLength, strDbInit.GetBuffer());
		fileTemp.Write(pCh, strlen(pCh));
		delete[] pCh;
		strDbInit.ReleaseBuffer();
		fileTemp.Close();
	}
#endif

	BOOL bSuc = FALSE;

	//CString strSql,strRead;
	//strSql.Empty();
	//while(file.ReadString(strRead))
	//{
	//	if(strRead.Trim().CompareNoCase(_T("GO"))==0)
	//	{
	//		if(!strSql.IsEmpty())
	//		{
	//			try
	//			{
	//				myDb.Execute(strSql);
	//				bSuc = TRUE;
	//			}
	//			catch (_com_error& e)
	//			{
	//				bSuc = FALSE;
	//				CString strErr;
	//				strErr.Format(_T("��ʼ��ʧ�ܣ�ִ�����ݿ��ʼ���ļ�ʧ��: %s"), e.ErrorMessage());
	//				MessageBox(strErr, _T("��ʼ�����ݿ�"));
	//				break;
	//			}
	//		}
	//	}
	//	else
	//	{
	//		strSql+=_T(" ")+strRead;
	//	}
	//}

	try
	{
		myDb.BeginTransaction();
		CString strSql = _T("USE [master]");
		myDb.Execute(strSql);
		strSql = _T("IF EXISTS (SELECT name FROM sys.databases WHERE name = N'Nurse') DROP DATABASE [Nurse]");
		strSql = _T("IF NOT EXISTS (SELECT name FROM sys.databases WHERE name = N'Nurse') CREATE DATABASE [Nurse]");
		strSql = _T("EXEC dbo.sp_dbcmptlevel @dbname=N'Nurse', @new_cmptlevel=90");
		strSql = _T("IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled')) EXEC [Nurse].[dbo].[sp_fulltext_database] @action = 'enable'");
		strSql = _T("ALTER DATABASE [Nurse] SET ANSI_NULL_DEFAULT OFF");
		strSql = _T("ALTER DATABASE [Nurse] SET ANSI_NULLS OFF ");
		strSql = _T("ALTER DATABASE [Nurse] SET ANSI_PADDING OFF ");
		strSql = _T("ALTER DATABASE [Nurse] SET ANSI_WARNINGS OFF");
		strSql = _T("ALTER DATABASE [Nurse] SET ARITHABORT OFF");
		strSql = _T("ALTER DATABASE [Nurse] SET AUTO_CLOSE OFF");
		strSql = _T("ALTER DATABASE [Nurse] SET AUTO_CREATE_STATISTICS ON");
		strSql = _T("ALTER DATABASE [Nurse] SET AUTO_SHRINK OFF");
		strSql = _T("ALTER DATABASE [Nurse] SET AUTO_UPDATE_STATISTICS ON");
		strSql = _T("ALTER DATABASE [Nurse] SET CURSOR_CLOSE_ON_COMMIT OFF");
		strSql = _T("ALTER DATABASE [Nurse] SET CURSOR_DEFAULT  GLOBAL");
		strSql = _T("ALTER DATABASE [Nurse] SET CONCAT_NULL_YIELDS_NULL OFF");
		strSql = _T("ALTER DATABASE [Nurse] SET NUMERIC_ROUNDABORT OFF");
		strSql = _T("ALTER DATABASE [Nurse] SET QUOTED_IDENTIFIER OFF");
		strSql = _T("ALTER DATABASE [Nurse] SET RECURSIVE_TRIGGERS OFF");
		strSql = _T("ALTER DATABASE [Nurse] SET  DISABLE_BROKER");
		strSql = _T("ALTER DATABASE [Nurse] SET AUTO_UPDATE_STATISTICS_ASYNC OFF");
		strSql = _T("ALTER DATABASE [Nurse] SET DATE_CORRELATION_OPTIMIZATION OFF");
		strSql = _T("ALTER DATABASE [Nurse] SET TRUSTWORTHY OFF");
		strSql = _T("ALTER DATABASE [Nurse] SET ALLOW_SNAPSHOT_ISOLATION OFF");
		strSql = _T("ALTER DATABASE [Nurse] SET PARAMETERIZATION SIMPLE");
		strSql = _T("ALTER DATABASE [Nurse] SET  READ_WRITE");
		strSql = _T("ALTER DATABASE [Nurse] SET RECOVERY FULL");
		strSql = _T("ALTER DATABASE [Nurse] SET  MULTI_USER");
		strSql = _T("ALTER DATABASE [Nurse] SET PAGE_VERIFY CHECKSUM");
		strSql = _T("ALTER DATABASE [Nurse] SET DB_CHAINING OFF");
		strSql = _T("USE [Nurse]");
		//
		strSql = _T("SET ANSI_NULLS ON");
		strSql = _T("SET QUOTED_IDENTIFIER ON");
		strSql = _T("IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[Nurse_Office]') AND type in (N'U')) CREATE TABLE [dbo].[Nurse_Office]([serial_id] [int] IDENTITY(1,1) NOT NULL,[nurse_id] [nvarchar](50) NOT NULL,[office_id] [nvarchar](50) NOT NULL,CONSTRAINT [PK_Nurse_Office] PRIMARY KEY CLUSTERED([serial_id] ASC)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]) ON [PRIMARY]");
		strSql = _T("");
		strSql = _T("");
		strSql = _T("");
		strSql = _T("");
		strSql = _T("");
		strSql = _T("");
		strSql = _T("");
		strSql = _T("");
		strSql = _T("");
		strSql = _T("");
		strSql = _T("");
		strSql = _T("");
		strSql = _T("");
		strSql = _T("");
		strSql = _T("");
		strSql = _T("");
		strSql = _T("");
		myDb.CommitTransaction();
		bSuc = TRUE;
	}
	catch (_com_error& e)
	{
		myDb.RollbackTransaction();
		bSuc = FALSE;
		CString strErr;
		strErr.Format(_T("��ʼ��ʧ�ܣ�ִ�����ݿ��ʼ��ʧ��: %s"), e.ErrorMessage());
		MessageBox(strErr, _T("��ʼ�����ݿ�"));
	}

	if(bSuc)
	{
		MessageBox(_T("��ʼ�����ݿ�ɹ�!"), _T("��ʼ�����ݿ�"));
		OnOK();
	}
	else
	{
		MessageBox(_T("��ʼ�����ݿ�ʧ��!"), _T("��ʼ�����ݿ�"));
	}
}
*/

void CInitLocalDbDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	//
	OnOK();
}