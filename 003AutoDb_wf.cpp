#include "StdAfx.h"
#include "..\IC_Bond.h"
#include "..\AllWork.h"

CAutoDbWf::CAutoDbWf()
{
	m_id = 3;
	m_strName = "WF";

	WFX = NULL;
	WFY = NULL;

	m_SearchDirX = 1;

	m_iWfNextX = 0;
	m_iWfNextY = 0;
}

CAutoDbWf::~CAutoDbWf()
{

}

int CAutoDbWf::GetImgNearPos()
{
	CTRealPoint RpCenter(CCD_W/2+g_Ins.GetPara(eCCD_WF,ePR_PT,eCENTOFFX),CCD_H/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY));
	CTRealPoint RpTemp;
	double dist1 = 10000;
	double dist = 0;
	int rtn = 0;
	for (int i=0;i<m_Num;i++)
	{
		RpTemp.Set(m_Posx[i],m_Posy[i]);
		dist = RpCenter.CalDist(RpTemp);
		if (dist < dist1)
		{
			rtn = 1;
			dist1 = dist;
			m_dCentPixX = m_Posx[i] - (CCD_W/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFX));
			m_dCentPixY = m_Posy[i] - (CCD_H/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY));
		}
	}
	return rtn;
}

int CAutoDbWf::GetImgNearPosOut()
{
	CTRealPoint RpCenter(CCD_W/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFX),CCD_H/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY));
	CTRealPoint RpTemp;
	double dist1 = 10000;
	double dist = 0;

	int w = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_X); //����
	int h = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_Y);
	CRect rect(CCD_W/2-w/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFX)
		,CCD_H/2-h/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY)
		,CCD_W/2+w/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFX)
		,CCD_H/2+h/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY));
	CPoint pt;
	int rtn = 0;
	for (int i=0;i<m_Num;i++)
	{
		pt.x = m_Posx[i];
		pt.y = m_Posy[i];
		if (rect.PtInRect(pt)) //�ų����ĵĵ�
		{
			break;
		}
		RpTemp.Set(m_Posx[i],m_Posy[i]);

		dist = RpCenter.CalDist(RpTemp);
		if (dist < dist1)
		{
			rtn = 1;
			dist1 = dist;
			m_dCentPixX = m_Posx[i] - (CCD_W/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFX));
			m_dCentPixY = m_Posy[i] - (CCD_H/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY));
		}
	}
	return rtn;
}

int CAutoDbWf::GetImgCenterPos()
{
	int w = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_X); //����
	int h = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_Y);

	CRect rect(CCD_W/2-w/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFX)
		,CCD_H/2-h/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY)
		,CCD_W/2+w/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFX)
		,CCD_H/2+h/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY));

	CPoint pt;

	int rtn = 0;
	for (int i=0;i<m_Num;i++)
	{
		pt.x = m_Posx[i] ;
		pt.y = m_Posy[i] ;
		if (rect.PtInRect(pt))
		{
			m_dCentPixX = m_Posx[i] - (CCD_W/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFX));
			m_dCentPixY = m_Posy[i] - (CCD_H/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY));

			if (m_Angle[i] > 180)
			{
				m_dCentAngle = m_Angle[i] - 360;
			}
			else
			{
				m_dCentAngle = m_Angle[i];
			}
			rtn = 1;
			break;
		}
	}
	//
	//PixToPulse(m_dCentPixX,m_dCentPixY,m_iCentPulseX,m_iCentPulseY);
	//g_Log.LogArray("���ĵ�ƫ������x=%.1f,y=%.1f,����x=%d,y=%d",m_dCentPixX,m_dCentPixY,m_iCentPulseX,m_iCentPulseY);
	//int posx = WFX->GetPos();
	//int posy = WFY->GetPos();
	//m_iWfPosX += m_iCentPulseX;
	//m_iWfPosY += m_iCentPulseY;
	//g_Log.LogArray("���ĵ�ԭʼλ��x=%d,y=%d,У����λ��x=%d,y=%d",posx,posy,m_iWfPosX,m_iWfPosY);
	return rtn;
}

void CAutoDbWf::PixToPulse(double pixx,double pixy,int& posx,int &posy) 
{
	double ratex = g_Ins.GetParaF(eCCD_WF, eCAL_RESULT_RX);
	double ratey = g_Ins.GetParaF(eCCD_WF, eCAL_RESULT_RY);
	double rateXDir = g_Ins.GetParaF(eCCD_WF, eCAL_RX_DIR) > 0 ?1.0 : -1.0;
	double rateYDir = g_Ins.GetParaF(eCCD_WF, eCAL_RY_DIR) > 0 ? 1.0 :-1.0;
	double xx = pixx * ratex * rateXDir;
	double yy = pixy * ratey * rateYDir;
	posx = WFX->MmToPulse(xx);
	posy = WFY->MmToPulse(yy);
}

int CAutoDbWf::GetImgRectNearPos(CRect rt) //��ȡ���ο�������������ĵ�
{
	CTRealPoint RpTemp;
	CTRealPoint RpCenter(CCD_W/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFX),CCD_H/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY));
	double dist1 = 1000;
	double dist  = 0;
	int rtn = 0;
	CPoint pt;
	for (int i=0;i<m_Num;i++)
	{
		pt.x = m_Posx[i];
		pt.y = m_Posy[i];
		if (rt.PtInRect(pt))
		{
			rtn = 1;
			RpTemp.Set(m_Posx[i],m_Posy[i]);
			dist = RpCenter.CalDist(RpTemp);
			if (dist < dist1)
			{
				dist1 = dist;
				m_dCentPixX = m_Posx[i]-(CCD_W/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFX));
				m_dCentPixY = m_Posy[i]-(CCD_H/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY));
			}
		}
	}

	PixToPulse(m_dCentPixX,m_dCentPixY,m_iCentPulseX,m_iCentPulseY);

	int posx = WFX->GetPos();
	int posy = WFY->GetPos();
	m_iWfPosX += m_iCentPulseX;
	m_iWfPosY += m_iCentPulseY;
	return rtn;
}

//���ڵ�ǰͼ�����ң�ͼ�����Ҳ�����ֱ������������������,
//1,ͼ�����Ϸ�
//2. ���Ͻ�-->����-->���
//	 ����-->����-->���
int	CAutoDbWf::GetNextDiePos()
{
	int rtn = 0;

	if (g_AllFlag.m_bSingleWfSerachStart)
	{
		rtn = GetWorldSearchStart();
		return rtn;
	}

	rtn = GetWorldDirNextDie();

	return rtn;
}

//ͼ���Ѿ� --ͼ����ʶ�𵽵Ķ��ǿ���ȥ���ģ�Ҫ��ǰ�ж��ã��������޵�Ҫ���޳����������ĵ��Ǹ�ҲҪ�޳�
//1.���Ϸ�1,2,3...		��������һ��
//2.�ұ߾��ο�1.2.3...  ���Ϸ��Ŀ�һ����������һ��
//3.�ұ���һ��			��һ�е��ұ߷���
//4.��߾��ο�1.2.3...  �л�����
//5.�����һ��			��һ�е���߷��� �л�����
//6.ͼ�����			�Զ��ж��л�����
//7.�������			�Զ��ж��л�����
int	CAutoDbWf::GetImgNextDie()
{
	int rtn = 0;
	double DieDistX = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_X); //����
	double DieDistY = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_Y);
	//��������Ͻ��ж�����
	int col = fabs((g_Ins.GetPara(eCCD_WF,ePR_PT,eROIWIDTH)-DieDistX)/2/DieDistX);
	WFMapPos  cur_pt;
	CPoint pt;
	CRect rect;
	int lx=0,ly=0,rx=0,ry=0;
	CTRealPoint RpCenter(CCD_W/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFX),CCD_H/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY));
	CTRealPoint RpTemp;
	double dist1 = 10000000;
	double dist  = 0;
	//1.���Ϸ�1,2,3...		��������һ��
#pragma region ��һ��
	lx = CCD_W/2 - DieDistX/2;
	ly = 0;
	rx = CCD_W/2 + DieDistX/2;
	ry = CCD_H/2 - DieDistY/2;
	rect.SetRect(lx,ly,rx,ry);
	rtn = GetImgRectNearPos(rect);
	g_Log.LogShow2("���Ϸ���������lx=%d,ly=%d,rx=%d,ry=%d",lx,ly,rx,ry);
	if (rtn) //�ҵ��� --������һ�������
	{
		gDlgMainBondWnd->m_pImageView[1].SetRect(rect);
		g_Log.LogShow2("1.���Ϸ��ҵ�оƬ������ƫ��x=%.1f,y=%.1f,��������x=%d,y=%d"
			,m_dCentPixX,m_dCentPixY,m_iWfPosX,m_iWfPosY);
		return rtn;
	}
#pragma endregion
	if (m_SearchDirX == 1) //���Ͻ�-->����-->���
	{
		//2.�ұ߾��ο�1.2.3...  ���Ϸ��Ŀ�һ����������һ��
#pragma region �ڶ���
	
		for (int i=0;i<col;i++)
		{
			lx = CCD_W/2 + DieDistX/2+DieDistX*i;
			ly = 0;
			rx = CCD_W/2 + DieDistX/2+DieDistX*(i+1);
			ry = CCD_H/2+DieDistY/2;
			rect.SetRect(lx,ly,rx,ry);
			rtn = GetImgRectNearPos(rect);
			g_Log.LogShow2("���Ͻ�%d,��������lx=%d,ly=%d,rx=%d,ry=%d",i+1,lx,ly,rx,ry);
			if (rtn)  //���Ͻ��ҵ�
			{
				gDlgMainBondWnd->m_pImageView[1].SetRect(rect);
				g_Log.LogShow2("2.���Ͻ�%d�ҵ�оƬ",i+1);
				return rtn;
			}
		}
#pragma endregion
		//3.�ұ���һ��			��һ�е��ұ߷���
#pragma region ������
		lx = CCD_W/2-DieDistX/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFX);
		ly = CCD_H/2+DieDistY/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY);
		rx = CCD_W;
		ry = CCD_H/2+DieDistY/2*3 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY);
		rect.SetRect(lx,ly,rx,ry);
		rtn = GetImgRectNearPos(rect);
		g_Log.LogShow2("�ұ���һ�о�������lx=%d,ly=%d,rx=%d,ry=%d",lx,ly,rx,ry);
		if (rtn)  //�ұ���һ���ҵ�
		{
			gDlgMainBondWnd->m_pImageView[1].SetRect(rect);
			g_Log.LogShow2("3.�ұ���һ���ҵ�оƬ");
			return rtn;
		}
