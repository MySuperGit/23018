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

	int w = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_X); //像素
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
		if (rect.PtInRect(pt)) //排除中心的点
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
	int w = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_X); //像素
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
	//g_Log.LogArray("中心点偏移像素x=%.1f,y=%.1f,脉冲x=%d,y=%d",m_dCentPixX,m_dCentPixY,m_iCentPulseX,m_iCentPulseY);
	//int posx = WFX->GetPos();
	//int posy = WFY->GetPos();
	//m_iWfPosX += m_iCentPulseX;
	//m_iWfPosY += m_iCentPulseY;
	//g_Log.LogArray("中心点原始位置x=%d,y=%d,校正后位置x=%d,y=%d",posx,posy,m_iWfPosX,m_iWfPosY);
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

int CAutoDbWf::GetImgRectNearPos(CRect rt) //获取矩形框内离中心最近的点
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

//先在当前图像上找，图像上找不到，直接找链表里离的最近的,
//1,图像正上方
//2. 右上角-->右下-->最近
//	 左上-->左下-->最近
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

//图像搜晶 --图像上识别到的都是可以去吸的，要提前判定好，超过极限的要先剔除掉，正中心的那个也要剔除
//1.正上方1,2,3...		不包括这一行
//2.右边矩形框1.2.3...  跟上方的框一样，包括这一行
//3.右边下一行			下一行的右边方向
//4.左边矩形框1.2.3...  切换方向
//5.左边下一行			下一行的左边方向 切换方向
//6.图像最近			自动判定切换方向
//7.链表最近			自动判定切换方向
int	CAutoDbWf::GetImgNextDie()
{
	int rtn = 0;
	double DieDistX = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_X); //像素
	double DieDistY = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_Y);
	//先算出右上角有多少列
	int col = fabs((g_Ins.GetPara(eCCD_WF,ePR_PT,eROIWIDTH)-DieDistX)/2/DieDistX);
	WFMapPos  cur_pt;
	CPoint pt;
	CRect rect;
	int lx=0,ly=0,rx=0,ry=0;
	CTRealPoint RpCenter(CCD_W/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFX),CCD_H/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY));
	CTRealPoint RpTemp;
	double dist1 = 10000000;
	double dist  = 0;
	//1.正上方1,2,3...		不包括这一行
#pragma region 第一步
	lx = CCD_W/2 - DieDistX/2;
	ly = 0;
	rx = CCD_W/2 + DieDistX/2;
	ry = CCD_H/2 - DieDistY/2;
	rect.SetRect(lx,ly,rx,ry);
	rtn = GetImgRectNearPos(rect);
	g_Log.LogShow2("正上方矩形坐标lx=%d,ly=%d,rx=%d,ry=%d",lx,ly,rx,ry);
	if (rtn) //找到了 --更新下一点的坐标
	{
		gDlgMainBondWnd->m_pImageView[1].SetRect(rect);
		g_Log.LogShow2("1.正上放找到芯片，像素偏移x=%.1f,y=%.1f,脉冲坐标x=%d,y=%d"
			,m_dCentPixX,m_dCentPixY,m_iWfPosX,m_iWfPosY);
		return rtn;
	}
#pragma endregion
	if (m_SearchDirX == 1) //右上角-->右下-->最近
	{
		//2.右边矩形框1.2.3...  跟上方的框一样，包括这一行
#pragma region 第二步
	
		for (int i=0;i<col;i++)
		{
			lx = CCD_W/2 + DieDistX/2+DieDistX*i;
			ly = 0;
			rx = CCD_W/2 + DieDistX/2+DieDistX*(i+1);
			ry = CCD_H/2+DieDistY/2;
			rect.SetRect(lx,ly,rx,ry);
			rtn = GetImgRectNearPos(rect);
			g_Log.LogShow2("右上角%d,矩形坐标lx=%d,ly=%d,rx=%d,ry=%d",i+1,lx,ly,rx,ry);
			if (rtn)  //右上角找到
			{
				gDlgMainBondWnd->m_pImageView[1].SetRect(rect);
				g_Log.LogShow2("2.右上角%d找到芯片",i+1);
				return rtn;
			}
		}
#pragma endregion
		//3.右边下一行			下一行的右边方向
#pragma region 第三步
		lx = CCD_W/2-DieDistX/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFX);
		ly = CCD_H/2+DieDistY/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY);
		rx = CCD_W;
		ry = CCD_H/2+DieDistY/2*3 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY);
		rect.SetRect(lx,ly,rx,ry);
		rtn = GetImgRectNearPos(rect);
		g_Log.LogShow2("右边下一行矩形坐标lx=%d,ly=%d,rx=%d,ry=%d",lx,ly,rx,ry);
		if (rtn)  //右边下一行找到
		{
			gDlgMainBondWnd->m_pImageView[1].SetRect(rect);
			g_Log.LogShow2("3.右边下一行找到芯片");
			return rtn;
		}
#pragma endregion
		//4.左边矩形框1.2.3...  切换方向
#pragma region 第四步
		for (int i=0;i<col;i++)
		{
			lx = CCD_W/2 - DieDistX/2-DieDistX*(i+1);
			ly = 0;
			rx = CCD_W/2 + DieDistX/2+DieDistX*i;
			ry = CCD_H/2+DieDistY/2;
			rect.SetRect(lx,ly,rx,ry);
			rtn = GetImgRectNearPos(rect);
			g_Log.LogShow2("左上角%d,矩形坐标lx=%d,ly=%d,rx=%d,ry=%d",i+1,lx,ly,rx,ry);
			if (rtn)  //左上角找到
			{
				m_SearchDirX = -1;
				gDlgMainBondWnd->m_pImageView[1].SetRect(rect);
				g_Log.LogShow2("4.左上角%d找到芯片",i+1);
				return rtn;
			}
		}
#pragma endregion
		//5.左边下一行			下一行的左边方向 切换方向
#pragma region 第五步
		lx = 0;;
		ly = CCD_H/2+DieDistY/2;
		rx = CCD_W/2-DieDistX/2;
		ry = CCD_H/2+DieDistY/2*3;
		rect.SetRect(lx,ly,rx,ry);
		rtn = GetImgRectNearPos(rect);
		g_Log.LogShow2("左边下一行矩形坐标lx=%d,ly=%d,rx=%d,ry=%d",lx,ly,rx,ry);
		if (rtn)  //左边下一行找到
		{
			m_SearchDirX = -1;
			gDlgMainBondWnd->m_pImageView[1].SetRect(rect);
			g_Log.LogShow2("5.左边下一行找到芯片");
			return rtn;
		}
#pragma endregion
		//6.图像最近			自动判定切换方向
#pragma region 第六步
		rtn = GetImgNearPosOut();
		if (rtn)  //左边下一行找到
		{
			//找到左边的，切换方向
			if (m_dCentPixX < CCD_W/2)
			{
				m_SearchDirX = -1;
			}
			g_Log.LogShow2("6.找到图像最近芯片");
			return rtn;
		}
