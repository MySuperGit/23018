/*
 *	定义程式数据的结构以及存取接口
 */
#ifndef _WH_DATA_H_
#define _WH_DATA_H_

#include <vector>
using namespace std;

#include "MachineData.h"

#define MAX_PROG_MACH 1000

enum ProgParaType
{
	PROG_RARA_ST,
		
		PROG_RUN_MODE,
		PROG_CHECK_DIE,
		
		PROG_POS_DBZ_PICK,
		PROG_POS_DBZ_PICK_RESET,
		PROG_POS_DBZ_BOND,
		PROG_POS_DBZ_BOND_RESET,
		
		PROG_POS_EJP_PICK,
		PROG_POS_EJP_PICK_RESET,
		
		PROG_POS_EPZ_PICK,//吸头放料位置
		PROG_POS_EPZ_PICK_RESET,//吸头取料位置
		
		PROG_POS_EPZ_BOND,//底板上喷胶高度
		
		PROG_POS_EPZ_BOND_RESET,
		
		PROG_LIGHT_WH_RING2,//胶光源值
		
		PROG_POS_EPZ_BOND_RUPTURE,
		PROG_VEL_EPZ_RUPTURE,
		
		PROG_DELAY_DB_PICK,
		PROG_DELAY_DB_PREPICK,
		PROG_DELAY_DB_BOND,
		PROG_DELAY_DB_PREBOND,
		PROG_DELAY_EP_PICK,//倒装取片延时
		
		PROG_DELAY_EP_BOND,
		
		PROG_DELAY_CLAMPSWITCH,//真空延时
		
		PROG_LIGHT_WH_RING,//底板光源值
		PROG_LIGHT_WH_COAX,//芯片光源值
		PROG_LIGHT_WF_RING,
		PROG_LIGHT_WF_COAX,
		
		PROG_STREET_X,
		PROG_STREET_Y,
		PROG_SRH_DIE_MODE,
		PROG_SRH_DIE_DIR,
		PROG_SRH_DIE_MISS_CNT,
		PROG_DIE_ACCEPT,
		PROG_DIE_GRAB_TIME,
		
		PROG_EPXDIE_OFFSET,//喷胶直径偏差
		
		PROG_DB_ANGLE,//贴片角度范围
		
		PROG_ALG_MODE,//对点模式
		
		PROG_ADJ_MODE,//固晶校正模式
		
		PROG_ALG_PR_DELAY,//所有样本查找延时
		PROG_ALG_ACCEPT,//底板匹配值
		
		PROG_PT_PR_DELAY,//校正固晶位置时查找胶量的匹配值
		
		PROG_PT_ACCEPT,//贴片后检验匹配值
		
		PROG_DB_SHOW_DELAY,
		
		PROG_READ_ED,
		
		PROG_DELAY_EP_LEAVE,//吸头旋转延时
		PROG_DELAY_COLLETPUTDOWN,//放片延时
		
		PROG_POS_EPZ_PREBOND,//倒装芯片上喷胶高度
};

enum ProgMachPara
{
	//点胶参数
	MACH_EP_START = 100,
	ID_MACH_EP_RDYZ,	//准备高度
	ID_MACH_EP_GETX,	//取胶位置
	ID_MACH_EP_GETZ,	//取胶高度
	ID_MACH_EP_SETX,	//点胶位置
	ID_MACH_EP_SETZ,	//点胶高度
	ID_MACH_BC_RDYX,	//出料位X
	ID_MACH_BC_RDYY,	//出料位X
	ID_MACH_EP_RDYX,    //预备点胶位置--暂时未用
	ID_MACH_EP_CLEAR,	//点胶清洗吸嘴位

