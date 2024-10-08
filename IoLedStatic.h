#if !defined(AFX_IOLEDSTATIC_H__8E16E52D_C20B_406F_A69F_83487AE74B00__INCLUDED_)
#define AFX_IOLEDSTATIC_H__8E16E52D_C20B_406F_A69F_83487AE74B00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IoLedStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIoLedStatic window

class CIoLedStatic : public CStatic
{
// Construction
public:
	CIoLedStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIoLedStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIoLedStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CIoLedStatic)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	void Init(CInBit* pInBit, HICON hIconOn, HICON hIconOff);
	void Refresh();
protected:	
	HICON d_HIconOn;
	HICON d_HIconOff;
	CInBit* d_pInBit;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IOLEDSTATIC_H__8E16E52D_C20B_406F_A69F_83487AE74B00__INCLUDED_)
