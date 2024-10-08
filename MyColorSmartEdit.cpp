#include "stdafx.h"
#include "mycolorsmartedit.h"

BEGIN_MESSAGE_MAP(CMyColorSmartEdit, CMySmartEdit)
//{{AFX_MSG_MAP(CMyColorSmartEdit)
ON_WM_CTLCOLOR_REFLECT()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONDBLCLK()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMyColorSmartEdit::CMyColorSmartEdit()
{
	fReadyOnly=0;
	fEditType=1;  //only number
	SetActive(0);
	m_bEditing = FALSE;
	m_bPass = FALSE;
}
CMyColorSmartEdit::~CMyColorSmartEdit()
{
}
void CMyColorSmartEdit::SetActive(int flag)
{
	if(flag)
	{
		m_ClrText = RGB(0, 0, 255);
		m_ClrBk = RGB(255, 150, 150);
	}
	else
	{
		m_ClrText = RGB(0, 0, 0);
		m_ClrBk = RGB(255, 255, 255);
		if (fReadyOnly)
		{
           m_ClrText = RGB(255, 255, 255);
		   m_ClrBk = RGB(100, 100, 200);
		}
	}
	m_BrBk.DeleteObject();
	m_BrBk.CreateSolidBrush( m_ClrBk);
	if(m_hWnd)
		Invalidate();
}

void CMyColorSmartEdit::SetPassword()
{
	m_bPass = TRUE;
	SetPasswordChar('*');
	InitVal("");
	//LimitText(6);
}

HBRUSH CMyColorSmartEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	pDC->SetTextColor(m_ClrText );    // text
	pDC->SetBkColor(m_ClrBk);    // text bkgnd
	return m_BrBk;                // ctl bkgnd
	
	// TODO: Return a non-NULL brush if the
	//    parent's handler should not be called
//	return NULL;
}

#include "..\\DialogKeybd.h"
#include "..\\DialogKeybdt.h"
int MouseLBtnMode=2;  //--- 1= 单击模式 2=双击模式
void CMyColorSmartEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CEdit::OnLButtonDown(nFlags, point);
	
	if (MouseLBtnMode != 1) return;
	CRect rect;
	GetWindowRect(&rect);
	
	CString str;
	GetWindowText(str);
	//AfxMessageBox(str);
	DWORD style;
	style=GetStyle();
	
	if (style == 0x50010880)
	{
		return;
	}
	
	if (fReadyOnly)
	{
		return;
	}
	
	/*
    if (fEditType == 1)
	{
		
		DialogKeybd keyb;
		keyb.KeybdPosX=rect.left;
		if (keyb.KeybdPosX > 1024 - 300 - 50)
		{
			keyb.KeybdPosX=keyb.KeybdPosX-200;
		}
		keyb.KeybdPosY=rect.top+50;
		if (keyb.KeybdPosY > 768 - 380)
		{
			keyb.KeybdPosY=keyb.KeybdPosY-380-50;
		}
		keyb.m_KeybData="";
		keyb.m_KeybData2=str;
		keyb.DoModal();
		SetWindowText(keyb.m_KeybData);
	}
		
		if (fEditType == 2)
		{			
			DialogKeybdT keyb;
			
			keyb.m_KeybData="";
			keyb.m_KeybData2=str;
			keyb.DoModal();
			SetWindowText(keyb.m_KeybData);
		}*/
}

void CMyColorSmartEdit::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CEdit::OnLButtonDblClk(nFlags, point);

	if (MouseLBtnMode != 2) return;

	//MessageBox("edit select !");
	CRect rect;
	GetWindowRect(&rect);

	CString str;
	GetWindowText(str);
	//AfxMessageBox(str);

	DWORD style;
	style=GetStyle();

	if (style == 0x50010880)
	{
		return;
	}

	if (fReadyOnly)
	{
		return;
	}

   if (fEditType == 1)
	{
		m_bEditing = TRUE;
	
		DialogKeybd keyb;
		keyb.KeybdPosX=rect.left;
		if (keyb.KeybdPosX > 1024 - 370 - 50)
		{
			keyb.KeybdPosX=keyb.KeybdPosX-200;
		}
		keyb.KeybdPosY=rect.top+50;
		if (keyb.KeybdPosY > 768 - 260)
		{
			keyb.KeybdPosY=keyb.KeybdPosY-260-50;
		}
		keyb.m_KeybData="";
		keyb.m_KeybData2=str;
		keyb.m_bPass = m_bPass;
		keyb.DoModal();
		SetWindowText(keyb.m_KeybData);
		CheckData();
		::PostMessage(GetParent()->m_hWnd,WM_USER_END_EDIT,GetDlgCtrlID(),(LPARAM)this);
		m_bEditing = FALSE;
	}

	if (fEditType == 2)
	{
		
		DialogKeybdT keyb;
		
		keyb.m_KeybData="";
		keyb.m_KeybData2=str;
		keyb.DoModal();
		SetWindowText(keyb.m_KeybData);
	}
}
BOOL CMyColorSmartEdit::PreTranslateMessage(MSG* pMsg)
{
	DWORD style;
	style=GetStyle();
	if (style == 0x50010880)
	{
		return 0;
	}

	if (fReadyOnly)
	{
		return 0;
	}

	if( pMsg->message == WM_KEYDOWN )	
	{		
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_DELETE || pMsg->wParam == VK_ESCAPE)// || GetKeyState( VK_CONTROL))
		{			
			::TranslateMessage(pMsg);
			::DispatchMessage(pMsg);
			return 1;
		}	
	}

	return CMySmartEdit::PreTranslateMessage(pMsg);
}