	//固晶参数
	MACH_BD_START = 200,
	ID_MACH_SW2_RDYZ,	//准备高度
	//ID_MACH_SW2_RDYX,   //固晶预备位，吸晶电机可以过来，但是点胶不能过去，相机都可以拍照位
	//ID_MACH_PK2_PREP_CAM2_POS,  //固晶电机预取料位置  校正相机可以拍照位---拍照前停
	ID_MACH_SW2_RDYX,	//固晶预备位
	ID_MACH_PK2_PREP_CAM2_POS_NOUSE, //弃用
	ID_MACH_SW2_GETX,	//取料位置
	ID_MACH_SW2_GETZ,   //取料高度
	ID_MACH_SW2_SETX,	//放料位置
	ID_MACH_SW2_SETZ,	//放料高度
	ID_MACH_PK2_AFTER_CAM3_POS, //固晶电机返回时，点胶相机可以拍照位 --拍照后判断
	ID_MACH_DIE_RDYX,	//矫正台工作位X
	ID_MACH_DIE_RDYY,	//矫正台工作位Y
	ID_MACH_BD_CLEAR,	//固晶清洗吸嘴位

	//取晶参数
	MACH_PK_SATRT = 300,
	ID_MACH_SW1_RDYZ,	 //准备高度
	//吸晶预备位，吸晶相机可以拍照位 吸晶前在这个位置停一下---拍照前停
	ID_MACH_SW1_RDYX,    //							吸晶后去放晶时---马达不停，判断位--拍照后判断
	ID_MACH_SW1_GETX,	//取料位置
	ID_MACH_SW1_GETZ,	//取料高度
	ID_MACH_SW1_SETX,	//放料位置
	ID_MACH_SW1_SETZ,	//放料高度
	ID_MACH_PK1_AFTER_CAM1_POS_NOUSE,		   //吸晶1返回时，校正台可以拍照位置 ---马达不停，判断位--拍照后判断
	ID_MACH_WF_RDYX,	//出料位X
	ID_MACH_WF_RDYY,	//出料位Y
	ID_MACH_IGNORE_TIMES,
	ID_MACH_PK_CLEAR,	//吸晶清洗吸嘴位

	//精度补偿
	MACH_PRECISION_START = 400,
	MACH_BD_PRECISION_X,
	MACH_BD_PRECISION_Y,
	MACH_BD_PRECISION_A,
	MACH_EP_PRECISION_X,
	MACH_EP_PRECISION_Y,
	MACH_PRECISION_END,

	

	//延时参数
	
	ID_MACH_GET1_DELAY,// 吸嘴1在晶圆台取料延时
	ID_MACH_GET2_DELAY,//吸嘴1在较正台放料延时 
	ID_MACH_SET2_DELAY,//吸嘴2在较正台取料延时
	ID_MACH_DIE_DELAY,	//吸嘴2固晶延时
	ID_MACH_EPGET_DELAY,//取胶延时
	ID_MACH_EPSET_DELAY,//点胶延时
	ID_MACH_CAM1_PREP_DELAY, //相机1拍照前延时
	ID_MACH_CAM2_PREP_DELAY, //相机1拍照前延时
	ID_MACH_CAM3_PREP_DELAY , //相机1拍照前延时
	MACH_BD_CAM_AFTER_DELAY, //固晶后图像显示延时


	//图像
	MACH_WF0_X_CPP = 700,
	MACH_WF0_Y_CPP,
	MACH_WF02_X_CPP,
	MACH_WF02_Y_CPP,
	MACH_WH0_X_CPP,
	MACH_WH0_Y_CPP,

	MACH_WF_X_CPP_DIR,
	MACH_WF_Y_CPP_DIR,
	MACH_WF2_X_CPP_DIR,
	MACH_WF2_Y_CPP_DIR,
	MACH_WH_X_CPP_DIR,
	MACH_WH_Y_CPP_DIR,

	MACH_EP_OFFSET_X, //点胶偏移X
	MACH_EP_OFFSET_Y, //点胶偏移Y	
	MACH_CAM2_OFFSET_X,
	MACH_CAM2_OFFSET_Y,
	MACH_CAM3_OFFSET_X,
	MACH_CAM3_OFFSET_Y,