#pragma endregion	
	}
	else
	{
		//2.左边矩形框1.2.3...  切换方向
#pragma region 第二步
		for (int i=0;i<col;i++)
		{
			lx = CCD_W/2 - DieDistX/2-DieDistX*(i+1);
			ly = 0;
			rx = CCD_W/2 + DieDistX/2+DieDistX*i;
			ry = CCD_H/2+DieDistY/2;
			rect.SetRect(lx,ly,rx,ry);
			rtn = GetImgRectNearPos(rect);
			g_Log.LogShow2("左上角%d,矩形坐标lx=%d,ly=%d,rx=%d,ry=%d",i+1,lx,ly,rx,ry);
			if (rtn)  //左上角找到
			{
				gDlgMainBondWnd->m_pImageView[1].SetRect(rect);
				g_Log.LogShow2("2.左上角%d找到芯片",i+1);
				return rtn;
			}
		}
#pragma endregion
		//3.左边下一行			下一行的左边方向 切换方向
#pragma region 第三步
		lx = 0;;
		ly = CCD_H/2+DieDistY/2;
		rx = CCD_W/2-DieDistX/2;
		ry = CCD_H/2+DieDistY/2*3;
		rect.SetRect(lx,ly,rx,ry);
		rtn = GetImgRectNearPos(rect);
		g_Log.LogShow2("左边下一行矩形坐标lx=%d,ly=%d,rx=%d,ry=%d",lx,ly,rx,ry);
		if (rtn)  //左边下一行找到
		{
			gDlgMainBondWnd->m_pImageView[1].SetRect(rect);
			g_Log.LogShow2("3.左边下一行找到芯片");
			return rtn;
		}
#pragma endregion
		//4.右边矩形框1.2.3...  跟上方的框一样，包括这一行
#pragma region 第四步
		//先算出右上角有多少列
		for (int i=0;i<col;i++)
		{
			lx = CCD_W/2 + DieDistX/2+DieDistX*i;
			ly = 0;
			rx = CCD_W/2 + DieDistX/2+DieDistX*(i+1);
			ry = CCD_H/2+DieDistY/2;
			rect.SetRect(lx,ly,rx,ry);
			rtn = GetImgRectNearPos(rect);
			g_Log.LogShow2("右上角%d,矩形坐标lx=%d,ly=%d,rx=%d,ry=%d",i+1,lx,ly,rx,ry);
			if (rtn)  //右上角找到
			{
				m_SearchDirX = 1;
				gDlgMainBondWnd->m_pImageView[1].SetRect(rect);
				g_Log.LogShow2("4.右上角%d找到芯片",i+1);
				return rtn;
			}
		}
#pragma endregion
		//5.右边下一行			下一行的右边方向
#pragma region 第五步
		lx = CCD_W/2-DieDistX/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFX);
		ly = CCD_H/2+DieDistY/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY);
		rx = CCD_W;
		ry = CCD_H/2+DieDistY/2*3;
		rect.SetRect(lx,ly,rx,ry);
		rtn = GetImgRectNearPos(rect);
		g_Log.LogShow2("右边下一行矩形坐标lx=%d,ly=%d,rx=%d,ry=%d",lx,ly,rx,ry);
		if (rtn)  //右边下一行找到
		{
			m_SearchDirX = 1;
			gDlgMainBondWnd->m_pImageView[1].SetRect(rect);
			g_Log.LogShow2("5.右边下一行找到芯片");
			return rtn;
		}
#pragma endregion

		//6.图像最近			自动判定切换方向
#pragma region 第六步
		rtn = GetImgNearPosOut();
		if (rtn) 
		{
			//找到左边的，切换方向
			if (m_dCentPixX > CCD_W/2)
			{
				m_SearchDirX = 1;
			}
			g_Log.LogShow2("6.找到图像最近芯片");
			return rtn;
		}
#pragma endregion	
	}

	//7.链表最近			自动判定切换方向
#pragma region 第七步
	int curPosX = WFX->GetPos();
	int curPosY = WFY->GetPos();
	RpCenter.Set(curPosX,curPosY);
	double dist2 = 100000000;
	for (POSITION pos = m_MapPosList.GetHeadPosition();pos;m_MapPosList.GetNext(pos))
	{
		cur_pt = m_MapPosList.GetAt(pos);
		if (cur_pt.flag == 1) //只在可用的链表中判断
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
		if (g_Ins.GetParaF(eCCD_WF,eCAL_RX_DIR) > 0) //正向，需要进行测试
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
		g_Log.LogShow2("7.链表中找到芯片");
		return rtn;
	}
#pragma endregion
	//图像和链表上都没找到，返回０
	g_Log.LogShow2("没有找到芯片");
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

//1.正上方1,2,3...		不包括这一行
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

	//直接以世界坐标为基准建立矩形
	//加上负限位，确保所有的数据都是正的，以免rect出问题
	if (g_Ins.GetParaF(eCCD_WF,eCAL_RX_DIR) < 0)//图像向右为负
	{
		lx = m_iWfCalX + DieDistX/2 + limitX;
		rx = m_iWfCalX - DieDistX/2 + limitX;
		//g_Log.LogArray("正上搜晶 图像向右为负 lx=%d+%d+%d,rx=%d-%d+%d",m_iWfCalX,DieDistX/2,limitX,m_iWfCalX,DieDistX/2,limitX);
	}
	else //图像向右为正
	{
		lx = m_iWfCalX - DieDistX/2 + limitX;
		rx = m_iWfCalX + DieDistX/2 + limitX;
		//g_Log.LogArray("正上搜晶 图像向右为正 lx=%d-%d+%d,rx=%d+%d+%d",m_iWfCalX,DieDistX/2,limitX,m_iWfCalX,DieDistX/2,limitX);
	}
	if (g_Ins.GetParaF(eCCD_WF,eCAL_RY_DIR) > 0) //图像向上为正
	{
		ly = m_iWfCalY - DieDistY/2 - DieDistY*row + limitY;	
		ry = m_iWfCalY - DieDistY/2 + limitY;
		//g_Log.LogArray("正上搜晶 图像向上为正 lx=%d-%d-%d+%d,rx=%d-%d+%d",m_iWfCalY,DieDistY/2,DieDistY*row,limitY,m_iWfCalY,DieDistY/2 ,limitY);

	}
	else //图像向上为负
	{
		ly = m_iWfCalY + DieDistY/2 + DieDistY*row + limitY;	
		ry = m_iWfCalY + DieDistY/2 + limitY;
		//g_Log.LogArray("正上搜晶 图像向上为负 lx=%d+%d+%d+%d,rx=%d+%d+%d",m_iWfCalY,DieDistY/2,DieDistY*row,limitY,m_iWfCalY,DieDistY/2 ,limitY);
	}
	rect.SetRect(lx,ly,rx,ry);
	rect.NormalizeRect();
	rtn = GetWorldRectNearPos(rect);
	//g_Log.LogShow2("自动搜晶-正上方矩形坐标lx=%d,ly=%d,rx=%d,ry=%d，rect lx=%d,ly=%d,rx=%d,ry=%d"
	//	,lx,ly,rx,ry,rect.TopLeft().x,rect.TopLeft().y,rect.BottomRight().x,rect.BottomRight().y);
	if (rtn) //找到了 --更新下一点的坐标
	{
		return rtn;
	}
	return rtn;
}

