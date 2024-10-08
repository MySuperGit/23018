#pragma once

#define JOT_MAX_CAN  2
#define JOT_MAX_CARD 8
class AFX_CLASS_IMPORT CJotCtrlCard
{
public:
	CJotCtrlCard(void);
	~CJotCtrlCard(void);

public:
	int Init();
	int Exit();
	int InitMotionSystem();
	int ExitMotionSystem();
	int InitCanCard(int canno);
	int ExitCanCard(int canno);
	int InitCardNo(int canno,int cardno);

public:
	BOOL m_bMotionSystemInit;
	BOOL m_bMotionSystemExit;
	BOOL m_bCanInit[JOT_MAX_CAN];
	BOOL m_bCardInit[JOT_MAX_CAN][JOT_MAX_CARD];
public:
	CString GetErrorInfo(int Error);
private:
	void CheckErrorLog(CString funcName,int Error);
};

