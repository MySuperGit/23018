// MyColorBtn.h: interface for the CMyColorBtn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCOLORBTN_H__015ACB54_F616_495A_973F_A59D744CEF5A__INCLUDED_)
#define AFX_MYCOLORBTN_H__015ACB54_F616_495A_973F_A59D744CEF5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\MODULE\GUI\BUTTONST\BtnST.h"

class CMyColorBtn : public CButtonST  
{
public:
	CMyColorBtn();
	virtual ~CMyColorBtn();
public:
	void SetBkColor(int color, int focus_color=-1);

};

class CMyColorCheck : public CButtonST  
{
public:
	CMyColorCheck();
	virtual ~CMyColorCheck();

};

#endif // !defined(AFX_MYCOLORBTN_H__015ACB54_F616_495A_973F_A59D744CEF5A__INCLUDED_)
