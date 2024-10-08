#ifndef _GLOBALOBH_H_
#define _GLOBALOBH_H_

#include "StdAfx.h"
#include "AllWork.h"
#include "Log.h"
#include "UserMsgBox.h"
#include "CInspectData.h"

#include "LogIn.h"
#include "HomMat2DEx.h"


#define PROG_TOTAL 20

//=================================
extern int flg_ResetProg;
//=================================


extern CSysData g_SysData;

extern CExCute_Run d_run;
extern CLog g_Log;
extern CUserMsgBox g_UserMsgBox;

extern BOOL g_bOffLineWork;

extern CInspectData g_InsData1;
extern CInspectData g_InsData2;
extern CInspectData g_InsData3;

extern CAllFlag			g_AllFlag;
extern CAutoPkDn		g_AutoPkDn;
extern CAutoBdTab1	    g_AutoBdTab1;
extern CAutoBdTab1Out  g_AutoBdTab1Out;

extern CAutoDbWh		g_AutoDbWh;
extern CAutoDbDb		g_AutoDbDb;
extern CAutoDbWf	    g_AutoDbWf;

extern BOOL g_Net_Insp_Mode;

extern CLogIn g_LogIn;
extern CHomMat2DEx g_HomMat2D;
extern BOOL g_bEnableWfInOut;


//��ʾ��ҳ����л�������̾�ҳ���л���֢��ҳ�棬����Ϊ1��ʾ��ҳ����ʾ������Ϊ0��ʾ��ҳ��Ҫ����
#define WM_USER_SWITCH_SHEET (WM_USER+1000) 

//������ҳ���л�������Ϊ1��ʾ��ҳ����ʾ������Ϊ0��ʾ��ҳ��Ҫ����
#define WM_USER_SWITCH_PAGE (WM_USER+1001)

#define WM_USER_SEL_PROG (WM_USER+1002)//�ڳ�ʽѡ��ҳ���ʾѡ���˳�ʽ����δ�ؼ���

#define WM_USER_END_EDIT (WM_USER+1003) //С�����������


#define WM_USER_LOG_TO_LIST (WM_USER+1010)  //������������ʾLOG�ļ�

//���Զ�������Ϣ
#define WM_USER_NOTIFY_MAIN (WM_USER+1011)  

//��ʽ�л��������淢��Ϣ
#define WM_USER_SWITCH_PROG (WM_USER+1012)

//��������һҳ��һҳ��ʾ
#define WM_USER_MAIN_PAGE_UPDOWN (WM_USER+1013)

//�������л����
#define WM_USER_MAIN_SWITCH_CAM (WM_USER+1014)

#define WM_USR_UPATE_CCD_WH		(WM_USER+1015)

#define WM_USR_UPATE_CCD_WF		(WM_USER+1016)

#define WM_USER_BDTAB2_INPUT	(WM_USER+1017)

#define WM_USER_CLAW2_INFO		(WM_USER+1019)// �̾�̨1����Ƭ����̾�̨2�����

#endif//_GLOBALOBH_H_

