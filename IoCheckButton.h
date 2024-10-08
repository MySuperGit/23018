#if !defined(AFX_IOCHECKBUTTON_H__FDECBB0C_B2F6_4D6E_91BB_D7171FA15400__INCLUDED_)
#define AFX_IOCHECKBUTTON_H__FDECBB0C_B2F6_4D6E_91BB_D7171FA15400__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IoCheckButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIoCheckButton window

class CIoCheckButton : public CButton
{
// Construction
public:
	CIoCheckButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIoCheckButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIoCheckButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CIoCheckButton)
	afx_msg void OnClicked();
	//}}AFX_MSG
protected:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);//必需重载的函数

	DECLARE_MESSAGE_MAP()
public:
	void Init(COutBit* pOutBit);
	void Refresh();
protected:
	COutBit* d_pOutBit;
public:
    COLORREF m_fg, m_bg, m_disabled_fg, m_disabled_bg;//四种颜色分别为文字，背景，失效时文字，失效时背景
};



class CInCheckButton : public CButton
{
	// Construction
public:
	CInCheckButton();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIoCheckButton)
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CInCheckButton();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CIoCheckButton)
	afx_msg void OnClicked();
	//}}AFX_MSG
protected:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);//必需重载的函数
	
	DECLARE_MESSAGE_MAP()
public:
	void Init(CInBit* pInBit);
	void Refresh();
protected:
	CInBit* d_pInBit;
public:
    COLORREF m_fg, m_bg, m_disabled_fg, m_disabled_bg;//四种颜色分别为文字，背景，失效时文字，失效时背景
};




class CIoCheck_3_Button : public CButton
{
	// Construction
public:
	CIoCheck_3_Button();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIoCheck_3_Button)
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CIoCheck_3_Button();

	// Generated message map functions
protected:
	//{{AFX_MSG(CIoCheck_3_Button)
	afx_msg void OnClicked();
	//}}AFX_MSG
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);//必需重载的函数

	DECLARE_MESSAGE_MAP()
public:
	void Init(COutBit* pOutBit,COutBit *pOutbBit2=NULL,COutBit *pOutbBit3=NULL);
	void Refresh();
protected:
	COutBit* d_pOutBit;
	COutBit* d_pOutBit2;
	COutBit* d_pOutBit3;

public:
	void Out_On();
	void Out_Off();

public:
	COLORREF m_fg, m_bg, m_disabled_fg, m_disabled_bg;//四种颜色分别为文字，背景，失效时文字，失效时背景
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IOCHECKBUTTON_H__FDECBB0C_B2F6_4D6E_91BB_D7171FA15400__INCLUDED_)