//右边矩形框1.2.3...  跟上方的框一样，包括这一行
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

	//直接以世界坐标为基准建立矩形
	//加上负限位，确保所有的数据都是正的，以免rect出问题
	for (int i=0;i<col;i++)
	{
		if (g_Ins.GetParaF(eCCD_WF,eCAL_RX_DIR) < 0) //图像向右为负
		{
			lx = m_iWfCalX - DieDistX/2-DieDistX*i + limitX;
			rx = m_iWfCalX - DieDistX/2-DieDistX*(i+1) + limitX;
		//	g_Log.LogArray("右上搜晶 图像向右为负 lx=%d-%d-%d+%d,rx=%d-%d-%d+%d",m_iWfCalX,DieDistX/2,DieDistX*i,limitX,m_iWfCalX,DieDistX/2,DieDistX/(i+1),limitX);
		}
		else //图像向右为正
		{
			lx = m_iWfCalX + DieDistX/2+DieDistX*i + limitX;
			rx = m_iWfCalX + DieDistX/2+DieDistX*(i+1) + limitX;
		//	g_Log.LogArray("右上搜晶 图像向右为正 lx=%d+%d+%d+%d,rx=%d+%d+%d+%d",m_iWfCalX,DieDistX/2,DieDistX*i,limitX,m_iWfCalX,DieDistX/2,DieDistX/(i+1),limitX);
		}

		if (g_Ins.GetParaF(eCCD_WF,eCAL_RY_DIR) > 0) //图像向上为正
		{
			ly = m_iWfCalY - DieDistY/2 - DieDistY*row + limitY;	
			ry = m_iWfCalY + DieDistY/2 + limitY;
		//	g_Log.LogArray("右上搜晶 图像向上为正 lx=%d-%d-%d+%d,rx=%d+%d+%d",m_iWfCalY,DieDistY/2,DieDistY*row,limitY,m_iWfCalY,DieDistY/2 ,limitY);
		}
		else //图像向上为负
		{
			ly = m_iWfCalY + DieDistY/2 + DieDistY*row + limitY;	
			ry = m_iWfCalY - DieDistY/2 + limitY;
			//g_Log.LogArray("右上搜晶 图像向上为负 lx=%d+%d+%d+%d,rx=%d-%d+%d",m_iWfCalY,DieDistY/2,DieDistY*row,limitY,m_iWfCalY,DieDistY/2 ,limitY);
		}
		rect.SetRect(lx,ly,rx,ry);
		rect.NormalizeRect();
		rtn = GetWorldRectNearPos(rect);
		//g_Log.LogShow2("自动搜晶-右上角矩形坐标lx=%d,ly=%d,rx=%d,ry=%d，rect lx=%d,ly=%d,rx=%d,ry=%d"
		//	,lx,ly,rx,ry,rect.TopLeft().x,rect.TopLeft().y,rect.BottomRight().x,rect.BottomRight().y);

		if (rtn)  //右上角找到
		{
			return rtn;
		}
	}
	return rtn;
}

//左边矩形框1.2.3...  跟上方的框一样，包括这一行
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

	//直接以世界坐标为基准建立矩形
	//加上负限位，确保所有的数据都是正的，以免rect出问题
	for (int i=0;i<col;i++)
	{
		if (g_Ins.GetParaF(eCCD_WF,eCAL_RX_DIR) < 0)//图像向右为负
		{
			lx = m_iWfCalX + DieDistX/2 + DieDistX*(i+1) + limitX;
			rx = m_iWfCalX + DieDistX/2 + DieDistX*i + limitX;
		}
		else //图像向右为正
		{
			lx = m_iWfCalX - DieDistX/2-DieDistX*i + limitX;
			rx = m_iWfCalX - DieDistX/2-DieDistX*(i+1) + limitX;
		}

		if (g_Ins.GetParaF(eCCD_WF,eCAL_RY_DIR) > 0) //图像向上为正
		{
			ly = m_iWfCalY - DieDistY/2 - DieDistY*row + limitY;	
			ry = m_iWfCalY + DieDistY/2 + limitY;
		//	g_Log.LogArray("左上搜晶 图像向上为正 lx=%d-%d-%d+%d,rx=%d+%d+%d",m_iWfCalY,DieDistY/2,DieDistY*row,limitY,m_iWfCalY,DieDistY/2 ,limitY);
		}
		else //图像向上为负
		{
			ly = m_iWfCalY + DieDistY/2 + DieDistY*row + limitY;	
			ry = m_iWfCalY - DieDistY/2 + limitY;
			//g_Log.LogArray("左上搜晶 图像向上为负 lx=%d+%d+%d+%d,rx=%d-%d+%d",m_iWfCalY,DieDistY/2,DieDistY*row,limitY,m_iWfCalY,DieDistY/2 ,limitY);
		}

		rect.SetRect(lx,ly,rx,ry);
		rect.NormalizeRect();
		rtn = GetWorldRectNearPos(rect);
		//g_Log.LogShow2("自动搜晶-左上角矩形坐标lx=%d,ly=%d,rx=%d,ry=%d，rect lx=%d,ly=%d,rx=%d,ry=%d"
		//	,lx,ly,rx,ry,rect.TopLeft().x,rect.TopLeft().y,rect.BottomRight().x,rect.BottomRight().y);

		if (rtn)  //左上角找到
		{	
			return rtn;
		}
	}
	return rtn;
}

//右边下一行			下一行的右边方向
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

	//直接以世界坐标为基准建立矩形
	//加上负限位，确保所有的数据都是正的，以免rect出问题
	if (g_Ins.GetParaF(eCCD_WF,eCAL_RX_DIR) < 0) //图像向右为负
	{
		lx = m_iWfCalX + DieDistX/2 + limitX;
		rx = m_iWfCalX - DieDistX/2 - DieDistX*col + limitX;
	}
	else //图像向右为正
	{
		lx = m_iWfCalX - DieDistX/2 + limitX;
		rx = m_iWfCalX + DieDistX/2 + DieDistX*col + limitX;
	}

	if (g_Ins.GetParaF(eCCD_WF,eCAL_RY_DIR) > 0) //图像向上为正
	{
		ly = m_iWfCalY + DieDistY/2 + limitY;	
		ry = m_iWfCalY + DieDistY/2*3 + limitY;
	//	g_Log.LogArray("右下一行搜晶 图像向上为正 ly=%d+%d+%d,ry=%d+%d+%d",m_iWfCalY,DieDistY/2,limitY,m_iWfCalY,DieDistY/2*3 ,limitY);
	}
	else //图像向上为负
	{
		ly = m_iWfCalY - DieDistY/2 + limitY;	
		ry = m_iWfCalY - DieDistY/2*3 + limitY;
	//	g_Log.LogArray("右下一行搜晶 图像向上为负 lx=%d-%d+%d,rx=%d-%d+%d",m_iWfCalY,DieDistY/2,limitY,m_iWfCalY,DieDistY/2*3,limitY);
	}

	rect.SetRect(lx,ly,rx,ry);
	rect.NormalizeRect();
	rtn = GetWorldRectNearPos(rect);
