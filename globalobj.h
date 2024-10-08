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


//表示主页面的切换，例如固晶页面切换到症断页面，参数为1表示该页面显示，参数为0表示该页面要隐藏
#define WM_USER_SWITCH_SHEET (WM_USER+1000) 

//在属性页间切换，参数为1表示该页面显示，参数为0表示该页面要隐藏
#define WM_USER_SWITCH_PAGE (WM_USER+1001)

#define WM_USER_SEL_PROG (WM_USER+1002)//在程式选择页面表示选择了程式，但未必加载

#define WM_USER_END_EDIT (WM_USER+1003) //小键盘输入完毕


#define WM_USER_LOG_TO_LIST (WM_USER+1010)  //在主界面上显示LOG文件

//往自动发送消息
#define WM_USER_NOTIFY_MAIN (WM_USER+1011)  

//程式切换往主界面发消息
#define WM_USER_SWITCH_PROG (WM_USER+1012)

//主界面上一页下一页显示
#define WM_USER_MAIN_PAGE_UPDOWN (WM_USER+1013)

//主界面切换相机
#define WM_USER_MAIN_SWITCH_CAM (WM_USER+1014)

#define WM_USR_UPATE_CCD_WH		(WM_USER+1015)

#define WM_USR_UPATE_CCD_WF		(WM_USER+1016)

#define WM_USER_BDTAB2_INPUT	(WM_USER+1017)

#define WM_USER_CLAW2_INFO		(WM_USER+1019)// 固晶台1将料片放入固晶台2已完成

#endif//_GLOBALOBH_H_

