// CPngButton.cpp : implementation file
//
#include "StdAfx.h"
#include "UPngButton.h"

// CPngButton
using namespace Gdiplus;
IMPLEMENT_DYNAMIC(CPngButton, CButton)
CPngButton::CPngButton()
{
	m_bText             = FALSE;
	m_bDisable			= FALSE;
	m_bCursorOnButton	= FALSE;
	m_bHover			= FALSE;
	m_bClick            = FALSE;
	m_strText           = "";
	m_pImage            = NULL;
	m_pGraphics         = NULL;
	nWidth            = 0;
	nHeight           = 0;
	m_pBrush		 = NULL;

}

CPngButton::~CPngButton()
{
	if(m_pImage != NULL)
	{
		delete m_pImage;
		m_pImage = NULL;
	}
	if(m_pGraphics != NULL)
	{
		delete m_pGraphics;
		m_pGraphics = NULL;
	}
}

BEGIN_MESSAGE_MAP(CPngButton, CButton)
    //{{AFX_MSG_MAP(CPngButton)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSEHOVER,OnMouseHover)
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



// CPngButton message handlers
void CPngButton::PreSubclassWindow() 
{
	ModifyStyle(0, BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}

void CPngButton::SetText(CString strText,COLORREF color, CString Font, INT size)
{
	m_bText = TRUE;
	m_strText = strText;
	m_TextColor = color;
	m_TextFont = Font;
	m_TextSize = size;
}
void CPngButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
//	PaintParent();
	UINT iCount = 4;
	int	iButtonIndex = 0;
	if(m_bDisable && iCount >= 4) iButtonIndex = 3;
	else if(m_bClick && iCount >= 3)iButtonIndex = 2;
	else if(m_bHover && iCount >= 2)iButtonIndex = 1;
	else iButtonIndex = 0;

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct -> hDC);
	CRect rect = lpDrawItemStruct->rcItem;
	UINT state = lpDrawItemStruct->itemState;
	m_rcText   = rect;
	m_rcText.DeflateRect(1,1);

	if(m_pGraphics == NULL)
		return;
	if(m_pImage == NULL)
		return;
//	pDC->SetBkMode(TRANSPARENT);

	//if (m_pBrush)
	//{
	//	CRect rc;
	//	GetClientRect(rc);
	//	MapWindowPoints(GetParent(),rc);
	//	pDC->SetBrushOrg(-rc.left,-rc.top);
	//	rc.OffsetRect(-rc.left,-rc.top);
	//	pDC->FillRect(&rc,m_pBrush);
	//}

	Gdiplus::SolidBrush brush(Color(150,211,250));
	m_pGraphics->FillRectangle(&brush,0,0,m_nWidth,m_nHeight);

	if( iButtonIndex==3 )//RECT里面的参数是图片在控件中的大小、位置
	{						//外面的参数是指定取图的范围、位置
		m_pGraphics->DrawImage(m_pImage,Rect(0,0,m_nWidth,m_nSliceHeight),m_nWidth*iButtonIndex,
		0,m_nWidth, m_nSliceHeight,UnitPixel);
	}
	else
	{
		// click state
		if( iButtonIndex==2 )//m_pImage根据需要修改
		{
			m_pGraphics->DrawImage(m_pImage,Rect(0,0,m_nWidth,m_nHeight),m_nWidth*iButtonIndex,
			0,m_nWidth, m_nSliceHeight,UnitPixel);
		}
		// hover state
		else if ( iButtonIndex==1 )
		{
			m_pGraphics->DrawImage(m_pImage,Rect(0,0,m_nWidth,m_nHeight),m_nWidth*iButtonIndex,
			0,m_nWidth, m_nSliceHeight,UnitPixel);
		}
		// enable state
		else
		{
			m_pGraphics->DrawImage(m_pImage,Rect(0,0,m_nWidth,m_nHeight),m_nWidth*iButtonIndex,
			0,m_nWidth, m_nSliceHeight,UnitPixel);
		}
	}
	if (m_bText == TRUE)
	{
		if (!m_strText.IsEmpty())//设置文字
		{
			//设置字体
			CFont myFont;
			//VERIFY(myFont.CreatePointFont(m_TextSize, m_TextFont, pDC));// m_TextSize/10 --- point
			VERIFY(myFont.CreateFont(m_TextSize, m_TextSize, 0, 0, m_TextSize*10, false, false, false, \
			ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial")));

			CSize Extent = pDC->GetTextExtent(m_strText);//取得文字大小
			//设置居中
			int offset_x = 0,offset_y = 0;
			//offset_y = m_TextSize/10;
			//offset_x = m_TextSize * Extent.cx / Extent.cy / 10;
			offset_x = m_TextSize * m_strText.GetLength();
			offset_y = m_TextSize;

			//CPoint pt( rect.CenterPoint().x - Extent.cx/2, rect.CenterPoint().y - Extent.cy/2 );
			CPoint pt( rect.CenterPoint().x - offset_x/2, rect.CenterPoint().y - offset_y/2);//   offset_x is suppose to be offset_x/2

			if (state & ODS_SELECTED) 
				pt.Offset(1,1);
			int nMode = pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(m_TextColor);
 
			
			//pDC->DrawState(pt, Extent, m_strText, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
			CFont* def_font = pDC->SelectObject(&myFont);
			pDC->TextOut(pt.x, pt.y, m_strText);
			pDC->SelectObject(def_font);
			
			pDC->SetBkMode(nMode);
			myFont.DeleteObject();
		}
	}
}

BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize)
{
	DWORD dwMinSize;
	dwMinSize = MultiByteToWideChar (CP_ACP, 0, lpcszStr, -1, NULL, 0);
	if(dwSize < dwMinSize)
	{ return FALSE; }
	MultiByteToWideChar (CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize); 
	return TRUE;
}

