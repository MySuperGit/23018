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
	};         //��ť״̬
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
	void SetButtonImage(WCHAR* pWStr);//�趨��ťͼƬ��ͼƬ�Ľ�ȡ��ʽ0Ϊ�����ȡ1��ֱ��ȡ
	void SetButtonImage(CString str1,CString str2,CString str3,CString str4);
	void SetText(CString strText,COLORREF color = RGB(0,0,0), CString Font = _T("Arial"), INT size = 120);//�趨��ť���ֺͰ�ť��ɫ
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

	BOOL			m_bDisable;			// ��ť�Ƿ����		
	BOOL			m_bCursorOnButton; 	// ����Ƿ��ڰ�ť��
	BOOL			m_bHover;			//
	BOOL            m_bText;
	BOOL            m_bClick;

	int				m_nWidth;       //ͼƬ��
	int				m_nHeight;     //ͼƬ��
	int				m_nSliceWidth;  //��ť��
	int             m_nSliceHeight; //��ť��
	COLORREF        m_TextColor; //������ɫ

//	CString         strImage;  //ͼƬ�ⲿ·��
	CString         m_strText; //����
	CString			m_TextFont;
	INT				m_TextSize;
	CRect           m_rectButton; //��ť����
	CRect           m_rcText; //��������

	CBrush*			m_pBrush;

protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
#endif

