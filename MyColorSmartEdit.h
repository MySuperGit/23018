#ifndef _MY_COLOR_SMARTEDIT_H_
#define _MY_COLOR_SMARTEDIT_H_

#include "..\\module\\gui\\MySmartEdit.h"

class CMyColorSmartEdit: public CMySmartEdit
{
public:
	CMyColorSmartEdit();
	virtual ~CMyColorSmartEdit();
	virtual BOOL  PreTranslateMessage(MSG* pMsg);
protected:
	//{{AFX_MSG(CMyColorSmartEdit)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
public:
	void SetActive(int flag);
	int fReadyOnly; //0=w/r, 1=readonly
	int fEditType;
	BOOL m_bEditing; //?y?¨²¡À¨¤?-
protected:
	COLORREF m_ClrText;
	COLORREF m_ClrBk;
	CBrush m_BrBk;

public:
	BOOL m_bPass;
	void SetPassword();
};

#endif//_MY_SMARTEDIT_H_
