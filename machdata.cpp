#include "stdafx.h"
#include <direct.h>
#include "machdata.h"
#define MOTORTOTAL	10
static char s_ParaMt[30]=".\\ParaMt";
static char s_ParaMa[30]=".\\ParaMa";


CMachData::CMachData()
{
	for(int i=0; i<1000; i++)
	{
		d_DebugPara[i] = 0;
	}
}
CMachData::~CMachData()
{
}

void CMachData::LoadMotorPara()
{
	FILE* pFile;
	char name[255];
	sprintf(name, "%s\\MotorPar.dat", s_ParaMt);
	pFile = fopen(name, "rb");
	if(!pFile)
		return;	
	//注意保存和载入的秩序必须是一致的
	dllCMotorBase* AllMotor[MOTORTOTAL];
	AllMotor[0] = &WHX;
	AllMotor[1] = &WHY;
	AllMotor[2] = &WFX;
	AllMotor[3] = &WFY;
	AllMotor[4] = &EJP;	
	AllMotor[5] = &BA;
	AllMotor[6] = &BZ;
	AllMotor[7] = &EA;
	AllMotor[8] = &EZ;
	AllMotor[9] = &ED;

	int para[MOTOR_PARA_ED-MOTOR_PARA_ST];
	for(int i=0; i<MOTORTOTAL; i++)
	{
		fread(para, sizeof(para), 1, pFile);
		AllMotor[i]->SetPara(MOTOR_HOME_VEL, para[MOTOR_HOME_VEL-MOTOR_PARA_ST]);
		AllMotor[i]->SetPara(MOTOR_MAX_VEL, para[MOTOR_MAX_VEL-MOTOR_PARA_ST]);
		AllMotor[i]->SetPara(MOTOR_MIN_VEL, para[MOTOR_MIN_VEL-MOTOR_PARA_ST]);
		AllMotor[i]->SetPara(MOTOR_INIT_VEL, para[MOTOR_INIT_VEL-MOTOR_PARA_ST]);
		AllMotor[i]->SetPara(MOTOR_VEL, para[MOTOR_VEL-MOTOR_PARA_ST]);
		AllMotor[i]->SetPara(MOTOR_MAX_ACC, para[MOTOR_MAX_ACC-MOTOR_PARA_ST]);
		AllMotor[i]->SetPara(MOTOR_MIN_ACC, para[MOTOR_MIN_ACC-MOTOR_PARA_ST]);
		AllMotor[i]->SetPara(MOTOR_ACC, para[MOTOR_ACC-MOTOR_PARA_ST]);	
		AllMotor[i]->SetPara(MOTOR_MAX_POS, para[MOTOR_MAX_POS-MOTOR_PARA_ST]);
		AllMotor[i]->SetPara(MOTOR_MIN_POS, para[MOTOR_MIN_POS-MOTOR_PARA_ST]);	
		AllMotor[i]->SetPara(MOTOR_START_POS, para[MOTOR_START_POS-MOTOR_PARA_ST]);
		AllMotor[i]->SetPara(MOTOR_END_POS, para[MOTOR_END_POS-MOTOR_PARA_ST]);
	}
	fclose(pFile);
}
void CMachData::SaveMotorPara()
{
	char name[255];
	sprintf(name, "%s", s_ParaMt);
	mkdir(s_ParaMt);// 先保证目录的存在

	FILE* pFile;
	sprintf(name, "%s\\MotorPar.dat", s_ParaMt);
	pFile = fopen(name, "wb");
	if(!pFile)
		return;	

	dllCMotorBase* AllMotor[MOTORTOTAL];
	AllMotor[0] = &WHX;
	AllMotor[1] = &WHY;
	AllMotor[2] = &WFX;
	AllMotor[3] = &WFY;
	AllMotor[4] = &EJP;	
	AllMotor[5] = &BA;
	AllMotor[6] = &BZ;
	AllMotor[7] = &EA;
	AllMotor[8] = &EZ;
	AllMotor[9] = &ED;
	

	int para[MOTOR_PARA_ED-MOTOR_PARA_ST];
	for(int j=0; j<MOTOR_PARA_ED-MOTOR_PARA_ST; j++)
	{
		para[j] = 0;
	}
	for(int i=0; i<MOTORTOTAL; i++)
	{
		para[MOTOR_HOME_VEL-MOTOR_PARA_ST] = AllMotor[i]->GetPara(MOTOR_HOME_VEL);
		para[MOTOR_MAX_VEL-MOTOR_PARA_ST] = AllMotor[i]->GetPara(MOTOR_MAX_VEL);
		para[MOTOR_MIN_VEL-MOTOR_PARA_ST] = AllMotor[i]->GetPara(MOTOR_MIN_VEL);
		para[MOTOR_INIT_VEL-MOTOR_PARA_ST]= AllMotor[i]->GetPara(MOTOR_INIT_VEL);
		para[MOTOR_VEL-MOTOR_PARA_ST] = AllMotor[i]->GetPara(MOTOR_VEL);
		para[MOTOR_MAX_ACC-MOTOR_PARA_ST] = AllMotor[i]->GetPara(MOTOR_MAX_ACC);
		para[MOTOR_MIN_ACC-MOTOR_PARA_ST] = AllMotor[i]->GetPara(MOTOR_MIN_ACC);
		para[MOTOR_ACC-MOTOR_PARA_ST] = AllMotor[i]->GetPara(MOTOR_ACC);
		para[MOTOR_MAX_POS-MOTOR_PARA_ST] = AllMotor[i]->GetPara(MOTOR_MAX_POS);
		para[MOTOR_MIN_POS-MOTOR_PARA_ST] = AllMotor[i]->GetPara(MOTOR_MIN_POS);
		para[MOTOR_START_POS-MOTOR_PARA_ST] = AllMotor[i]->GetPara(MOTOR_START_POS);
		para[MOTOR_END_POS-MOTOR_PARA_ST] = AllMotor[i]->GetPara(MOTOR_END_POS);
		fwrite(para, sizeof(para), 1, pFile);
	}
	fclose(pFile);
}

