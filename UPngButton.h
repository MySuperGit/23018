#ifndef _PNGBUTTON_H
#define _PNGBUTTON_H

#if _MSC_VER >= 1000
#pragma once
#endif 

#include "gdiplus.h"
using namespace Gdiplus;  
#pragma comment(lib, "gdiplus.lib") 


class CPngButton : public CButton
{
	DECLARE_DYNAMIC(CPngButton)
public:
	enum BUTTON_STATE
	{
		BUTTON_ENABLE = 0,
		BUTTON_HOVER = 1,
		BUTTON_CLICK = 2,
		BUTTON_DISABLE= 3 
	};         //按钮状态
	CPngButton();
	virtual ~CPngButton();


protected:
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMouseHover(WPARAM wparam, LPARAM lparam);
	Image * m_pImage;
	Image *  m_pImage1;
	Image *  m_pImage2;
	Image *  m_pImage3;
	Image *  m_pImage4;
	Graphics * m_pGraphics;
	DECLARE_MESSAGE_MAP()
public:
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void SetButtonImage(WCHAR* pWStr);//设定按钮图片及图片的截取方式0为横向截取1竖直截取
	void SetButtonImage(CString str1,CString str2,CString str3,CString str4);
	void SetText(CString strText,COLORREF color = RGB(0,0,0), CString Font = _T("Arial"), INT size = 120);//设定按钮文字和按钮颜色
	void Enable(bool bEnable);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	void SetBrush(CBrush *pbr);
	void PaintParent();

	int	iButtonIndex;
	int nHeight;
	int nWidth;

	BOOL			m_bDisable;			// 按钮是否禁用		
	BOOL			m_bCursorOnButton; 	// 鼠标是否在按钮上
	BOOL			m_bHover;			//
	BOOL            m_bText;
	BOOL            m_bClick;

	int				m_nWidth;       //图片宽
	int				m_nHeight;     //图片高
	int				m_nSliceWidth;  //按钮宽
	int             m_nSliceHeight; //按钮高
	COLORREF        m_TextColor; //文字颜色

//	CString         strImage;  //图片外部路径
	CString         m_strText; //文字
	CString			m_TextFont;
	INT				m_TextSize;
	CRect           m_rectButton; //按钮区域
	CRect           m_rcText; //文字区域

	CBrush*			m_pBrush;

protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
#endif