#pragma endregion
		//4.��߾��ο�1.2.3...  �л�����
#pragma region ���Ĳ�
		for (int i=0;i<col;i++)
		{
			lx = CCD_W/2 - DieDistX/2-DieDistX*(i+1);
			ly = 0;
			rx = CCD_W/2 + DieDistX/2+DieDistX*i;
			ry = CCD_H/2+DieDistY/2;
			rect.SetRect(lx,ly,rx,ry);
			rtn = GetImgRectNearPos(rect);
			g_Log.LogShow2("���Ͻ�%d,��������lx=%d,ly=%d,rx=%d,ry=%d",i+1,lx,ly,rx,ry);
			if (rtn)  //���Ͻ��ҵ�
			{
				m_SearchDirX = -1;
				gDlgMainBondWnd->m_pImageView[1].SetRect(rect);
				g_Log.LogShow2("4.���Ͻ�%d�ҵ�оƬ",i+1);
				return rtn;
			}
		}
#pragma endregion
		//5.�����һ��			��һ�е���߷��� �л�����
#pragma region ���岽
		lx = 0;;
		ly = CCD_H/2+DieDistY/2;
		rx = CCD_W/2-DieDistX/2;
		ry = CCD_H/2+DieDistY/2*3;
		rect.SetRect(lx,ly,rx,ry);
		rtn = GetImgRectNearPos(rect);
		g_Log.LogShow2("�����һ�о�������lx=%d,ly=%d,rx=%d,ry=%d",lx,ly,rx,ry);
		if (rtn)  //�����һ���ҵ�
		{
			m_SearchDirX = -1;
			gDlgMainBondWnd->m_pImageView[1].SetRect(rect);
			g_Log.LogShow2("5.�����һ���ҵ�оƬ");
			return rtn;
		}
#pragma endregion
		//6.ͼ�����			�Զ��ж��л�����
#pragma region ������
		rtn = GetImgNearPosOut();
		if (rtn)  //�����һ���ҵ�
		{
			//�ҵ���ߵģ��л�����
			if (m_dCentPixX < CCD_W/2)
			{
				m_SearchDirX = -1;
			}
			g_Log.LogShow2("6.�ҵ�ͼ�����оƬ");
			return rtn;
		}
#pragma endregion	
	}
	else
	{
		//2.��߾��ο�1.2.3...  �л�����
#pragma region �ڶ���
		for (int i=0;i<col;i++)
		{
			lx = CCD_W/2 - DieDistX/2-DieDistX*(i+1);
			ly = 0;
			rx = CCD_W/2 + DieDistX/2+DieDistX*i;
			ry = CCD_H/2+DieDistY/2;
			rect.SetRect(lx,ly,rx,ry);
			rtn = GetImgRectNearPos(rect);
			g_Log.LogShow2("���Ͻ�%d,��������lx=%d,ly=%d,rx=%d,ry=%d",i+1,lx,ly,rx,ry);
			if (rtn)  //���Ͻ��ҵ�
			{
				gDlgMainBondWnd->m_pImageView[1].SetRect(rect);
				g_Log.LogShow2("2.���Ͻ�%d�ҵ�оƬ",i+1);
				return rtn;
			}
		}
#pragma endregion
		//3.�����һ��			��һ�е���߷��� �л�����
#pragma region ������
		lx = 0;;
		ly = CCD_H/2+DieDistY/2;
		rx = CCD_W/2-DieDistX/2;
		ry = CCD_H/2+DieDistY/2*3;
		rect.SetRect(lx,ly,rx,ry);
		rtn = GetImgRectNearPos(rect);
		g_Log.LogShow2("�����һ�о�������lx=%d,ly=%d,rx=%d,ry=%d",lx,ly,rx,ry);
		if (rtn)  //�����һ���ҵ�
		{
			gDlgMainBondWnd->m_pImageView[1].SetRect(rect);
			g_Log.LogShow2("3.�����һ���ҵ�оƬ");
			return rtn;
		}
#pragma endregion
		//4.�ұ߾��ο�1.2.3...  ���Ϸ��Ŀ�һ����������һ��
#pragma region ���Ĳ�
		//��������Ͻ��ж�����
		for (int i=0;i<col;i++)
		{
			lx = CCD_W/2 + DieDistX/2+DieDistX*i;
			ly = 0;
			rx = CCD_W/2 + DieDistX/2+DieDistX*(i+1);
			ry = CCD_H/2+DieDistY/2;
			rect.SetRect(lx,ly,rx,ry);
			rtn = GetImgRectNearPos(rect);
			g_Log.LogShow2("���Ͻ�%d,��������lx=%d,ly=%d,rx=%d,ry=%d",i+1,lx,ly,rx,ry);
			if (rtn)  //���Ͻ��ҵ�
			{
				m_SearchDirX = 1;
				gDlgMainBondWnd->m_pImageView[1].SetRect(rect);
				g_Log.LogShow2("4.���Ͻ�%d�ҵ�оƬ",i+1);
				return rtn;
			}
		}
#pragma endregion
		//5.�ұ���һ��			��һ�е��ұ߷���
#pragma region ���岽
		lx = CCD_W/2-DieDistX/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFX);
		ly = CCD_H/2+DieDistY/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY);
		rx = CCD_W;
		ry = CCD_H/2+DieDistY/2*3;
		rect.SetRect(lx,ly,rx,ry);
		rtn = GetImgRectNearPos(rect);
		g_Log.LogShow2("�ұ���һ�о�������lx=%d,ly=%d,rx=%d,ry=%d",lx,ly,rx,ry);
		if (rtn)  //�ұ���һ���ҵ�
		{
			m_SearchDirX = 1;
			gDlgMainBondWnd->m_pImageView[1].SetRect(rect);
			g_Log.LogShow2("5.�ұ���һ���ҵ�оƬ");
			return rtn;
		}
#pragma endregion

		//6.ͼ�����			�Զ��ж��л�����
#pragma region ������
		rtn = GetImgNearPosOut();
		if (rtn) 
		{
			//�ҵ���ߵģ��л�����
			if (m_dCentPixX > CCD_W/2)
			{
				m_SearchDirX = 1;
			}
			g_Log.LogShow2("6.�ҵ�ͼ�����оƬ");
			return rtn;
		}
#pragma endregion	
	}

	//7.�������			�Զ��ж��л�����
#pragma region ���߲�
	int curPosX = WFX->GetPos();
	int curPosY = WFY->GetPos();
	RpCenter.Set(curPosX,curPosY);
	double dist2 = 100000000;
	for (POSITION pos = m_MapPosList.GetHeadPosition();pos;m_MapPosList.GetNext(pos))
	{
		cur_pt = m_MapPosList.GetAt(pos);
		if (cur_pt.flag == 1) //ֻ�ڿ��õ��������ж�
		{
			RpTemp.Set(cur_pt.wfx,cur_pt.wfy); 
			dist = RpCenter.CalDist(RpTemp);
			rtn = 1;
			if (dist < dist2)
			{
				dist1 = dist;
				m_iWfPosX = cur_pt.wfx;
				m_iWfPosY = cur_pt.wfy;
			}	
		}
	}
	if (rtn)
	{
		if (g_Ins.GetParaF(eCCD_WF,eCAL_RX_DIR) > 0) //������Ҫ���в���
		{
			if (m_iWfPosX < curPosX)
			{
				m_SearchDirX = -1;
			}
		}
		else
		{
			if (m_iWfPosX > curPosX)
			{
				m_SearchDirX = -1;
			}
		}
		g_Log.LogShow2("7.�������ҵ�оƬ");
		return rtn;
	}
#pragma endregion
	//ͼ��������϶�û�ҵ������أ�
	g_Log.LogShow2("û���ҵ�оƬ");
	return rtn;
} 

int CAutoDbWf::GetWorldRectNearPos(CRect rt)
{
	CTRealPoint RpTemp;
	CTRealPoint RpCenter(m_iWfCalX,m_iWfCalY);
	double dist1 = 10000000;

	double dist  = 0;
	int rtn = 0;
	CPoint pt;
	WFMapPos cur_pt;
	for (POSITION pos = m_MapPosList.GetHeadPosition();pos;m_MapPosList.GetNext(pos))
	{
		cur_pt = m_MapPosList.GetAt(pos);
		if (cur_pt.flag != 1)
		{
			continue;
		}
		pt.x = cur_pt.wfx+ limitX;
		pt.y = cur_pt.wfy+ limitY;
		RpTemp.Set(cur_pt.wfx,cur_pt.wfy); 
		if (rt.PtInRect(pt))
		{
			rtn = 1;
			dist = RpCenter.CalDist(RpTemp);
			if (dist < dist1)
			{
				dist1 = dist;
				m_iWfNextX = cur_pt.wfx;
				m_iWfNextY = cur_pt.wfy;
			}	
		}
	}
	return rtn;
}