//	g_Log.LogShow2("自动搜晶-右边下一行矩形坐标lx=%d,ly=%d,rx=%d,ry=%d，rect lx=%d,ly=%d,rx=%d,ry=%d"
//		,lx,ly,rx,ry,rect.TopLeft().x,rect.TopLeft().y,rect.BottomRight().x,rect.BottomRight().y);

	if (rtn)  //右边下一行找到
	{
		return rtn;
	}
	return rtn;
}

//左边下一行			下一行的左边方向 
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

	//直接以世界坐标为基准建立矩形
	//加上负限位，确保所有的数据都是正的，以免rect出问题
	if (g_Ins.GetParaF(eCCD_WF,eCAL_RX_DIR) < 0) //图像向右为负
	{
		lx = m_iWfCalX - DieDistX/2 + limitX;
		rx = m_iWfCalX + DieDistX/2 + DieDistX*col + limitX;
	}
	else //图像向右为正
	{
		lx = m_iWfCalX + DieDistX/2 + limitX;
		rx = m_iWfCalX - DieDistX/2 - DieDistX*col + limitX;
	}

	if (g_Ins.GetParaF(eCCD_WF,eCAL_RY_DIR) > 0) //图像向上为正
	{
		ly = m_iWfCalY + DieDistY/2 + limitY;	
		ry = m_iWfCalY + DieDistY/2*3 + limitY;
	//	g_Log.LogArray("左下一行搜晶 图像向上为正 ly=%d+%d+%d,ry=%d+%d+%d",m_iWfCalY,DieDistY/2,limitY,m_iWfCalY,DieDistY/2*3 ,limitY);
	}
	else //图像向上为负
	{
		ly = m_iWfCalY - DieDistY/2 + limitY;	
		ry = m_iWfCalY - DieDistY/2*3 + limitY;
	//	g_Log.LogArray("左下一行搜晶 图像向上为负 lx=%d-%d+%d,rx=%d-%d+%d",m_iWfCalY,DieDistY/2,limitY,m_iWfCalY,DieDistY/2*3,limitY);
	}
	rect.SetRect(lx,ly,rx,ry);
	rect.NormalizeRect();
	rtn = GetWorldRectNearPos(rect);
	//g_Log.LogShow2("自动搜晶-左边下一行矩形坐标lx=%d,ly=%d,rx=%d,ry=%d，rect lx=%d,ly=%d,rx=%d,ry=%d"
	//	,lx,ly,rx,ry,rect.TopLeft().x,rect.TopLeft().y,rect.BottomRight().x,rect.BottomRight().y);
	if (rtn)  //左边下一行找到
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

	//6.链表最近			自动判定切换方向

	int curPosX = WFX->GetPos();
	int curPosY = WFY->GetPos();
	RpCenter.Set(curPosX,curPosY);
	double dist2 = 100000000;
	for (POSITION pos = m_MapPosList.GetHeadPosition();pos;m_MapPosList.GetNext(pos))
	{
		cur_pt = m_MapPosList.GetAt(pos);
		if (cur_pt.flag == 1) //只在可用的链表中判断
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

//世界地图搜晶 --  可以记录好每个晶片的状态，比如说超极限或者识别NG，下次就不去了
//1..1,2,3...		    不包括这一行
//2.右边矩形框1.2.3...  跟上方的框一样，包括这一行
//3.右边下一行			下一行的右边方向
//4.左边矩形框1.2.3...  切换方向
//5.左边下一行			下一行的左边方向 切换方向
//6.链表最近			自动判定切换方向
int CAutoDbWf::GetWorldNextDie()  //在世界坐标上搜晶模式
{
	int rtn = 0;
	int searchMode = g_MachDat.GetPara(MACH_WF_SRH_MODE);

	DieDistX = g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_X); //脉冲间距
	DieDistY = g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_Y);
	//g_Log.LogArray("脉冲间距 DieDistX = %.f,DieDistY = %.f",DieDistX,DieDistY);

	ImgDistX = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_X);
	ImgDistY = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_Y);
	//g_Log.LogArray("像素间距 ImgDistX = %.f,ImgDistY = %.f",ImgDistX,ImgDistY);

	//先算出右上角有多少列
	col = fabs((g_Ins.GetPara(eCCD_WF,ePR_PT,eROIWIDTH)-ImgDistX)/2/ImgDistX)+1;
//	g_Log.LogArray("col = (%d-%.f/2/%.f=%d",g_Ins.GetPara(eCCD_WF,ePR_PT,eROIWIDTH),ImgDistX,ImgDistX,col);
	row = fabs((g_Ins.GetPara(eCCD_WF,ePR_PT,eROIHEIGHT)-ImgDistY)/2/ImgDistY)+1;
//	g_Log.LogArray("row = (%d-%.f/2/%.f=%d",g_Ins.GetPara(eCCD_WF,ePR_PT,eROIHEIGHT),DieDistY,DieDistY,row);

	//保存链表里所有点的坐标
	WFMapPos cur_pt;