	MACH_WF_T_CPP_DIR,

	//曝光增益
	ID_EXPS_CAM1=800,
	ID_EXPS_CAM2,
	ID_EXPS_CAM3,
	ID_GAIN_CAM1,
	ID_GAIN_CAM2,
	ID_GAIN_CAM3,
	ID_MARK_CAM1,
	ID_MARK_CAM2,
	ID_MARK_CAM3,
};

//程式信息体：点数，组群数，程式名称
struct ProgInfo_Blk
{
	int prg;
	int group_total;
	int pos_total;
	char name[255];
	char lasttime[255];

};

//点位置x，y，
struct Pos_Blk//POSX,Y
{
	int x;
	int y;
};

//底板定位点
struct Group_Blk
{
	Pos_Blk Alg1;
	Pos_Blk Alg2;

	int ref_x;
	int ref_y;
	double ref_angle;	
	Group_Blk()
	{
		ref_x = 0;
		ref_y = 0;
		ref_angle = 0.0;
	}
};

//多个样本对像的共用体中用到数据
struct PrPara_Blk
{
	int ring;
	int coax;

	int w;
	int h;
	int offset_x;
	int offset_y;
	int tp_w;
	int tp_h;
	int tp_angle;
	int valid;

	int accept;
	int certainty;
};
union AllPrPara_Blk//接上实例化样本共用体
{
	PrPara_Blk PrPara;
	int all_para[40];

	AllPrPara_Blk()
	{
		PrPara.ring = 100;
		PrPara.coax = 100;

		PrPara.valid = 0;
		PrPara.w = 100;
		PrPara.h = 100;
		PrPara.offset_x = 0;
		PrPara.offset_y = 0;
		PrPara.tp_w = 100;
		PrPara.tp_h = 100;
		PrPara.tp_angle = 0;

		PrPara.accept = 80;
		PrPara.certainty = 50;
	}
};

struct Pr_Blk//样本及有关样本的参数
{	
	unsigned char* pimage;
	AllPrPara_Blk AllPrPara;
	
	Pr_Blk()
	{
		pimage = 0;
	}
};
struct Para_Blk//对点基准位置与程式对应数据
{
	char name[255];
	int no;
	int base_x;
	int base_y;
	double base_angle;
	
	//AllProgPara_Blk AllProgPara;
	
	Para_Blk()
	{
		memset(name,0,255);
		no = 0;
		base_x = 0;
		base_y = 0;
		base_angle = 0.0;
	}
};

struct ProgPara_Blk
{
	int run_mode;
	int check_die;

	//about wf
	int streetx;
	int streety;	
	int srh_die_mode;
	int srh_die_dir;
	int curpos_x;
	int curpos_y;

	//about pos
	int pos_dbz_pick;
	int pos_dbz_pick_reset;
	int pos_dbz_bond;
	int pos_dbz_bond_reset;

	int pos_ejp_pick;
	int pos_ejp_reset;

	int pos_epz_pick;
	int pos_epz_pick_reset;
	int pos_epz_bond;
	int pos_epz_bond_reset;
	
	//about delay
	int delay_db_pick;
	int delay_db_bond;
	int delay_pr_not_use;
	int delay_epx_timeout;

	//about light
	int light_wh_ring;
	int light_wh_coax;
	int light_wf_ring;
	int light_wf_coax;

	//新增的参数依次放在后面，避免以往保存的参数在载入后错位
	//about delay
	int delay_ep_pick;
	int delay_ep_bond;

	//about wf
	int srh_die_miss_cnt;//漏空数：1～10
	int die_accept;//晶片相似度：40 ～ 100 %
	int die_grab_time;//取图时间：20 ～ 50 ms
	
	//about wh
	int alg_mode;//对点模式：1=仅对点  2=仅校正固晶点（支架模式）  3=对点+校正固晶点
	int adj_mode;// 校正模式  1=固前校正  
	int alg_pr_dly;// 对点图像延时:校正前延时，20ms
	int alg_accept;// 对点相似度:  40~100%
	int pt_pr_dly;// 固晶点图像延时: 校正前延时，20ms
	int pt_accept;// 固晶点相似度：  40~100%
	int db_show_dly;// 固晶后图像延时：固晶完成后显示图像时间,25ms