//1.���Ϸ�1,2,3...		��������һ��
int CAutoDbWf::GetWorldTopNextDie()
{
	int rtn = 0;
	CPoint pt;
	CRect rect;
	int lx=0,ly=0,rx=0,ry=0;
	CTRealPoint RpCenter(m_iWfCalX,m_iWfCalY);
	CTRealPoint RpTemp;
	double dist1 = 10000000;
	double dist  = 0;

	//ֱ������������Ϊ��׼��������
	//���ϸ���λ��ȷ�����е����ݶ������ģ�����rect������
	if (g_Ins.GetParaF(eCCD_WF,eCAL_RX_DIR) < 0)//ͼ������Ϊ��
	{
		lx = m_iWfCalX + DieDistX/2 + limitX;
		rx = m_iWfCalX - DieDistX/2 + limitX;
		//g_Log.LogArray("�����Ѿ� ͼ������Ϊ�� lx=%d+%d+%d,rx=%d-%d+%d",m_iWfCalX,DieDistX/2,limitX,m_iWfCalX,DieDistX/2,limitX);
	}
	else //ͼ������Ϊ��
	{
		lx = m_iWfCalX - DieDistX/2 + limitX;
		rx = m_iWfCalX + DieDistX/2 + limitX;
		//g_Log.LogArray("�����Ѿ� ͼ������Ϊ�� lx=%d-%d+%d,rx=%d+%d+%d",m_iWfCalX,DieDistX/2,limitX,m_iWfCalX,DieDistX/2,limitX);
	}
	if (g_Ins.GetParaF(eCCD_WF,eCAL_RY_DIR) > 0) //ͼ������Ϊ��
	{
		ly = m_iWfCalY - DieDistY/2 - DieDistY*row + limitY;	
		ry = m_iWfCalY - DieDistY/2 + limitY;
		//g_Log.LogArray("�����Ѿ� ͼ������Ϊ�� lx=%d-%d-%d+%d,rx=%d-%d+%d",m_iWfCalY,DieDistY/2,DieDistY*row,limitY,m_iWfCalY,DieDistY/2 ,limitY);

	}
	else //ͼ������Ϊ��
	{
		ly = m_iWfCalY + DieDistY/2 + DieDistY*row + limitY;	
		ry = m_iWfCalY + DieDistY/2 + limitY;
		//g_Log.LogArray("�����Ѿ� ͼ������Ϊ�� lx=%d+%d+%d+%d,rx=%d+%d+%d",m_iWfCalY,DieDistY/2,DieDistY*row,limitY,m_iWfCalY,DieDistY/2 ,limitY);
	}
	rect.SetRect(lx,ly,rx,ry);
	rect.NormalizeRect();
	rtn = GetWorldRectNearPos(rect);
	//g_Log.LogShow2("�Զ��Ѿ�-���Ϸ���������lx=%d,ly=%d,rx=%d,ry=%d��rect lx=%d,ly=%d,rx=%d,ry=%d"
	//	,lx,ly,rx,ry,rect.TopLeft().x,rect.TopLeft().y,rect.BottomRight().x,rect.BottomRight().y);
	if (rtn) //�ҵ��� --������һ�������
	{
		return rtn;
	}
	return rtn;
}

//�ұ߾��ο�1.2.3...  ���Ϸ��Ŀ�һ����������һ��
int CAutoDbWf::GetWorldTopRightDie()
{
	int rtn = 0;
	CPoint pt;
	CRect rect;
	int lx=0,ly=0,rx=0,ry=0;
	CTRealPoint RpCenter(m_iWfCalX,m_iWfCalY);
	CTRealPoint RpTemp;
	double dist1 = 10000000;
	double dist  = 0;

	//ֱ������������Ϊ��׼��������
	//���ϸ���λ��ȷ�����е����ݶ������ģ�����rect������
	for (int i=0;i<col;i++)
	{
		if (g_Ins.GetParaF(eCCD_WF,eCAL_RX_DIR) < 0) //ͼ������Ϊ��
		{
			lx = m_iWfCalX - DieDistX/2-DieDistX*i + limitX;
			rx = m_iWfCalX - DieDistX/2-DieDistX*(i+1) + limitX;
		//	g_Log.LogArray("�����Ѿ� ͼ������Ϊ�� lx=%d-%d-%d+%d,rx=%d-%d-%d+%d",m_iWfCalX,DieDistX/2,DieDistX*i,limitX,m_iWfCalX,DieDistX/2,DieDistX/(i+1),limitX);
		}
		else //ͼ������Ϊ��
		{
			lx = m_iWfCalX + DieDistX/2+DieDistX*i + limitX;
			rx = m_iWfCalX + DieDistX/2+DieDistX*(i+1) + limitX;
		//	g_Log.LogArray("�����Ѿ� ͼ������Ϊ�� lx=%d+%d+%d+%d,rx=%d+%d+%d+%d",m_iWfCalX,DieDistX/2,DieDistX*i,limitX,m_iWfCalX,DieDistX/2,DieDistX/(i+1),limitX);
		}

		if (g_Ins.GetParaF(eCCD_WF,eCAL_RY_DIR) > 0) //ͼ������Ϊ��
		{
			ly = m_iWfCalY - DieDistY/2 - DieDistY*row + limitY;	
			ry = m_iWfCalY + DieDistY/2 + limitY;
		//	g_Log.LogArray("�����Ѿ� ͼ������Ϊ�� lx=%d-%d-%d+%d,rx=%d+%d+%d",m_iWfCalY,DieDistY/2,DieDistY*row,limitY,m_iWfCalY,DieDistY/2 ,limitY);
		}
		else //ͼ������Ϊ��
		{
			ly = m_iWfCalY + DieDistY/2 + DieDistY*row + limitY;	
			ry = m_iWfCalY - DieDistY/2 + limitY;
			//g_Log.LogArray("�����Ѿ� ͼ������Ϊ�� lx=%d+%d+%d+%d,rx=%d-%d+%d",m_iWfCalY,DieDistY/2,DieDistY*row,limitY,m_iWfCalY,DieDistY/2 ,limitY);
		}
		rect.SetRect(lx,ly,rx,ry);
		rect.NormalizeRect();
		rtn = GetWorldRectNearPos(rect);
		//g_Log.LogShow2("�Զ��Ѿ�-���ϽǾ�������lx=%d,ly=%d,rx=%d,ry=%d��rect lx=%d,ly=%d,rx=%d,ry=%d"
		//	,lx,ly,rx,ry,rect.TopLeft().x,rect.TopLeft().y,rect.BottomRight().x,rect.BottomRight().y);

		if (rtn)  //���Ͻ��ҵ�
		{
			return rtn;
		}
	}
	return rtn;
}

//��߾��ο�1.2.3...  ���Ϸ��Ŀ�һ����������һ��
int CAutoDbWf::GetWorldTopLeftDie()
{
	int rtn = 0;
	CPoint pt;
	CRect rect;
	int lx=0,ly=0,rx=0,ry=0;
	CTRealPoint RpCenter(m_iWfCalX,m_iWfCalY);
	CTRealPoint RpTemp;
	double dist1 = 10000000;
	double dist  = 0;

	//ֱ������������Ϊ��׼��������
	//���ϸ���λ��ȷ�����е����ݶ������ģ�����rect������
	for (int i=0;i<col;i++)
	{
		if (g_Ins.GetParaF(eCCD_WF,eCAL_RX_DIR) < 0)//ͼ������Ϊ��
		{
			lx = m_iWfCalX + DieDistX/2 + DieDistX*(i+1) + limitX;
			rx = m_iWfCalX + DieDistX/2 + DieDistX*i + limitX;
		}
		else //ͼ������Ϊ��
		{
			lx = m_iWfCalX - DieDistX/2-DieDistX*i + limitX;
			rx = m_iWfCalX - DieDistX/2-DieDistX*(i+1) + limitX;
		}

		if (g_Ins.GetParaF(eCCD_WF,eCAL_RY_DIR) > 0) //ͼ������Ϊ��
		{
			ly = m_iWfCalY - DieDistY/2 - DieDistY*row + limitY;	
			ry = m_iWfCalY + DieDistY/2 + limitY;
		//	g_Log.LogArray("�����Ѿ� ͼ������Ϊ�� lx=%d-%d-%d+%d,rx=%d+%d+%d",m_iWfCalY,DieDistY/2,DieDistY*row,limitY,m_iWfCalY,DieDistY/2 ,limitY);
		}
		else //ͼ������Ϊ��
		{
			ly = m_iWfCalY + DieDistY/2 + DieDistY*row + limitY;	
			ry = m_iWfCalY - DieDistY/2 + limitY;
			//g_Log.LogArray("�����Ѿ� ͼ������Ϊ�� lx=%d+%d+%d+%d,rx=%d-%d+%d",m_iWfCalY,DieDistY/2,DieDistY*row,limitY,m_iWfCalY,DieDistY/2 ,limitY);
		}

		rect.SetRect(lx,ly,rx,ry);
		rect.NormalizeRect();
		rtn = GetWorldRectNearPos(rect);
		//g_Log.LogShow2("�Զ��Ѿ�-���ϽǾ�������lx=%d,ly=%d,rx=%d,ry=%d��rect lx=%d,ly=%d,rx=%d,ry=%d"
		//	,lx,ly,rx,ry,rect.TopLeft().x,rect.TopLeft().y,rect.BottomRight().x,rect.BottomRight().y);

		if (rtn)  //���Ͻ��ҵ�
		{	
			return rtn;
		}
	}
	return rtn;
}