//	g_Log.LogArray("记录链表里的所有坐标");
	//int i=1;
	//for (POSITION pos = m_MapPosList.GetHeadPosition();pos;m_MapPosList.GetNext(pos))
	//{
	//	cur_pt = m_MapPosList.GetAt(pos);
	////	g_Log.LogArray("第%2d点，标记=%d,x=%6d,y=%6d",i++,cur_pt.flag,cur_pt.wfx+limitX,cur_pt.wfy+limitY);
	//}
	
	
	if (searchMode == 2)
	{
		rtn = GetWorldTopNextDie();
		if (rtn)
		{
			g_Log.LogShow2("向上搜晶 --OK");
		}
		else
		{
			g_Log.LogShow2("向上搜晶 --NG");
		}
		return rtn;
	}
	else if  (searchMode == 3)
	{
		rtn = GetWorldTopRightDie();
		if (rtn)
		{
			g_Log.LogShow2("右上搜晶 --OK");
		}
		else
		{
			g_Log.LogShow2("右上搜晶 --NG");
		}
		return rtn;
	}
	else if  (searchMode == 4)
	{
		rtn = GetWorldTopLeftDie();
		if (rtn)
		{
			g_Log.LogShow2("左上搜晶 --OK");
		}
		else
		{
			g_Log.LogShow2("左上搜晶 --NG");
		}
		return rtn;
	}
	else if  (searchMode == 5)
	{
		rtn = GetWorldBottomRightLine();
		if (rtn)
		{
			g_Log.LogShow2("右下一行搜晶 --OK");
		}
		else
		{
			g_Log.LogShow2("右下一行搜晶 --NG");
		}
		return rtn;
	}
	else if  (searchMode == 6)
	{
		rtn = GetWorldBottomLeftLine();
		if (rtn)
		{
			g_Log.LogShow2("左下一行搜晶 --OK");
		}
		else
		{
			g_Log.LogShow2("左下一行搜晶 --NG");
		}
		return rtn;
	}
	else if  (searchMode == 7)
	{
		rtn = GetWorldListDie();
		if (rtn)
		{
			g_Log.LogShow2("链表搜晶 --OK");
		}
		else
		{
			g_Log.LogShow2("链表搜晶 --NG");
		}
		return rtn;
	}


	rtn = GetWorldTopNextDie();
	if (rtn) //找到了 --更新下一点的坐标
	{
	//	g_Log.LogShow2("自动搜晶-1.正上放找到芯片，脉冲坐标x=%d,y=%d",m_iWfPosX,m_iWfPosY);
		return rtn;
	}

	if (m_SearchDirX == 1) 
	{
		rtn = GetWorldTopRightDie();
		if (rtn)  //右上角找到
		{
		//	g_Log.LogShow2("自动搜晶-2.右上角找到芯片");
			return rtn;
		}
		rtn = GetWorldTopLeftDie();
		if (rtn)  //左上角找到
		{
			m_SearchDirX = -1;
		//	g_Log.LogShow2("自动搜晶-3.左上角%d找到芯片");
			return rtn;
		}
		rtn = GetWorldBottomRightLine();
		if (rtn)  //右边下一行找到
		{
		//	g_Log.LogShow2("自动搜晶-4.右边下一行找到芯片");
			return rtn;
		}
		rtn = GetWorldTopLeftDie();
		if (rtn)  //左边下一行找到
		{
			m_SearchDirX = -1;
		//	g_Log.LogShow2("自动搜晶-5.左边下一行找到芯片");
			return rtn;
		}
	}
	else
	{
		rtn = GetWorldTopLeftDie();
		if (rtn)  //左上角找到
		{		
		//	g_Log.LogShow2("自动搜晶-12.左上角%d找到芯片");
			return rtn;
		}
		rtn = GetWorldTopRightDie();
		if (rtn)  //右上角找到
		{
			m_SearchDirX = 1;
		//	g_Log.LogShow2("自动搜晶-13.右上角找到芯片");
			return rtn;
		}
		rtn = GetWorldBottomLeftLine();
		if (rtn)  //左边下一行找到
		{
		//	g_Log.LogShow2("自动搜晶-14.左边下一行找到芯片");
			return rtn;
		}
		rtn = GetWorldBottomRightLine();
		if (rtn)  //右边下一行找到
		{
			m_SearchDirX = 1;
		//	g_Log.LogShow2("自动搜晶-15.右边下一行找到芯片");
			return rtn;
		}
	}

	rtn = GetWorldListDie();
	int curPosX = WFX->GetPos();
	int curPosY = WFY->GetPos();
	if (rtn)
	{
		if (g_Ins.GetParaF(eCCD_WF,eCAL_RX_DIR) > 0) //图像向右为负
		{
			if (m_iWfPosX < curPosX) //计算点小于当前点，说明向右
			{
				m_SearchDirX = 1;
			}
			else
			{
				m_SearchDirX = -1;
			}
		}
		else //图像向右为正
		{
			if (m_iWfPosX < curPosX) //计算点小于当前点，说明向左
			{
				m_SearchDirX = -1;
			}
			else
			{
				m_SearchDirX = 1;
			}
		}

	//	g_Log.LogShow2("自动搜晶-20.链表中找到芯片");
		return rtn;
	}
	//图像和链表上都没找到，返回０
	g_Log.LogShow2("没有找到芯片");
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

	double DieDistX = g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_X); //脉冲单位
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
		if (rect.PtInRect(pt)) //当前点已经在链表中了，更新
		{
			bExist = TRUE;
			//cur_pt.flag = flag;  //如果已经存在，不为1，那么只更新坐标
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

int CAutoDbWf::GetWorldRectDie(CRect rt) //判断这个矩形框内是否有晶片
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

	//直接以世界坐标为基准建立矩形
	//加上负限位，确保所有的数据都是正的，以免rect出问题
	if (g_Ins.GetParaF(eCCD_WF, eCAL_RX_DIR) < 0)//图像向右为负
	{
		lx = m_iWfCalX + DieDistX / 2 + limitX - DieDistX * XNum;
		rx = m_iWfCalX - DieDistX / 2 + limitX - DieDistX * XNum;
		//g_Log.LogArray("正上搜晶 图像向右为负 lx=%d+%d+%d,rx=%d-%d+%d",m_iWfCalX,DieDistX/2,limitX,m_iWfCalX,DieDistX/2,limitX);
	}
	else //图像向右为正
	{
		lx = m_iWfCalX - DieDistX / 2 + limitX + DieDistX * XNum;
		rx = m_iWfCalX + DieDistX / 2 + limitX + DieDistX * XNum;
		//g_Log.LogArray("正上搜晶 图像向右为正 lx=%d-%d+%d,rx=%d+%d+%d",m_iWfCalX,DieDistX/2,limitX,m_iWfCalX,DieDistX/2,limitX);
	}
	if (g_Ins.GetParaF(eCCD_WF, eCAL_RY_DIR) > 0) //图像向上为正
	{
		ly = m_iWfCalY + DieDistY / 2 + limitY - DieDistY * YNum;
		ry = m_iWfCalY - DieDistY / 2 + limitY - DieDistY * YNum;
		//g_Log.LogArray("正上搜晶 图像向上为正 lx=%d-%d-%d+%d,rx=%d-%d+%d",m_iWfCalY,DieDistY/2,DieDistY*row,limitY,m_iWfCalY,DieDistY/2 ,limitY);

	}
	else //图像向上为负
	{
		ly = m_iWfCalY - DieDistY / 2 + limitY + DieDistY * YNum;
		ry = m_iWfCalY + DieDistY / 2 + limitY + DieDistY * YNum;
		//g_Log.LogArray("正上搜晶 图像向上为负 lx=%d+%d+%d+%d,rx=%d+%d+%d",m_iWfCalY,DieDistY/2,DieDistY*row,limitY,m_iWfCalY,DieDistY/2 ,limitY);
	}
	rect.SetRect(lx, ly, rx, ry);
	rect.NormalizeRect();

	rtn = GetWorldRectDie(rect);
	return rtn;
}

//世界地图搜晶 --  可以记录好每个晶片的状态，比如说超极限或者识别NG，下次就不去了
//1..1,2,3...		    不包括这一行
//2.右边矩形框1.2.3...  跟上方的框一样，包括这一行
//3.右边下一行			下一行的右边方向
//4.左边矩形框1.2.3...  切换方向
//5.左边下一行			下一行的左边方向 切换方向
//6.链表最近			自动判定切换方向
int CAutoDbWf::GetWorldDirNextDie()
{
	int rtn = 0;
	int searchMode = g_MachDat.GetPara(MACH_WF_SRH_MODE);

	if (searchMode == 2)
	{
		//保存链表里所有点的坐标
		WFMapPos cur_pt;
		//g_Log.LogArray("记录链表里的所有坐标");
		int i = 1;
		//for (POSITION pos = m_MapPosList.GetHeadPosition(); pos; m_MapPosList.GetNext(pos))
		//{
		//	cur_pt = m_MapPosList.GetAt(pos);
		//	g_Log.LogArray("第%2d点，标记=%d,x=%6d,y=%6d",i++,cur_pt.flag,cur_pt.wfx+limitX,cur_pt.wfy+limitY);
		//}

		rtn = GetWorldListDie();
		int curPosX = WFX->GetPos();
		int curPosY = WFY->GetPos();
		if (rtn)
		{
			g_Log.LogShow("链表中找到芯片");
			if (g_Ins.GetParaF(eCCD_WF, eCAL_RX_DIR) > 0) //图像向右为负
			{
				if (m_iWfPosX < curPosX) //计算点小于当前点，说明向右
				{
					m_SearchDirX = 1;
				}
				else
				{
					m_SearchDirX = -1;
				}
			}
			else //图像向右为正
			{
				if (m_iWfPosX < curPosX) //计算点小于当前点，说明向左
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
			g_Log.LogShow("链表中没有找到芯片");
		}	
		return rtn;
	}

	DieDistX = g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_X); //脉冲间距
	DieDistY = g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_Y);
