#pragma once

#include "BaseMotor.h"
#include "ButtonEx.h"
// CJogButton

class CJogButton : public CButtonEx
{
	DECLARE_DYNAMIC(CJogButton)

public:
	CJogButton();
	virtual ~CJogButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

public:
	CBaseMotor* pBaseMotor;
	int m_dir;
	double m_dSpd;
	void Init(CBaseMotor* p);
	void SetDir(int dir);
	void SetSpd(double spd);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
};


