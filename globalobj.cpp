#include "StdAfx.h"
#include "globalobj.h"

///////////////////////
int flg_ResetProg = 0;
CSysData g_SysData;

CExCute_Run d_run;
CLog g_Log;
CUserMsgBox g_UserMsgBox;

CInspectData g_InsData1(1);
CInspectData g_InsData2(2);
CInspectData g_InsData3(3);

CAllFlag		g_AllFlag;
CAutoPkDn		g_AutoPkDn;
CAutoBdTab1	    g_AutoBdTab1;
CAutoBdTab1Out  g_AutoBdTab1Out;

CAutoDbWh		g_AutoDbWh;
CAutoDbDb		g_AutoDbDb;
CAutoDbWf	    g_AutoDbWf;


BOOL g_Net_Insp_Mode = 1;

CLogIn g_LogIn;

CHomMat2DEx g_HomMat2D;
BOOL g_bEnableWfInOut = FALSE;

