// ReadHis.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QueueServer.h"
#include "ReadHis.h"
#include "WriteLog.h"
#include "../NurseStation/BaseConfig.h"
#include "../NurseStation/MyCommon.h"
#include "../NurseStation/MyString.h"


// CReadHis


CReadHis::CReadHis()
: m_pReadPatientThread(NULL)
, m_pReadOtherDataThread(NULL)
, m_pAutoDeleteThread(NULL)
, m_bHisDbErr(FALSE)
, m_bMyDbErr(FALSE)
, m_strHisDbConn(_T(""))
, m_strMyDbConnStr(_T(""))
{

}

CReadHis::~CReadHis()
{

}

BOOL CReadHis::Start()
{
	//ReadDepart();
	//ReadClinic();
	//ReadDoctor();

	//m_nHisDays = GetHisDays(5);
	LoadConf();

	LoadMap();

	BOOL bThread = StartPatientThread();

	BOOL b1 = TRUE, b2 = TRUE;
	if(!m_timerReadOtherData.IsActive())
	{
		b1 = m_timerReadOtherData.StartTimer(
			this, 60000, &CReadHis::ReadOtherDataTimerProc);//1����ִ��һ��
	}
	if(!m_timerAutoDeletePatient.IsActive())
	{
		b2 = m_timerAutoDeletePatient.StartTimer(
			this, 600000, &CReadHis::AutoDeletePatientTimerProc);//6����ִ��һ��
	}

	if(bThread && b1 && b2)
	{
		return TRUE;
	}
	else
	{
		if(!bThread)
		{
			WriteLog::WriteTimeErrLog(_T("������HIS���������߳�ʧ��"));
		}
		if(!b1)
		{
			WriteLog::WriteTimeErrLog(_T("������HIS�������ݶ�ʱ��ʧ��"));
		}
		if(!b2)
		{
			WriteLog::WriteTimeErrLog(_T("�����Զ�ɾ�����ݶ�ʱ��ʧ��"));
		}
		return FALSE;
	}
}

void CReadHis::Close()
{
	m_timerReadOtherData.KillTimer();
	m_timerAutoDeletePatient.KillTimer();
	EndPatientThread();
}

BOOL CReadHis::StartPatientThread()
{
	if(m_pReadPatientThread == NULL)
	{
		m_pReadPatientThread = AfxBeginThread(ReadPatientThreadProc, this);
	}

	return m_pReadPatientThread != NULL;
}

void CReadHis::EndPatientThread()
{
	if(m_pReadPatientThread)
	{
		m_bReadPatientThread = FALSE;
		::WaitForSingleObject(m_pReadPatientThread->m_hThread, 20);
		delete m_pReadPatientThread;
		m_pReadPatientThread = NULL;
	}
}

UINT CReadHis::ReadPatientThreadProc(LPVOID pParam)
{
	CReadHis* pThis = (CReadHis*)pParam;
	pThis->m_bReadPatientThread = TRUE;
	while(pThis->m_bReadPatientThread)
	{
		pThis->ReadPatient();
		Sleep(3000);
	}
	::ExitThread(0);
	return 0;
}

void CReadHis::ReadOtherDataTimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	if(!m_pReadOtherDataThread)
	{
		m_pReadOtherDataThread = AfxBeginThread(ReadOtherDataThreadProc, this);
	}
}

UINT CReadHis::ReadOtherDataThreadProc(LPVOID pParam)
{
	CReadHis* pThis = (CReadHis*)pParam;
	pThis->ReadDepart();
	pThis->ReadItem();
	pThis->ReadClinic();
	pThis->ReadDoctor();

	pThis->m_pReadOtherDataThread = NULL;

	return 0;
}

void CReadHis::AutoDeletePatientTimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	if(!m_pAutoDeleteThread)
	{
		m_pAutoDeleteThread = AfxBeginThread(AutoDeleteThreadProc, this);
	}
}

UINT CReadHis::AutoDeleteThreadProc(LPVOID pParam)
{
	CReadHis* pThis = (CReadHis*)pParam;
	pThis->AutoDeletePatient();

	pThis->m_pAutoDeleteThread = NULL;

	return 0;
}