void CMachData::LoadMachPara()
{
	FILE* pFile;
	char name[255];
	sprintf(name, "%s\\MachPar.dat", s_ParaMa);
	pFile = fopen(name, "rb");
	if(!pFile)
		return;	
	fread(&d_MachPara, sizeof(d_MachPara), 1, pFile);
	fclose(pFile);

	sprintf(name, "%s\\MachDebugPar.dat", s_ParaMa);
	pFile = fopen(name, "rb");
	if(!pFile)
		return;	

	fread(d_DebugPara, sizeof(d_DebugPara), 1, pFile);
	fclose(pFile);

	InitMotorLmtPos();
}


void CMachData::SaveMachPara()
{
	char name[255];
	sprintf(name, "%s", s_ParaMa);
	mkdir(s_ParaMa);// 先保证目录的存在

	FILE* pFile;
	sprintf(name, "%s\\MachPar.dat", s_ParaMa);
	pFile = fopen(name, "wb");
	if(!pFile)
		return;	
	fwrite(&d_MachPara, sizeof(d_MachPara), 1, pFile);
	fclose(pFile);


	sprintf(name, "%s\\MachDebugPar.dat", s_ParaMa);
	pFile = fopen(name, "wb");
	if(!pFile)
		return;	
	fwrite(d_DebugPara, sizeof(d_DebugPara), 1, pFile);
	fclose(pFile);
}