//�ұ���һ��			��һ�е��ұ߷���
int CAutoDbWf::GetWorldBottomRightLine()
{
	int rtn = 0;
	CPoint pt;
	CRect rect;
	int lx=0,ly=0,rx=0,ry=0;
	CTRealPoint RpCenter(m_iWfCalX,m_iWfCalY);
	CTRealPoint RpTemp;
	double dist1 = 10000000;
	double dist  = 0;

	//ֱ������������Ϊ��׼��������
	//���ϸ���λ��ȷ�����е����ݶ������ģ�����rect������
	if (g_Ins.GetParaF(eCCD_WF,eCAL_RX_DIR) < 0) //ͼ������Ϊ��
	{
		lx = m_iWfCalX + DieDistX/2 + limitX;
		rx = m_iWfCalX - DieDistX/2 - DieDistX*col + limitX;
	}
	else //ͼ������Ϊ��
	{
		lx = m_iWfCalX - DieDistX/2 + limitX;
		rx = m_iWfCalX + DieDistX/2 + DieDistX*col + limitX;
	}

	if (g_Ins.GetParaF(eCCD_WF,eCAL_RY_DIR) > 0) //ͼ������Ϊ��
	{
		ly = m_iWfCalY + DieDistY/2 + limitY;	
		ry = m_iWfCalY + DieDistY/2*3 + limitY;
	//	g_Log.LogArray("����һ���Ѿ� ͼ������Ϊ�� ly=%d+%d+%d,ry=%d+%d+%d",m_iWfCalY,DieDistY/2,limitY,m_iWfCalY,DieDistY/2*3 ,limitY);
	}
	else //ͼ������Ϊ��
	{
		ly = m_iWfCalY - DieDistY/2 + limitY;	
		ry = m_iWfCalY - DieDistY/2*3 + limitY;
	//	g_Log.LogArray("����һ���Ѿ� ͼ������Ϊ�� lx=%d-%d+%d,rx=%d-%d+%d",m_iWfCalY,DieDistY/2,limitY,m_iWfCalY,DieDistY/2*3,limitY);
	}

	rect.SetRect(lx,ly,rx,ry);
	rect.NormalizeRect();
	rtn = GetWorldRectNearPos(rect);
//	g_Log.LogShow2("�Զ��Ѿ�-�ұ���һ�о�������lx=%d,ly=%d,rx=%d,ry=%d��rect lx=%d,ly=%d,rx=%d,ry=%d"
//		,lx,ly,rx,ry,rect.TopLeft().x,rect.TopLeft().y,rect.BottomRight().x,rect.BottomRight().y);

	if (rtn)  //�ұ���һ���ҵ�
	{
		return rtn;
	}
	return rtn;
}

//�����һ��			��һ�е���߷��� 
int CAutoDbWf::GetWorldBottomLeftLine()
{
	int rtn = 0;
	CPoint pt;
	CRect rect;
	int lx=0,ly=0,rx=0,ry=0;
	CTRealPoint RpCenter(m_iWfCalX,m_iWfCalY);
	CTRealPoint RpTemp;
	double dist1 = 10000000;
	double dist  = 0;

	//ֱ������������Ϊ��׼��������
	//���ϸ���λ��ȷ�����е����ݶ������ģ�����rect������
	if (g_Ins.GetParaF(eCCD_WF,eCAL_RX_DIR) < 0) //ͼ������Ϊ��
	{
		lx = m_iWfCalX - DieDistX/2 + limitX;
		rx = m_iWfCalX + DieDistX/2 + DieDistX*col + limitX;
	}
	else //ͼ������Ϊ��
	{
		lx = m_iWfCalX + DieDistX/2 + limitX;
		rx = m_iWfCalX - DieDistX/2 - DieDistX*col + limitX;
	}

	if (g_Ins.GetParaF(eCCD_WF,eCAL_RY_DIR) > 0) //ͼ������Ϊ��
	{
		ly = m_iWfCalY + DieDistY/2 + limitY;	
		ry = m_iWfCalY + DieDistY/2*3 + limitY;
	//	g_Log.LogArray("����һ���Ѿ� ͼ������Ϊ�� ly=%d+%d+%d,ry=%d+%d+%d",m_iWfCalY,DieDistY/2,limitY,m_iWfCalY,DieDistY/2*3 ,limitY);
	}
	else //ͼ������Ϊ��
	{
		ly = m_iWfCalY - DieDistY/2 + limitY;	
		ry = m_iWfCalY - DieDistY/2*3 + limitY;
	//	g_Log.LogArray("����һ���Ѿ� ͼ������Ϊ�� lx=%d-%d+%d,rx=%d-%d+%d",m_iWfCalY,DieDistY/2,limitY,m_iWfCalY,DieDistY/2*3,limitY);
	}
	rect.SetRect(lx,ly,rx,ry);
	rect.NormalizeRect();
	rtn = GetWorldRectNearPos(rect);
	//g_Log.LogShow2("�Զ��Ѿ�-�����һ�о�������lx=%d,ly=%d,rx=%d,ry=%d��rect lx=%d,ly=%d,rx=%d,ry=%d"
	//	,lx,ly,rx,ry,rect.TopLeft().x,rect.TopLeft().y,rect.BottomRight().x,rect.BottomRight().y);
	if (rtn)  //�����һ���ҵ�
	{
		return rtn;
	}
	return rtn;
}

int CAutoDbWf::GetWorldListDie()
{
	int rtn = 0;
	WFMapPos  cur_pt;
	CPoint pt;
	CRect rect;
	int lx=0,ly=0,rx=0,ry=0;
	CTRealPoint RpCenter(m_iWfCalX,m_iWfCalY);
	CTRealPoint RpTemp;
	double dist1 = 10000000;
	double dist  = 0;

	//6.�������			�Զ��ж��л�����

	int curPosX = WFX->GetPos();
	int curPosY = WFY->GetPos();
	RpCenter.Set(curPosX,curPosY);
	double dist2 = 100000000;
	for (POSITION pos = m_MapPosList.GetHeadPosition();pos;m_MapPosList.GetNext(pos))
	{
		cur_pt = m_MapPosList.GetAt(pos);
		if (cur_pt.flag == 1) //ֻ�ڿ��õ��������ж�
		{
			RpTemp.Set(cur_pt.wfx,cur_pt.wfy); 
			dist = RpCenter.CalDist(RpTemp);			
			if (dist < dist2)
			{
				rtn = 1;
				dist2 = dist;
				m_iWfNextX = cur_pt.wfx;
				m_iWfNextY = cur_pt.wfy;
			}	
		}
	}
	return rtn;
}

//�����ͼ�Ѿ� --  ���Լ�¼��ÿ����Ƭ��״̬������˵�����޻���ʶ��NG���´ξͲ�ȥ��
//1..1,2,3...		    ��������һ��
//2.�ұ߾��ο�1.2.3...  ���Ϸ��Ŀ�һ����������һ��
//3.�ұ���һ��			��һ�е��ұ߷���
//4.��߾��ο�1.2.3...  �л�����
//5.�����һ��			��һ�е���߷��� �л�����
//6.�������			�Զ��ж��л�����
int CAutoDbWf::GetWorldNextDie()  //�������������Ѿ�ģʽ
{
	int rtn = 0;
	int searchMode = g_MachDat.GetPara(MACH_WF_SRH_MODE);

	DieDistX = g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_X); //������
	DieDistY = g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_Y);
	//g_Log.LogArray("������ DieDistX = %.f,DieDistY = %.f",DieDistX,DieDistY);

	ImgDistX = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_X);
	ImgDistY = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_Y);
	//g_Log.LogArray("���ؼ�� ImgDistX = %.f,ImgDistY = %.f",ImgDistX,ImgDistY);

	//��������Ͻ��ж�����
	col = fabs((g_Ins.GetPara(eCCD_WF,ePR_PT,eROIWIDTH)-ImgDistX)/2/ImgDistX)+1;
//	g_Log.LogArray("col = (%d-%.f/2/%.f=%d",g_Ins.GetPara(eCCD_WF,ePR_PT,eROIWIDTH),ImgDistX,ImgDistX,col);
	row = fabs((g_Ins.GetPara(eCCD_WF,ePR_PT,eROIHEIGHT)-ImgDistY)/2/ImgDistY)+1;
//	g_Log.LogArray("row = (%d-%.f/2/%.f=%d",g_Ins.GetPara(eCCD_WF,ePR_PT,eROIHEIGHT),DieDistY,DieDistY,row);

	//�������������е������
	WFMapPos cur_pt;
