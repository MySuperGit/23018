#if !defined(AFX_IMAGEVIEW_H__0FE35854_C626_4B55_8F01_5D1E7A3301D8__INCLUDED_)
#define AFX_IMAGEVIEW_H__0FE35854_C626_4B55_8F01_5D1E7A3301D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageView.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CImageView window
#define CCD_W 640
#define CCD_H 480

#include "ins.h"

//1/4œ‘ æ 
class AFX_CLASS_IMPORT CImageView : public CStatic
{ 
	typedef struct tag_BmpInfo
	{
		BITMAPINFOHEADER bmiHeader;
		RGBQUAD quad[256];
	}BMPInfo;
	
	BMPInfo BmpInfo;	
	
private:
	CDC memdc;
	CBitmap membmp;
	CDC* pdc;
	
	BYTE ImageBuf[CCD_W*CCD_H];
	BYTE TpBuf[100*100];

	DWORD m_WinSizeX,m_WinSizeY;
	//DWORD m_BuffX,m_BuffY;
	
	BYTE* m_pImageBufMain;

	BOOL   m_bcolor;
	// Construction
public:
	CImageView( );
	// Attributes
	
public:
	int Create(CWnd* pwnd,int wx,int wy);
	int DrawView();
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageView)
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CImageView();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CImageView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	eCCDName ccdid;
	ePRName prid;
	int ModWidth,ModHeight;
	int RoiWidth,RoiHeight;
	BOOL m_bCalMode;
	int m_iNum;
	double m_dRatio;

	double score[100];
	double tpx[100];
	double tpy[100];
	double angle[100];
	double time;
	int    tpnum;

	BOOL m_bIsRuning;
	CBaseMotor* pMtrX;
	CBaseMotor* pMtrY;

	double m_CenR,m_CenX,m_CenY;
	CRect m_Rect;
public:
	int SetID(eCCDName ccd,ePRName pr);
	void SetCalMode(BOOL bCalMode);
	void SetCalNum(int iNum);
	void GetID(eCCDName &ccd,ePRName &pr);

	void SetIsRuning(BOOL bRun){m_bIsRuning = bRun;}
	void SetMtr(CBaseMotor* pX,CBaseMotor* pY)
	{
		pMtrX = pX;
		pMtrY = pY;
	}
	int CheckLimit(int x,int y);
	void SetCircle(double cenR,double cenX,double cenY);
	void SetRect(CRect rt);


private:
	BOOL m_bInkDotMode;
public:
	void SetInkDotMode(BOOL mode) { m_bInkDotMode = mode; }
private:
	BOOL m_bContShow;
public:
	void SetContShow(BOOL bShow) { m_bContShow = bShow; }
private:
	int m_iMachineNum;
public:
	void SetMachineNum(int num);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEVIEW_H__0FE35854_C626_4B55_8F01_5D1E7A3301D8__INCLUDED_)
