#pragma once

class SLZData
{
public:
	SLZData(void);
	~SLZData(void);
	//////	���� Get/Set���� //////
	//��ȡҵ����ˮ��
	CString GetSerialId() const
	{
		return m_strSerialId;
	}
	//����ҵ����ˮ��
	void SetSerialId(const CString& strSerialId)
	{
		m_strSerialId = strSerialId;
	}
	// ҽ��
	CString GetDoctorName(){return m_strDoctorName;}
	void SetDoctorName(const CString& doctorName){m_strDoctorName=doctorName;}
	//��������
	CString GetOfficeName(){return m_strOfficeName;}
	void SetOfficeName(const CString& officeName){m_strOfficeName = officeName;}
	//��������
	CString GetConsultName(){return m_strConsultName;}
	void SetConsultName(const CString& consultName){m_strConsultName = consultName;}
	//�ŶӺ���
	CString GetQueNum(){return m_strQueNum;}
	void SetQueNum(const CString& queNum){m_strQueNum=queNum;}
	//��������
	CString GetPatientName(){return m_strPatientName;}
	void SetPatientName(const CString& patientName){m_strPatientName = patientName;}
	//�Ǽ�
	UINT GetCusLevel(){return m_iCusLevel;}
	void SetCusLevel(UINT level){m_iCusLevel = level;}
	//Ctime
	CTime GetTakingNumTime(){return m_timeTakingNum;}
	void SetTakingNumTime(const CTime& time){m_timeTakingNum = time;}
private:
	CString m_strSerialId;	//ҵ����ˮ��
	CString m_strDoctorName;//ҽ������
	CString m_strOfficeName;//��������
	CString m_strConsultName;//��������
	CString m_strQueNum;//�ŶӺ���
	CString m_strPatientName;//��������
	//CString m_CustGender;	//�ͻ��Ա�
	UINT m_iCusLevel;		//�ͻ��ȼ�
	CTime m_timeTakingNum;	//ȡ��ʱ��
};