//	g_Log.LogArray("��¼���������������");
	//int i=1;
	//for (POSITION pos = m_MapPosList.GetHeadPosition();pos;m_MapPosList.GetNext(pos))
	//{
	//	cur_pt = m_MapPosList.GetAt(pos);
	////	g_Log.LogArray("��%2d�㣬���=%d,x=%6d,y=%6d",i++,cur_pt.flag,cur_pt.wfx+limitX,cur_pt.wfy+limitY);
	//}
	
	
	if (searchMode == 2)
	{
		rtn = GetWorldTopNextDie();
		if (rtn)
		{
			g_Log.LogShow2("�����Ѿ� --OK");
		}
		else
		{
			g_Log.LogShow2("�����Ѿ� --NG");
		}
		return rtn;
	}
	else if  (searchMode == 3)
	{
		rtn = GetWorldTopRightDie();
		if (rtn)
		{
			g_Log.LogShow2("�����Ѿ� --OK");
		}
		else
		{
			g_Log.LogShow2("�����Ѿ� --NG");
		}
		return rtn;
	}
	else if  (searchMode == 4)
	{
		rtn = GetWorldTopLeftDie();
		if (rtn)
		{
			g_Log.LogShow2("�����Ѿ� --OK");
		}
		else
		{
			g_Log.LogShow2("�����Ѿ� --NG");
		}
		return rtn;
	}
	else if  (searchMode == 5)
	{
		rtn = GetWorldBottomRightLine();
		if (rtn)
		{
			g_Log.LogShow2("����һ���Ѿ� --OK");
		}
		else
		{
			g_Log.LogShow2("����һ���Ѿ� --NG");
		}
		return rtn;
	}
	else if  (searchMode == 6)
	{
		rtn = GetWorldBottomLeftLine();
		if (rtn)
		{
			g_Log.LogShow2("����һ���Ѿ� --OK");
		}
		else
		{
			g_Log.LogShow2("����һ���Ѿ� --NG");
		}
		return rtn;
	}
	else if  (searchMode == 7)
	{
		rtn = GetWorldListDie();
		if (rtn)
		{
			g_Log.LogShow2("�����Ѿ� --OK");
		}
		else
		{
			g_Log.LogShow2("�����Ѿ� --NG");
		}
		return rtn;
	}


	rtn = GetWorldTopNextDie();
	if (rtn) //�ҵ��� --������һ�������
	{
	//	g_Log.LogShow2("�Զ��Ѿ�-1.���Ϸ��ҵ�оƬ����������x=%d,y=%d",m_iWfPosX,m_iWfPosY);
		return rtn;
	}

	if (m_SearchDirX == 1) 
	{
		rtn = GetWorldTopRightDie();
		if (rtn)  //���Ͻ��ҵ�
		{
		//	g_Log.LogShow2("�Զ��Ѿ�-2.���Ͻ��ҵ�оƬ");
			return rtn;
		}
		rtn = GetWorldTopLeftDie();
		if (rtn)  //���Ͻ��ҵ�
		{
			m_SearchDirX = -1;
		//	g_Log.LogShow2("�Զ��Ѿ�-3.���Ͻ�%d�ҵ�оƬ");
			return rtn;
		}
		rtn = GetWorldBottomRightLine();
		if (rtn)  //�ұ���һ���ҵ�
		{
		//	g_Log.LogShow2("�Զ��Ѿ�-4.�ұ���һ���ҵ�оƬ");
			return rtn;
		}
		rtn = GetWorldTopLeftDie();
		if (rtn)  //�����һ���ҵ�
		{
			m_SearchDirX = -1;
		//	g_Log.LogShow2("�Զ��Ѿ�-5.�����һ���ҵ�оƬ");
			return rtn;
		}
	}
	else
	{
		rtn = GetWorldTopLeftDie();
		if (rtn)  //���Ͻ��ҵ�
		{		
		//	g_Log.LogShow2("�Զ��Ѿ�-12.���Ͻ�%d�ҵ�оƬ");
			return rtn;
		}
		rtn = GetWorldTopRightDie();
		if (rtn)  //���Ͻ��ҵ�
		{
			m_SearchDirX = 1;
		//	g_Log.LogShow2("�Զ��Ѿ�-13.���Ͻ��ҵ�оƬ");
			return rtn;
		}
		rtn = GetWorldBottomLeftLine();
		if (rtn)  //�����һ���ҵ�
		{
		//	g_Log.LogShow2("�Զ��Ѿ�-14.�����һ���ҵ�оƬ");
			return rtn;
		}
		rtn = GetWorldBottomRightLine();
		if (rtn)  //�ұ���һ���ҵ�
		{
			m_SearchDirX = 1;
		//	g_Log.LogShow2("�Զ��Ѿ�-15.�ұ���һ���ҵ�оƬ");
			return rtn;
		}
	}

	rtn = GetWorldListDie();
	int curPosX = WFX->GetPos();
	int curPosY = WFY->GetPos();
	if (rtn)
	{
		if (g_Ins.GetParaF(eCCD_WF,eCAL_RX_DIR) > 0) //ͼ������Ϊ��
		{
			if (m_iWfPosX < curPosX) //�����С�ڵ�ǰ�㣬˵������
			{
				m_SearchDirX = 1;
			}
			else
			{
				m_SearchDirX = -1;
			}
		}
		else //ͼ������Ϊ��
		{
			if (m_iWfPosX < curPosX) //�����С�ڵ�ǰ�㣬˵������
			{
				m_SearchDirX = -1;
			}
			else
			{
				m_SearchDirX = 1;
			}
		}

	//	g_Log.LogShow2("�Զ��Ѿ�-20.�������ҵ�оƬ");
		return rtn;
	}
	//ͼ��������϶�û�ҵ������أ�
	g_Log.LogShow2("û���ҵ�оƬ");
	return rtn;
}

int CAutoDbWf::AddWFPos(int flag,int x,int y)
{
	if (CheckLimit(x,y) == 0)
	{
		return 0;
	}
	WFMapPos  cur_pt;
	if (m_MapPosList.IsEmpty())
	{
		cur_pt.flag = flag;
		cur_pt.wfx = x;
		cur_pt.wfy = y;
		m_MapPosList.AddHead(cur_pt);
		return 1;
	}

	CPoint pt(x+limitX,y+limitY);

	double DieDistX = g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_X); //���嵥λ
	double DieDistY = g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_Y);

	CRect rect;
	int lx=0,ly=0,rx=0,ry=0;
	BOOL bExist =FALSE;
	for (POSITION pos = m_MapPosList.GetHeadPosition();pos;m_MapPosList.GetNext(pos))
	{
		cur_pt = m_MapPosList.GetAt(pos);
		
		lx = cur_pt.wfx - DieDistX/2+limitX;
		ly = cur_pt.wfy - DieDistY/2+limitY;
		rx = cur_pt.wfx + DieDistX/2+limitX;
		ry = cur_pt.wfy + DieDistY/2+limitY;
		rect.SetRect(lx,ly,rx,ry);
		if (rect.PtInRect(pt)) //��ǰ���Ѿ����������ˣ�����
		{
			bExist = TRUE;
			//cur_pt.flag = flag;  //����Ѿ����ڣ���Ϊ1����ôֻ��������
			cur_pt.wfx = x;
			cur_pt.wfy = y;
			m_MapPosList.SetAt(pos,cur_pt);
			break;
		}
	}
	if (!bExist)
	{
		cur_pt.flag = flag;
		cur_pt.wfx = x;
		cur_pt.wfy = y;
		m_MapPosList.AddHead(cur_pt);
	}
	return 1;
}

int CAutoDbWf::GetWorldRectDie(CRect rt) //�ж�������ο����Ƿ��о�Ƭ
{
	int rtn = 0;
	CTRealPoint RpTemp;
	CPoint pt;
	WFMapPos cur_pt;
	for (POSITION pos = m_MapPosList.GetHeadPosition(); pos; m_MapPosList.GetNext(pos))
	{
		cur_pt = m_MapPosList.GetAt(pos);
		if (cur_pt.flag != 1)
		{
			continue;
		}
		pt.x = cur_pt.wfx + limitX;
		pt.y = cur_pt.wfy + limitY;
		RpTemp.Set(cur_pt.wfx, cur_pt.wfy);
		if (rt.PtInRect(pt))
		{
			rtn = 1;
			m_iWfNextX = cur_pt.wfx;
			m_iWfNextY = cur_pt.wfy;
		}
	}
	return rtn;
}

int CAutoDbWf::GetWorldDirDie(int XNum, int YNum)
{
	int rtn = 0;
	CPoint pt;
	CRect rect;
	int lx = 0, ly = 0, rx = 0, ry = 0;

	//ֱ������������Ϊ��׼��������
	//���ϸ���λ��ȷ�����е����ݶ������ģ�����rect������
	if (g_Ins.GetParaF(eCCD_WF, eCAL_RX_DIR) < 0)//ͼ������Ϊ��
	{
		lx = m_iWfCalX + DieDistX / 2 + limitX - DieDistX * XNum;
		rx = m_iWfCalX - DieDistX / 2 + limitX - DieDistX * XNum;
		//g_Log.LogArray("�����Ѿ� ͼ������Ϊ�� lx=%d+%d+%d,rx=%d-%d+%d",m_iWfCalX,DieDistX/2,limitX,m_iWfCalX,DieDistX/2,limitX);
	}
	else //ͼ������Ϊ��
	{
		lx = m_iWfCalX - DieDistX / 2 + limitX + DieDistX * XNum;
		rx = m_iWfCalX + DieDistX / 2 + limitX + DieDistX * XNum;
		//g_Log.LogArray("�����Ѿ� ͼ������Ϊ�� lx=%d-%d+%d,rx=%d+%d+%d",m_iWfCalX,DieDistX/2,limitX,m_iWfCalX,DieDistX/2,limitX);
	}
	if (g_Ins.GetParaF(eCCD_WF, eCAL_RY_DIR) > 0) //ͼ������Ϊ��
	{
		ly = m_iWfCalY + DieDistY / 2 + limitY - DieDistY * YNum;
		ry = m_iWfCalY - DieDistY / 2 + limitY - DieDistY * YNum;
		//g_Log.LogArray("�����Ѿ� ͼ������Ϊ�� lx=%d-%d-%d+%d,rx=%d-%d+%d",m_iWfCalY,DieDistY/2,DieDistY*row,limitY,m_iWfCalY,DieDistY/2 ,limitY);

	}
	else //ͼ������Ϊ��
	{
		ly = m_iWfCalY - DieDistY / 2 + limitY + DieDistY * YNum;
		ry = m_iWfCalY + DieDistY / 2 + limitY + DieDistY * YNum;
		//g_Log.LogArray("�����Ѿ� ͼ������Ϊ�� lx=%d+%d+%d+%d,rx=%d+%d+%d",m_iWfCalY,DieDistY/2,DieDistY*row,limitY,m_iWfCalY,DieDistY/2 ,limitY);
	}
	rect.SetRect(lx, ly, rx, ry);
	rect.NormalizeRect();

	rtn = GetWorldRectDie(rect);
	return rtn;
}

//�����ͼ�Ѿ� --  ���Լ�¼��ÿ����Ƭ��״̬������˵�����޻���ʶ��NG���´ξͲ�ȥ��
//1..1,2,3...		    ��������һ��
//2.�ұ߾��ο�1.2.3...  ���Ϸ��Ŀ�һ����������һ��
//3.�ұ���һ��			��һ�е��ұ߷���
//4.��߾��ο�1.2.3...  �л�����
//5.�����һ��			��һ�е���߷��� �л�����
//6.�������			�Զ��ж��л�����
int CAutoDbWf::GetWorldDirNextDie()
{
	int rtn = 0;
	int searchMode = g_MachDat.GetPara(MACH_WF_SRH_MODE);

	if (searchMode == 2)
	{
		//�������������е������
		WFMapPos cur_pt;
		//g_Log.LogArray("��¼���������������");
		int i = 1;
		//for (POSITION pos = m_MapPosList.GetHeadPosition(); pos; m_MapPosList.GetNext(pos))
		//{
		//	cur_pt = m_MapPosList.GetAt(pos);
		//	g_Log.LogArray("��%2d�㣬���=%d,x=%6d,y=%6d",i++,cur_pt.flag,cur_pt.wfx+limitX,cur_pt.wfy+limitY);
		//}

		rtn = GetWorldListDie();
		int curPosX = WFX->GetPos();
		int curPosY = WFY->GetPos();
		if (rtn)
		{
			g_Log.LogShow("�������ҵ�оƬ");
			if (g_Ins.GetParaF(eCCD_WF, eCAL_RX_DIR) > 0) //ͼ������Ϊ��
			{
				if (m_iWfPosX < curPosX) //�����С�ڵ�ǰ�㣬˵������
				{
					m_SearchDirX = 1;
				}
				else
				{
					m_SearchDirX = -1;
				}
			}
			else //ͼ������Ϊ��
			{
				if (m_iWfPosX < curPosX) //�����С�ڵ�ǰ�㣬˵������
				{
					m_SearchDirX = -1;
				}
				else
				{
					m_SearchDirX = 1;
				}
			}
		}
		else
		{
			g_Log.LogShow("������û���ҵ�оƬ");
		}	
		return rtn;
	}

	DieDistX = g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_X); //������
	DieDistY = g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_Y);
