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
		
	return 2;//SetNextStep(360); //ȥ��
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
	case 100: // �̾�̨׼�����ˣ���ȥ����
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

	case 200:// ȡ��ǰ�ж������Ƿ����
	{
		d_run.Out_ColletVac_On();
		
		SetNextStep(240);
	}
	break;

	case 240:// оƬ�Ƿ�׼����
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

	case 250:// BAת����ȡ��λ�� [2022-9-21 Pizhufan]
		{
			BA->ChangePosMove(g_MachDat.GetPara(MACH_BA_PICK_POS));
			d_run.pOut_EjpVac->On();
			WaitStopMtr(BA,1,TRUE);	
			
			SleepExms(g_MachDat.GetPara(MACH_BA_PICK_PRE_DELAY),TRUE); //Ԥȡ��ʱ
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
	case 270:// ȡ��ǰ�ж������Ƿ����
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
							g_UserMsgBox.ShowUserMsgBox("���챻����,��������ϴ����!", OK_RED);
							SetNextStep(9999);
							break;
						}
					}
				}
			}
			SetNextStep(300);
		}
		break;
	case 300:// BZ��ѹ��ȡ��λ�ã�ȡ����ɺ�ص�Ԥȡ���߶� [2022-9-21 Pizhufan]
		{			
			if (g_AllFlag.m_bSingleStepBd)
			{
				if (IDCANCEL == g_UserMsgBox.ShowUserMsgBox("�����̾��У��Ƿ����...",OK_CAN_YEW))
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
				if (IDCANCEL == g_UserMsgBox.ShowUserMsgBox("�����̾��У��Ƿ����...",OK_CAN_YEW))
				{
					BZ->MoveAbs(g_MachDat.GetPara(MACH_BZ_PICK_RESET));
					BZ->WaitStop();
					g_AllFlag.m_bStop = TRUE;
					SetNextStep(9999);
					break;
				}
			}
			EJP->MoveAbsMm(g_MachDat.GetParaF(MACH_F_EJP_PICK_POS)+g_MachDat.GetParaF(MACH_F_EJP_RESET));//���붥��Zȡ��λ
			WaitStopMtr(EJP,1,TRUE);

			// ���뵱ǰʹ�ô�����1
			int nTimes = g_MachDat.GetPara(MACH_CURR_EJP_NUM) + 1;
			g_MachDat.SetPara(MACH_CURR_EJP_NUM, nTimes);
			if (nTimes >= g_MachDat.GetPara(MACH_EJP_NUM_MAX))
			{
				g_UserMsgBox.ShowUserMsgBox("����ʹ�ô����ﵽ����!",OK_RED);
				BZ->MoveAbs(g_MachDat.GetPara(MACH_BZ_PICK_RESET));
				BZ->WaitStop();
				g_AllFlag.m_bStop = TRUE;
				SetNextStep(9999);
				break;
			}

			// ���쵱ǰʹ�ô�����1
			nTimes = g_MachDat.GetPara(MACH_CURR_NZ_NUM) + 1;
			g_MachDat.SetPara(MACH_CURR_NZ_NUM, nTimes);
			if (nTimes >= g_MachDat.GetPara(MACH_NZ_NUM_MAX))
			{
				g_UserMsgBox.ShowUserMsgBox("����ʹ�ô����ﵽ����.",OK_RED);

				BZ->MoveAbs(g_MachDat.GetPara(MACH_BZ_PICK_RESET));
				BZ->WaitStop();
				g_AllFlag.m_bStop = TRUE;
				SetNextStep(9999);
				break;
			}
		
			if (g_AllFlag.m_bSingleStepBd)
			{
				if (IDCANCEL == g_UserMsgBox.ShowUserMsgBox("�����̾��У��Ƿ����...",OK_CAN_YEW))
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
			SleepExms(g_MachDat.GetPara(MACH_BA_PICK_DELAY),TRUE); //ȡ����ʱ
			BZ->MoveAbs(g_MachDat.GetPara(MACH_BZ_PICK_RESET));
			g_AllFlag.m_bBdClawPkReady = TRUE;
			WaitStopMtr(BZ,1,TRUE);	

			if (g_AllFlag.m_bSingleStepBd)
			{
				if (IDCANCEL == g_UserMsgBox.ShowUserMsgBox("�����̾��У��Ƿ����...", OK_CAN_YEW))
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

	case 350:// ©�����
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
						if (g_UserMsgBox.ShowUserMsgBox("����©����������",OK_RED))
						{
							EJP->MoveAbsMm(g_MachDat.GetParaF(MACH_F_EJP_RESET));
							EJP->WaitStop();
							g_AllFlag.m_bBdClawPkReady = FALSE;
							g_AllFlag.m_bStop = TRUE;
							SetNextStep(9999);
							break;
						}
					}
					SetNextStep(360); //ȥ��
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

	case 360:// ©��������ȡ�� [2022-9-21 Pizhufan]
		{
			EJP->MoveAbsMm(g_MachDat.GetParaF(MACH_F_EJP_RESET));
			BA->MoveAbs(g_MachDat.GetPara(MACH_BA_CLEAR_POS));
			WaitStopMtr(EJP,1,TRUE);	
			WaitStopMtr(BA,1,TRUE);	

			g_AllFlag.m_bWFDieReady = FALSE;

			d_run.pOutBit[OUT_EJP_VAC]->Off();
			d_run.Out_ColletBlow_On();// ������
			SleepExms(g_MachDat.GetPara(MACH_BA_BOND_CEAR_BLOW_DELAY),TRUE);
			d_run.Out_ColletBlow_Off();// �ر������������
			BA->MoveAbs(g_MachDat.GetPara(MACH_BA_PICK_PRE));
			SetNextStep(200);
		}
		break;

	case 400:// BAת����Ԥ��λ��
		{
			BA->MoveAbs(g_MachDat.GetPara(MACH_BA_BOND_PRE));
			BZ->MoveAbs(g_MachDat.GetPara(MACH_BZ_BOND_RESET));
			EJP->MoveAbsMm(g_MachDat.GetParaF(MACH_F_EJP_RESET));

			//�̾�����������
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
			//	g_UserMsgBox.ShowUserMsgBox("����©����������",OK_RED);
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
				if (IDCANCEL == g_UserMsgBox.ShowUserMsgBox("�����̾��У��Ƿ����...",OK_CAN_YEW))
				{
					g_AllFlag.m_bStop = TRUE;
					SetNextStep(9999);
					break;
				}
			}

			SetNextStep(500);
		}
		break;

	case 500:// BAת�����̾�λ��
		{
			//����Ƭ������ͣ
			//if (g_AllFlag.m_bStop)
			//{
			//	SetNextStep(9999);
			//	break;
			//}
			
			//����Ƭ�󣬹���̨�Ѿ�ֹͣ�ˣ�����û��׼���ã�����Ҫֹͣ����Ȼ�Ῠ��
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

	case 600:// �̾�ǰ©����Ⲣ�ȴ�BAͦ��
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
							g_UserMsgBox.ShowUserMsgBox("����©����������", OK_RED);
							EJP->MoveAbsMm(g_MachDat.GetParaF(MACH_F_EJP_RESET));
							EJP->WaitStop();
							g_AllFlag.m_bStop = TRUE;
							g_AllFlag.m_bBdClawPkReady = FALSE;
							SetNextStep(9999);
							break;
						}
						else
						{
							SetNextStep(360); //ȥ��
						}
						break;
					}
				}
				g_AllFlag.m_iMissDieTimes = 1;
			}

			SleepExms(g_MachDat.GetPara(MACH_BA_BOND_PRE_DELAY),TRUE);//Ԥ���ӳ�
			if (g_AllFlag.m_bSingleStepBd)
			{
				if (IDCANCEL == g_UserMsgBox.ShowUserMsgBox("�����̾��У��Ƿ����...",OK_CAN_YEW))
				{
					g_AllFlag.m_bStop = TRUE;
					SetNextStep(9999);
					break;
				}
			}
			SetNextStep(700);
		}
		break;

	case 700:// BZ��ѹ���̾���ʱ��BZ̧��
		{
			BZ->MoveAbs(g_MachDat.GetPara(MACH_BZ_BOND_POS));
			WaitStopMtr(BZ,1,TRUE);	
			if (g_AllFlag.m_bSingleStepBd)
			{
				if (IDCANCEL == g_UserMsgBox.ShowUserMsgBox("�����̾��У��Ƿ����...",OK_CAN_YEW))
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
			//�̾���ɺ󣬵�λ����
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
				if (IDCANCEL == g_UserMsgBox.ShowUserMsgBox("�����̾��У��Ƿ����...",OK_CAN_YEW))
				{
					g_AllFlag.m_bStop = TRUE;
					SetNextStep(9999);
					break;
				}
			}
			SetNextStep(800);
		}
		break;

	case 800: //�ڱ۰ڹ�Ԥ���̾�λ�ã�������
		{

			//��������������
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
		
			g_AllFlag.m_bWHTabToReadyPos = FALSE; // ����һ�¸��̾�λ��

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