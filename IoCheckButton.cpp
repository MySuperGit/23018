// IoCheckButton.cpp : implementation file
//

#include "stdafx.h"
#include "IoCheckButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIoCheckButton

CIoCheckButton::CIoCheckButton()
{
	d_pOutBit = NULL;
}

CIoCheckButton::~CIoCheckButton()
{
}


BEGIN_MESSAGE_MAP(CIoCheckButton, CButton)
	//{{AFX_MSG_MAP(CIoCheckButton)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIoCheckButton message handlers
void CIoCheckButton::Init(COutBit* pOutBit)
{
//	ModifyStyle(0,BS_OWNERDRAW,0);
	d_pOutBit = pOutBit;
	Refresh();
}
void CIoCheckButton::Refresh()
{
	/*if (!d_pOutBit)
	{	
	}*/

	ASSERT(d_pOutBit);
	SetCheck(d_pOutBit->Get());
}

void CIoCheckButton::OnClicked() 
{
	// TODO: Add your control notification handler code here
	/*if (!d_pOutBit)
	{

	}*/
 	if(GetCheck())
 		d_pOutBit->On();
 	else
 		d_pOutBit->Off();
 	Sleep(100);

}

void CIoCheckButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
    CDC* pDC = CDC::FromHandle(lpDIS->hDC);//???????DC

    UINT state = lpDIS->itemState; //�õ�״̬
    CRect focusRect, btnRect;//�������Σ���ʾ�õ����뽹��ʱ�����߾��κͰ�ť����     
    focusRect.CopyRect(&lpDIS->rcItem); 
    btnRect.CopyRect(&lpDIS->rcItem); 

    //
    // �õ�Button������
    //
   const int bufSize = 512;
   TCHAR buffer[bufSize];
   GetWindowText(buffer, bufSize);
    
   // ʹ��m_fg, m_bg��ɫ���� Draw3dRect(...)���ư�ť�߿�

   // FillRect(...)��䰴ť�ڲ�
   //CBrush brh(RGB(0,255,0));
   // CBrush brh1(RGB(28, 69, 125));
   CBrush brh(RGB(100,0,0)); 
   CBrush brh1(RGB(120,180,180));
   CBrush brh2(RGB(100,100,100));

   // DrawText(...)��������
//	pDC->FillRect(btnRect,&brh1);
    //���ݵ�ǰ״̬������ʾ
    //
   pDC->SetTextColor(RGB(255,255,255));
    if (state & ODS_FOCUS)
	{
        //�õ����뽹�㣬ͨ��focusRect������
        if (state & ODS_SELECTED)
		{ 
			if (d_pOutBit)
			{
				// �����£��������ݱ߿�
				if( d_pOutBit->Get() == 0)
				{
					pDC->FillRect(btnRect,&brh);
					pDC->SetTextColor(RGB(0,0,0));
				}
				else
				{
					pDC->FillRect(btnRect,&brh1);
					
				}
				d_pOutBit->Get() == 0? d_pOutBit->On(): d_pOutBit->Off();
			}
     
		}
    }
    else if (state & ODS_DISABLED)
	{
    //ʧЧ��ͨ��m_disabled_fg, m_disabled_bg �ػ水ť�ڲ�
		pDC->FillRect(btnRect,&brh2);
	}
	else
	{
		pDC->FillRect(btnRect,&brh1);	
	}

	btnRect.top += 12;
	pDC->SetBkMode(TRANSPARENT);

	if (d_pOutBit)
	{
		if( d_pOutBit->Get() == 1)
		{		
			pDC->SetTextColor(RGB(0,0,0));
		}
		else
		{
			pDC->SetTextColor(RGB(255,255,255));
			
		}
	}


	
	pDC->DrawText(buffer,btnRect,DT_VCENTER|DT_CENTER);

} 


//=====================================

CInCheckButton::CInCheckButton()
{
	d_pInBit = NULL;
}

CInCheckButton::~CInCheckButton()
{
}


BEGIN_MESSAGE_MAP(CInCheckButton, CButton)
	//{{AFX_MSG_MAP(CInCheckButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIoCheckButton message handlers
