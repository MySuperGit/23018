// JogButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JogButton.h"


// CJogButton

IMPLEMENT_DYNAMIC(CJogButton, CButtonEx)

CJogButton::CJogButton()
{
	pBaseMotor = NULL;
	m_dir = 1;
	m_dSpd = 3.5;
}

CJogButton::~CJogButton()
{
}


BEGIN_MESSAGE_MAP(CJogButton, CButtonEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()



// CJogButton ��Ϣ�������




void CJogButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (pBaseMotor)
	{
		if (m_dir >0)
		{
			pBaseMotor->ConstMove(pBaseMotor->GetLimitP(),m_dSpd);
		}
		else
		{
			pBaseMotor->ConstMove(pBaseMotor->GetLimitN(),m_dSpd);
		}		
	}

	CButtonEx::OnLButtonDown(nFlags, point);
}


void CJogButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (pBaseMotor)
	{
		pBaseMotor->StopMove();
	}

	CButtonEx::OnLButtonUp(nFlags, point);
}

void CJogButton::Init( CBaseMotor* p )
{
	pBaseMotor = p;
}

void CJogButton::SetDir(int dir)
{
	m_dir = dir;
}


void CJogButton::SetSpd( double spd )
{
	m_dSpd = spd;
}

LRESULT CJogButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (pBaseMotor)
	{
		pBaseMotor->StopMove();
	}

	return CButtonEx::OnMouseLeave(wParam, lParam);
}