	int delay_ep_leave;
	int vel_mode;

	int pos_epz_prebond;

	int delay_db_prepick;
	int delay_db_prebond;

	int pos_epz_pick_rupture;
	int vel_epz_rupture;
	int pos_epz_bond_rupture;
	int rdyx_ep;


};
/*
union AllProgPara_Blk//程式数据共用体
{
	ProgPara_Blk ProgPara;
	int all_para[200];
	AllProgPara_Blk()
	{
		ProgPara.srh_die_mode = 1;
		ProgPara.srh_die_dir = 1;
		ProgPara.srh_die_miss_cnt = 1;
		ProgPara.die_accept = 30;
		ProgPara.die_grab_time = 30;

		ProgPara.alg_mode = 1;
		ProgPara.adj_mode = 1;
		ProgPara.alg_pr_dly = 20;
		ProgPara.alg_accept = 30;
		ProgPara.pt_pr_dly = 20;
		ProgPara.pt_accept = 30;
		ProgPara.db_show_dly = 25;

		ProgPara.delay_db_bond = 5;
		ProgPara.delay_db_pick = 5;
		ProgPara.delay_ep_bond = 5;
		ProgPara.delay_ep_pick = 5;
		ProgPara.delay_epx_timeout = 100;

		ProgPara.light_wh_ring = 100;
		ProgPara.light_wh_coax = 100;
		ProgPara.light_wf_ring = 100;
		ProgPara.light_wf_coax = 100;		
	
		ProgPara.delay_db_prepick = 5;
		ProgPara.delay_db_prebond = 5;

		ProgPara.pos_epz_pick_rupture = 0;
		ProgPara.vel_epz_rupture = 0;
		ProgPara.pos_epz_bond_rupture = 0;
	}
};*/
//机台参数改成程式参数
struct MachProg_Blk
{
	int m_iVal[MAX_PROG_MACH];
	double m_fVal[MAX_PROG_MACH];
};

int GetProgInfo(int prg_no, ProgInfo_Blk& ProgIhfo,int sub_id);
void UpdateCurProcProgInfo();
class CProgData
{
public:
	int m_nSubID;
	CString m_sSubName;
public:
	CProgData(int subid);
	~CProgData();
public:
	//int m_nsubid;
public:
	int SaveParaDB();
	int LoadParaDB();//load原对应到程式的参数
	int DeletFile(int prg);

	int SetPrgID(int prg);

	int Load(int prg);
	int Import(char* file_name);
	int Save();
	int Export(char* file_name);
	void Empty();
	void EmptyPt();
	void EmptyGroup();

	//set data
	void SetBaseAlg(int alg1_x, int alg1_y, int alg2_x, int alg2_y);//设置第一个组群的两个对点计算基准点
	void AddGroup(int alg1_x, int alg1_y);//增加组群到末尾，偏移值为输入参数和第一个组群的第一个对点的距离
	void AddGroup(int alg1_x, int alg1_y, int grp_st, int grp_ed);//增加组群到末尾
	void AddGroup(int group, int alg1_x, int alg1_y);//在group后增加组群
	void DelGroup(int group);
	void SetAlg1(int group, int x, int y);//修改组群对点
	void SetAlg2(int group, int x, int y);
	void SetBaseAlg1(int x, int y);//修改对点
	void SetBaseAlg2(int x, int y);
	void AddPos(int x, int y);
	void AddPos(int x, int y, int pos_st, int pos_ed);
	void AddPos(int pos, int x, int y);//在pos后增加固晶点
	void DelPos(int pos);
	void SetPos(int pos, int x, int y);//修改固晶点
	void SetRefAlg(int group, int alg1_x, int alg1_y, int alg2_x, int alg2_y);//在对点找完后设置新找到的对点
	//get data
	int GetGroupTotal();
	int GetPosTotal();
	void GetAlg1(int group, int& outx, int& outy);//base 1
	void GetAlg2(int group, int& outx, int& outy);	
	void GetBaseAlg1(int& outx, int& outy);//base 1
	void GetBaseAlg2(int& outx, int& outy);
	void GetPos(int group, int pt, int& out_x, int& out_y);//base 1
	void GetAdjPos(int group, int pt, int& out_x, int& out_y);//base 1