void CMachData::SetPara(int para_id, int para_val)
{
	switch(para_id)
	{

	case MACH_BA_PICK:
		d_MachPara.db_pick = para_val;
		break;
	case MACH_BA_PREPICK:
		d_MachPara.db_prepick = para_val;
		break;
	case MACH_BA_BOND:
		d_MachPara.db_bond = para_val;
		break;
	case MACH_BA_PREBOND:
		d_MachPara.db_prebond = para_val;
		break;
	case MACH_BA_CLEAR:
		d_MachPara.db_clear = para_val;
		break;

	case MACH_EA_PICK:
		d_MachPara.ep_pick = para_val;
		break;
	case MACH_EA_BOND:
		d_MachPara.ep_bond = para_val;
		break;

	case MACH_EA_PRE_BOND:
		d_MachPara.ep_pre_bond = para_val;
		break;

	case MACH_ETO_X:
		d_MachPara.eto_x = para_val;
		break;
	case MACH_ETO_Y:
		d_MachPara.eto_y = para_val;
		break;

	case MACH_ETO_X2:
		d_MachPara.eto_x2 = para_val;
		break;
	case MACH_ETO_Y2:
		d_MachPara.eto_y2 = para_val;
		break;

	case MACH_ETO_X3:
		d_MachPara.eto_x3 = para_val;
		break;
	case MACH_ETO_Y3:
		d_MachPara.eto_y3 = para_val;
		break;

	case MACH_ETO_X4:
		d_MachPara.eto_x4 = para_val;
		break;
	case MACH_ETO_Y4:
		d_MachPara.eto_y4 = para_val;
		break;


	case MACH_PARK_X:
		d_MachPara.park_x = para_val;
		break;
	case MACH_PARK_Y:
		d_MachPara.park_y = para_val;
		break;

	case MACH_WH_SET_X1:
		d_MachPara.wh_work_set_x1 = para_val;
		break;

	case MACH_WH_SET_Y1:
		d_MachPara.wh_work_set_y1 = para_val;
		break;

	case MACH_WH_SET_X2:
		d_MachPara.wh_work_set_x2 = para_val;
		break;

	case MACH_WH_SET_Y2:
		d_MachPara.wh_work_set_y2 = para_val;
		break;

	case MACH_WHX_OUTPOS:
		d_MachPara.wh_load_x1 = para_val;
		break;

	case MACH_WHY_OUTPOS:
		d_MachPara.wh_load_y1 = para_val;
		break;

	case MACH_WH_LOAD_SPEED:
		d_MachPara.wh_load_x2 = para_val;
		break;

	case MACH_WH_LOAD_Y2:
		d_MachPara.wh_load_y2 = para_val;
		break;

			//--- 上料器工作参数
	case MACH_MAG_RUN_MODE:
		d_MachPara.mag_run_mode = para_val;
		break;

	case MACH_WH_RUN_MODE:
		d_MachPara.wh_run_mode = para_val;
		break;

	case MACH_MAG_X_INPOS:
		d_MachPara.mag_x_inpos = para_val;
		break;

		case MACH_MAG_X_OUTPOS:
		d_MachPara.mag_x_outpos = para_val;
		break;


	case MACH_DELAY_AFTERBOND:
		d_MachPara.mag_wh1_inpos = para_val;
		break;

	case MACH_MAG_CHECKSWITCH:
		d_MachPara.mag_wh2_inpos = para_val;
		break;

	case MACH_MAG_Z_1STPOS:
		d_MachPara.mag_z_1stpos = para_val;
		break;

	case MACH_MAG_Z_GAPSTEP:
		d_MachPara.mag_z_gapstep = para_val;
		break;

	case MACH_MAG_Z_SLOTS:
		d_MachPara.mag_z_slots = para_val;
		break;
	case MACH_MAG_Z_OFFSETPOS:
		d_MachPara.mag_z_offsetpos = para_val;
		break;

	case MACH_MAG_Y_SETPOS:
		d_MachPara.mag_y_setpos = para_val;
		break;

	case MACH_MAG_Y_SLPOS:
		d_MachPara.mag_y_slpos = para_val;
		break;

	case MACH_MAG_Y_SLVEL:
		d_MachPara.mag_y_slvel = para_val;
		break;

	case MACH_MAG_K_OUTPOS:
		d_MachPara.mag_k_outpos = para_val;
		break;

	case MACH_MAG_K_BACKPOS:
		d_MachPara.mag_k_bakpos = para_val;
		break;
	case MACH_WH_MODE:
		d_MachPara.wh2_sw_mode = para_val;
		break;


	case MACH_WH1_OFF_X:
		d_MachPara.wh1_offx = para_val;
		break;

	case MACH_WH1_OFF_Y:
		d_MachPara.wh1_offy = para_val;
		break;

	case MACH_WH2_OFF_X:
		d_MachPara.wh2_offx = para_val;
		break;

	case MACH_WH2_OFF_Y:
		d_MachPara.wh2_offy = para_val;
		break;
	case MACH_WH_CCD_DX:
		d_MachPara.wh_ccd_dx = para_val;
		break;

	case MACH_WH_CCD_DY:
		d_MachPara.wh_ccd_dy = para_val;
		break;

	case MACH_WF_CCD_DX:
		d_MachPara.wf_ccd_dx = para_val;
		break;

	case MACH_WF_CCD_DY:
		d_MachPara.wf_ccd_dy = para_val;
		break;

	case MACH_WF_1_POSX:
		d_MachPara.wf_1_posx = para_val;
		break;
		
	case MACH_WF_1_POSY:
		d_MachPara.wf_1_posy = para_val;
		break;


	default:
		//ASSERT(FALSE);
		break;
	}
}

