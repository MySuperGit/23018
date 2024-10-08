// IoLedStatic.cpp : implementation file
//

#include "stdafx.h"
#include "IoLedStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIoLedStatic

CIoLedStatic::CIoLedStatic()
{
	d_pInBit = NULL;
}

CIoLedStatic::~CIoLedStatic()
{
}


BEGIN_MESSAGE_MAP(CIoLedStatic, CStatic)
	//{{AFX_MSG_MAP(CIoLedStatic)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIoLedStatic message handlers
void CIoLedStatic::Init(CInBit* pInBit, HICON hIconOn, HICON hIconOff)
{
	d_pInBit = pInBit;
	d_HIconOn = hIconOn;
	d_HIconOff = hIconOff;
}
void CIoLedStatic::Refresh()
{
	ASSERT(d_pInBit);
	if(d_pInBit->Get())   //--- 1=ºìµÆ£¬0=ºÚµÆ£¨Ãð£©
	{
		SetIcon(d_HIconOn);
	}
	else
	{
		SetIcon(d_HIconOff);
	}
}