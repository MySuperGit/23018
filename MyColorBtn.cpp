// MyColorBtn.cpp: implementation of the CMyColorBtn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyColorBtn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyColorBtn::CMyColorBtn()
{
//	int btn_color = g_SysData.GetButtonColor();
	int offset_color = 30;
	SetFlat(FALSE, FALSE);
	SetColor(CButtonST::BTNST_COLOR_BK_OUT, g_SysData.GetButtonBkColor(), FALSE);//��겻�ڰ�ť��
	SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, g_SysData.GetButtonFocusBkColor(), FALSE);//��ť�н���
	SetColor(CButtonST::BTNST_COLOR_BK_IN, g_SysData.GetButtonBkColor(), FALSE);//����ڰ�ť��Χ��
	OffsetColor(CButtonST::BTNST_COLOR_BK_IN, offset_color, FALSE);
}

CMyColorBtn::~CMyColorBtn()
{

}

void CMyColorBtn::SetBkColor(int color, int focus_color)
{
	SetColor(CButtonST::BTNST_COLOR_BK_OUT, color, FALSE);//��겻�ڰ�ť��
	SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, focus_color==-1?color:focus_color, FALSE);//��ť�н���
	SetColor(CButtonST::BTNST_COLOR_BK_IN, color, FALSE);//����ڰ�ť��Χ

}

CMyColorCheck::CMyColorCheck()
{
	int offset_color = 0;
// 	SetFlat(FALSE, FALSE);
	SetColor(CButtonST::BTNST_COLOR_BK_OUT, g_SysData.GetCheckBkColor(), FALSE);//��겻�ڰ�ť��
	SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, g_SysData.GetCheckFocusBkColor(), FALSE);//��ť�н���
	SetColor(CButtonST::BTNST_COLOR_BK_IN, g_SysData.GetCheckFocusBkColor(), FALSE);//����ڰ�ť��Χ��
	OffsetColor(CButtonST::BTNST_COLOR_BK_IN, offset_color, FALSE);
	DrawBorder(TRUE, FALSE);
}

CMyColorCheck::~CMyColorCheck()
{

}