//	g_Log.LogArray("������ DieDistX = %.f,DieDistY = %.f",DieDistX,DieDistY);

	ImgDistX = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_X);
	ImgDistY = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_Y);
//	g_Log.LogArray("���ؼ�� ImgDistX = %.f,ImgDistY = %.f",ImgDistX,ImgDistY);

	//��������Ͻ��ж�����
	col = fabs((g_Ins.GetPara(eCCD_WF, ePR_PT, eROIWIDTH) - ImgDistX) / 2 / ImgDistX)+1;
	//	g_Log.LogArray("col = (%d-%.f/2/%.f=%d",g_Ins.GetPara(eCCD_WF,ePR_PT,eROIWIDTH),ImgDistX,ImgDistX,col);
	row = fabs((g_Ins.GetPara(eCCD_WF, ePR_PT, eROIHEIGHT) - ImgDistY) / 2 / ImgDistY)+1;
	//g_Log.LogArray("row = %d,col = %d", row, col);
	for (int i=0;i<row;i++)
	{
		rtn = GetWorldDirDie(0,i+1);
		if (rtn)
		{
			//g_Log.LogShow2("���Ϸ���%d���ҵ�оƬ",i+1);
			return rtn;
		}		
	}
	//g_Log.LogShow2("���Ϸ�û���ҵ�оƬ");

	if (m_SearchDirX == 1) //�����Ѿ�
	{
		//��ǰ��
		for (int i = 0; i < row; i++)
		{			
			rtn = GetWorldDirDie(i + 1, 0);
			if (rtn)
			{
				//g_Log.LogShow2("�����Ѿ���%d���ҵ�оƬ", i + 1);
				return rtn;
			}
		}
		//g_Log.LogShow2("�����Ѿ�û���ҵ�оƬ");

		//��һ��
		for (int i = 0; i < row; i++)
		{			
			rtn = GetWorldDirDie(i + 1, 1);
			if (rtn)
			{
				//g_Log.LogShow2("������һ���Ѿ���%d���ҵ�оƬ", i + 1);
				return rtn;
			}
		}
	//	g_Log.LogShow2("������һ���Ѿ�û���ҵ�оƬ");

		//���·�
		rtn = GetWorldDirDie(0, -1);
		if (rtn)
		{
			m_SearchDirX = -1;
			//g_Log.LogShow2("���·��ҵ�оƬ");
			return rtn;
		}
		//g_Log.LogShow2("���·���û���ҵ�оƬ");
		//��һ��
		for (int i = 0; i < row; i++)
		{
			rtn = GetWorldDirDie(i + 1, -1);
			if (rtn)
			{
				//g_Log.LogShow2("������һ���Ѿ���%d���ҵ�оƬ", i + 1);
				return rtn;
			}
		}
		//g_Log.LogShow2("������һ��û���ҵ�оƬ");


		if (rtn == 0)
		{
			
			//��ǰ��
			for (int i = 0; i < row; i++)
			{			
				rtn = GetWorldDirDie(-1 * i - 1, 0);
				if (rtn)
				{
					m_SearchDirX = -1;
					//g_Log.LogShow2("�����Ѿ���%d���ҵ�оƬ", i + 1);
					return rtn;
				}
			}
			//g_Log.LogShow2("�����Ѿ�û���ҵ�оƬ");
			//��һ��
			for (int i = 0; i < row; i++)
			{
				rtn = GetWorldDirDie(-1 * i - 1, 1);
				if (rtn)
				{
					m_SearchDirX = -1;
					//g_Log.LogShow2("������һ���Ѿ���%d���ҵ�оƬ", i + 1);
					return rtn;
				}
			}
			//g_Log.LogShow2("������һ���Ѿ�û���ҵ�оƬ");
			//��һ��
			for (int i = 0; i < row; i++)
			{
				rtn = GetWorldDirDie(-1 * i - 1, -1);
				if (rtn)
				{
					m_SearchDirX = -1;
					//g_Log.LogShow2("������һ���Ѿ���%d���ҵ�оƬ", i + 1);
					return rtn;
				}
			}
			//g_Log.LogShow2("������һ���Ѿ�û���ҵ�оƬ");
		}
	}
	else //�����Ѿ�
	{
		//��ǰ��
		for (int i = 0; i < row; i++)
		{
			rtn = GetWorldDirDie(-1 * i - 1, 0);
			if (rtn)
			{
				//g_Log.LogShow2("�����Ѿ���%d���ҵ�оƬ", i + 1);
				return rtn;
			}
		}
		//g_Log.LogShow2("�����Ѿ�û���ҵ�оƬ");
		//��һ��
		for (int i = 0; i < row; i++)
		{
			rtn = GetWorldDirDie(-1 * i - 1, 1);
			if (rtn)
			{
				//g_Log.LogShow2("������һ���Ѿ���%d���ҵ�оƬ", i + 1);
				return rtn;
			}
		}
		//g_Log.LogShow2("������һ��û���ҵ�оƬ");
		//���·�
		rtn = GetWorldDirDie(0, -1);
		if (rtn)
		{
			m_SearchDirX = 1;
			//g_Log.LogShow2("���·��ҵ�оƬ");
			return rtn;
		}
		//g_Log.LogShow2("���·�û���ҵ�оƬ");
		//��һ��
		for (int i = 0; i < row; i++)
		{
			rtn = GetWorldDirDie(-1 * i - 1, -1);
			if (rtn)
			{
				//g_Log.LogShow2("������һ���Ѿ���%d���ҵ�оƬ", i + 1);
				return rtn;
			}
		}
		//g_Log.LogShow2("������һ���Ѿ�û���ҵ�оƬ");
		//��ǰ��
		for (int i = 0; i < row; i++)
		{
			rtn = GetWorldDirDie(i + 1, 0);
			if (rtn)
			{
				m_SearchDirX = 1;
				//g_Log.LogShow2("�����Ѿ���%d���ҵ�оƬ", i + 1);
				return rtn;
			}
		}
		//g_Log.LogShow2("�����Ѿ�û���ҵ�оƬ");
		//��һ��
		for (int i = 0; i < row; i++)
		{
			rtn = GetWorldDirDie(i + 1, 1);
			if (rtn)
			{
				m_SearchDirX = 1;
				//g_Log.LogShow2("������һ���Ѿ���%d���ҵ�оƬ", i + 1);
				return rtn;
			}
		}
		//g_Log.LogShow2("������һ���Ѿ�û���ҵ�оƬ");
		//��һ��
		for (int i = 0; i < row; i++)
		{
			rtn = GetWorldDirDie(i + 1, -1);
			if (rtn)
			{
				m_SearchDirX = 1;
				//g_Log.LogShow2("������һ���Ѿ���%d���ҵ�оƬ", i + 1);
				return rtn;
			}
		}
		//g_Log.LogShow2("������һ���Ѿ�û���ҵ�оƬ");
	}



	//�������������е������
	WFMapPos cur_pt;
	g_Log.LogArray("��¼���������������");
	int i = 1;
	for (POSITION pos = m_MapPosList.GetHeadPosition(); pos; m_MapPosList.GetNext(pos))
	{
		cur_pt = m_MapPosList.GetAt(pos);
		//g_Log.LogArray("��%2d�㣬���=%d,x=%6d,y=%6d", i++, cur_pt.flag, cur_pt.wfx + limitX, cur_pt.wfy + limitY);
	}

	rtn = GetWorldListDie();
	int curPosX = WFX->GetPos();
	int curPosY = WFY->GetPos();
	if (rtn)
	{
		//g_Log.LogShow2("�������ҵ�оƬ");
		if (g_Ins.GetParaF(eCCD_WF, eCAL_RX_DIR) > 0) //ͼ������Ϊ��
		{
			if (m_iWfNextX < curPosX) //�����С�ڵ�ǰ�㣬˵������
			{
				m_SearchDirX = 1;
			}
			else
			{
				m_SearchDirX = -1;
			}
		}
		else //ͼ������Ϊ��
		{
			if (m_iWfNextX < curPosX) //�����С�ڵ�ǰ�㣬˵������
			{
				m_SearchDirX = -1;
			}
			else
			{
				m_SearchDirX = 1;
			}
		}
		return rtn;
	}
	else
	{
		//ͼ��������϶�û�ҵ������أ�
		g_Log.LogShow2("û���ҵ�оƬ");
	}

	return 0;
}