	//para data
	int GetProgNo();
	void SetName(char* name);
	char* GetName();
	int GetPara(int para_id)const;
	void SetPara(int para_id, int para_val);

protected:
	int Load(FILE* pFile);
	int Save(FILE* pFile);

public:
	void ResetProgPoint();
	
	void GetTempPos();
	void SetTempPos(int x, int y);
	
	int GetPosTotalTemp();

public:
	vector<Pos_Blk> d_PosVec;
	vector<Group_Blk> d_GroupVec;

	Group_Blk m_WHStripAlgChk;// 固晶料片对点检测

	vector<Pos_Blk> d_AllPosVec_temp;
	vector<Group_Blk> d_GroupVec_temp;


	Para_Blk d_ParaBlk;//底板定位基点

	ProgPara_Blk d_ProgPara;//原对应到程式的参数


	//====


	Pr_Blk d_PrWf;
	Pr_Blk d_PrPt;
	Pr_Blk d_PrAlg1;
	Pr_Blk d_PrAlg2;

	MachProg_Blk d_MachProg;

//阵列加工
public:
	int GetRow(){return m_row;}
	int GetCol(){return m_col;}
	void GetRectPoint(int num,Pos_Blk& pos); //num 0:左上，1：右上，2：坐下

	void SetRow(int row);
	void SetCol(int col);
	void SetRectPoint(int num,Pos_Blk pos);//num 0:左上，1：右上，2：坐下

	void SetGrpRow(int row);
	void SetGrpCol(int col);
	void SetGrpRectPoint(int num, int x, int y);//num 0:左上，1：右上，2：坐下
	void SetBdOffsetX(int x);
	void SetBdOffsetY(int y);

public:
	int GetMachPara(int id);
	int SetMachPara(int id,int val); 
	int GetMachParaF(int id,double &val);
	int SetMachParaF(int id,double val); 

private:
	int m_row;
	int m_col;
	Pos_Blk m_Pos[3];	

public:
	int m_GrpRow;
	int m_GrpCol;
	Pos_Blk m_GrpPos[3];

//光源
public:
	int GetBdLight(){return m_BdLight;}
	int GetCalLight() {return m_CalLight;}
	int GetPkLight() {return m_PkLight;}

	void SetBdLight(int val) {m_BdLight = val;}
	void SetCalLight(int val) {m_CalLight = val;}
	void SetPkLight(int val) {m_PkLight = val;}
private:
	int m_BdLight;
	int m_CalLight;
	int m_PkLight;

//分点
public:
	BOOL m_bEnableFd; //开启分点功能
	int  m_iTTFd;	  //分点总数
	int  m_iCurFd;	  //当前分点

	void GetFdPos(int idx,double &x,double &y);
	void SetFdPos(int idx,double x,double y);

	void AddFdPos(double x,double y);
	void ChangeFdPos(int idx,double x,double y);
	void DelFdPos();//删除最后一个

	void SetCurFd(int idx);

	void SetEnableFd(BOOL bFd);

public:
	void Set_Modify_GrpAlg1(int group, int x, int y);//修改组群点

private:
	double m_dFdX[100];
	double m_dFdY[100];

public:
	int m_iBdOffX;
	int m_iBdOffY;
};


extern CProgData g_ProgDataBd; //固晶




extern int GetProgInfo(int prg_no, ProgInfo_Blk& ProgInfo);

#endif//_WH_DATA_H_

