// MyColorSpin.cpp: implementation of the CMyColorSpin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyColorSpin.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyColorSpin::CMyColorSpin()
{
	SetBkColor(g_SysData.GetDialogBkColor());
	SetBorderColor(RGB(0, 0, 0));
	SetArrowColor(g_SysData.GetStaticTextColor());
	SetActiveArrowColor(g_SysData.GetButtonFocusBkColor());
}

CMyColorSpin::~CMyColorSpin()
{

}