//Ѱ���Ѿ���㣬�ȵ����Ϸ����ٵ������
int CAutoDbWf::GetWorldSearchStart()
{
	int rtn = 0;

	DieDistX = g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_X); //������
	DieDistY = g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_Y);
	//g_Log.LogArray("������ DieDistX = %.f,DieDistY = %.f",DieDistX,DieDistY);

	ImgDistX = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_X);
	ImgDistY = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_Y);
	//g_Log.LogArray("���ؼ�� ImgDistX = %.f,ImgDistY = %.f",ImgDistX,ImgDistY);

	//��������Ͻ��ж�����
	col = fabs((g_Ins.GetPara(eCCD_WF, ePR_PT, eROIWIDTH) - ImgDistX) / 2 / ImgDistX);
	//	g_Log.LogArray("col = (%d-%.f/2/%.f=%d",g_Ins.GetPara(eCCD_WF,ePR_PT,eROIWIDTH),ImgDistX,ImgDistX,col);
	row = fabs((g_Ins.GetPara(eCCD_WF, ePR_PT, eROIHEIGHT) - ImgDistY) / 2 / ImgDistY);


	for (int i = row; i >= 0; i--)
	{
		rtn = GetWorldDirDie(0, i + 1);
		if (rtn)
		{
			g_Log.LogShow2("���Ϸ���%d���ҵ�оƬ", i + 1);
			return rtn;
		}
	}

	for (int i=0;i<col;i++)
	{
		for (int j=row;j>=0;j--)
		{
			rtn = GetWorldDirDie(j, i + 1);
			g_Log.LogShow2("�Ϸ���%d���ҵ�оƬ", i + 1);
			return rtn;
		}
	}

	//��ǰ��
	for (int i = row -1 ; i >= 0; i--)
	{
		rtn = GetWorldDirDie(-1 * i - 1, 0);
		if (rtn)
		{
			m_SearchDirX = -1;
			g_Log.LogShow2("�����Ѿ���%d���ҵ�оƬ", i + 1);
			return rtn;
		}
	}

	return 0;
}


void CAutoDbWf::AddAllWFPos()
{
	int centPosX = WFX->GetPos();
	int centPosY = WFY->GetPos();

	//g_Log.LogArray("�������ʱ��������x=%d,y=%d",centPosX,centPosY);
	int pulseX=0,pulseY=0;
	double offx,offy;
	for (int i=0;i<m_Num;i++)
	{
		offx = m_Posx[i]-(CCD_W/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFX));
		offy = m_Posy[i]-(CCD_H/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY));
		//if (g_MachDat.GetPara(MACH_WF_SRH_MODE) == 1) //��ͼ�����Ѿ������м���Ǹ�����ӵ����������´��ֹ���һ��
		//{
		//	//�����ĵ��Ǹ�����ӵ�������
		//	if (offx < g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_X) && offy < g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_Y))
		//	{
		//		continue;
		//	}
		//}

		PixToPulse(offx,offy,pulseX,pulseY);
		//g_Log.LogArray("�������%d,����ƫ��x=%.2f,y=%.2f,����ƫ��x=%d,y=%d",i+1,offx,offy,pulseX,pulseY);
		pulseX += centPosX;
		pulseY += centPosY;		
		if (CheckLimit(pulseX,pulseY))
		{
			AddWFPos(1,pulseX,pulseY);
		}
		else
		{
			g_Log.LogShow2("���������������λ ���=%d������x=%d,y=%d",i,pulseX,pulseY);
		}	
	}
}

int CAutoDbWf::CheckLimit(int x,int y)
{
	double cx = g_MachDat.GetParaF(PROG_F_WF_CEN_X);
	double cy = g_MachDat.GetParaF(PROG_F_WF_CEN_Y);
	double  r = g_MachDat.GetParaF(PROG_F_WF_CEN_R);

	double dx = x-cx;
	double dy = y-cy;
	double dr = sqrt(dx*dx+dy*dy);
	if (dr < r)
	{
		return 1;
	}
	return 0;
}

int CAutoDbWf::SetPickDieFlag(int flag,int wfx,int wfy, int Remove)
{
	WFMapPos  cur_pt;
	CPoint pt;
	CRect rt;
	int lx=0,ly=0,rx=0,ry=0;
	double dDieDistX = g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_X);
	double dDieDistY = g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_Y);

	pt.x = wfx+limitX;
	pt.y = wfy+limitY;

	for (POSITION pos = m_MapPosList.GetHeadPosition();pos;m_MapPosList.GetNext(pos))
	{
		cur_pt = m_MapPosList.GetAt(pos);
		lx = cur_pt.wfx - dDieDistX/2 + limitX;
		ly = cur_pt.wfy - dDieDistY/2 + limitY;
		rx = cur_pt.wfx + dDieDistX/2+ limitX;
		ry = cur_pt.wfy + dDieDistY/2+ limitY;
		rt.SetRect(lx,ly,rx,ry);
		rt.NormalizeRect();
		if (rt.PtInRect(pt))
		{
			cur_pt.wfx = wfx;
			cur_pt.wfy = wfy;
			cur_pt.flag = flag;
			m_MapPosList.SetAt(pos,cur_pt);
			if (flag == 2 && Remove) //ץȡ����Ҫ�ڿ���������ɾ��
			{
				m_MapPosList.RemoveAt(pos);		
			}
			break;
		}
	}
	return 1;
}

void CAutoDbWf::Reset()
{
	m_SearchDirX = 1;
	m_MapPosList.RemoveAll();

	limitX = WFX->GetLimitN() * (-1) + 10 * g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_X);
	limitY = WFY->GetLimitN() * (-1) + 10 * g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_Y);
}

void CAutoDbWf::ShowWfImage()
{
	::PostMessage(gDlgMainBondWnd->GetSafeHwnd(), WM_USR_UPATE_CCD_WF,0,0);
}


