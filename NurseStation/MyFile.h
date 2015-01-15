
#ifndef _MyFile_h_
#define _MyFile_h_


// judge this is this file exit in disk, 

class Cfileliststr
{
public:
	CString		 filepath;
	CString		 filename;
	CTime		 m_fileaccesstime;
	CTime		 m_filewritetime;
	DWORD		 m_size;
};


#define FILE_EXIT		1
#define FOLDER_EXIT		2
#define FILE_EMPTY		0

int		IsFileExit( const CString& pathname );

int		ComparePath( const CString& path1, const CString& path2 );

// Ϊ�˷�ֹͬ����NewFileName ���ؿ϶���һ��û��ͬ�����ļ�����
CString NewFileName( const CString& oldName );

// �ļ�·�����ļ����֡��ļ���չ������

// example : "file.etp", "file1.doc"..
CString pathnameGetname_ext( const CString &pathname );

// example : "file", "file1"..
CString pathnameGetname( const CString& pathname );

// example ".ETP", ".DOC";
CString nameGetExp( const CString& filename );

// example c:\ 
CString pathNameGetPath( const CString& filepathname );

// ���·��
CString path_append( const CString& path1, const CString& path2 );

// 
CString parentDirectory(const CString& path );
// 0: �ɹ��� ������ʧ��
int		createDirectory( const CString& path );

// �ļ�����
BOOL MyCopyFile(CString strSource, CString strDest );

int		del_path_and_file( CString strPath );
int		move_file( CString oldPath, CString newPath, bool bDelOldPath=TRUE );

//  szFile
//   [in]: Ҫִ�е��ļ���·��
//  bWait:
//   [in]: �Ƿ�Ҫ�ȴ��ó������н���
void ExecFile( const CString&  szFile, BOOL bWait = FALSE );
//Cfileliststr of CPtrList& listfile			
void	SearchDirectory( const CString& strfolder,CPtrList& listfile,const CString& filter,const CString& filterfolder);
void	RealseDirectory(CPtrList & listfile);
// �ļ��п���
void MyCopyDirectory(CString strSource, CString strDest );
//�ж� �ļ���Сconst DWORD& filesize, ʱ���Ƿ������ǰʱ�� const CString& acesstime 
BOOL	isNewFile(const CString& filename,const DWORD& filesize,const CString& acesstime);
////////////////////////////////////////////////////////////////////////// 
//   DelDirectory 
//   ɾ��һ���ļ��� 
//   lpszPath   -   Ҫɾ�����ļ���·�� 
//   ����ֵ���ɹ�����TRUE�����򷵻�FALSE 
//   ��ע���������ɾ�������ļ� 
////////////////////////////////////////////////////////////////////////// 
BOOL   DeleteDirectory(   LPCTSTR   lpszPath   );
BOOL BrowseForFolder(CString& strpath,HWND  hWnd);

//////////////////////////////////////////////////////////////////////////

class CMyStdioFile : public CStdioFile
{
public:
	CMyStdioFile();
public:
	
	BOOL	ReadString( CString& str );
	void	WriteString( const CString& str );
};
bool HSelectDir(CString &strPath, HWND hWnd=0);
int  HSelectFile(CStringArray &array, 
							BOOL bOpen=TRUE,
							const CString &filter=_T(""), 
							BOOL bMulti=FALSE, 
							DWORD dwFlags=0, 
							CWnd* pParent=NULL );

int  HSelectFileMany(CStringArray &array, 
				 BOOL bOpen=TRUE,
				 const CString &filter=_T(""), 
				 BOOL bMulti=FALSE, 
				 DWORD dwFlags=0, 
							CWnd* pParent=NULL );
#endif // _MyFile_h_