void CMachData::GetPara(int para_id, int& para_val)
{
	switch(para_id)
	{
	case MACH_WHX_OUTPOS:
		para_val = d_MachPara.wh_load_x1;
		break;

	case MACH_WHY_OUTPOS:
		para_val = d_MachPara.wh_load_y1;
		break;

	case MACH_WH_LOAD_SPEED:
		para_val = d_MachPara.wh_load_x2;
		break;

	case MACH_WH_LOAD_Y2:
		para_val = d_MachPara.wh_load_y2;
		break;

	case MACH_WH_SET_X1:
		para_val = d_MachPara.wh_work_set_x1;
		break;

	case MACH_WH_SET_Y1:
		para_val = d_MachPara.wh_work_set_y1;
		break;

	case MACH_WH_SET_X2:
		para_val = d_MachPara.wh_work_set_x2;
		break;

	case MACH_WH_SET_Y2:
		para_val = d_MachPara.wh_work_set_y2;
		break;

	case MACH_BA_PICK:
		para_val = d_MachPara.db_pick;
		break;
	case MACH_BA_PREPICK:
		para_val = d_MachPara.db_prepick;
		break;
	case MACH_BA_BOND:
		para_val = d_MachPara.db_bond;
		break;
	case MACH_BA_PREBOND:
		para_val = d_MachPara.db_prebond;
		break;
	case MACH_BA_CLEAR:
		para_val = d_MachPara.db_clear;
		break;

	case MACH_EA_PICK:
		para_val = d_MachPara.ep_pick;
		break;
	case MACH_EA_BOND:
		para_val = d_MachPara.ep_bond;
		break;

	case MACH_EA_PRE_BOND:
		para_val=d_MachPara.ep_pre_bond;
		break;

	case MACH_ETO_X:
		para_val = d_MachPara.eto_x;
		break;
	case MACH_ETO_Y:
		para_val = d_MachPara.eto_y;
		break;

	case MACH_ETO_X2:
		para_val = d_MachPara.eto_x2;
		break;
	case MACH_ETO_Y2:
		para_val = d_MachPara.eto_y2;
		break;

	case MACH_ETO_X3:
		para_val = d_MachPara.eto_x3;
		break;
	case MACH_ETO_Y3:
		para_val = d_MachPara.eto_y3;
		break;

	case MACH_ETO_X4:
		para_val = d_MachPara.eto_x4;
		break;
	case MACH_ETO_Y4:
		para_val = d_MachPara.eto_y4;
		break;


	case MACH_PARK_X:
		para_val = d_MachPara.park_x;
		break;
	case MACH_PARK_Y:
		para_val = d_MachPara.park_y;
		break;

	//--- 上料器工作参数
	case MACH_MAG_RUN_MODE:
		para_val = d_MachPara.mag_run_mode;
		break;

	case MACH_WH_RUN_MODE:
		para_val = d_MachPara.wh_run_mode;
		break;

	case MACH_MAG_X_INPOS:
		para_val = d_MachPara.mag_x_inpos;
		break;

		case MACH_MAG_X_OUTPOS:
		para_val = d_MachPara.mag_x_outpos;
		break;


	case MACH_DELAY_AFTERBOND:
		para_val = d_MachPara.mag_wh1_inpos;
		break;

	case MACH_MAG_CHECKSWITCH:
		para_val = d_MachPara.mag_wh2_inpos;
		break;

	case MACH_MAG_Z_1STPOS:
		para_val = d_MachPara.mag_z_1stpos;
		break;

	case MACH_MAG_Z_GAPSTEP:
		para_val = d_MachPara.mag_z_gapstep;
		break;

	case MACH_MAG_Z_SLOTS:
		para_val = d_MachPara.mag_z_slots;
		break;

	case MACH_MAG_Z_OFFSETPOS:
		para_val = d_MachPara.mag_z_offsetpos;
		break;
		
	case MACH_MAG_Y_SETPOS:
		para_val = d_MachPara.mag_y_setpos;
		break;
		
	case MACH_MAG_Y_SLPOS:
		para_val = d_MachPara.mag_y_slpos;
		break;
		
	case MACH_MAG_Y_SLVEL:
		para_val = d_MachPara.mag_y_slvel;
		break;

	case MACH_MAG_K_OUTPOS:
		para_val = d_MachPara.mag_k_outpos;
		break;

	case MACH_MAG_K_BACKPOS:
		para_val = d_MachPara.mag_k_bakpos;
		break;

	case MACH_WH_MODE:
		para_val = d_MachPara.wh2_sw_mode;
		break;
		
	case MACH_WH1_OFF_X:
		para_val = d_MachPara.wh1_offx;
		break;

	case MACH_WH1_OFF_Y:
		para_val = d_MachPara.wh1_offy;
		break;

	case MACH_WH2_OFF_X:
		para_val = d_MachPara.wh2_offx;
		break;

	case MACH_WH2_OFF_Y:
		para_val = d_MachPara.wh2_offy;
		break;

	case MACH_WH_CCD_DX:
		para_val = d_MachPara.wh_ccd_dx;
		break;

	case MACH_WH_CCD_DY:
		para_val = d_MachPara.wh_ccd_dy;
		break;

	case MACH_WF_CCD_DX:
		para_val = d_MachPara.wf_ccd_dx;
		break;

	case MACH_WF_CCD_DY:
		para_val = d_MachPara.wf_ccd_dy;
		break;

	case MACH_WF_1_POSX:
		para_val = d_MachPara.wf_1_posx;
		break;

	case MACH_WF_1_POSY:
		para_val = d_MachPara.wf_1_posy;
		break;

	default:
//		ASSERT(FALSE);
		break;
	}
}