//	g_Log.LogArray("脉冲间距 DieDistX = %.f,DieDistY = %.f",DieDistX,DieDistY);

	ImgDistX = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_X);
	ImgDistY = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_Y);
//	g_Log.LogArray("像素间距 ImgDistX = %.f,ImgDistY = %.f",ImgDistX,ImgDistY);

	//先算出右上角有多少列
	col = fabs((g_Ins.GetPara(eCCD_WF, ePR_PT, eROIWIDTH) - ImgDistX) / 2 / ImgDistX)+1;
	//	g_Log.LogArray("col = (%d-%.f/2/%.f=%d",g_Ins.GetPara(eCCD_WF,ePR_PT,eROIWIDTH),ImgDistX,ImgDistX,col);
	row = fabs((g_Ins.GetPara(eCCD_WF, ePR_PT, eROIHEIGHT) - ImgDistY) / 2 / ImgDistY)+1;
	//g_Log.LogArray("row = %d,col = %d", row, col);
	for (int i=0;i<row;i++)
	{
		rtn = GetWorldDirDie(0,i+1);
		if (rtn)
		{
			//g_Log.LogShow2("正上方第%d行找到芯片",i+1);
			return rtn;
		}		
	}
	//g_Log.LogShow2("正上方没有找到芯片");

	if (m_SearchDirX == 1) //向右搜晶
	{
		//当前行
		for (int i = 0; i < row; i++)
		{			
			rtn = GetWorldDirDie(i + 1, 0);
			if (rtn)
			{
				//g_Log.LogShow2("向右搜晶第%d列找到芯片", i + 1);
				return rtn;
			}
		}
		//g_Log.LogShow2("向右搜晶没有找到芯片");

		//上一行
		for (int i = 0; i < row; i++)
		{			
			rtn = GetWorldDirDie(i + 1, 1);
			if (rtn)
			{
				//g_Log.LogShow2("向右上一行搜晶第%d列找到芯片", i + 1);
				return rtn;
			}
		}
	//	g_Log.LogShow2("向右上一行搜晶没有找到芯片");

		//正下方
		rtn = GetWorldDirDie(0, -1);
		if (rtn)
		{
			m_SearchDirX = -1;
			//g_Log.LogShow2("正下方找到芯片");
			return rtn;
		}
		//g_Log.LogShow2("正下方晶没有找到芯片");
		//下一行
		for (int i = 0; i < row; i++)
		{
			rtn = GetWorldDirDie(i + 1, -1);
			if (rtn)
			{
				//g_Log.LogShow2("向右下一行搜晶第%d列找到芯片", i + 1);
				return rtn;
			}
		}
		//g_Log.LogShow2("向右下一行没有找到芯片");


		if (rtn == 0)
		{
			
			//当前行
			for (int i = 0; i < row; i++)
			{			
				rtn = GetWorldDirDie(-1 * i - 1, 0);
				if (rtn)
				{
					m_SearchDirX = -1;
					//g_Log.LogShow2("向左搜晶第%d列找到芯片", i + 1);
					return rtn;
				}
			}
			//g_Log.LogShow2("向左搜晶没有找到芯片");
			//上一行
			for (int i = 0; i < row; i++)
			{
				rtn = GetWorldDirDie(-1 * i - 1, 1);
				if (rtn)
				{
					m_SearchDirX = -1;
					//g_Log.LogShow2("向左上一行搜晶第%d列找到芯片", i + 1);
					return rtn;
				}
			}
			//g_Log.LogShow2("向左上一行搜晶没有找到芯片");
			//下一行
			for (int i = 0; i < row; i++)
			{
				rtn = GetWorldDirDie(-1 * i - 1, -1);
				if (rtn)
				{
					m_SearchDirX = -1;
					//g_Log.LogShow2("向左下一行搜晶第%d列找到芯片", i + 1);
					return rtn;
				}
			}
			//g_Log.LogShow2("向左下一行搜晶没有找到芯片");
		}
	}
	else //向左搜晶
	{
		//当前行
		for (int i = 0; i < row; i++)
		{
			rtn = GetWorldDirDie(-1 * i - 1, 0);
			if (rtn)
			{
				//g_Log.LogShow2("向左搜晶第%d列找到芯片", i + 1);
				return rtn;
			}
		}
		//g_Log.LogShow2("向左搜晶没有找到芯片");
		//上一行
		for (int i = 0; i < row; i++)
		{
			rtn = GetWorldDirDie(-1 * i - 1, 1);
			if (rtn)
			{
				//g_Log.LogShow2("向左上一行搜晶第%d列找到芯片", i + 1);
				return rtn;
			}
		}
		//g_Log.LogShow2("向左上一行没有找到芯片");
		//正下方
		rtn = GetWorldDirDie(0, -1);
		if (rtn)
		{
			m_SearchDirX = 1;
			//g_Log.LogShow2("正下方找到芯片");
			return rtn;
		}
		//g_Log.LogShow2("正下方没有找到芯片");
		//下一行
		for (int i = 0; i < row; i++)
		{
			rtn = GetWorldDirDie(-1 * i - 1, -1);
			if (rtn)
			{
				//g_Log.LogShow2("向左下一行搜晶第%d列找到芯片", i + 1);
				return rtn;
			}
		}
		//g_Log.LogShow2("向左下一行搜晶没有找到芯片");
		//当前行
		for (int i = 0; i < row; i++)
		{
			rtn = GetWorldDirDie(i + 1, 0);
			if (rtn)
			{
				m_SearchDirX = 1;
				//g_Log.LogShow2("向右搜晶第%d列找到芯片", i + 1);
				return rtn;
			}
		}
		//g_Log.LogShow2("向右搜晶没有找到芯片");
		//上一行
		for (int i = 0; i < row; i++)
		{
			rtn = GetWorldDirDie(i + 1, 1);
			if (rtn)
			{
				m_SearchDirX = 1;
				//g_Log.LogShow2("向右上一行搜晶第%d列找到芯片", i + 1);
				return rtn;
			}
		}
		//g_Log.LogShow2("向右上一行搜晶没有找到芯片");
		//下一行
		for (int i = 0; i < row; i++)
		{
			rtn = GetWorldDirDie(i + 1, -1);
			if (rtn)
			{
				m_SearchDirX = 1;
				//g_Log.LogShow2("向右下一行搜晶第%d列找到芯片", i + 1);
				return rtn;
			}
		}
		//g_Log.LogShow2("向右下一行搜晶没有找到芯片");
	}



	//保存链表里所有点的坐标
	WFMapPos cur_pt;
	g_Log.LogArray("记录链表里的所有坐标");
	int i = 1;
	for (POSITION pos = m_MapPosList.GetHeadPosition(); pos; m_MapPosList.GetNext(pos))
	{
		cur_pt = m_MapPosList.GetAt(pos);
		//g_Log.LogArray("第%2d点，标记=%d,x=%6d,y=%6d", i++, cur_pt.flag, cur_pt.wfx + limitX, cur_pt.wfy + limitY);
	}

	rtn = GetWorldListDie();
	int curPosX = WFX->GetPos();
	int curPosY = WFY->GetPos();
	if (rtn)
	{
		//g_Log.LogShow2("链表中找到芯片");
		if (g_Ins.GetParaF(eCCD_WF, eCAL_RX_DIR) > 0) //图像向右为负
		{
			if (m_iWfNextX < curPosX) //计算点小于当前点，说明向右
			{
				m_SearchDirX = 1;
			}
			else
			{
				m_SearchDirX = -1;
			}
		}
		else //图像向右为正
		{
			if (m_iWfNextX < curPosX) //计算点小于当前点，说明向左
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
		//图像和链表上都没找到，返回０
		g_Log.LogShow2("没有找到芯片");
	}

	return 0;
}

