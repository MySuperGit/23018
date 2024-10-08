#include "StdAfx.h"
#include "..\IC_Bond.h"
#include "..\AllWork.h"


CAutoDbDb::CAutoDbDb()
{
	m_id = 2;
	m_strName = "DB";

	BA = NULL;
	BZ = NULL;
	EJP = NULL;
}

CAutoDbDb::~CAutoDbDb()
{

}

int CAutoDbDb::ChkMissDie()
{
	int nRet = 0;
	if (!g_MachDat.GetPara(MACH_ENABLE_MISSDIE) || d_run.pIn_MissDie->Get() == 1)
	{
		g_AllFlag.m_iMissDieTimes = 1;
		return 0;
	}

	g_AllFlag.m_iMissDieTimes++;
	g_AllFlag.m_iMissDieCounts++;
	g_MachDat.SetPara(MACH_MISS_DIE_TIMES, g_AllFlag.m_iMissDieCounts);
	if (g_AllFlag.m_iMissDieTimes > g_MachDat.GetPara(MACH_BA_MISSDIE_CNT))
	{
		return 1;
	}
		
	return 2;//SetNextStep(360); //去吹
}

int CAutoDbDb::Step()
{
	/*CString str;
	str.Format("CAutoDbDb::Step%d",m_step);
	g_Log.LogShow2(str);*/
	int rt = 1;
	switch (m_step)
	{
	case 0: 
		{
			g_AllFlag.m_iMissDieTimes = 1;
			d_run.Out_ColletVac_On();
			BZ->MoveAbs(0);
			BZ->WaitStop();
			EJP->MoveAbsMm(g_MachDat.GetParaF(MACH_F_EJP_RESET));
			EJP->WaitStop();
			if (g_AllFlag.m_bBdClawPkReady)
			{
				SetNextStep(400);
				break;
			}
			BA->MoveAbs(g_MachDat.GetPara(MACH_BA_PICK_PRE));
			BA->WaitStop();
			SetNextStep(100);
		}
		break;
	case 100: // 固晶台准备好了，再去吸晶
		{
			if (g_AllFlag.m_bStop)
			{
				SetNextStep(9999);
				break;
			}

			if (g_AllFlag.m_bSingleLookDh)
			{
				SetNextStep(200);
				break;
			}

			if (g_AllFlag.m_bBdOk || !d_run.IsTab1Ready() || !g_AllFlag.m_bCanBd)
			{
				SleepExms(50);
				break;
			}
				
			SetNextStep(200);
		}
		break;

	case 200:// 取晶前判断吸嘴是否堵塞
	{
		d_run.Out_ColletVac_On();
		
		SetNextStep(240);
	}
	break;

	case 240:// 芯片是否准备好
		{
			if (g_AllFlag.m_bStop)
			{
				SetNextStep(9999);
				break;
			}		
			if ( (g_AllFlag.m_bWFDieReady&& !g_AllFlag.m_bBdOk) || (g_MachDat.GetPara(MACH_WF_SRH_MODE) == 0))
			{
				SetNextStep(250);
				break;
			}
			SleepExms(1);
		}
		break;

	case 250:// BA转动到取晶位置 [2022-9-21 Pizhufan]
		{
			BA->ChangePosMove(g_MachDat.GetPara(MACH_BA_PICK_POS));
			d_run.pOut_EjpVac->On();
			WaitStopMtr(BA,1,TRUE);	
			
			SleepExms(g_MachDat.GetPara(MACH_BA_PICK_PRE_DELAY),TRUE); //预取延时
			SetNextStep(260);
		}
		break;
	case 260:
		{
			if (g_AllFlag.m_bStop)
			{
				SetNextStep(9999);
				break;
			}
			if (g_AllFlag.m_bBdInsOk)
			{
				SetNextStep(270);
				break;
			}
			SleepExms(1,TRUE);
		}
		break;
	case 270:// 取晶前判断吸嘴是否堵塞
		{
			if (g_MachDat.GetPara(MACH_ENABLE_MISSDIE))
			{
				if (d_run.pIn_MissDie->Get())
				{
					SleepExms(1);
					if (d_run.pIn_MissDie->Get())
					{
						SleepExms(10);
						if (d_run.pIn_MissDie->Get())
						{
							g_AllFlag.m_bStop = TRUE;
							EJP->MoveAbsMm(g_MachDat.GetParaF(MACH_F_EJP_RESET));
							EJP->WaitStop();
							g_UserMsgBox.ShowUserMsgBox("吸嘴被堵塞,请立即清洗吸嘴!", OK_RED);
							SetNextStep(9999);
							break;
						}
					}
				}
			}
			SetNextStep(300);
		}
		break;
	case 300:// BZ下压到取晶位置，取晶完成后回到预取晶高度 [2022-9-21 Pizhufan]
		{			
			if (g_AllFlag.m_bSingleStepBd)
			{
				if (IDCANCEL == g_UserMsgBox.ShowUserMsgBox("单步固晶中，是否继续...",OK_CAN_YEW))
				{
					g_AllFlag.m_bStop = TRUE;
					SetNextStep(9999);
					break;
				}
			}
			BZ->MoveAbs(g_MachDat.GetPara(MACH_BZ_PICK_POS));
			WaitStopMtr(BZ,1,TRUE);
					
			if (g_AllFlag.m_bSingleStepBd)
			{
				if (IDCANCEL == g_UserMsgBox.ShowUserMsgBox("单步固晶中，是否继续...",OK_CAN_YEW))
				{
					BZ->MoveAbs(g_MachDat.GetPara(MACH_BZ_PICK_RESET));
					BZ->WaitStop();
					g_AllFlag.m_bStop = TRUE;
					SetNextStep(9999);
					break;
				}
			}
			EJP->MoveAbsMm(g_MachDat.GetParaF(MACH_F_EJP_PICK_POS)+g_MachDat.GetParaF(MACH_F_EJP_RESET));//顶针顶起到Z取晶位
			WaitStopMtr(EJP,1,TRUE);

			// 顶针当前使用次数加1
			int nTimes = g_MachDat.GetPara(MACH_CURR_EJP_NUM) + 1;
			g_MachDat.SetPara(MACH_CURR_EJP_NUM, nTimes);
			if (nTimes >= g_MachDat.GetPara(MACH_EJP_NUM_MAX))
			{
				g_UserMsgBox.ShowUserMsgBox("顶针使用次数达到上限!",OK_RED);
				BZ->MoveAbs(g_MachDat.GetPara(MACH_BZ_PICK_RESET));
				BZ->WaitStop();
				g_AllFlag.m_bStop = TRUE;
				SetNextStep(9999);
				break;
			}

			// 吸嘴当前使用次数加1
			nTimes = g_MachDat.GetPara(MACH_CURR_NZ_NUM) + 1;
			g_MachDat.SetPara(MACH_CURR_NZ_NUM, nTimes);
			if (nTimes >= g_MachDat.GetPara(MACH_NZ_NUM_MAX))
			{
				g_UserMsgBox.ShowUserMsgBox("吸嘴使用次数达到上限.",OK_RED);

				BZ->MoveAbs(g_MachDat.GetPara(MACH_BZ_PICK_RESET));
				BZ->WaitStop();
				g_AllFlag.m_bStop = TRUE;
				SetNextStep(9999);
				break;
			}
		
			if (g_AllFlag.m_bSingleStepBd)
			{
				if (IDCANCEL == g_UserMsgBox.ShowUserMsgBox("单步固晶中，是否继续...",OK_CAN_YEW))
				{
					BZ->MoveAbs(g_MachDat.GetPara(MACH_BZ_PICK_RESET));
					EJP->MoveAbsMm(g_MachDat.GetParaF(MACH_F_EJP_RESET));
					EJP->WaitStop();
					BZ->WaitStop();
					g_AllFlag.m_bStop = TRUE;
					SetNextStep(9999);
					break;
				}
			}
			SleepExms(g_MachDat.GetPara(MACH_BA_PICK_DELAY),TRUE); //取晶延时
			BZ->MoveAbs(g_MachDat.GetPara(MACH_BZ_PICK_RESET));
			g_AllFlag.m_bBdClawPkReady = TRUE;
			WaitStopMtr(BZ,1,TRUE);	

			if (g_AllFlag.m_bSingleStepBd)
			{
				if (IDCANCEL == g_UserMsgBox.ShowUserMsgBox("单步固晶中，是否继续...", OK_CAN_YEW))
				{
					g_AllFlag.m_bStop = TRUE;
					SetNextStep(9999);
					break;
				}
			}

			if (g_AllFlag.m_bSingleLookDh)
			{
				SetNextStep(9999);
				break;
			}

			SetNextStep(400);
		}
		break;

	case 350:// 漏晶检测
		{
			if (g_MachDat.GetPara(MACH_ENABLE_MISSDIE))
			{		
				if (d_run.pIn_MissDie->Get() == 0)
				{					
					g_AllFlag.m_iMissDieTimes++;
					g_AllFlag.m_iMissDieCounts++;
					g_MachDat.SetPara(MACH_MISS_DIE_TIMES, g_AllFlag.m_iMissDieCounts);
					if (g_AllFlag.m_iMissDieTimes > g_MachDat.GetPara(MACH_BA_MISSDIE_CNT))
					{
						if (g_UserMsgBox.ShowUserMsgBox("吸嘴漏晶次数过多",OK_RED))
						{
							EJP->MoveAbsMm(g_MachDat.GetParaF(MACH_F_EJP_RESET));
							EJP->WaitStop();
							g_AllFlag.m_bBdClawPkReady = FALSE;
							g_AllFlag.m_bStop = TRUE;
							SetNextStep(9999);
							break;
						}
					}
					SetNextStep(360); //去吹
					break;

				}
				else
				{
					g_AllFlag.m_iMissDieTimes = 1;
				}
			}
			SetNextStep(400);
		}
		break;

	case 360:// 漏晶后重新取晶 [2022-9-21 Pizhufan]
		{
			EJP->MoveAbsMm(g_MachDat.GetParaF(MACH_F_EJP_RESET));
			BA->MoveAbs(g_MachDat.GetPara(MACH_BA_CLEAR_POS));
			WaitStopMtr(EJP,1,TRUE);	
			WaitStopMtr(BA,1,TRUE);	

			g_AllFlag.m_bWFDieReady = FALSE;

			d_run.pOutBit[OUT_EJP_VAC]->Off();
			d_run.Out_ColletBlow_On();// 打开弱吹
			SleepExms(g_MachDat.GetPara(MACH_BA_BOND_CEAR_BLOW_DELAY),TRUE);
			d_run.Out_ColletBlow_Off();// 关闭吸嘴所有真空
			BA->MoveAbs(g_MachDat.GetPara(MACH_BA_PICK_PRE));
			SetNextStep(200);
		}
		break;

	case 400:// BA转动到预固位置
		{
			BA->MoveAbs(g_MachDat.GetPara(MACH_BA_BOND_PRE));
			BZ->MoveAbs(g_MachDat.GetPara(MACH_BZ_BOND_RESET));
			EJP->MoveAbsMm(g_MachDat.GetParaF(MACH_F_EJP_RESET));

			//固晶方向是正的
			int dir = g_MachDat.GetPara(MACH_BA_BOND_POS) > 0?1:0;
			while (BA->IsMoving())
			{
				if (dir)
				{
					if (BA->GetPos() > g_MachDat.GetPara(MACH_BA_PICK_PRE))
					{
						break;
					}
				}
				else
				{
					if (BA->GetPos() < g_MachDat.GetPara(MACH_BA_PICK_PRE))
					{
						break;
					}
				}
				SleepExms(4,1);
			}

			//if (1==ChkMissDie())
			//{
			//	g_UserMsgBox.ShowUserMsgBox("吸嘴漏晶次数过多",OK_RED);
			//
			//	EJP->MoveAbs(g_MachDat.GetPara(MACH_EJP_RESET));
			//	WaitStopMtr(EJP,1,TRUE);	
			//	WaitStopMtr(BZ,1,TRUE);	
			//	g_AllFlag.m_bStop = TRUE;
			//	SetNextStep(9999);
			//	break;
			//}
			//if (2==ChkMissDie())
			//{
			//	WaitStopMtr(EJP,1,TRUE);	
			//	WaitStopMtr(BZ,1,TRUE);	
			//	SetNextStep(360);
			//	break;
			//}
			//else
			//{
			//	//continue;
			//}
			g_AllFlag.m_bWFDieReady = FALSE;
			WaitStopMtr(EJP,1,TRUE);	
			WaitStopMtr(BZ,1,TRUE);	

			d_run.pOutBit[OUT_EJP_VAC]->Off();


			if (g_AllFlag.m_bSingleStepBd)
			{
				if (IDCANCEL == g_UserMsgBox.ShowUserMsgBox("单步固晶中，是否继续...",OK_CAN_YEW))
				{
					g_AllFlag.m_bStop = TRUE;
					SetNextStep(9999);
					break;
				}
			}

			SetNextStep(500);
		}
		break;

	case 500:// BA转动到固晶位置
		{
			//吸起晶片后不能暂停
			//if (g_AllFlag.m_bStop)
			//{
			//	SetNextStep(9999);
			//	break;
			//}
			
			//吸起晶片后，工作台已经停止了，并且没有准备好，这里要停止，不然会卡死
			if (!g_AllFlag.m_bDbWhIsRuning && !g_AllFlag.m_bWHTabToReadyPos)
			{
				SetNextStep(9999);
				break;
			}
			if (!g_AllFlag.m_bWHTabToReadyPos)
			{
				SleepExms(1,1);
				break;
			}
			BA->ChangePosMove(g_MachDat.GetPara(MACH_BA_BOND_POS));
			SetNextStep(600);
		}
		break;

	case 600:// 固晶前漏晶检测并等待BA挺稳
		{
			WaitStopMtr(BA,1,TRUE);	

			if (g_MachDat.GetPara(MACH_ENABLE_MISSDIE))
			{
				if (d_run.pIn_MissDie->Get() == 0)
				{
					SleepExms(5);
					if (d_run.pIn_MissDie->Get() == 0)
					{
						g_AllFlag.m_iMissDieTimes++;
						g_AllFlag.m_iMissDieCounts++;
						g_MachDat.SetPara(MACH_MISS_DIE_TIMES, g_AllFlag.m_iMissDieCounts);
						if (g_AllFlag.m_iMissDieTimes > g_MachDat.GetPara(MACH_BA_MISSDIE_CNT))
						{
							g_UserMsgBox.ShowUserMsgBox("吸嘴漏晶次数过多", OK_RED);
							EJP->MoveAbsMm(g_MachDat.GetParaF(MACH_F_EJP_RESET));
							EJP->WaitStop();
							g_AllFlag.m_bStop = TRUE;
							g_AllFlag.m_bBdClawPkReady = FALSE;
							SetNextStep(9999);
							break;
						}
						else
						{
							SetNextStep(360); //去吹
						}
						break;
					}
				}
				g_AllFlag.m_iMissDieTimes = 1;
			}

			SleepExms(g_MachDat.GetPara(MACH_BA_BOND_PRE_DELAY),TRUE);//预固延迟
			if (g_AllFlag.m_bSingleStepBd)
			{
				if (IDCANCEL == g_UserMsgBox.ShowUserMsgBox("单步固晶中，是否继续...",OK_CAN_YEW))
				{
					g_AllFlag.m_bStop = TRUE;
					SetNextStep(9999);
					break;
				}
			}
			SetNextStep(700);
		}
		break;

	case 700:// BZ下压，固晶延时，BZ抬起
		{
			BZ->MoveAbs(g_MachDat.GetPara(MACH_BZ_BOND_POS));
			WaitStopMtr(BZ,1,TRUE);	
			if (g_AllFlag.m_bSingleStepBd)
			{
				if (IDCANCEL == g_UserMsgBox.ShowUserMsgBox("单步固晶中，是否继续...",OK_CAN_YEW))
				{
					BZ->MoveAbs(g_MachDat.GetPara(MACH_BZ_BOND_RESET));
					BZ->WaitStop();
					g_AllFlag.m_bStop = TRUE;
					SetNextStep(9999);
					break;
				}
			}
	
			d_run.Out_Collet_WeakBlow_On();
			if (g_AllFlag.CurGroupBonded == 1 && g_AllFlag.CurDieBonded == 1)
			{
				SleepExms(g_MachDat.GetPara(MACH_BA_BOND_DELAY)+10);
			}
			else
			{
				SleepExms(g_MachDat.GetPara(MACH_BA_BOND_DELAY),TRUE);
			}		
			d_run.Out_ColletBlow_Off();

			SleepExms(g_MachDat.GetPara(MACH_BA_BOND_POST_DELAY),TRUE);
	
			BZ->MoveAbs(g_MachDat.GetPara(MACH_BZ_BOND_RESET));
			WaitStopMtr(BZ,1,TRUE);
		
			g_AllFlag.m_bBdClawPkReady = FALSE;
			g_AllFlag.m_bBdInsOk = FALSE;
			//固晶完成后，点位增加
			if (g_ProgDataBd.m_bEnableFd)
			{
				g_AllFlag.CurFdBonded++;
				if (g_AllFlag.CurFdBonded > g_ProgDataBd.m_iTTFd)
				{
					g_AllFlag.CurDieBonded++;
					g_AllFlag.CurFdBonded = 1;
				}
			}
			else
			{
				g_AllFlag.CurDieBonded++;
			}
			g_AllFlag.m_Die_Bd_TT++;
			g_MachDat.SetPara(MACH_DIE_BD_TOTAL, g_AllFlag.m_Die_Bd_TT);
			g_AllFlag.m_iBdCycle = g_AllFlag.m_tmCycle.Getms();
			g_AllFlag.m_tmCycle.Start();


			if (g_ProgDataBd.m_bEnableFd)
			{
				if (g_AllFlag.CurFdBonded > g_ProgDataBd.m_iTTFd)
				{
					g_AllFlag.CurDieBonded++;
					g_AllFlag.CurFdBonded = 1;
				}
			}
			if (g_AllFlag.CurDieBonded > g_ProgDataBd.GetPosTotal() || g_AllFlag.CurGroupBonded > g_ProgDataBd.GetGroupTotal())
			{
				g_AllFlag.CurDieBonded = 1;
				g_AllFlag.CurGroupBonded += 1;
				g_AllFlag.m_bBdAlgOk = FALSE;
				if (g_AllFlag.CurGroupBonded > g_ProgDataBd.GetGroupTotal())
				{
					g_AllFlag.CurGroupBonded = g_ProgDataBd.GetGroupTotal() + 1;
					g_AllFlag.m_bBdOk = TRUE;
				}
			}

		

			if (g_AllFlag.m_bSingleStepBd)
			{
				if (IDCANCEL == g_UserMsgBox.ShowUserMsgBox("单步固晶中，是否继续...",OK_CAN_YEW))
				{
					g_AllFlag.m_bStop = TRUE;
					SetNextStep(9999);
					break;
				}
			}
			SetNextStep(800);
		}
		break;

	case 800: //摆臂摆过预备固晶位置，就拍照
		{

			//吸晶方向是正的
			int dir = g_MachDat.GetPara(MACH_BA_PICK_POS) > 0?1:0;

			BA->MoveAbs(g_MachDat.GetPara(MACH_BA_PICK_PRE));
			
			while (BA->IsMoving())
			{
				if (dir)
				{
					if (BA->GetPos() > g_MachDat.GetPara(MACH_BA_BOND_PRE))
					{
						break;
					}
				}
				else
				{
					if (BA->GetPos() < g_MachDat.GetPara(MACH_BA_BOND_PRE))
					{
						break;
					}
				}                                                  

				SleepExms(4,TRUE);
			}
		
			g_AllFlag.m_bWHTabToReadyPos = FALSE; // 发动一下个固晶位置

			if (g_AllFlag.m_bStop || g_AllFlag.m_bSingleBd ||g_AllFlag.m_bSingleStepBd || (g_AllFlag.m_bSingleAutoBd && g_AllFlag.m_bBdOk))
			{
				BA->ChangePosMove(g_MachDat.GetPara(MACH_BA_CLEAR_POS));
				BA->WaitStop();				
				SetNextStep(9999);
				break;
			}
			//d_run.Out_ColletVac_On();
			SetNextStep(100);			
		}
		break;

	case 9999:
		{
			if (!g_AllFlag.m_bSingleLookDh)
			{
				d_run.Out_ColletVac_Off();
			}	
			g_AllFlag.m_bBdClawPkReady = FALSE;
			g_AllFlag.m_bBdInsOk = TRUE;
			d_run.pOut_EjpVac->Off();
			BZ->MoveAbs(0);
			BZ->WaitStop();
			EJP->MoveAbsMm(g_MachDat.GetParaF(MACH_F_EJP_RESET));
			EJP->WaitStop();
			BA->ChangePosMove(g_MachDat.GetPara(MACH_BA_CLEAR_POS));
			BA->WaitStop();
			rt = 0;
		}
	}
	return rt;
}