void CInCheckButton::Init(CInBit* pInBit)
{
//	ModifyStyle(0,BS_OWNERDRAW,0);
	d_pInBit = pInBit;
}
void CInCheckButton::Refresh()
{
	if (!d_pInBit)
	{

	}
	ASSERT(d_pInBit);
	SetCheck(d_pInBit->Get());
}

void CInCheckButton::OnClicked() 
{
	// TODO: Add your control notification handler code here
// 	if(GetCheck())
// 		d_pOutBit->On();
// 	else
// 		d_pOutBit->Off();
// 	Sleep(100);

}

void CInCheckButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
    CDC* pDC = CDC::FromHandle(lpDIS->hDC);//???????DC

    UINT state = lpDIS->itemState; //�õ�״̬
    CRect focusRect, btnRect;//�������Σ���ʾ�õ����뽹��ʱ�����߾��κͰ�ť����     
    focusRect.CopyRect(&lpDIS->rcItem); 
    btnRect.CopyRect(&lpDIS->rcItem); 

    //
    // �õ�Button������
    //
   const int bufSize = 512;
   TCHAR buffer[bufSize];
   GetWindowText(buffer, bufSize);
    
   // ʹ��m_fg, m_bg��ɫ���� Draw3dRect(...)���ư�ť�߿�

   // FillRect(...)��䰴ť�ڲ�
   //CBrush brh(RGB(0,255,0));
   // CBrush brh1(RGB(28, 69, 125));
   CBrush brh(RGB(100,0,0)); 
   CBrush brh1(RGB(120,180,180));
   CBrush brh2(RGB(100,100,100));

   // DrawText(...)��������
//	pDC->FillRect(btnRect,&brh1);
    //���ݵ�ǰ״̬������ʾ
    //
   pDC->SetTextColor(RGB(255,255,255));
    if (state & ODS_FOCUS)
	{
        //�õ����뽹�㣬ͨ��focusRect������
        if (state & ODS_SELECTED)
		{
			if (!d_pInBit)
			{
				
			}
			else
			{
			// �����£��������ݱ߿�
				if( d_pInBit->Get() == 0)
				{
					pDC->FillRect(btnRect,&brh);
					pDC->SetTextColor(RGB(0,0,0));
				}
				else
				{
					pDC->FillRect(btnRect,&brh1);
					
				}
			}
		//	d_pOutBit->Get() == 0? d_pOutBit->On(): d_pOutBit->Off();
		}
    }
    else if (state & ODS_DISABLED)
	{
    //ʧЧ��ͨ��m_disabled_fg, m_disabled_bg �ػ水ť�ڲ�
		pDC->FillRect(btnRect,&brh2);
	}
	else
	{
		pDC->FillRect(btnRect,&brh1);	
	}

	btnRect.top += 12;
	pDC->SetBkMode(TRANSPARENT);

	if (!d_pInBit)
	{
		
	}
	else
	{
		if( d_pInBit->Get() == 1)
		{		
			pDC->SetTextColor(RGB(0,0,0));
		}
		else
		{
			pDC->SetTextColor(RGB(255,255,255));
			
		}
	}

	
	pDC->DrawText(buffer,btnRect,DT_VCENTER|DT_CENTER);

} 


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CIoCheck_3_Button

CIoCheck_3_Button::CIoCheck_3_Button()
{
	d_pOutBit  =NULL;
	d_pOutBit2 =NULL;
	d_pOutBit3 =NULL;

}

CIoCheck_3_Button::~CIoCheck_3_Button()
{
	d_pOutBit  =NULL;
	d_pOutBit2 =NULL;
	d_pOutBit3 =NULL;
}


BEGIN_MESSAGE_MAP(CIoCheck_3_Button, CButton)
	//{{AFX_MSG_MAP(CIoCheck_3_Button)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIoCheckButton message handlers