//寻找搜晶起点，先到最上方，再到最左边
int CAutoDbWf::GetWorldSearchStart()
{
	int rtn = 0;

	DieDistX = g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_X); //脉冲间距
	DieDistY = g_MachDat.GetParaF(MACH_F_WF_DIE_DIST_Y);
	//g_Log.LogArray("脉冲间距 DieDistX = %.f,DieDistY = %.f",DieDistX,DieDistY);

	ImgDistX = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_X);
	ImgDistY = g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_Y);
	//g_Log.LogArray("像素间距 ImgDistX = %.f,ImgDistY = %.f",ImgDistX,ImgDistY);

	//先算出右上角有多少列
	col = fabs((g_Ins.GetPara(eCCD_WF, ePR_PT, eROIWIDTH) - ImgDistX) / 2 / ImgDistX);
	//	g_Log.LogArray("col = (%d-%.f/2/%.f=%d",g_Ins.GetPara(eCCD_WF,ePR_PT,eROIWIDTH),ImgDistX,ImgDistX,col);
	row = fabs((g_Ins.GetPara(eCCD_WF, ePR_PT, eROIHEIGHT) - ImgDistY) / 2 / ImgDistY);


	for (int i = row; i >= 0; i--)
	{
		rtn = GetWorldDirDie(0, i + 1);
		if (rtn)
		{
			g_Log.LogShow2("正上方第%d行找到芯片", i + 1);
			return rtn;
		}
	}

	for (int i=0;i<col;i++)
	{
		for (int j=row;j>=0;j--)
		{
			rtn = GetWorldDirDie(j, i + 1);
			g_Log.LogShow2("上方第%d行找到芯片", i + 1);
			return rtn;
		}
	}

	//当前行
	for (int i = row -1 ; i >= 0; i--)
	{
		rtn = GetWorldDirDie(-1 * i - 1, 0);
		if (rtn)
		{
			m_SearchDirX = -1;
			g_Log.LogShow2("向左搜晶第%d列找到芯片", i + 1);
			return rtn;
		}
	}

	return 0;
}


