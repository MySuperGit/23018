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

	MACH_ETO_X3,//正装芯片上喷胶高度值

	MACH_ETO_Y3,//芯片上喷胶延时

	MACH_ETO_X4,//WHX预先喷胶位置
	MACH_ETO_Y4,//WHY预先喷胶位置

	//--- CCD图像校正比例
	MACH_WH_X_CPP,
	MACH_WH_Y_CPP,
	MACH_WF_X_CPP,
	MACH_WF_Y_CPP,


	MACH_PARK_X,//X进料位置
	MACH_PARK_Y,//Y进料位置

	//--- 夹具工作位
	//--- 1#
	MACH_WH_SET_X1,
	MACH_WH_SET_Y1,

	MACH_WHX_OUTPOS, //X出料位置
	MACH_WHY_OUTPOS,//Y出料位置

    //--- 2#
	MACH_WH_SET_X2,
	MACH_WH_SET_Y2,

	MACH_WH_LOAD_SPEED,//进出料速度值

	MACH_WH_LOAD_Y2,

	//--- 上料器工作参数

	MACH_MAG_RUN_MODE, //--- Z向气缸延时

	MACH_WH_RUN_MODE,  //--- X向气缸延时
	
	MACH_MAG_X_INPOS,  //--- 推入 pos

	MACH_MAG_X_OUTPOS, //--- 挤胶回退距离

	MACH_DELAY_AFTERBOND,  //--- 固晶及放片后延时

	MACH_MAG_CHECKSWITCH,  //--- 进料信号检测开关：0-开，1-关

	MACH_MAG_Z_1STPOS,		//--- 料盒第一层 pos
	MACH_MAG_Z_GAPSTEP,		//--- 料盒层高
	MACH_MAG_Z_SLOTS,		//--- 料盒层数
	MACH_MAG_Z_OFFSETPOS,   //--- MGZ接料时回退距离

	MACH_MAG_Y_SETPOS,	//--- MGY送料传动距离
	MACH_MAG_Y_SLPOS,	//--- MGY进料时低速缓冲距离
	MACH_MAG_Y_SLVEL,	//--- MGY进料时低速缓冲速度

	MACH_MAG_K_OUTPOS,  //--- 推出料盒 pos
	MACH_MAG_K_BACKPOS, //--- 退回 pos

	MACH_WH_MODE,		//--- 跑料模式

	MACH_WH1_OFF_X,
	MACH_WH1_OFF_Y,

	MACH_WH2_OFF_X,
	MACH_WH2_OFF_Y,

	MACH_EA_PRE_BOND,

	MACH_WH_CCD_DX,
	MACH_WH_CCD_DY,

	MACH_WF_CCD_DX,
	MACH_WF_CCD_DY,

	//--- 上一次 wafer 的位置
	MACH_WF_1_POSX,
	MACH_WF_1_POSY,


	MACH_PARA_ED=100
};

//******************************************************
//结构体中增加数据必须放在最后面，否则将导致原有数据错位
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

	int wh_x_cnt_per_pixel;//实际值是该值的千分之一
	int wh_y_cnt_per_pixel;
	int wf_x_cnt_per_pixel;
	int wf_y_cnt_per_pixel;

	int park_x;
	int park_y;

	//--- 夹具工作位
	int wh_work_set_x1;
	int wh_work_set_y1;

	int wh_load_x1;
	int wh_load_y1;

	int wh_work_set_x2;
	int wh_work_set_y2;

	int wh_load_x2;
	int wh_load_y2;


	//--- 上料器工作参数
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
	//--双夹具位
	int wh2_sw_mode;
	int wh1_offx;
	int wh1_offy;

	int wh2_offx;
	int wh2_offy;

	int ep_pre_bond;

	//--- CCD 十字线中心偏移量
	int wh_ccd_dx;
	int wh_ccd_dy;

	int wf_ccd_dx;
	int wf_ccd_dy;

	//--- 上一次 wafer 的位置
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
// 		//实际值是该值的千分之一
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