BOOL CReadHis::OpenHisDb(CADODatabase& hisDb)
{
	//��HIS���ݿ�
	try
		//TRY
	{
		hisDb.Open(m_strHisDbConn);
		//hisDb.Open(m_strHisDbConnStr);
	}
	catch (_com_error& e)
	{
		if(!m_bHisDbErr)
		{
			m_bHisDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("����HIS���ݿ�ʧ��: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}

		return FALSE;
	}
	//END_CATCH_ALL
	//m_bHisDbErr = FALSE;
	return TRUE;
}

BOOL CReadHis::OpenMyDb(CADODatabase& myDb)
{
	//�򿪱�ϵͳ���ݿ�
	try
	{
		myDb.Open(m_strMyDbConnStr);
	}
	catch (_com_error& e)
	{
		if(!m_bMyDbErr)
		{
			m_bMyDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("�����Ŷ�ϵͳ���ݿ�ʧ��: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}

		return FALSE;
	}
	//m_bMyDbErr = FALSE;
	return TRUE;
}


BOOL CReadHis::ReadPatient()
{
	//����HIS���ݿ����ODBC�������ڲ����ݿ����ADO
	CADODatabase hisDb;

	//��HIS���ݿ�
	if(!OpenHisDb(hisDb))
	{
		return FALSE;
	}

	//�򿪱�ϵͳ���ݿ�
	CADODatabase myDb;
	if(!OpenMyDb(myDb))
	{
		return FALSE;
	}

	//CString strQuery(_T("SELECT * FROM (SELECT serial_id,reg_id,id_card,queue_num,patient_name,patient_gender,patient_birth,id_depart,time,id_doctor,id_item,in_flag FROM HisForBjlb_Patient WHERE time>to_date(to_char(sysdate,'yyyymmdd'),'yyyymmdd') ORDER BY time DESC) WHERE rownum<500"));
	CString strQuery(_T("SELECT * FROM (SELECT serial_id,reg_id,id_card,queue_num,patient_name,patient_gender,patient_birth,id_depart,time,id_doctor,id_item,in_flag,patient_id,em_flag FROM HisForBjlb_Patient P WHERE time>to_date(to_char(sysdate,'yyyymmdd'),'yyyymmdd') ORDER BY time DESC) WHERE rownum<500"));
	//CString strQuery(_T("SELECT * FROM (SELECT serial_id,reg_id,id_card,queue_num,patient_name,patient_gender,patient_birth,id_depart,time,id_doctor,id_item,item_desc,in_flag FROM HisForBjlb_Patient WHERE time>to_date(to_char(sysdate,'yyyymmdd'),'yyyymmdd') ORDER BY time DESC) P where rownum<200"));

	//��ȡHIS����
	CADORecordset hisRset(&hisDb);
	try
	{
		if(!hisRset.Open(strQuery))
		{
			return FALSE;
		}

		if(hisRset.IsBOF())
		{
			return TRUE;
		}
	}
	catch (_com_error& e)
	{
		if(!m_bHisDbErr)
		{
			m_bHisDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadPatient:��ȡHIS���ݿⲡ���Ŷ���ͼ��[HISFORBJLB_PATIENT]ʧ��: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		return FALSE;
	}
	//m_bHisDbErr = FALSE;

	//��HIS����д�뱾ϵͳ���ݿ�
	CADORecordset myRset(&myDb);
	CString strInsert;
	try
	{
		for(; !hisRset.IsEOF(); hisRset.MoveNext())
		{
			CString strSerialId;

			CString strRegId,strIdCard,strQueueNum,strPatientName,strPatientGender,strPatientBirth,
				strIdDepart,strTime,strIdDoctor,strIdItem,strItemDesc,strInFlag,strPatientId,strEmFlag;

			hisRset.GetFieldValue(_T("serial_id"), strSerialId);
			hisRset.GetFieldValue(_T("reg_id"), strRegId);
			if(strRegId.IsEmpty())
			{
				strRegId = strSerialId;
			}
			//strRegId.Remove('.');
			hisRset.GetFieldValue(_T("id_card"), strIdCard);
			hisRset.GetFieldValue(_T("queue_num"), strQueueNum);
			hisRset.GetFieldValue(_T("patient_id"), strPatientId);
			hisRset.GetFieldValue(_T("patient_name"), strPatientName);
			//WriteLog::Write(strPatientName + _T("|"));
			//strPatientName.Trim();
			hisRset.GetFieldValue(_T("patient_gender"), strPatientGender);
			if(!hisRset.IsFieldNull(_T("patient_birth")))
			{
				hisRset.GetFieldValue(_T("patient_birth"), strPatientBirth);
				//COleDateTime odt;
				//odt.ParseDateTime(strPatientBirth);
				//strPatientBirth = odt.Format(_T("yyyy-mm-dd"));
				strPatientBirth = _T("'") + strPatientBirth + _T("'");
			}
			else
			{
				strPatientBirth = _T("null");
			}

			hisRset.GetFieldValue(_T("id_depart"), strIdDepart);
			hisRset.GetFieldValue(_T("time"), strTime);
			if(hisRset.IsFieldNull(_T("id_doctor")))
			{
				strIdDoctor = _T("null");
			}
			else
			{
				hisRset.GetFieldValue(_T("id_doctor"), strIdDoctor);
				strIdDoctor = _T("'") + strIdDoctor + _T("'");
			}

			//hisRset.GetFieldValue(_T("id_item"), strIdItem);
			//if(!strIdItem.IsEmpty())
			//{
			//	strIdDepart = m_mapItemDepart[strIdItem];
			//}
			if(hisRset.IsFieldNull(_T("id_item")))
			{
				strIdItem = _T("null");
			}
			else
			{
				hisRset.GetFieldValue(_T("id_item"), strIdItem);
				if(!strIdItem.IsEmpty())
				{
					if(!m_mapItemDepart[strIdItem].IsEmpty())
					{
						strIdDepart = m_mapItemDepart[strIdItem];
					}
					strIdItem = _T("'") + strIdItem + _T("'");
				}
				else
				{
					strIdItem = _T("null");
				}
			}
			//hisRset.GetFieldValue(_T("item_desc"), strItemDesc);
			hisRset.GetFieldValue(_T("in_flag"), strInFlag);
			if(strInFlag.IsEmpty())
			{
				strInFlag = _T("0");
			}
			else if(strInFlag.GetAt(strInFlag.GetLength()-1) == '.')
			{
				strInFlag.Delete(strInFlag.GetLength()-1);
			}
			hisRset.GetFieldValue(_T("em_flag"), strEmFlag);
			if(strEmFlag.IsEmpty())
			{
				strEmFlag = _T("0");
			}
			else if(strEmFlag.GetAt(strEmFlag.GetLength()-1) == '.')
			{
				strEmFlag.Delete(strEmFlag.GetLength()-1);
			}

			CString strQuery;
			strQuery.Format(_T("SELECT serial_id FROM HisForBjlb_Patient WHERE patient_id='%s' AND id_depart='%s' AND time='%s'"),
				strPatientId,strIdDepart,strTime);
			try
			{
				myRset.Open(strQuery);
				if(!myRset.IsBOF())
				{
					myRset.Close();
					continue;
				}
				myRset.Close();
			}
			catch (_com_error& e)
			{
				if(!m_bMyDbErr)
				{
					m_bMyDbErr = TRUE;
					CString strErr;
					strErr.Format(_T("ReadPatient:��ȡ���˱�[HisForBjlb_Patient].[serial_id]ʱ����: %s"), e.ErrorMessage());
					WriteLog::WriteTimeErrLog(strErr);
				}
				myRset.Close();
				continue;
			}

			strInsert.Format(_T("INSERT INTO HisForBjlb_Patient(serial_id,reg_id,id_card,queue_num,patient_name,patient_gender,patient_birth,id_depart,time,id_doctor,id_item,in_flag,patient_id,em_flag) VALUES('%s','%s','%s','%s','%s',%s,%s,'%s','%s',%s,%s,%s,'%s','%s');"),
				strSerialId,strRegId,strIdCard,strQueueNum,strPatientName,strPatientGender,strPatientBirth,
				strIdDepart,strTime,strIdDoctor,strIdItem,strInFlag,strPatientId,strEmFlag);

			//WriteLog::Write(strInsert);

			try
			{
				if(!strInsert.IsEmpty())
				{
					//WriteLog::Write(strInsert);
					myDb.Execute(strInsert);
				}
				else
				{
					//WriteLog::Write(_T("Insert null"));
				}
			}
			catch (_com_error& e)
			{
				if(!m_bMyDbErr)
				{
					m_bMyDbErr = TRUE;
					CString strErr;
					strErr.Format(_T("ReadPatient:��HIS�ŶӲ�������д���Ŷ�ϵͳ���ݿ�ʱ����: %s"), e.ErrorMessage());
					WriteLog::WriteTimeErrLog(strErr);
					//WriteLog::Write(strInsert);
				}

				//return FALSE;
				continue;
			}
			//m_bMyDbErr = FALSE;
		}
	}
	catch (_com_error& e)
	{
		if(!m_bHisDbErr)
		{
			m_bHisDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadPatient:����HIS�ŶӲ�������ʱ����: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		return FALSE;
	}
	//m_bHisDbErr = FALSE;

	return TRUE;
}

BOOL CReadHis::ReadDepart()
{
	//����HIS���ݿ����ODBC�������ڲ����ݿ����ADO
	CADODatabase hisDb;

	//��HIS���ݿ�
	if(!OpenHisDb(hisDb))
	{
		return FALSE;
	}

	//�򿪱�ϵͳ���ݿ�
	CADODatabase myDb;
	if(!OpenMyDb(myDb))
	{
		return FALSE;
	}

	//��ȡHIS����
	CADORecordset hisRset(&hisDb);
	try
	{
		hisRset.Open(_T("SELECT ID,NAME,ID_PARENT FROM HISFORBJLB_DEPART"));
		if(hisRset.IsBOF())
		{
			return FALSE;
		}
	}
	catch (_com_error& e)
	{
		if(!m_bHisDbErr)
		{
			m_bHisDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadDepart:��ȡHIS���ݿⲿ����ͼ��[HISFORBJLB_DEPART]ʧ��: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		return FALSE;
	}
	//m_bHisDbErr = FALSE;

	//��ȡ��ϵͳ���ݿⲿ�ű��Ѵ��ڵĲ���ID�б�
	CStringArray strArrId;
	CADORecordset myRset(&myDb);
	try
	{
		myRset.Open(_T("SELECT office_id FROM Office;"));
		for(;!myRset.IsEOF(); myRset.MoveNext())
		{
			CString strId;
			myRset.GetFieldValue((int)0, strId);
			strArrId.Add(strId);
		}
		myRset.Close();
	}
	catch (_com_error& e)
	{
		if(!m_bMyDbErr)
		{
			m_bMyDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadDepart:��ȡ�Ŷ�ϵͳ���ݿⲿ�ű�[Office].[office_id]ʧ��: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		return FALSE;
	}
	//m_bMyDbErr = FALSE;

	//��HIS����д�뱾ϵͳ���ݿ�
	CString strSql;
	try
	{
		for(; !hisRset.IsEOF(); hisRset.MoveNext())
		{
			int nId,nIdParent;
			CString strId, strName, strIdParent;

			hisRset.GetFieldValue(_T("ID"), strId);
			hisRset.GetFieldValue(_T("NAME"), strName);
			hisRset.GetFieldValue(_T("ID_PARENT"), strIdParent);

			if(StringExistInStringArray(strId, strArrId))
			{
				strSql.Format(_T("UPDATE Office SET name='%s',parent_id='%s' WHERE office_id='%s';"),
					strName, strIdParent, strId);
			}
			else
			{
				strSql.Format(_T("INSERT INTO Office(office_id,name,call_name,parent_id,his_flag) VALUES('%s','%s','%s','%s',1);"),
					strId,strName,strName,strIdParent);
			}

			try
			{
				myDb.Execute(strSql);
			}
			catch (_com_error& e)
			{
				if(!m_bMyDbErr)
				{
					m_bMyDbErr = TRUE;
					CString strErr;
					strErr.Format(_T("ReadDepart:��HIS��������д���Ŷ�ϵͳ���ݿ�ʱ����: %s"), e.ErrorMessage());
					WriteLog::WriteTimeErrLog(strErr);
				}
			}
		}
	}
	catch (_com_error& e)
	{
		if(!m_bHisDbErr)
		{
			m_bHisDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadDepart:������������ʱ����: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		return FALSE;
	}
	//m_bHisDbErr = FALSE;


	return TRUE;
}

BOOL CReadHis::ReadItem()
{
	//����HIS���ݿ����ODBC�������ڲ����ݿ����ADO
	CADODatabase hisDb;

	//��HIS���ݿ�
	if(!OpenHisDb(hisDb))
	{
		return FALSE;
	}

	//�򿪱�ϵͳ���ݿ�
	CADODatabase myDb;
	if(!OpenMyDb(myDb))
	{
		return FALSE;
	}

	//��ȡHIS����
	CADORecordset hisRset(&hisDb);
	try
	{
		hisRset.Open(_T("SELECT ID,NAME,PRICE FROM HISFORBJLB_ITEM"));
		if(hisRset.IsBOF())
		{
			return FALSE;
		}
	}
	catch (_com_error& e)
	{
		if(!m_bHisDbErr)
		{
			m_bHisDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadItem:��ȡHIS���ݿ�����Ŀ��ͼ��[HISFORBJLB_ITEM]ʧ��: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		return FALSE;
	}
	//m_bHisDbErr = FALSE;

	//��ȡ��ϵͳ���ݿⲿ�ű��Ѵ��ڵĲ���ID�б�
	CStringArray strArrId;
	CADORecordset myRset(&myDb);
	try
	{
		myRset.Open(_T("SELECT id FROM Item"));
		for(;!myRset.IsEOF(); myRset.MoveNext())
		{
			CString strId;
			myRset.GetFieldValue((int)0, strId);
			strArrId.Add(strId);
		}
		myRset.Close();
	}
	catch (_com_error& e)
	{
		if(!m_bMyDbErr)
		{
			m_bMyDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadItem:��ȡ�Ŷ�ϵͳ���ݿ�����Ŀ��[ITEM].[id]ʧ��: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		return FALSE;
	}
	//m_bMyDbErr = FALSE;

	//��HIS����д�뱾ϵͳ���ݿ�
	CString strSql;
	try
	{
		for(; !hisRset.IsEOF(); hisRset.MoveNext())
		{
			int nId,nIdParent;
			CString strId, strName, strPrice;

			hisRset.GetFieldValue(_T("ID"), strId);
			hisRset.GetFieldValue(_T("NAME"), strName);
			hisRset.GetFieldValue(_T("PRICE"), strPrice);

			if(StringExistInStringArray(strId, strArrId))
			{
				strSql.Format(_T("UPDATE Item SET name='%s',price='%s' WHERE id='%s';"),
					strName, strPrice, strId);
			}
			else
			{
				strSql.Format(_T("INSERT INTO Item(id,name,price) VALUES('%s','%s','%s');"),
					strId,strName,strPrice);
			}

			try
			{
				myDb.Execute(strSql);
			}
			catch (_com_error& e)
			{
				if(!m_bMyDbErr)
				{
					m_bMyDbErr = TRUE;
					CString strErr;
					strErr.Format(_T("ReadItem:��HIS�����Ŀ����д���Ŷ�ϵͳ���ݿ�ʱ����: %s"), e.ErrorMessage());
					WriteLog::WriteTimeErrLog(strErr);
				}
			}
		}
	}
	catch (_com_error& e)
	{
		if(!m_bHisDbErr)
		{
			m_bHisDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadItem:���������Ŀ����ʱ����: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		return FALSE;
	}
	//m_bHisDbErr = FALSE;

	return TRUE;
}

BOOL CReadHis::ReadClinic()
{
	//����HIS���ݿ����ODBC�������ڲ����ݿ����ADO
	CADODatabase hisDb;

	//��HIS���ݿ�
	if(!OpenHisDb(hisDb))
	{
		return FALSE;
	}

	//�򿪱�ϵͳ���ݿ�
	CADODatabase myDb;
	if(!OpenMyDb(myDb))
	{
		return FALSE;
	}

	//��ȡHIS����
	CADORecordset hisRset(&hisDb);
	try
	{
		hisRset.Open(_T("SELECT ID,NAME,POSITION,ID_DEPART FROM HISFORBJLB_CLINIC"));

		if(hisRset.IsBOF())
		{
			return FALSE;
		}
	}
	catch (_com_error& e)
	{
		if(!m_bHisDbErr)
		{
			m_bHisDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadClinic:��ȡHIS���ݿ�������ͼ��[HISFORBJLB_CLINIC]ʧ��: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		return FALSE;
	}
	//m_bHisDbErr = FALSE;

	//��ȡ��ϵͳ���ݿⲿ�ű��Ѵ��ڵĲ���ID�б�
	CStringArray strArrId;
	CADORecordset myRset(&myDb);
	try
	{
		myRset.Open(_T("SELECT consult_id FROM Consult;"));
		for(;!myRset.IsEOF(); myRset.MoveNext())
		{
			CString strId;
			myRset.GetFieldValue((int)0, strId);
			strArrId.Add(strId);
		}
		myRset.Close();
	}
	catch (_com_error& e)
	{
		if(!m_bMyDbErr)
		{
			m_bMyDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadClinic:��ȡ�Ŷ�ϵͳ���ݿ����ұ�[Consult].[consult_id]ʧ��: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}

		return FALSE;
	}
	//m_bMyDbErr = FALSE;

	//��HIS����д�뱾ϵͳ���ݿ�
	CString strSql;
	try
	{
		for(; !hisRset.IsEOF(); hisRset.MoveNext())
		{
			CString strId,strName,strPosition, strIdDepart;

			hisRset.GetFieldValue(_T("ID"), strId);
			hisRset.GetFieldValue(_T("NAME"), strName);
			hisRset.GetFieldValue(_T("POSITION"), strPosition);
			hisRset.GetFieldValue(_T("ID_DEPART"), strIdDepart);

			if(StringExistInStringArray(strId, strArrId))
			{
				strSql.Format(_T("UPDATE Consult SET name='%s',position='%s',office_id='%s' WHERE consult_id='%s';"),
					strName, strPosition, strIdDepart, strId);
			}
			else
			{
				strSql.Format(_T("INSERT INTO Consult(consult_id,name,call_name,position,office_id,his_flag) VALUES('%s','%s','%s','%s','%s',1);"),
					strId, strName, strName, strPosition, strIdDepart);
			}

			try
			{
				myDb.Execute(strSql);
			}
			catch (_com_error& e)
			{
				if(!m_bMyDbErr)
				{
					m_bMyDbErr = TRUE;
					CString strErr;
					strErr.Format(_T("ReadClinic:��HIS��������д���Ŷ�ϵͳ���ݿ�ʱ����: %s"), e.ErrorMessage());
					WriteLog::WriteTimeErrLog(strErr);
				}
			}
		}
	}
	catch (_com_error& e)
	{
		if(!m_bHisDbErr)
		{
			m_bHisDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadClinic:����HIS��������ʱ����: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}

		return FALSE;
	}
	//m_bHisDbErr = FALSE;

	return TRUE;
}

BOOL CReadHis::ReadDoctor()
{
	//����HIS���ݿ����ODBC�������ڲ����ݿ����ADO
	CADODatabase hisDb;

	//��HIS���ݿ�
	if(!OpenHisDb(hisDb))
	{
		return FALSE;
	}

	//�򿪱�ϵͳ���ݿ�
	CADODatabase myDb;
	if(!OpenMyDb(myDb))
	{
		hisDb.Close();
		return FALSE;
	}

	//��ȡHIS����
	CADORecordset hisRset(&hisDb);
	try
	{
		hisRset.Open(_T("SELECT ID,NAME,GENDER,TITLE,EXPERT_FLAG,ID_DEPART,LOGIN_ID FROM HISFORBJLB_DOCTOR"));

		if(hisRset.IsBOF())
		{

			return FALSE;
		}
	}
	catch (_com_error& e)
	{
		if(!m_bHisDbErr)
		{
			m_bHisDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadDoctor:��ȡHIS���ݿ�ҽ����ͼ��[HISFORBJLB_DOCTOR]ʧ��: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}

		return FALSE;
	}
	//m_bHisDbErr = FALSE;

	//��ȡ��ϵͳ���ݿⲿ�ű��Ѵ��ڵĲ���ID�б�
	CStringArray strArrId;
	CADORecordset myRset(&myDb);
	try
	{
		myRset.Open(_T("SELECT doctor_id FROM Doctor;"));
		for(;!myRset.IsEOF(); myRset.MoveNext())
		{
			CString strId;
			myRset.GetFieldValue((int)0, strId);
			strArrId.Add(strId);
		}
		myRset.Close();
	}
	catch (_com_error& e)
	{
		if(!m_bMyDbErr)
		{
			m_bMyDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadDoctor:��ȡ�Ŷ�ϵͳ���ݿ�ҽ����[Doctor].[doctor_id]ʧ��: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}

		return FALSE;
	}
	//m_bMyDbErr = FALSE;

	CString strCallSound = _T("��[�ŶӺ���]��[��������]��[��������]��");
	CString strWaitSound = _T("��[�ŶӺ���]��[��������]����׼����");
	CString strCallDisplay = _T("#0#��#1#[�ŶӺ���]#0#��#1#[��������]#0#��#0#[��������]");
	CString strWaitDisplay = _T("#0#��#1#[�ŶӺ���]#0#��#1#[��������]#0#����׼�������ң�#0#[��������]");

	//��HIS����д�뱾ϵͳ���ݿ�
	CString strSql;
	try
	{
		for(; !hisRset.IsEOF(); hisRset.MoveNext())
		{
			CString strId,strLoginId,strName,strTitle,strGender,strExpertFlag, strIdDepart;

			hisRset.GetFieldValue(_T("ID"), strId);
			hisRset.GetFieldValue(_T("NAME"), strName);
			hisRset.GetFieldValue(_T("GENDER"), strGender);
			hisRset.GetFieldValue(_T("TITLE"), strTitle);
			hisRset.GetFieldValue(_T("EXPERT_FLAG"), strExpertFlag);
			hisRset.GetFieldValue(_T("ID_DEPART"), strIdDepart);
			hisRset.GetFieldValue(_T("LOGIN_ID"), strLoginId);
			if(strLoginId.IsEmpty())
			{
				strLoginId = strName;
			}

			if(StringExistInStringArray(strId, strArrId))
			{
				strSql.Format(_T("UPDATE Doctor SET name='%s',gender=%s,title='%s' WHERE doctor_id='%s';"),
					strName, strGender, strTitle, strId);
			}
			else
			{
				strSql.Format(_T("INSERT INTO Doctor(doctor_id,login_id,name,gender,title,expert_flag,office_id,password,his_flag,sound_call,sound_wait,display_call,display_wait) VALUES('%s','%s','%s',%s,'%s',%s,'%s','123',1,'%s','%s','%s','%s');"),
					strId, strLoginId, strName, strGender, strTitle, strExpertFlag, strIdDepart, strCallSound, strWaitSound, strCallDisplay, strWaitDisplay);
				//WriteLog::Write(strSql);
			}

			try
			{
				myDb.Execute(strSql);
			}
			catch (_com_error& e)
			{
				if(!m_bMyDbErr)
				{
					m_bMyDbErr = TRUE;
					CString strErr;
					strErr.Format(_T("ReadDoctor:��HISҽ������д���Ŷ�ϵͳ���ݿ�ʱ����: %s"), e.ErrorMessage());
					WriteLog::WriteTimeErrLog(strErr);
				}
			}
		}
	}
	catch (_com_error& e)
	{
		if(!m_bHisDbErr)
		{
			m_bHisDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadDoctor:����HISҽ������ʱ����: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}

		return FALSE;
	}
	//m_bHisDbErr = FALSE;

	//try
	//{
	//	myDb.Execute(strSql);
	//}
	//catch (_com_error& e)
	//{
	//	if(!m_bMyDbErr)
	//	{
	//		m_bMyDbErr = TRUE;
	//		CString strErr;
	//		strErr.Format(_T("ReadDoctor:��HISҽ������д���Ŷ�ϵͳ���ݿ�ʱ����: %s"), e.ErrorMessage());
	//		WriteLog::WriteTimeErrLog(strErr);
	//	}

	//	return FALSE;
	//}

	return TRUE;
}

BOOL CReadHis::AutoDeletePatient()
{
	CADODatabase myDb;
	static BOOL bDbErr = FALSE;
	if(!OpenMyDb(myDb))
	{
		if(!bDbErr)
		{
			bDbErr = TRUE;
			WriteLog::WriteTimeErrLog(_T("AutoDeletePatient:��ʱɾ���Ŷ�ϵͳ���ݿ�[HisForBjlb_Patient]ʱ����:�����ݿ�ʧ��"));
		}
		return FALSE;
	}
	CString strDel;
	//strDel.Format(_T("DELETE FROM HisForBjlb_Patient WHERE time < DATEADD(day,-%d,getdate())"), m_nHisDays + 1);
	strDel.Format(_T("DELETE FROM HisForBjlb_Patient WHERE time < CONVERT(varchar(100), DATEADD(day,-%d,getdate()), 23)"), m_nHisDays + 1);
	try
	{
		myDb.Execute(strDel);
		myDb.Close();
	}
	catch (_com_error& e)
	{
		if(!bDbErr)
		{
			bDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("AutoDeletePatient:��ʱɾ���Ŷ�ϵͳ���ݿ�[HisForBjlb_Patient]ʱ����: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		myDb.Close();
		return FALSE;
	}

	return TRUE;
}

BOOL CReadHis::StringExistInStringArray(CString str, CStringArray& arr)
{
	if(arr.IsEmpty()) return FALSE;
	for(int i = 0; i < arr.GetCount(); i++)
	{
		if(arr[i].Compare(str) == 0)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void CReadHis::LoadConf()
{
	m_strMyDbConnStr.Format(_T("Driver={%s};Server=%s;Uid=%s;Pwd=%s;Database=Nurse;"),
		MyCommon::GetProfileString(_T("conn"), _T("DRIVER"), _T("SQL Server"), _T("\\SYS\\mydb.ini")), 
		MyCommon::GetProfileString(_T("conn"), _T("SERVER"), _T("127.0.0.1"), _T("\\SYS\\mydb.ini")), 
		MyCommon::GetProfileString(_T("conn"), _T("UID"), _T("sa"), _T("\\SYS\\mydb.ini")), 
		MyCommon::GetProfileString(_T("conn"), _T("PWD"), _T("123456"), _T("\\SYS\\mydb.ini"))
		);
	//Provider=OraOLEDB.Oracle.1
	//Provider=MSDAORA.1
	//m_strHisDbConn.Format(_T("Provider=OraOLEDB.Oracle.1;Persist Security Info=False;User ID=%s;Password=%s;hos=%s;port=%s;Data Source=%s;"), 
	//	MyCommon::GetProfileString(_T("conn"), _T("USER_ID"), _T("hisforbjlb"), _T("\\SYS\\hisdb.ini")), 
	//	MyCommon::GetProfileString(_T("conn"), _T("PASSWORD"), _T("bjlb2007"), _T("\\SYS\\hisdb.ini")),
	//	MyCommon::GetProfileString(_T("conn"), _T("HOST"), _T("127.0.0.1"), _T("\\SYS\\hisdb.ini")),
	//	MyCommon::GetProfileString(_T("conn"), _T("PORT"), _T("1521"), _T("\\SYS\\hisdb.ini")),
	//	MyCommon::GetProfileString(_T("conn"), _T("SERVICE_NAME"), _T("orcl"), _T("\\SYS\\hisdb.ini"))
	//	);

	//m_strHisDbConn.Format(_T("Provider=OraOLEDB.Oracle.1;Persist Security Info=False;User ID=%s;Password=%s;Data Source=(DESCRIPTION=(ADDRESS=(PROTOCOL=TCP)(HOST=%s)(PORT=%s))(CONNECT_DATA=(SERVER_NAME=%s)));"), 
	//	MyCommon::GetProfileString(_T("conn"), _T("USER_ID"), _T("hisforbjlb"), _T("\\SYS\\hisdb.ini")), 
	//	MyCommon::GetProfileString(_T("conn"), _T("PASSWORD"), _T("bjlb2007"), _T("\\SYS\\hisdb.ini")),
	//	MyCommon::GetProfileString(_T("conn"), _T("HOST"), _T("192.168.100.2"), _T("\\SYS\\hisdb.ini")),
	//	MyCommon::GetProfileString(_T("conn"), _T("PORT"), _T("1521"), _T("\\SYS\\hisdb.ini")),
	//	MyCommon::GetProfileString(_T("conn"), _T("SERVICE_NAME"), _T("orcl"), _T("\\SYS\\hisdb.ini"))
	//	);
	//m_strHisDbConn = _T("Provider=OraOLEDB.Oracle.1;Persist Security Info=False;User ID=hisforbjlb;Password=bjlb2007;Data Source=(DESCRIPTION=(ADDRESS_LIST=(ADDRESS =(PROTOCOL=TCP)(HOST=192.168.100.2)(PORT=1521)))(CONNECT_DATA=(SERVER=DEDICATED)(SERVICE_NAME=orcl)));");
	m_strHisDbConn.Format(_T("Provider=OraOLEDB.Oracle.1;Persist Security Info=False;User ID=%s;Password=%s;Data Source=(DESCRIPTION=(ADDRESS_LIST=(ADDRESS =(PROTOCOL=TCP)(HOST=%s)(PORT=%s)))(CONNECT_DATA=(SERVER=DEDICATED)(SERVICE_NAME=%s)));"),
		MyCommon::GetProfileString(_T("conn"), _T("USER_ID"), _T("hisforbjlb"), _T("\\SYS\\hisdb.ini")), 
		MyCommon::GetProfileString(_T("conn"), _T("PASSWORD"), _T("bjlb2007"), _T("\\SYS\\hisdb.ini")),
		MyCommon::GetProfileString(_T("conn"), _T("HOST"), _T("192.168.10.2"), _T("\\SYS\\hisdb.ini")),
		MyCommon::GetProfileString(_T("conn"), _T("PORT"), _T("1521"), _T("\\SYS\\hisdb.ini")),
		MyCommon::GetProfileString(_T("conn"), _T("SERVICE_NAME"), _T("orcl"), _T("\\SYS\\hisdb.ini"))
		);


	//m_strHisDbConn.Format(_T("DSN=%s;"), 
	//	MyCommon::GetProfileString(
	//	_T("conn"), _T("DSN"), _T("NurseHisDb"), _T("\\SYS\\hisdb.ini")).Trim());

	//WriteLog::Write(m_strHisDbConnStr);
	m_nHisDays = MyCommon::GetProfileInt(
		_T("data"), _T("DATA_DAYS"), 0, _T("\\SYS\\hisdb.ini"));
	if(m_nHisDays < 0)
	{
		m_nHisDays = 0;
	}
}

void CReadHis::LoadMap()
{
	CString strModuleDir = MyCommon::GetModuleDir();
	CStringArray arrstrFileList;
	MyCommon::GetFilesAbsNameInDir(
		strModuleDir + _T("map"), arrstrFileList, _T(".ini"));
	CStdioFile file;
	for(int i = 0; i < arrstrFileList.GetCount(); i++)
	{
		if(file.Open(arrstrFileList[i], CFile::modeRead|CFile::typeText))
		{
			CString strLine;
			if(file.ReadString(strLine))
			{
				CString strIdDepart = strLine;
				for (; file.ReadString(strLine); )
				{
					if(!strLine.IsEmpty())
					{
						m_mapItemDepart[strLine] = strIdDepart;
					}
				}
			}
			file.Close();
		}
		else
		{
			CString strErr;
			strErr.Format(_T("%s �ļ���ʧ�ܣ�"), arrstrFileList[i]);
			WriteLog::WriteTimeErrLog(strErr);
		}
	}
	//POSITION pos = m_mapItemDepart.GetStartPosition();
	//CString strKey;
	//CString strValue;
	//CString strOut;
	//for(; pos; )
	//{
	//	m_mapItemDepart.GetNextAssoc(pos, strKey, strValue);
	//	strOut += strKey + _T(" : ") + strValue + _T("\r\n");
	//}
	//WriteLog::Write(strOut);
}