void CMachData::SetPara(int para_id, double para_fval)
{
	int para_val = int(para_fval*1000);
	switch(para_id)
	{
	case MACH_WH_X_CPP:
		d_MachPara.wh_x_cnt_per_pixel = para_val;
		break;
	case MACH_WH_Y_CPP:
		d_MachPara.wh_y_cnt_per_pixel = para_val;
		break;
	case MACH_WF_X_CPP:
		d_MachPara.wf_x_cnt_per_pixel = para_val;
		break;
	case MACH_WF_Y_CPP:
		d_MachPara.wf_y_cnt_per_pixel = para_val;
		break;
	default:
//		ASSERT(FALSE);
		break;
	}
}

void CMachData::GetPara(int para_id, double& para_fval)
{
	switch(para_id)
	{
	case MACH_WH_X_CPP:
		para_fval = d_MachPara.wh_x_cnt_per_pixel;
		break;
	case MACH_WH_Y_CPP:
		para_fval = d_MachPara.wh_y_cnt_per_pixel;
		break;
	case MACH_WF_X_CPP:
		para_fval = d_MachPara.wf_x_cnt_per_pixel;
		break;
	case MACH_WF_Y_CPP:
		para_fval = d_MachPara.wf_y_cnt_per_pixel;
		break;
	default:
//		ASSERT(FALSE);
		break;
	}
   para_fval /= 1000;
}

