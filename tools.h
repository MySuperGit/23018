#pragma once

#pragma comment(lib,"..\\exlib\\mdu_tools.lib")

AFX_API_EXPORT CString  GetAppVersion();
AFX_API_EXPORT CString	GetAppFolder();
AFX_API_EXPORT BOOL		MakeFolder(CString lPath);
AFX_API_EXPORT void  	LogInfo(CString lInfoStr);   //�Ե�ǰ����Ϊ�ļ�����¼����¼��ÿһ�в���ʱ��
AFX_API_EXPORT void  	LogInfoTime(CString lInfoStr); //�Ե�ǰ����Ϊ�ļ�����¼����¼��ÿһ�д�ʱ��
AFX_API_EXPORT void 	LogInfo(CString lPrefix, CString lInfoStr); //�Ե�ǰ����+ǰ׺Ϊ�ļ�����¼����¼��ÿһ�в���ʱ��
AFX_API_EXPORT void 	LogInfoTime(CString lPrefix, CString lInfoStr); //�Ե�ǰ����+ǰ׺Ϊ�ļ�����¼����¼��ÿһ�д�ʱ��
AFX_API_EXPORT void		LogInfo(CStringArray* pStrArr, CString lPrefix); //�Ե�ǰ����Ϊ�ļ�����¼����¼һ�����飬����ʱ��

class AFX_CLASS_IMPORT CIniFile  //INI�ļ�������
{
#define MAXCSTRLEN 1024
public:
	CIniFile(CString strFileName,CString strCreateDir =_T(""));
	CIniFile(CString strFileName);
public:
	CIniFile();
	virtual ~CIniFile();
public:
	CString GetStringFromFile(CString strSection,CString strKey,CString strDefault,bool bCreateIfFailed = true);
	int     GetIntFromFile(CString strSection,   CString strKey,int nDefault);
	DWORD   GetDWORDFromFile(CString strSection, CString strKey,DWORD dwDefault);
	BOOL    WriteDWORDToFile(CString strSection, CString strKey,DWORD dwValue);
	BOOL    WriteStringToFile(CString strSection,CString strKey,CString strValue);
	BOOL    WriteIntToFile(CString strSection,   CString strKey,int iWriteVal);

	static BOOL WriteString(LPCTSTR pszFileName, LPCTSTR pszSectionName, LPCTSTR lpKeyName, LPCTSTR lpString);
	static BOOL WriteLong(LPCTSTR pszFileName, LPCTSTR pszSectionName, LPCTSTR lpKeyName, long lLong);
	static BOOL WriteDouble(LPCTSTR pszFileName, LPCTSTR pszSectionName, LPCTSTR lpKeyName, double dDouble);

	static CString GetString(LPCTSTR pszFileName, LPCTSTR pszSectionName, LPCTSTR lpKeyName, LPCTSTR lpDefaultString, BOOL bCreateIfFail = TRUE);
	static long    GetLong(LPCTSTR pszFileName, LPCTSTR pszSectionName, LPCTSTR lpKeyName,	long lDefaultLong, BOOL bCreateIfFail = TRUE);
	static double  GetDouble(LPCTSTR pszFileName, LPCTSTR pszSectionName, LPCTSTR lpKeyName,	double dDefaultDouble, BOOL bCreateIfFail = TRUE);
	static CString GetAppPath();

	//�Ƿ���ڴ��ļ�
	static BOOL IsExistFile(CString strFileName);
	BOOL    GetIsExistFile();
	//��ȡϵͳ�Ĺ���Ŀ¼,ȷ����"\"��β
	CString GetWorkDirectory(){return m_strSysWorkDir;};
	//�õ�Ӧ�ó���ĵ�ǰ·��,������"\"

	void    SetFileName(CString strFileName);
	CString CreateDir(CString strSetDir);
	CString GetFilePath(){return m_strIniFile;}
	void    DeleteIniFile();
protected:
	CString m_strIniFile;
private:
	CString m_strSysWorkDir;//ϵͳ����Ŀ¼·����Ϣ,���ڹ��캯���г�ʼ��	
private:
	CRITICAL_SECTION m_CritSec;
};
