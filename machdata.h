#ifndef _MACH_DATA_H_
#define _MACH_DATA_H_

enum MachParaType
{
	MACH_PARA_ST,
	
	MACH_TEST,

	MACH_BA_PICK,
	MACH_BA_PREPICK,
	MACH_BA_BOND,
	MACH_BA_PREBOND,
	MACH_BA_CLEAR,

	MACH_EA_PICK,
	MACH_EA_BOND,

	MACH_ETO_X,
	MACH_ETO_Y,

	MACH_ETO_X2,
	MACH_ETO_Y2,

	MACH_ETO_X3,//��װоƬ���罺�߶�ֵ

	MACH_ETO_Y3,//оƬ���罺��ʱ

	MACH_ETO_X4,//WHXԤ���罺λ��
	MACH_ETO_Y4,//WHYԤ���罺λ��

	//--- CCDͼ��У������
	MACH_WH_X_CPP,
	MACH_WH_Y_CPP,
	MACH_WF_X_CPP,
	MACH_WF_Y_CPP,


	MACH_PARK_X,//X����λ��
	MACH_PARK_Y,//Y����λ��

	//--- �о߹���λ
	//--- 1#
	MACH_WH_SET_X1,
	MACH_WH_SET_Y1,

	MACH_WHX_OUTPOS, //X����λ��
	MACH_WHY_OUTPOS,//Y����λ��

    //--- 2#
	MACH_WH_SET_X2,
	MACH_WH_SET_Y2,

	MACH_WH_LOAD_SPEED,//�������ٶ�ֵ

	MACH_WH_LOAD_Y2,

	//--- ��������������

	MACH_MAG_RUN_MODE, //--- Z��������ʱ

	MACH_WH_RUN_MODE,  //--- X��������ʱ
	
	MACH_MAG_X_INPOS,  //--- ���� pos

	MACH_MAG_X_OUTPOS, //--- �������˾���

	MACH_DELAY_AFTERBOND,  //--- �̾�����Ƭ����ʱ

	MACH_MAG_CHECKSWITCH,  //--- �����źż�⿪�أ�0-����1-��

	MACH_MAG_Z_1STPOS,		//--- �Ϻе�һ�� pos
	MACH_MAG_Z_GAPSTEP,		//--- �Ϻв��
	MACH_MAG_Z_SLOTS,		//--- �Ϻв���
	MACH_MAG_Z_OFFSETPOS,   //--- MGZ����ʱ���˾���

	MACH_MAG_Y_SETPOS,	//--- MGY���ϴ�������
	MACH_MAG_Y_SLPOS,	//--- MGY����ʱ���ٻ������
	MACH_MAG_Y_SLVEL,	//--- MGY����ʱ���ٻ����ٶ�

	MACH_MAG_K_OUTPOS,  //--- �Ƴ��Ϻ� pos
	MACH_MAG_K_BACKPOS, //--- �˻� pos

	MACH_WH_MODE,		//--- ����ģʽ

	MACH_WH1_OFF_X,
	MACH_WH1_OFF_Y,

	MACH_WH2_OFF_X,
	MACH_WH2_OFF_Y,

	MACH_EA_PRE_BOND,

	MACH_WH_CCD_DX,
	MACH_WH_CCD_DY,

	MACH_WF_CCD_DX,
	MACH_WF_CCD_DY,

	//--- ��һ�� wafer ��λ��
	MACH_WF_1_POSX,
	MACH_WF_1_POSY,


	MACH_PARA_ED=100
};

//******************************************************
//�ṹ�����������ݱ����������棬���򽫵���ԭ�����ݴ�λ
//******************************************************
struct MachPara_Blk
{
	int db_pick;
	int db_prepick;
	int db_bond;
	int db_prebond;
	int db_clear;

	int ep_pick;
	int ep_bond;

	int eto_x;
	int eto_y;

	int wh_x_cnt_per_pixel;//ʵ��ֵ�Ǹ�ֵ��ǧ��֮һ
	int wh_y_cnt_per_pixel;
	int wf_x_cnt_per_pixel;
	int wf_y_cnt_per_pixel;

	int park_x;
	int park_y;

	//--- �о߹���λ
	int wh_work_set_x1;
	int wh_work_set_y1;

	int wh_load_x1;
	int wh_load_y1;

	int wh_work_set_x2;
	int wh_work_set_y2;

	int wh_load_x2;
	int wh_load_y2;


	//--- ��������������
	int mag_run_mode;
	int wh_run_mode;

	int mag_x_inpos;
	int mag_x_outpos;

	int mag_wh1_inpos;
	int mag_wh2_inpos;

	int mag_z_1stpos;
	int mag_z_gapstep;
	int mag_z_slots;


	int mag_k_outpos;
	int mag_k_bakpos;
	//--˫�о�λ
	int wh2_sw_mode;
	int wh1_offx;
	int wh1_offy;

	int wh2_offx;
	int wh2_offy;

	int ep_pre_bond;

	//--- CCD ʮ��������ƫ����
	int wh_ccd_dx;
	int wh_ccd_dy;

	int wf_ccd_dx;
	int wf_ccd_dy;

	//--- ��һ�� wafer ��λ��
	int wf_1_posx;
	int wf_1_posy;

	int mag_z_offsetpos;
	
	int mag_y_setpos;
	int mag_y_slpos;
	int mag_y_slvel;

	int eto_x2;
	int eto_y2;

	int eto_x3;
	int eto_y3;

	int eto_x4;
	int eto_y4;

//	int reserved[100];

	MachPara_Blk()
	{
// 		db_pick = 0;
// 		db_prepick = 0;
// 		db_bond = 0;
// 		db_prebond = 0;
// 		db_clear = 0;
// 
// 		ep_pick = 0;
// 		ep_bond = 0;
// 
// 		eto_x = 0;
// 		eto_y = 0;
// 		
// 		//ʵ��ֵ�Ǹ�ֵ��ǧ��֮һ
// 		wh_x_cnt_per_pixel = 1000;
// 		wh_y_cnt_per_pixel = 1000;
// 		wf_x_cnt_per_pixel = 1000;
// 		wf_y_cnt_per_pixel = 1000;
// 
// 		park_x = 0;
// 		park_y = 0;

// 		for(int i=0; i<100; i++)
// 		{
// 			reserved[i] = 0;
// 		}
	}
};

class CMachData
{
public:
	CMachData();
	~CMachData();
public:
	void LoadMotorPara();
	void SaveMotorPara();

	void LoadMachPara();
	void SaveMachPara();

	void LoadMachDebugPara();
	void SaveMachDebugPara();

public:
	void SetPara(int para_id, int para_val);
	void SetPara(int para_id, double para_fval);
	void GetPara(int para_id, int& para_val);
	void GetPara(int para_id, double& para_fval);
	
	int GetPara(int para_id)
	{
		
	    int para_val=0;
	     
	    GetPara(para_id, para_val);
	    
	    return(para_val);	
	}

	int GetDebugPara(int para_id);
	void SetDebugPara(int para_id, int para_val);
	void InitMotorLmtPos();
protected:
	
	void SetMotorLmtPos(int para_id, int para_val);

protected:
	MachPara_Blk d_MachPara;
	int d_DebugPara[1000];
};

#endif//_MACH_DATA_H_