//把button大小设置为图片大小
void CPngButton::SetButtonImage(WCHAR* pWStr)
{


// 	char buf[255];
// 	strcpy(buf, str); 
// 	WCHAR wBuf[255];
// 	MByteToWChar(buf,wBuf,255);
// 	for (int i =0;i<255;i++)
// 	{
// 		TRACE("%c",wBuf[i]);
// 	}
// 
//	m_pImage = Image::FromFile(wBuf);
// 
// 	Image* image = new Image(L"FakePhoto.jpg");
// 	printf("The width of the image is %u.\n", image->GetWidth());
// 	printf("The height of the image is %u.\n", image->GetHeight()); 
// 	
// 	delete image;

	m_pImage = Image::FromFile(pWStr);

	if ( !m_pImage )
	{
		return;
	}
	m_nWidth = m_pImage->GetWidth()/4;
	m_nHeight = m_pImage->GetHeight();

	m_nSliceWidth = m_nWidth;
	m_nSliceHeight = m_nHeight;
	CWnd *pWnd = this -> GetParent();
	GetWindowRect( &m_rectButton );
	pWnd -> ScreenToClient(m_rectButton);
	m_rectButton.right	= m_rectButton.left + m_nSliceWidth;
	m_rectButton.bottom	= m_rectButton.top  + m_nHeight;

	//MoveWindow(m_rectButton);      //调整按钮大小以适应图片
	SetWindowPos(NULL,0,0,m_rectButton.Width(),m_rectButton.Height(),SWP_NOMOVE);
	nWidth = m_rectButton.Width();
	nHeight = m_rectButton.Height();
	m_pGraphics = new Graphics(GetWindowDC()->m_hDC);
}

void CPngButton::SetButtonImage(CString str1,CString str2,CString str3,CString str4)
{
// 	//strImage = str;
// 
// 	m_pImage1 = Image::FromFile(str1);
// 	m_pImage2 = Image::FromFile(str2);
// 	m_pImage3 = Image::FromFile(str3);
// 	m_pImage4 = Image::FromFile(str4);
// 
// 	if ( !m_pImage1 )
// 	{
// 	return;
// 	}
// 	m_nWidth = m_pImage1->GetWidth();
// 	m_nHeight = m_pImage1->GetHeight();
// 
// 	m_nSliceWidth = m_nWidth;
// 	m_nSliceHeight = m_nHeight;
// 	CWnd *pWnd = this -> GetParent();
// 	GetWindowRect( &m_rectButton );
// 	pWnd -> ScreenToClient(m_rectButton);
// 	m_rectButton.right	= m_rectButton.left + m_nSliceWidth;
// 	m_rectButton.bottom	= m_rectButton.top  + m_nHeight;
// 
// 	//MoveWindow(m_rectButton);      //调整按钮大小以适应图片
// 	SetWindowPos(NULL,0,0,m_rectButton.Width(),m_rectButton.Height(),SWP_NOMOVE);
// 	nWidth = m_rectButton.Width();
// 	nHeight = m_rectButton.Height();
// 	m_pGraphics = new Graphics(GetWindowDC()->m_hDC);
}

void CPngButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if( m_bCursorOnButton == FALSE )
	{
		TRACKMOUSEEVENT tme;
		ZeroMemory(&tme,sizeof(TRACKMOUSEEVENT));
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE|TME_HOVER;
		tme.dwHoverTime = 1;
		m_bCursorOnButton = _TrackMouseEvent(&tme);
	}
	//::SetCursor(AfxGetApp()->LoadStandardCursor(MAKEINTRESOURCE(32649)));
	//::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
	CButton::OnMouseMove(nFlags, point);
}

LRESULT CPngButton::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_bCursorOnButton	= FALSE;
	m_bHover	= FALSE;
	//PaintParent();
	Invalidate();
	return 0L;
}

LRESULT CPngButton::OnMouseHover(WPARAM wparam, LPARAM lparam)
{
	m_bHover = TRUE;
	//PaintParent();
	Invalidate();
	return 0L;
}


void CPngButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bClick = TRUE;
	//PaintParent();
	Invalidate();
	CButton::OnLButtonDown(nFlags, point);
}

void CPngButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bClick = FALSE;
	//PaintParent();
	Invalidate();
	CButton::OnLButtonUp(nFlags, point);
}

LRESULT CPngButton::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_LBUTTONDBLCLK)
	{
		message = WM_LBUTTONDBLCLK;//可修改
		//message = WM_LBUTTONDOWN;
	}
	return CButton::DefWindowProc(message, wParam, lParam);//很重要,消除双击没反应
}

BOOL CPngButton::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

BOOL CPngButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	//::SetCursor(AfxGetApp()->LoadStandardCursor(MAKEINTRESOURCE(32649)));//与下面的形式一样
//	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
	return TRUE;
}

void CPngButton::Enable(bool bEnable)
{
	m_bDisable = bEnable;
}

void CPngButton::PaintParent()
{  
	//CRect   rect; 
	//GetWindowRect(&rect); 
	//GetParent()-> ScreenToClient(&rect); 
	//GetParent()-> InvalidateRect(&rect);
}

void CPngButton::SetBrush(CBrush *pbr)
{
	//m_pBrush = pbr;
}

