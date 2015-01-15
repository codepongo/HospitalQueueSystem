#include "StdAfx.h"
#include "DoFile.h"

CDoFile::CDoFile(void)
{
}

CDoFile::~CDoFile(void)
{
}

int CDoFile::CreateMyDirectory(const CString& path)
{
	int nerr = -1;
	CString	_path = path;
	
	if(_path.Right(1) == '\\')
		_path=path.Left(_path.GetLength()-1);
	if(IsFileExit(_path))
		return 0;//�ļ���/Ŀ¼�Ѿ�����
	CString parentPath=ParentPath(_path);
	if(!parentPath.IsEmpty())//��Ŀ¼
	{
		nerr = CreateMyDirectory(parentPath);//�ݹ鴴��
		if(0 != nerr)
		{
			return nerr;
		}
	}
	if(CreateDirectory(_path,NULL))
		nerr=0;
	return nerr;
}

BOOL CDoFile::IsFileExit(const CString& pathname)
{
	int length=pathname.GetLength();

	if(length<=0)
		return FALSE;

	CString _pathname=pathname;

	if(_pathname.Right(1) == '\\')
		_pathname = _pathname.Left(length-1);
	
	
	WIN32_FIND_DATA find_data = {0};

	HANDLE handle =FindFirstFile(_pathname,&find_data);
	if(handle != INVALID_HANDLE_VALUE)
	{
		if(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
		
	}
	else
	{
		return FALSE;
	}
	FindClose(handle);
}

CString CDoFile::ParentPath(const CString& path)
{
	if(path.GetLength() < 2) return _T("");

	CString		minPath = path;
	int pos = minPath.ReverseFind('\\');
	if( pos != -1 )
		minPath = minPath.Left( pos );

	return minPath;
}

BOOL CDoFile::MyDeleteDirectory(const CString& path)
{
	CFileFind tempFind;//��������
	char tempFileFind[MAX_PATH]={0};//��ʽ�������ַ�
	CString DirName=path;
	if(!DirName.IsEmpty() && DirName.Right(1) == '\\')
		DirName=DirName.Left(DirName.GetLength()-1);
	sprintf_s(tempFileFind, "%s\\*.*",DirName); //ƥ���ʽΪ*.*,����Ŀ¼�µ������ļ�  
	CString w_tempFileFind;
	m_convert.CharToCstring(w_tempFileFind,tempFileFind);
	BOOL IsFind=tempFind.FindFile(w_tempFileFind);

	while(IsFind)
	{
		IsFind=tempFind.FindNextFile();//�˺������ڱ���Ŀ¼���ļ�ʱ���жϵ�ǰĿ¼���Ƿ�����һ��Ŀ¼���ļ�
		if(!tempFind.IsDots())//ÿ��Ŀ¼�¶���ȱʡ������Ŀ¼�����Ʒֱ�Ϊ '. '�� '.. '���ֱ������Ŀ¼����һ��Ŀ¼����ˣ��������ڱ���Ŀ¼���ļ�ʱ����Ҫ���˵�������ȱʡĿ¼��
		{
			CString FoundFileName=tempFind.GetFileName();//�ҵ���Ŀ¼������
			if(tempFind.IsDirectory())//�����Ŀ¼
			{
				CString AddFoundFileName=DirName+_T("\\")+FoundFileName;
				MyDeleteDirectory(AddFoundFileName);//�ݹ����,������Ŀ¼����û�ҵ�exit
			}
			else
			{
				//���ļ�ֱ��ɾ��
				CString AddFounFilePath=DirName+_T("\\")+FoundFileName;
				DeleteFile(AddFounFilePath);//ɾ��Ŀ¼���ļ�
			}
		}
	}
	tempFind.Close();
	//ɾ��Ŀ¼
	if(!RemoveDirectory(DirName))
	{
		return FALSE;
	}
	return TRUE;
}

CString CDoFile::GetExeFullFilePath()
{
	TCHAR lpPath[MAX_PATH]=TEXT("");
	DWORD dwResult=GetModuleFileName(NULL,lpPath,MAX_PATH);
	if(dwResult==0)return _T("");
	for(int i=dwResult;i>0;i--)
	{
		if(lpPath[i]=='\\'){lpPath[i]=0;break;}
	}
	m_strPath=lpPath;
	return m_strPath;
}