int CMachData::GetDebugPara(int para_id)
{
	ASSERT(para_id>0 && para_id<=1000);
	return d_DebugPara[para_id-1];
}
void CMachData::SetDebugPara(int para_id, int para_val)
{
	ASSERT(para_id>0 && para_id<=1000);
	d_DebugPara[para_id-1] = para_val;
	SetMotorLmtPos(para_id, para_val);
}
void CMachData::InitMotorLmtPos()
{
	return;

	WHX.SetPara(MOTOR_MAX_POS, GetDebugPara(100));
	WHX.SetPara(MOTOR_MIN_POS, GetDebugPara(110));

	WHY.SetPara(MOTOR_MAX_POS, GetDebugPara(101));
	WHY.SetPara(MOTOR_MIN_POS, GetDebugPara(111));
	
	WFX.SetPara(MOTOR_MAX_POS, GetDebugPara(102));
	WFX.SetPara(MOTOR_MIN_POS, GetDebugPara(112));
	
	WFY.SetPara(MOTOR_MAX_POS, GetDebugPara(103));
	WFY.SetPara(MOTOR_MIN_POS, GetDebugPara(113));
	
	BZ.SetPara(MOTOR_MAX_POS, GetDebugPara(104));
	BZ.SetPara(MOTOR_MIN_POS, GetDebugPara(114));
	
	BA.SetPara(MOTOR_MAX_POS, GetDebugPara(105));
	BA.SetPara(MOTOR_MIN_POS, GetDebugPara(115));
	
	EZ.SetPara(MOTOR_MAX_POS, GetDebugPara(106));
	EZ.SetPara(MOTOR_MIN_POS, GetDebugPara(116));
	
	EA.SetPara(MOTOR_MAX_POS, GetDebugPara(107));
	EA.SetPara(MOTOR_MIN_POS, GetDebugPara(117));

	ExtZ.SetPara(MOTOR_MAX_POS, GetDebugPara(108));
	ExtZ.SetPara(MOTOR_MIN_POS, GetDebugPara(118));
	
	EJP.SetPara(MOTOR_MAX_POS, GetDebugPara(109));
	EJP.SetPara(MOTOR_MIN_POS, GetDebugPara(119));


	
}
void CMachData::SetMotorLmtPos(int para_id, int para_val)
{
	return;
	switch(para_id)
	{
	case 100:
		WHX.SetPara(MOTOR_MAX_POS, para_val);
		break;
	case 110:
		WHX.SetPara(MOTOR_MIN_POS, para_val);
		break;

	case 101:
		WHY.SetPara(MOTOR_MAX_POS, para_val);
		break;
	case 111:
		WHY.SetPara(MOTOR_MIN_POS, para_val);
		break;
	
	case 102:
		WFX.SetPara(MOTOR_MAX_POS, para_val);
		break;
	case 112:
		WFX.SetPara(MOTOR_MIN_POS, para_val);
		break;
	
	case 103:
		WFY.SetPara(MOTOR_MAX_POS, para_val);
		break;
	case 113:
		WFY.SetPara(MOTOR_MIN_POS, para_val);
		break;
	
	case 104:
		BZ.SetPara(MOTOR_MAX_POS, para_val);
		break;
	case 114:
		BZ.SetPara(MOTOR_MIN_POS, para_val);
		break;
	
	case 105:
		BA.SetPara(MOTOR_MAX_POS, para_val);
		break;
	case 115:
		BA.SetPara(MOTOR_MIN_POS, para_val);
		break;
	
	case 106:
		EZ.SetPara(MOTOR_MAX_POS, para_val);
		break;
	case 116:
		EZ.SetPara(MOTOR_MIN_POS, para_val);
		break;
	
	case 107:
		EA.SetPara(MOTOR_MAX_POS, para_val);
		ExtZ.SetPara(MOTOR_MAX_POS, para_val);

		break;
	case 117:
		EA.SetPara(MOTOR_MIN_POS, para_val);
		ExtZ.SetPara(MOTOR_MIN_POS, para_val);
		break;
	case 108:
		ExtZ.SetPara(MOTOR_MAX_POS, para_val);
		
		break;
	case 118:
	
		ExtZ.SetPara(MOTOR_MIN_POS, para_val);
		break;
	
	case 109:
		EJP.SetPara(MOTOR_MAX_POS, para_val);
		break;
	case 119:
		EJP.SetPara(MOTOR_MIN_POS, para_val);
		break;

	default:
		break;
	}
}

