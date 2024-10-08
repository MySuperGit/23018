#include "StdAfx.h"
#include "..\IC_Bond.h"
#include "..\AllWork.h"


CAutoDbWh::CAutoDbWh()
{
	m_id = 1;
	m_strName = "WH";

	m_iAlg1RefPosX = 0;
	m_iAlg1RefPosY = 0;
	m_iAlg2RefPosX = 0;
	m_iAlg2RefPosY = 0;
}

CAutoDbWh::~CAutoDbWh()
{

}

int CAutoDbWh::Step()
{
	/*CString str;
	str.Format("CAutoDbWh::Step%d",m_step);
	g_Log.LogShow2(str);*/

	int rt = 1;
	switch (m_step)
	{
	case 0:
		{

			if (g_AllFlag.m_bSingleBdAlg)
			{
				SetNextStep(100);
				break;
			}
			if (!d_run.IsTab1Ready() || g_AllFlag.m_bBdOk || !g_AllFlag.m_bCanBd)
			{
				if (g_AllFlag.m_bStop || g_AllFlag.m_bSingleAutoBd)
				{
					SetNextStep(9999);
					break;
				}
				Sleep(50);
				break;
			}

			SetNextStep(100);
		}
		break;

	case 100:
		{
			if (g_ProgDataBd.m_bEnableFd)
			{
				if (g_AllFlag.CurFdBonded > g_ProgDataBd.m_iTTFd)
				{
					g_AllFlag.CurDieBonded++;
					g_AllFlag.CurFdBonded = 1;
				}
			}
			if (g_AllFlag.CurDieBonded > g_ProgDataBd.GetPosTotal() || g_AllFlag.CurGroupBonded>g_ProgDataBd.GetGroupTotal())
			{
				g_AllFlag.CurDieBonded=1;
				g_AllFlag.CurGroupBonded+=1;
				g_AllFlag.m_bBdAlgOk = FALSE;
				if (g_AllFlag.CurGroupBonded > g_ProgDataBd.GetGroupTotal())
				{
					g_AllFlag.CurGroupBonded = g_ProgDataBd.GetGroupTotal() + 1;
					g_AllFlag.m_bBdOk = TRUE;
					if (g_AllFlag.m_bSingleAutoBd)
					{
						SetNextStep(9999);
						break;
					}
					SetNextStep(0);
					break;
				}
			}

			if (g_MachDat.GetPara(MACH_BD_ALG_MODE) == 0 || g_MachDat.GetPara(MACH_BD_ALG_MODE) == 1)  //不对点
			{
				SetNextStep(3000);
				break;
			}
			//else if (g_MachDat.GetPara(MACH_BD_ALG_MODE) == 1) //组群对点
			//{
			//	if (!g_AllFlag.m_bBdAlgOk ||g_AllFlag.m_bSingleBdAlg)
			//	{
			//		SetNextStep(1000);
			//		break;
			//	}
			//}
			else  //每次对点
			{
				SetNextStep(2000);
				break;
			}
			SetNextStep(3000);
		}
		break;

	case 1000:  //组群对点
		{
			int AlgPosx1, AlgPosy1;
			g_ProgDataBd.GetAlg1(g_AllFlag.CurGroupBonded,AlgPosx1, AlgPosy1);
			WHX->MoveAbs(AlgPosx1);
			WaitStopMtr(WHX,1,FALSE);
			WHY->MoveAbs(AlgPosy1);
			WaitStopMtr(WHY,1,FALSE);
		
			SleepExms(g_MachDat.GetPara(MACH_WH_CCD_DELAY));			
			g_Ins.SoftTrig(eCCD_WH);
			g_Ins.DoSerach(eCCD_WH,ePR_ALG1);
			gDlgMainBondWnd->m_pImageView[0].SetID(eCCD_WH, ePR_ALG1);
			double score, posx, posy, angle, time;
			g_Ins.GetResult(eCCD_WH, ePR_ALG1, &score, &posx, &posy, &angle, &time);
			BOOL bFind = TRUE;
			if (score < g_Ins.GetPara(eCCD_WH, ePR_ALG1, eSCORE) || score < 1)
			{
				bFind = FALSE;
				g_Log.LogShow("固晶台对点1图像识别分数：%d小于设定分数：%d", time, g_Ins.GetPara(eCCD_WH, ePR_ALG1, eSCORE));
			}
			g_Log.LogShow("固晶台对点1图像识别分数：%.2f,时间：%.2f", score, time);
			if (bFind)
			{
				double ratex = g_Ins.GetParaF(eCCD_WH, eCAL_RESULT_RX);
				double ratey = g_Ins.GetParaF(eCCD_WH, eCAL_RESULT_RY);
				double rateXDir = g_Ins.GetParaF(eCCD_WH, eCAL_RX_DIR) > 0 ? 1.0 : -1.0;
				double rateYDir = g_Ins.GetParaF(eCCD_WH, eCAL_RY_DIR) > 0 ? 1.0 : -1.0;
				double xx = posx * ratex * rateXDir;
				double yy = posy * ratey * rateYDir;

				m_iAlg1RefPosX = AlgPosx1 + WHX->MmToPulse(xx);
				m_iAlg1RefPosY = AlgPosy1 + WHY->MmToPulse(yy);

				WHX->MoveRelMm(xx);
				WHY->MoveRelMm(yy);
				WaitStopMtr(WHX,1,FALSE);
				WaitStopMtr(WHY,1,FALSE);

				SleepExms(g_MachDat.GetPara(MACH_WH_CCD_DELAY));
				g_Ins.SoftTrig(eCCD_WH);	
				g_Ins.WaitImageOk(eCCD_WH);
				SetNextStep(1200);
				break;
			}
			else
			{
				if (g_AllFlag.m_bDemoMode)
				{
					m_iAlg1RefPosX = AlgPosx1;
					m_iAlg1RefPosY = AlgPosy1;
					SetNextStep(1200);
					break;
				}
				SetNextStep(1100);
			}
		}
		break;

	case 1100:
		{
			int rtn = g_UserMsgBox.ShowManualAlgDlg(eCCD_WH, WHX, WHY);
			if (IDOK == rtn)
			{
				m_iAlg1RefPosX = WHX->GetPos();
				m_iAlg1RefPosY = WHY->GetPos();
				SetNextStep(1200);
			}
			else
			{
				g_AllFlag.m_bStop = TRUE;
				SetNextStep(9999);
				break;
			}
		}
		break;

	case 1200:
		{
			int AlgPosx2, AlgPosy2;
			g_ProgDataBd.GetAlg2(g_AllFlag.CurGroupBonded,AlgPosx2, AlgPosy2);
			WHX->MoveAbs(AlgPosx2);
			WHY->MoveAbs(AlgPosy2);
			WaitStopMtr(WHX,1,FALSE);
			WaitStopMtr(WHY,1,FALSE);
			SleepExms(g_MachDat.GetPara(MACH_WH_CCD_DELAY));			
			g_Ins.SoftTrig(eCCD_WH);
			g_Ins.DoSerach(eCCD_WH,ePR_ALG2);
			gDlgMainBondWnd->m_pImageView[0].SetID(eCCD_WH, ePR_ALG2);
			double score, posx, posy, angle, time;
			g_Ins.GetResult(eCCD_WH, ePR_ALG2, &score, &posx, &posy, &angle, &time);
			BOOL bFind = TRUE;
			if (score < g_Ins.GetPara(eCCD_WH, ePR_ALG2, eSCORE) || score < 1)
			{
				bFind = FALSE;
				g_Log.LogShow("固晶台对点2图像识别分数：%d小于设定分数：%d", time, g_Ins.GetPara(eCCD_WH, ePR_ALG2, eSCORE));
			}
			g_Log.LogShow("固晶台对点2图像识别分数：%.2f,时间：%.2f", score, time);
			if (bFind)
			{
				double ratex = g_Ins.GetParaF(eCCD_WH, eCAL_RESULT_RX);
				double ratey = g_Ins.GetParaF(eCCD_WH,  eCAL_RESULT_RY);
				double rateXDir = g_Ins.GetParaF(eCCD_WH, eCAL_RX_DIR) > 0 ? 1.0 : -1.0;
				double rateYDir = g_Ins.GetParaF(eCCD_WH, eCAL_RY_DIR) > 0 ? 1.0 : -1.0;
				double xx = posx * ratex * rateXDir;
				double yy = posy * ratey * rateYDir;

				m_iAlg2RefPosX = AlgPosx2 + WHX->MmToPulse(xx);
				m_iAlg2RefPosY = AlgPosy2 + WHY->MmToPulse(yy);

				WHX->MoveRelMm(xx);
				WHY->MoveRelMm(yy);
				WaitStopMtr(WHX,1,FALSE);
				WaitStopMtr(WHY,1,FALSE);
				SleepExms(g_MachDat.GetPara(MACH_WH_CCD_DELAY));
				g_Ins.SoftTrig(eCCD_WH);	
				g_Ins.WaitImageOk(eCCD_WH);
				SetNextStep(1400);
				break;
			}
			else
			{
				if (g_AllFlag.m_bDemoMode)
				{
					m_iAlg2RefPosX = AlgPosx2;
					m_iAlg2RefPosY = AlgPosy2;
					SetNextStep(1400);
					break;
				}
				SetNextStep(1300);
			}
		}
		break;

	case 1300:
		{
			int rtn = g_UserMsgBox.ShowManualAlgDlg(eCCD_WH, WHX, WHY);
			if (IDOK == rtn)
			{
				m_iAlg2RefPosX = WHX->GetPos();
				m_iAlg2RefPosY = WHY->GetPos();
				SetNextStep(1400);
			}
			else
			{
				g_AllFlag.m_bStop = TRUE;
				SetNextStep(9999);
				break;
			}
		}
		break;

	case 1400: //固晶台对点结束
		{
			g_ProgDataBd.SetRefAlg(g_AllFlag.CurGroupBonded, m_iAlg1RefPosX,m_iAlg1RefPosY, m_iAlg2RefPosX,m_iAlg2RefPosY);

			g_AllFlag.m_bBdAlgOk = TRUE;

			if (g_AllFlag.m_bSingleBdAlg)
			{
				SetNextStep(9999);
				break;
			}
			SetNextStep(3000);
			break;
		}
		break;

	case 2000: //单次校正
		{
			g_ProgDataBd.GetPos(g_AllFlag.CurGroupBonded,g_AllFlag.CurDieBonded,m_iCurPosX,m_iCurPosY);
			double mmx,mmy;
			int Fdx=0,Fdy=0;
			if (g_ProgDataBd.m_bEnableFd)
			{
				g_ProgDataBd.GetFdPos(g_AllFlag.CurFdBonded,mmx,mmy);
				Fdx = WHX->MmToPulse(mmx);
				Fdy = WHY->MmToPulse(mmy);
			}
			m_iCurPosX += Fdx;
			m_iCurPosY += Fdy;

			WHX->MoveAbs(m_iCurPosX);
			WHY->MoveAbs(m_iCurPosY);
			WaitStopMtr(WHX,1,FALSE);
			WaitStopMtr(WHY,1,FALSE);
			SleepExms(g_MachDat.GetPara(MACH_WH_CCD_DELAY));			
			g_Ins.SoftTrig(eCCD_WH);
			g_Ins.DoSerach(eCCD_WH,ePR_PT);
			gDlgMainBondWnd->m_pImageView[0].SetID(eCCD_WH, ePR_PT);
			double score, posx, posy, angle, time;
			g_Ins.GetResult(eCCD_WH, ePR_PT, &score, &posx, &posy, &angle, &time);
			BOOL bFind = TRUE;
			if (score < g_Ins.GetPara(eCCD_WH, ePR_PT, eSCORE) || score < 1)
			{
				bFind = FALSE;
				g_Log.LogShow("固晶样本识别分数：%d小于设定分数：%d", time, g_Ins.GetPara(eCCD_WH, ePR_ALG1, eSCORE));
			}
			//g_Log.LogShow("固晶台对点1图像识别分数：%.2f,时间：%.2f", score, time);
			if (g_AllFlag.CurFdBonded == 1)
			{
				bFind = FALSE;
			}
			else
			{
				bFind = TRUE;
			}
			if (bFind)
			{
				g_AllFlag.m_iBdTabMissTimes = 0;
				double ratex = g_Ins.GetParaF(eCCD_WH, eCAL_RESULT_RX);
				double ratey = g_Ins.GetParaF(eCCD_WH, eCAL_RESULT_RY);
				double rateXDir = g_Ins.GetParaF(eCCD_WH, eCAL_RX_DIR) > 0 ? 1.0 : -1.0;
				double rateYDir = g_Ins.GetParaF(eCCD_WH, eCAL_RY_DIR) > 0 ? 1.0 : -1.0;
				double xx = posx * ratex * rateXDir;
				double yy = posy * ratey * rateYDir;
				int posxx = WHX->MmToPulse(xx);
				int posyy = WHY->MmToPulse(yy);
				/*if (g_MachDat.GetPara(MACH_ENABLE_BDTAB_BAD_JUMP))
				{
				WHX->MoveAbs(m_iCurPosX + g_ProgDataBd.m_iBdOffX);
				WHY->MoveAbs(m_iCurPosY + g_ProgDataBd.m_iBdOffY);
				}
				else*/
				{
					WHX->MoveAbs(m_iCurPosX + posxx + g_ProgDataBd.m_iBdOffX);
					WHY->MoveAbs(m_iCurPosY + posyy + g_ProgDataBd.m_iBdOffY);
				}
				WaitStopMtr(WHX,1,FALSE);
				WaitStopMtr(WHY,1,FALSE);
				SleepExms(g_MachDat.GetPara(MACH_WH_CCD_DELAY));
				g_Ins.SoftTrig(eCCD_WH);	
				g_Ins.WaitImageOk(eCCD_WH);
				SetNextStep(4000);
				break;
			}
			else
			{
				if (g_MachDat.GetPara(MACH_ENABLE_BDTAB_BAD_JUMP))
				{
					if (g_AllFlag.CurFdBonded == 1)
					{
						g_AllFlag.CurDieBonded++;
						g_AllFlag.CurFdBonded = 1;
						g_AllFlag.m_iBdTabMissTimes++;
						if (g_AllFlag.m_iBdTabMissTimes > g_MachDat.GetPara(MACH_BDTAB_CONT_NG_TIMES))
						{
							g_UserMsgBox.ShowUserMsgBox("固晶台连续NG次数过多", OK_RED);
							g_AllFlag.m_bStop = TRUE;
							SetNextStep(9999);
							break;
						}
					}
					else
					{
						SetNextStep(4000);
						break;
					}

					SetNextStep(0);
					break;
				}
				if (g_AllFlag.m_bDemoMode)
				{
					SetNextStep(2200);
					break;
				}
				SetNextStep(2100);
			}
		}
		break;

	case 2100:
		{
			int rtn = g_UserMsgBox.ShowManualAlgDlg(eCCD_WH, WHX, WHY);
			if (IDOK == rtn)
			{
				WHX->MoveRel( g_ProgDataBd.m_iBdOffX);
				WHY->MoveRel( g_ProgDataBd.m_iBdOffY);
				WaitStopMtr(WHX,1,FALSE);
				WaitStopMtr(WHY,1,FALSE);
				SetNextStep(4000);
			}
			else
			{
				g_AllFlag.m_bStop = TRUE;
				SetNextStep(9999);
				break;
			}
		}
		break;

	case 3000:  //不对点或者组群对点，到固晶位
		{
			
			g_AllFlag.m_bWHTabToReadyPos = FALSE; //固晶台准备好置0
			//if (g_MachDat.GetPara(MACH_BD_ALG_MODE) == 1) //组群对点
			//{
			//	g_ProgDataBd.GetAdjPos(g_AllFlag.CurGroupBonded,g_AllFlag.CurDieBonded,m_iCurPosX,m_iCurPosY);
			//}
			//else
			{
				g_ProgDataBd.GetPos(g_AllFlag.CurGroupBonded,g_AllFlag.CurDieBonded,m_iCurPosX,m_iCurPosY);
			}
			
			double mmx,mmy;
			int Fdx=0,Fdy=0;
			if (g_ProgDataBd.m_bEnableFd)
			{
				g_ProgDataBd.GetFdPos(g_AllFlag.CurFdBonded,mmx,mmy);
				Fdx = WHX->MmToPulse(mmx);
				Fdy = WHY->MmToPulse(mmy);
			}
			m_iCurPosX += Fdx + g_ProgDataBd.m_iBdOffX;
			m_iCurPosY += Fdy + g_ProgDataBd.m_iBdOffY;

			WHX->ChangePosMove(m_iCurPosX);
			WHY->ChangePosMove(m_iCurPosY);
			WaitStopMtr(WHX,1,FALSE);
			WaitStopMtr(WHY,1,FALSE);
	
			if (g_AllFlag.CurGroupBonded == 1 && g_AllFlag.CurDieBonded == 1)
			{
				SleepExms(10);
			}
			SetNextStep(4000);
		}
		break;

	case 4000:// 固前检测
		{
			if (g_MachDat.GetPara(MACH_PRE_BD_INS))
			{
				Sleep(g_MachDat.GetPara(MACH_WH_CCD_DELAY));
				g_Ins.SoftTrig(eCCD_WH);
				g_Ins.WaitImageOk(eCCD_WH);

				ePRName prid = ePR_PRE;
				gDlgMainBondWnd->m_pImageView[0].SetID(eCCD_WH, prid);
				g_Ins.DoSerach(eCCD_WH, prid);
				double score, posx, posy, angle, time;
				g_Ins.GetResult(eCCD_WH, prid, &score, &posx, &posy, &angle, &time);
				BOOL bFind = TRUE;
				if (score < g_Ins.GetPara(eCCD_WH, prid, eSCORE) || score < 1)
				{
					bFind = FALSE;
					g_Log.LogShow("固前检测识别分数：%d小于设定分数：%d", time, g_Ins.GetPara(eCCD_WH, prid, eSCORE));
					if (IDCANCEL == g_UserMsgBox.ShowUserMsgBox("固晶前检测失败，是否继续？", OK_CAN_RED))
					{
						g_AllFlag.m_bStop = TRUE;
						SetNextStep(9999);
						break;
					}
				}		
			}
			SetNextStep(4001);
		}
		break;
	case 4001: //到固晶中心位置了，可以下来固晶了
		{
			g_AllFlag.m_bWHTabToReadyPos = TRUE;
			if ( g_AllFlag.m_bSingleBdAlg|| (g_AllFlag.m_bSingleAutoBd && g_AllFlag.m_bBdOk))
			{
				SetNextStep(9999);
				break;
			}
			SetNextStep(4100);
		}
		break;

	case 4100:
		{
		if (g_AllFlag.m_bStop && !g_AllFlag.m_bBdClawPkReady)
		{
			SetNextStep(9999);
			break;
		}
			if (g_AllFlag.m_bSingleAutoBd && g_AllFlag.m_bBdOk)
			{
				SetNextStep(9999);
				break;
			}
			SleepExms(4,1);
			if (!g_AllFlag.m_bWHTabToReadyPos) //晶片抓走以后要拍照
			{
				SetNextStep(4200);
			}
		}
		break;

	case 4200:
		{
			//不是每次对点，要给固好的芯片拍张照显示出来
			//if (g_MachDat.GetPara(MACH_BD_ALG_MODE) != 2) 
		Sleep(g_MachDat.GetPara(MACH_WH_CCD_DELAY));
		g_Ins.SoftTrig(eCCD_WH);
		g_Ins.WaitImageOk(eCCD_WH);
		if (g_MachDat.GetPara(MACH_ENABLE_BD_INS))
		{
			ePRName prid = ePR_AFTA;
			gDlgMainBondWnd->m_pImageView[0].SetID(eCCD_WH, prid);
			g_Ins.DoSerach(eCCD_WH, prid);
			double score, posx, posy, angle, time;
			g_Ins.GetResult(eCCD_WH, prid, &score, &posx, &posy, &angle, &time);
			BOOL bFind = TRUE;
			if (score < g_Ins.GetPara(eCCD_WH, prid, eSCORE) || score < 1)
			{
				bFind = FALSE;
				g_Log.LogShow("固后检测识别分数：%d小于设定分数：%d", time, g_Ins.GetPara(eCCD_WH, prid, eSCORE));
				g_UserMsgBox.ShowUserMsgBox("固晶后检测分数过低", OK_RED);
				g_AllFlag.m_bStop = TRUE;
				SetNextStep(9999);
				break;
			}		
			
		}
		g_AllFlag.m_bBdInsOk = TRUE;

			if (g_AllFlag.m_bSingleStepBd || g_AllFlag.m_bSingleBd ||g_AllFlag.m_bStop)
			{
				SetNextStep(9999);
				break;
			}
			SetNextStep(0);
		}
		break;

	//	//换料
	//case 6000:
	//	{
	//		d_run.pMtrWHX->MoveAbs(g_MachDat.GetPara(MACH_BDTAB_INPUT_X));
	//		d_run.pMtrWHY->MoveAbs(g_MachDat.GetPara(MACH_BDTAB_INPUT_Y));
	//		d_run.pMtrWHX->WaitStop();
	//		d_run.pMtrWHY->WaitStop();
	//		if (IDOK == g_UserMsgBox.ShowUserMsgBox("请更换固晶台料盘",OK_CAN_RED))
	//		{
	//			g_AllFlag.m_bBdTabReady = TRUE;
	//			g_AllFlag.CurGroupBonded = 1;
	//			g_AllFlag.CurDieBonded = 1;
	//			g_AllFlag.CurFdBonded = 1;
	//			g_AllFlag.m_bBdOk = FALSE;
	//			SetNextStep(0);
	//		}
	//		else
	//		{
	//			g_AllFlag.m_bStop = TRUE;
	//			SetNextStep(9999);
	//			break;
	//		}
	//	}
	//	break;

	case 9999:
		{
			g_AllFlag.m_iBdTabMissTimes = 0;
			rt = 0;
		}
	}
	return rt;
}