int CAutoDbWf::Step()
{
	int rt = 1;
	switch (m_step)
	{
	case 0:
		{
			if (g_AllFlag.m_bStop)
			{
				SetNextStep(9999);
				break;
			}
			g_AllFlag.m_bWFDieReady = FALSE;
			if (g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_X) <=10 || g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_Y)<=10  )
			{
				g_AllFlag.m_bStop = TRUE;
				g_UserMsgBox.ShowUserMsgBox("��Ƭ��಻��ȷ�����������þ�Ƭ���",OK_RED);
				SetNextStep(9999);
				break;
			}
			SetNextStep(50);
		}
		break;

	case 50:
		{
			if (g_AllFlag.m_bSingleWfSerach)
			{
				SetNextStep(100);
				break;
			}
			if (g_AllFlag.m_bSingleWfNextDie)
			{
				if (m_MapPosList.IsEmpty()) //�����ǿյģ�Ҫ��������ʶ��
				{
					SetNextStep(100);
					break;
				}
				else  //ֱ��ȥ��һλ��
				{
					SetNextStep(200);
					break;
				}
			}
			if (g_MachDat.GetPara(MACH_WF_SRH_MODE) == 0)
			{
				SetNextStep(9999);
				break;
			}
			SetNextStep(100);
		}
		break;

	case 100: //��һ��
		{
			Reset();
		//	g_Log.LogShow2("��һ������ʱԭʼλ��x=%d,y=%d",WFX->GetPos(),WFY->GetPos());
			SleepExms(g_MachDat.GetPara(MACH_WF_CCD_DELAY));
			g_Ins.SoftTrig(eCCD_WF);
			int time = g_Ins.WaitImageOk(eCCD_WF);
			if (time > 80)
			{
				g_Log.LogArray("WF case 100 ͼ����=%d", time);
			}
			g_Ins.DoSerach(eCCD_WF,ePR_PT);
			g_Ins.GetResult(eCCD_WF, ePR_PT,&m_Num,m_Score, m_Posx, m_Posy,m_Angle, &m_Time);
			if (m_Time > 100)
			{
				g_Log.LogArray("WF case 100 ʶ��ʱ��=%.1f",m_Time);
			}
			ShowWfImage();
			if (m_Num >= 1)
			{
				AddAllWFPos();
				if (GetImgNearPos()) //��ȡ��������
				{
					PixToPulse(m_dCentPixX,m_dCentPixY,m_iCentPulseX,m_iCentPulseY);
					//g_Log.LogArray("���ĵ�ƫ������x=%.1f,y=%.1f,����x=%d,y=%d",m_dCentPixX,m_dCentPixY,m_iCentPulseX,m_iCentPulseY);
					m_iWfPosX = WFX->GetPos() + m_iCentPulseX;
					m_iWfPosY = WFY->GetPos() + m_iCentPulseY;
					m_iWfNextX = m_iWfPosX ;
					m_iWfNextY = m_iWfPosY;
					//g_Log.LogShow2("��һ�����պ����λ��x:%d+%d,y:%d+%d��",WFX->GetPos(),m_iCentPulseX,WFY->GetPos(),m_iCentPulseY);
					SetNextStep(300);
					break;
				}
			}
			g_AllFlag.m_bStop = TRUE;
			g_UserMsgBox.ShowUserMsgBox("û���ҵ���Ƭ, ��ȷ����Ƭ�����Ƿ���ȷ",OK_RED);
			SetNextStep(9999);
		}
		break;

	case 200:  //��ȡ��һ��
		{
			if (g_AllFlag.m_bStop||(g_AllFlag.m_bSingleAutoBd && g_AllFlag.m_bBdOk))
			{
				SetNextStep(9999);
				break;
			}
			//g_Log.LogShow2("��оƬ֮ǰ����x=%d,y=%d",WFX->GetPos(),WFY->GetPos());
			int rtn = GetNextDiePos();
			//g_Log.LogShow2("%d = GetNextDiePos()", rtn);
			if (rtn == 0)
			{
				g_AllFlag.m_bStop = TRUE;
				if (g_AllFlag.m_bSingleWfSerachStart)
				{
					g_UserMsgBox.ShowUserMsgBox("��Ƭ���������!",OK_YEW);
					SetNextStep(9999);
					break;
				}
				g_Ins.SoftTrig(eCCD_WF);
				g_Ins.DoSerach(eCCD_WF, ePR_PT);
				ShowWfImage();
				g_UserMsgBox.ShowUserMsgBox("��Ƭ���ҽ������������Բ��",OK_RED);
				SetNextStep(9999);
				break;
			}
			SetNextStep(300);
		}
		break;

	case 300: //�жϵ�ǰ���Ƿ���Բ��
		{
			if (CheckLimit(m_iWfNextX, m_iWfNextY)) //��Բ��
			{
				SetNextStep(400);
				break;
			}
			else
			{
				g_Log.LogShow("��Բ̨����x:%d,y:%d��������", m_iWfNextX, m_iWfNextY);
				SetPickDieFlag(3,m_iWfPosX,m_iWfPosY);
				SetNextStep(200); //ȥ��һ��
				break;
			}
		}
		break;

	case 400:  //��һ�㵽ͼ����������У��
		{
			m_iWfPosX = m_iWfNextX;
			m_iWfPosY = m_iWfNextY;
			//g_Log.LogShow2("У��ʱλ��x=%d,y=%d",m_iWfPosX,m_iWfPosY);
			WFX->MoveAbs(m_iWfPosX);
			WFY->MoveAbs(m_iWfPosY);
			WaitStopMtr(WFX,1,FALSE);
			WaitStopMtr(WFY,1,FALSE);
			SleepExms(g_MachDat.GetPara(MACH_WF_CCD_DELAY));
			if (FALSE == g_Ins.SoftTrig(eCCD_WF))
			{
				g_AllFlag.m_bStop = TRUE;
				g_UserMsgBox.ShowUserMsgBox("��Բ�������ʧ�ܣ�");
				SetNextStep(9999);
				break;
			}
			if (-1 == g_Ins.WaitImageOk(eCCD_WF))
			{
				g_AllFlag.m_bStop = TRUE;
				g_UserMsgBox.ShowUserMsgBox("��Բ����ɼ�ͼƬʧ�ܣ�");
				SetNextStep(9999);
				break;
			}

			/*if (time > 80)
			{
			g_Log.LogArray("WF case 100 ͼ����=%d", time);
			}*/
			g_Ins.DoSerach(eCCD_WF,ePR_PT);
			g_Ins.GetResult(eCCD_WF, ePR_PT,&m_Num,m_Score, m_Posx, m_Posy,m_Angle, &m_Time);
			if (m_Time > 100)
			{
				g_Log.LogArray("WF case 400 ʶ��ʱ��=%.1f", m_Time);
			}
			//ShowWfImage();
			if (m_Num >= 1)
			{
				AddAllWFPos();
				if (GetImgCenterPos()) //��ȡ��������--�ҵ���
				{
					PixToPulse(m_dCentPixX,m_dCentPixY,m_iCentPulseX,m_iCentPulseY);
					int centPosX = WFX->GetPos() + m_iCentPulseX;
					int centPosY = WFY->GetPos() + m_iCentPulseY;
					//g_Log.LogShow2("У����λ��x��%d+%d,y:%d+%d",m_iWfPosX,m_iCentPulseX,m_iWfPosY,m_iCentPulseY);

					//g_Log.LogShow("��Բʶ��Ƕ�=%.1f", m_dCentAngle);

					double yy, xx;

					m_iWfCalX = centPosX;
					m_iWfCalY = centPosY;
					g_AllFlag.m_bCalAngle = FALSE;
					if (!g_AllFlag.m_bSingleWfSerachStart && !g_AllFlag.m_bSingleWfTestDie &&
						fabs(m_dCentAngle) > g_MachDat.GetPara(MACH_WF_ANGLE_ALARM))
					{
						if (g_MachDat.GetPara(MACH_ENABLE_AUTO_ANGLE_CAL))
						{
							g_HomMat2D.SetCenter(g_MachDat.GetPara(MACH_WF_ROTATE_CENT_Y), g_MachDat.GetPara(MACH_WF_ROTATE_CENT_X));
							g_HomMat2D.GetCalPos(centPosY, centPosX, m_dCentAngle, yy, xx);
							m_iWfCalY = (int)yy;
							m_iWfCalX = (int)xx;
							SetNextStep(410);
							break;
						}
					}
					if (!g_MachDat.GetPara(MACH_ENABLE_AUTO_ANGLE_CAL) && fabs(m_dCentAngle) > g_MachDat.GetPara(MACH_WF_ANGLE_ALARM))
					{
						SetPickDieFlag(4, m_iWfPosX, m_iWfPosY);
						SetNextStep(200);//ȥ��һ���ж�
						break;
					}
					SetNextStep(500);
					break;
				}
				else  //������û�ҵ����� ����ת��һ����bug����Բ�̲���
				{
					g_Log.LogShow2("ͼ��������û���ҵ�����");
					SetPickDieFlag(4,m_iWfPosX,m_iWfPosY);
					g_AllFlag.m_bStop = TRUE;
					g_UserMsgBox.ShowUserMsgBox("ͼ��������û���ҵ�����", OK_RED);
					SetNextStep(9999);
					//SetNextStep(200);//ȥ��һ���ж�
					break;
				}
			}
			else  //������û�ҵ�����
			{

				g_Log.LogShow2("ͼ��������û���ҵ�����");
				SetPickDieFlag(4, m_iWfPosX, m_iWfPosY);
				//g_AllFlag.m_bStop = TRUE;
				//g_UserMsgBox.ShowUserMsgBox("ͼ��������û���ҵ�����", OK_RED);
				//SetNextStep(9999);
				SetNextStep(100);//ȥ��һ���ж�
				break;
			}
		}
		break;
	case 410:
		{
			//g_Log.LogShow2("��Բʶ��Ƕ�:%.1f,�趨�Ƕ�=%d", m_dCentAngle, g_MachDat.GetPara(MACH_WF_ANGLE_ALARM));

			g_AllFlag.m_bCalAngle = TRUE;
			double dist =  m_dCentAngle * g_MachDat.GetPara(MACH_WF_R_PULSE_PER_DEG);

			if (!g_AllFlag.m_bSingleWfSerachStart && !g_AllFlag.m_bSingleWfTestDie &&
				fabs(m_dCentAngle) > g_MachDat.GetPara(MACH_WF_ANGLE_ALARM))
			{
				if (g_MachDat.GetPara(MACH_ENABLE_AUTO_ANGLE_CAL))
				{
					d_run.pMtrWFR->MoveRel((int)dist);
					//g_Log.LogShow2("��Բ1��ת����:%d", (int)dist);
				}
			}


			if (CheckLimit(m_iWfCalX, m_iWfCalY))
			{
				m_iWfNextX = m_iWfCalX;
				m_iWfNextY = m_iWfCalY;

				WFX->MoveAbs(m_iWfCalX);
				WFY->MoveAbs(m_iWfCalY);

				WFX->WaitStop();
				WFY->WaitStop();
			}
			else
			{
				//g_Log.LogShow("��ת����󳬳�����");
				g_AllFlag.m_bStop = TRUE;
				g_UserMsgBox.ShowUserMsgBox("��Բ1��ת�󳬳�����", OK_RED);
				SetNextStep(9999);
				break;
			}
			d_run.pMtrWFR->WaitStop();
			SetNextStep(500);
		}
		break;

	case 500: // �ƶ���������--������ʾ--��԰̨׼����
		{
			WFX->MoveAbs(m_iWfCalX);
			WFY->MoveAbs(m_iWfCalY);
			WaitStopMtr(WFX,1,FALSE);
			WaitStopMtr(WFY,1,FALSE);

			Sleep(g_MachDat.GetPara(MACH_WF_CCD_DELAY));
			g_Ins.SoftTrig(eCCD_WF);
			g_Ins.WaitImageOk(eCCD_WF);
			ShowWfImage();
			if (g_AllFlag.m_bCalAngle)// �Ƕ�У����������ĵ�
			{
				g_Ins.DoSerach(eCCD_WF, ePR_PT);
				g_Ins.GetResult(eCCD_WF, ePR_PT, &m_Num, m_Score, m_Posx, m_Posy, m_Angle, &m_Time);
				if (m_Num >= 1)
				{
					AddAllWFPos();
					if (GetImgCenterPos()) //��ȡ��������--�ҵ���
					{
						PixToPulse(m_dCentPixX, m_dCentPixY, m_iCentPulseX, m_iCentPulseY);
						int centPosX = WFX->GetPos() + m_iCentPulseX;
						int centPosY = WFY->GetPos() + m_iCentPulseY;
						WFX->MoveAbs(m_iWfCalX);
						WFY->MoveAbs(m_iWfCalY);
						while (WFX->IsMoving()) { Sleep(1); }
						while (WFY->IsMoving()) { Sleep(1); }

						Sleep(g_MachDat.GetPara(MACH_WF_CCD_DELAY));
						g_Ins.SoftTrig(eCCD_WF);
						g_Ins.WaitImageOk(eCCD_WF);
						ShowWfImage();
					}
				}
			}
	
			//SleepExms(g_MachDat.GetPara(MACH_WF_CCD_DELAY));
			//g_Ins.SoftTrig(eCCD_WF);
			//while (true)
			//{
			//	if (g_Ins.GetImageOk(eCCD_WF))
			//	{
			//		break;
			//	}
			//	SleepExms(1);
			//}
			//ShowWfImage();
			SetNextStep(550);
		}
		break;

	case 550:
	{
		g_AllFlag.m_bWFDieReady = TRUE;

		if (g_AllFlag.m_bSingleWfSerach || g_AllFlag.m_bSingleWfNextDie || g_AllFlag.m_bSingleBd 
			|| g_AllFlag.m_bSingleStepBd || g_AllFlag.m_bSingleLookDh)
		{
			if (g_AllFlag.m_bSingleWfNextDie)
			{
				SetPickDieFlag(2, m_iWfCalX, m_iWfCalY,0);
			}
			SetNextStep(9999);
			break;
		}

		if (g_AllFlag.m_bSingleWfTestDie || g_AllFlag.m_bSingleWfSerachStart)
		{
			SetPickDieFlag(2, m_iWfCalX, m_iWfCalY,0);
			SetNextStep(200);
			break;
		}

		SetNextStep(600);
	}
	break;

	case 600:
		{
			if (g_AllFlag.m_bStop)
			{
				SetNextStep(9999);
				break;
			}
			SleepExms(2);
			if (g_AllFlag.m_bWFDieReady ) //��Ƭ������
			{
				break;
			}
			SetPickDieFlag(2,m_iWfCalX,m_iWfCalY);
			SetNextStep(200);
		}
		break;


	case 9999:
		{
			rt = 0;
		}
	}
	return rt;
}