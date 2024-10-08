#pragma once

#pragma comment(lib,"..\\exlib\\mdu_tools.lib")

AFX_API_EXPORT CString  GetAppVersion();
AFX_API_EXPORT CString	GetAppFolder();
AFX_API_EXPORT BOOL		MakeFolder(CString lPath);
AFX_API_EXPORT void  	LogInfo(CString lInfoStr);   //以当前日期为文件名记录，记录的每一行不带时间
AFX_API_EXPORT void  	LogInfoTime(CString lInfoStr); //以当前日期为文件名记录，记录的每一行带时间
AFX_API_EXPORT void 	LogInfo(CString lPrefix, CString lInfoStr); //以当前日期+前缀为文件名记录，记录的每一行不带时间
AFX_API_EXPORT void 	LogInfoTime(CString lPrefix, CString lInfoStr); //以当前日期+前缀为文件名记录，记录的每一行带时间
AFX_API_EXPORT void		LogInfo(CStringArray* pStrArr, CString lPrefix); //以当前日期为文件名记录，记录一个数组，不带时间

class AFX_CLASS_IMPORT CIniFile  //INI文件操作类
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

	//是否存在此文件
	static BOOL IsExistFile(CString strFileName);
	BOOL    GetIsExistFile();
	//获取系统的工作目录,确保以"\"结尾
	CString GetWorkDirectory(){return m_strSysWorkDir;};
	//得到应用程序的当前路径,后面有"\"

	void    SetFileName(CString strFileName);
	CString CreateDir(CString strSetDir);
	CString GetFilePath(){return m_strIniFile;}
	void    DeleteIniFile();
protected:
	CString m_strIniFile;
private:
	CString m_strSysWorkDir;//系统工作目录路径信息,需在构造函数中初始话	
private:
	CRITICAL_SECTION m_CritSec;
};