void CAutoDbWf::AddAllWFPos()
{
	int centPosX = WFX->GetPos();
	int centPosY = WFY->GetPos();

	//g_Log.LogArray("添加链表时中心坐标x=%d,y=%d",centPosX,centPosY);
	int pulseX=0,pulseY=0;
	double offx,offy;
	for (int i=0;i<m_Num;i++)
	{
		offx = m_Posx[i]-(CCD_W/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFX));
		offy = m_Posy[i]-(CCD_H/2 + g_Ins.GetPara(eCCD_WF, ePR_PT, eCENTOFFY));
		//if (g_MachDat.GetPara(MACH_WF_SRH_MODE) == 1) //再图像中搜晶，正中间的那个不添加到链表里，免得下次又过来一次
		//{
		//	//正中心的那个不添加到链表里
		//	if (offx < g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_X) && offy < g_MachDat.GetParaF(MACH_F_WF_PIX_DIST_Y))
		//	{
		//		continue;
		//	}
		//}

		PixToPulse(offx,offy,pulseX,pulseY);
		//g_Log.LogArray("添加链表%d,像素偏移x=%.2f,y=%.2f,脉冲偏移x=%d,y=%d",i+1,offx,offy,pulseX,pulseY);
		pulseX += centPosX;
		pulseY += centPosY;		
		if (CheckLimit(pulseX,pulseY))
		{
			AddWFPos(1,pulseX,pulseY);
		}
		else
		{
			g_Log.LogShow2("添加链表，超出极限位 序号=%d，坐标x=%d,y=%d",i,pulseX,pulseY);
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
			if (flag == 2 && Remove) //抓取到的要在可用链表中删除
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
				g_UserMsgBox.ShowUserMsgBox("晶片间距不正确，请重新设置晶片间距",OK_RED);
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
				if (m_MapPosList.IsEmpty()) //链表是空的，要重新拍照识别
				{
					SetNextStep(100);
					break;
				}
				else  //直接去下一位置
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

	case 100: //第一次
		{
			Reset();
		//	g_Log.LogShow2("第一次拍照时原始位置x=%d,y=%d",WFX->GetPos(),WFY->GetPos());
			SleepExms(g_MachDat.GetPara(MACH_WF_CCD_DELAY));
			g_Ins.SoftTrig(eCCD_WF);
			int time = g_Ins.WaitImageOk(eCCD_WF);
			if (time > 80)
			{
				g_Log.LogArray("WF case 100 图像传输=%d", time);
			}
			g_Ins.DoSerach(eCCD_WF,ePR_PT);
			g_Ins.GetResult(eCCD_WF, ePR_PT,&m_Num,m_Score, m_Posx, m_Posy,m_Angle, &m_Time);
			if (m_Time > 100)
			{
				g_Log.LogArray("WF case 100 识别时间=%.1f",m_Time);
			}
			ShowWfImage();
			if (m_Num >= 1)
			{
				AddAllWFPos();
				if (GetImgNearPos()) //获取中心坐标
				{
					PixToPulse(m_dCentPixX,m_dCentPixY,m_iCentPulseX,m_iCentPulseY);
					//g_Log.LogArray("中心点偏移像素x=%.1f,y=%.1f,脉冲x=%d,y=%d",m_dCentPixX,m_dCentPixY,m_iCentPulseX,m_iCentPulseY);
					m_iWfPosX = WFX->GetPos() + m_iCentPulseX;
					m_iWfPosY = WFY->GetPos() + m_iCentPulseY;
					m_iWfNextX = m_iWfPosX ;
					m_iWfNextY = m_iWfPosY;
					//g_Log.LogShow2("第一次拍照后计算位置x:%d+%d,y:%d+%d，",WFX->GetPos(),m_iCentPulseX,WFY->GetPos(),m_iCentPulseY);
					SetNextStep(300);
					break;
				}
			}
			g_AllFlag.m_bStop = TRUE;
			g_UserMsgBox.ShowUserMsgBox("没有找到晶片, 请确定晶片放置是否正确",OK_RED);
			SetNextStep(9999);
		}
		break;

	case 200:  //获取下一次
		{
			if (g_AllFlag.m_bStop||(g_AllFlag.m_bSingleAutoBd && g_AllFlag.m_bBdOk))
			{
				SetNextStep(9999);
				break;
			}
			//g_Log.LogShow2("找芯片之前坐标x=%d,y=%d",WFX->GetPos(),WFY->GetPos());
			int rtn = GetNextDiePos();
			//g_Log.LogShow2("%d = GetNextDiePos()", rtn);
			if (rtn == 0)
			{
				g_AllFlag.m_bStop = TRUE;
				if (g_AllFlag.m_bSingleWfSerachStart)
				{
					g_UserMsgBox.ShowUserMsgBox("晶片起点查找完成!",OK_YEW);
					SetNextStep(9999);
					break;
				}
				g_Ins.SoftTrig(eCCD_WF);
				g_Ins.DoSerach(eCCD_WF, ePR_PT);
				ShowWfImage();
				g_UserMsgBox.ShowUserMsgBox("晶片查找结束，请更换晶圆盘",OK_RED);
				SetNextStep(9999);
				break;
			}
			SetNextStep(300);
		}
		break;

	case 300: //判断当前点是否在圆内
		{
			if (CheckLimit(m_iWfNextX, m_iWfNextY)) //在圆内
			{
				SetNextStep(400);
				break;
			}
			else
			{
				g_Log.LogShow("晶圆台坐标x:%d,y:%d超出极限", m_iWfNextX, m_iWfNextY);
				SetPickDieFlag(3,m_iWfPosX,m_iWfPosY);
				SetNextStep(200); //去下一点
				break;
			}
		}
		break;

	case 400:  //下一点到图像正中心来校正
		{
			m_iWfPosX = m_iWfNextX;
			m_iWfPosY = m_iWfNextY;
			//g_Log.LogShow2("校正时位置x=%d,y=%d",m_iWfPosX,m_iWfPosY);
			WFX->MoveAbs(m_iWfPosX);
			WFY->MoveAbs(m_iWfPosY);
			WaitStopMtr(WFX,1,FALSE);
			WaitStopMtr(WFY,1,FALSE);
			SleepExms(g_MachDat.GetPara(MACH_WF_CCD_DELAY));
			if (FALSE == g_Ins.SoftTrig(eCCD_WF))
			{
				g_AllFlag.m_bStop = TRUE;
				g_UserMsgBox.ShowUserMsgBox("晶圆相机软触发失败！");
				SetNextStep(9999);
				break;
			}
			if (-1 == g_Ins.WaitImageOk(eCCD_WF))
			{
				g_AllFlag.m_bStop = TRUE;
				g_UserMsgBox.ShowUserMsgBox("晶圆相机采集图片失败！");
				SetNextStep(9999);
				break;
			}

			/*if (time > 80)
			{
			g_Log.LogArray("WF case 100 图像传输=%d", time);
			}*/
			g_Ins.DoSerach(eCCD_WF,ePR_PT);
			g_Ins.GetResult(eCCD_WF, ePR_PT,&m_Num,m_Score, m_Posx, m_Posy,m_Angle, &m_Time);
			if (m_Time > 100)
			{
				g_Log.LogArray("WF case 400 识别时间=%.1f", m_Time);
			}
			//ShowWfImage();
			if (m_Num >= 1)
			{
				AddAllWFPos();
				if (GetImgCenterPos()) //获取中心坐标--找到了
				{
					PixToPulse(m_dCentPixX,m_dCentPixY,m_iCentPulseX,m_iCentPulseY);
					int centPosX = WFX->GetPos() + m_iCentPulseX;
					int centPosY = WFY->GetPos() + m_iCentPulseY;
					//g_Log.LogShow2("校正后位置x：%d+%d,y:%d+%d",m_iWfPosX,m_iCentPulseX,m_iWfPosY,m_iCentPulseY);

					//g_Log.LogShow("晶圆识别角度=%.1f", m_dCentAngle);

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
						SetNextStep(200);//去下一点判断
						break;
					}
					SetNextStep(500);
					break;
				}
				else  //正中心没找到样本 ，跳转下一点有bug，晶圆盘不动
				{
					g_Log.LogShow2("图像正中心没有找到样本");
					SetPickDieFlag(4,m_iWfPosX,m_iWfPosY);
					g_AllFlag.m_bStop = TRUE;
					g_UserMsgBox.ShowUserMsgBox("图像正中心没有找到样本", OK_RED);
					SetNextStep(9999);
					//SetNextStep(200);//去下一点判断
					break;
				}
			}
			else  //正中心没找到样本
			{

				g_Log.LogShow2("图像正中心没有找到样本");
				SetPickDieFlag(4, m_iWfPosX, m_iWfPosY);
				//g_AllFlag.m_bStop = TRUE;
				//g_UserMsgBox.ShowUserMsgBox("图像正中心没有找到样本", OK_RED);
				//SetNextStep(9999);
				SetNextStep(100);//去下一点判断
				break;
			}
		}
		break;
	case 410:
		{
			//g_Log.LogShow2("晶圆识别角度:%.1f,设定角度=%d", m_dCentAngle, g_MachDat.GetPara(MACH_WF_ANGLE_ALARM));

			g_AllFlag.m_bCalAngle = TRUE;
			double dist =  m_dCentAngle * g_MachDat.GetPara(MACH_WF_R_PULSE_PER_DEG);

			if (!g_AllFlag.m_bSingleWfSerachStart && !g_AllFlag.m_bSingleWfTestDie &&
				fabs(m_dCentAngle) > g_MachDat.GetPara(MACH_WF_ANGLE_ALARM))
			{
				if (g_MachDat.GetPara(MACH_ENABLE_AUTO_ANGLE_CAL))
				{
					d_run.pMtrWFR->MoveRel((int)dist);
					//g_Log.LogShow2("晶圆1旋转脉冲:%d", (int)dist);
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
				//g_Log.LogShow("旋转计算后超出极限");
				g_AllFlag.m_bStop = TRUE;
				g_UserMsgBox.ShowUserMsgBox("晶圆1旋转后超出极限", OK_RED);
				SetNextStep(9999);
				break;
			}
			d_run.pMtrWFR->WaitStop();
			SetNextStep(500);
		}
		break;

	case 500: // 移动到正中心--拍照显示--晶园台准备好
		{
			WFX->MoveAbs(m_iWfCalX);
			WFY->MoveAbs(m_iWfCalY);
			WaitStopMtr(WFX,1,FALSE);
			WaitStopMtr(WFY,1,FALSE);

			Sleep(g_MachDat.GetPara(MACH_WF_CCD_DELAY));
			g_Ins.SoftTrig(eCCD_WF);
			g_Ins.WaitImageOk(eCCD_WF);
			ShowWfImage();
			if (g_AllFlag.m_bCalAngle)// 角度校正后对齐中心点
			{
				g_Ins.DoSerach(eCCD_WF, ePR_PT);
				g_Ins.GetResult(eCCD_WF, ePR_PT, &m_Num, m_Score, m_Posx, m_Posy, m_Angle, &m_Time);
				if (m_Num >= 1)
				{
					AddAllWFPos();
					if (GetImgCenterPos()) //获取中心坐标--找到了
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
			if (g_AllFlag.m_bWFDieReady ) //晶片被吸走
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