void CIoCheck_3_Button::Init(COutBit* pOutBit,COutBit* pOutBit2,COutBit* pOutBit3)
{
	//	ModifyStyle(0,BS_OWNERDRAW,0);
	d_pOutBit = pOutBit;
	d_pOutBit2 = pOutBit2;
	d_pOutBit3 = pOutBit3;

}
void CIoCheck_3_Button::Refresh()
{
	if (!d_pOutBit)
	{
		return ;
	}
	ASSERT(d_pOutBit);
	SetCheck(d_pOutBit->Get());
}

void CIoCheck_3_Button::OnClicked() 
{
	// TODO: Add your control notification handler code here
	// 	if(GetCheck())
	// 		d_pOutBit->On();
	// 	else
	// 		d_pOutBit->Off();
	// 	Sleep(100);

}

void CIoCheck_3_Button::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);//???????DC

	UINT state = lpDIS->itemState; //�õ�״̬
	CRect focusRect, btnRect;//�������Σ���ʾ�õ����뽹��ʱ�����߾��κͰ�ť����     
	focusRect.CopyRect(&lpDIS->rcItem); 
	btnRect.CopyRect(&lpDIS->rcItem); 

	//
	// �õ�Button������
	//
	const int bufSize = 512;
	TCHAR buffer[bufSize];
	GetWindowText(buffer, bufSize);

	// ʹ��m_fg, m_bg��ɫ���� Draw3dRect(...)���ư�ť�߿�

	// FillRect(...)��䰴ť�ڲ�
	CBrush brh(RGB(0,255,0));
	CBrush brh1(RGB(0,162,232));//(RGB(28, 69, 125));//RGB(200,200,200));//(142,180,225));//(RGB(28, 69, 125));
	CBrush brh2(RGB(217,223,228));//(RGB(100,100,100));

	// DrawText(...)��������
	//	pDC->FillRect(btnRect,&brh1);
	//���ݵ�ǰ״̬������ʾ
	//00
	pDC->SetTextColor(RGB(0,0,0));
	if (state & ODS_FOCUS)
	{
		//�õ����뽹�㣬ͨ��focusRect������
		if (state & ODS_SELECTED)
		{ 
			if (d_pOutBit)
			{
				// �����£��������ݱ߿�
				if( d_pOutBit->Get() == 0)
				{
					pDC->FillRect(btnRect,&brh);
					pDC->SetTextColor(RGB(0,0,0));
				}
				else
				{
					pDC->FillRect(btnRect,&brh1);

				}

				if (d_pOutBit->Get() == 0)
				{
					if (d_pOutBit2)
					{
						d_pOutBit2->Off();
					}
					if (d_pOutBit3)
					{
						d_pOutBit3->Off();
					}
					d_pOutBit->On();
				}
				else
				{
					d_pOutBit->Off();

				}

				//d_pOutBit->Get() == 0 ?d_pOutBit2->Off(),d_pOutBit->On(): d_pOutBit->Off();
			}
		}
	}
	else if (state & ODS_DISABLED)
	{
		//ʧЧ��ͨ��m_disabled_fg, m_disabled_bg �ػ水ť�ڲ�
		pDC->FillRect(btnRect,&brh2);
	}
	else
	{
		pDC->FillRect(btnRect,&brh1);	
	}

	btnRect.top += 12;
	pDC->SetBkMode(TRANSPARENT);

	if (d_pOutBit)
	{
		if( d_pOutBit->Get() == 1)
		{		
			pDC->SetTextColor(RGB(0,0,0));
		}
		else
		{
			pDC->SetTextColor(RGB(255,255,255));

		}
	}


	pDC->DrawText(buffer,btnRect,DT_VCENTER|DT_CENTER);

} 

void CIoCheck_3_Button::Out_On()
{
	if (d_pOutBit){
		d_pOutBit->On();
	}

	if (d_pOutBit2){
		d_pOutBit2->Off();
	}

	if (d_pOutBit3){
		d_pOutBit3->Off();
	}

	Refresh();
}


void CIoCheck_3_Button::Out_Off()
{
	if (d_pOutBit){
		d_pOutBit->Off();
	}

	if (d_pOutBit2){
		d_pOutBit2->Off();
	}

	if (d_pOutBit3){
		d_pOutBit3->Off();
	}

	Refresh();
}
