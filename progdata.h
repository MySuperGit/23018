/*
 *	�����ʽ���ݵĽṹ�Լ���ȡ�ӿ�
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
		
		PROG_POS_EPZ_PICK,//��ͷ����λ��
		PROG_POS_EPZ_PICK_RESET,//��ͷȡ��λ��
		
		PROG_POS_EPZ_BOND,//�װ����罺�߶�
		
		PROG_POS_EPZ_BOND_RESET,
		
		PROG_LIGHT_WH_RING2,//����Դֵ
		
		PROG_POS_EPZ_BOND_RUPTURE,
		PROG_VEL_EPZ_RUPTURE,
		
		PROG_DELAY_DB_PICK,
		PROG_DELAY_DB_PREPICK,
		PROG_DELAY_DB_BOND,
		PROG_DELAY_DB_PREBOND,
		PROG_DELAY_EP_PICK,//��װȡƬ��ʱ
		
		PROG_DELAY_EP_BOND,
		
		PROG_DELAY_CLAMPSWITCH,//�����ʱ
		
		PROG_LIGHT_WH_RING,//�װ��Դֵ
		PROG_LIGHT_WH_COAX,//оƬ��Դֵ
		PROG_LIGHT_WF_RING,
		PROG_LIGHT_WF_COAX,
		
		PROG_STREET_X,
		PROG_STREET_Y,
		PROG_SRH_DIE_MODE,
		PROG_SRH_DIE_DIR,
		PROG_SRH_DIE_MISS_CNT,
		PROG_DIE_ACCEPT,
		PROG_DIE_GRAB_TIME,
		
		PROG_EPXDIE_OFFSET,//�罺ֱ��ƫ��
		
		PROG_DB_ANGLE,//��Ƭ�Ƕȷ�Χ
		
		PROG_ALG_MODE,//�Ե�ģʽ
		
		PROG_ADJ_MODE,//�̾�У��ģʽ
		
		PROG_ALG_PR_DELAY,//��������������ʱ
		PROG_ALG_ACCEPT,//�װ�ƥ��ֵ
		
		PROG_PT_PR_DELAY,//У���̾�λ��ʱ���ҽ�����ƥ��ֵ
		
		PROG_PT_ACCEPT,//��Ƭ�����ƥ��ֵ
		
		PROG_DB_SHOW_DELAY,
		
		PROG_READ_ED,
		
		PROG_DELAY_EP_LEAVE,//��ͷ��ת��ʱ
		PROG_DELAY_COLLETPUTDOWN,//��Ƭ��ʱ
		
		PROG_POS_EPZ_PREBOND,//��װоƬ���罺�߶�
};

enum ProgMachPara
{
	//�㽺����
	MACH_EP_START = 100,
	ID_MACH_EP_RDYZ,	//׼���߶�
	ID_MACH_EP_GETX,	//ȡ��λ��
	ID_MACH_EP_GETZ,	//ȡ���߶�
	ID_MACH_EP_SETX,	//�㽺λ��
	ID_MACH_EP_SETZ,	//�㽺�߶�
	ID_MACH_BC_RDYX,	//����λX
	ID_MACH_BC_RDYY,	//����λX
	ID_MACH_EP_RDYX,    //Ԥ���㽺λ��--��ʱδ��
	ID_MACH_EP_CLEAR,	//�㽺��ϴ����λ

	//�̾�����
	MACH_BD_START = 200,
	ID_MACH_SW2_RDYZ,	//׼���߶�
	//ID_MACH_SW2_RDYX,   //�̾�Ԥ��λ������������Թ��������ǵ㽺���ܹ�ȥ���������������λ
	//ID_MACH_PK2_PREP_CAM2_POS,  //�̾����Ԥȡ��λ��  У�������������λ---����ǰͣ
	ID_MACH_SW2_RDYX,	//�̾�Ԥ��λ
	ID_MACH_PK2_PREP_CAM2_POS_NOUSE, //����
	ID_MACH_SW2_GETX,	//ȡ��λ��
	ID_MACH_SW2_GETZ,   //ȡ�ϸ߶�
	ID_MACH_SW2_SETX,	//����λ��
	ID_MACH_SW2_SETZ,	//���ϸ߶�
	ID_MACH_PK2_AFTER_CAM3_POS, //�̾��������ʱ���㽺�����������λ --���պ��ж�
	ID_MACH_DIE_RDYX,	//����̨����λX
	ID_MACH_DIE_RDYY,	//����̨����λY
	ID_MACH_BD_CLEAR,	//�̾���ϴ����λ

	//ȡ������
	MACH_PK_SATRT = 300,
	ID_MACH_SW1_RDYZ,	 //׼���߶�
	//����Ԥ��λ�����������������λ ����ǰ�����λ��ͣһ��---����ǰͣ
	ID_MACH_SW1_RDYX,    //							������ȥ�ž�ʱ---��ﲻͣ���ж�λ--���պ��ж�
	ID_MACH_SW1_GETX,	//ȡ��λ��
	ID_MACH_SW1_GETZ,	//ȡ�ϸ߶�
	ID_MACH_SW1_SETX,	//����λ��
	ID_MACH_SW1_SETZ,	//���ϸ߶�
	ID_MACH_PK1_AFTER_CAM1_POS_NOUSE,		   //����1����ʱ��У��̨��������λ�� ---��ﲻͣ���ж�λ--���պ��ж�
	ID_MACH_WF_RDYX,	//����λX
	ID_MACH_WF_RDYY,	//����λY
	ID_MACH_IGNORE_TIMES,
	ID_MACH_PK_CLEAR,	//������ϴ����λ

	//���Ȳ���
	MACH_PRECISION_START = 400,
	MACH_BD_PRECISION_X,
	MACH_BD_PRECISION_Y,
	MACH_BD_PRECISION_A,
	MACH_EP_PRECISION_X,
	MACH_EP_PRECISION_Y,
	MACH_PRECISION_END,

	

	//��ʱ����
	
	ID_MACH_GET1_DELAY,// ����1�ھ�Բ̨ȡ����ʱ
	ID_MACH_GET2_DELAY,//����1�ڽ���̨������ʱ 
	ID_MACH_SET2_DELAY,//����2�ڽ���̨ȡ����ʱ
	ID_MACH_DIE_DELAY,	//����2�̾���ʱ
	ID_MACH_EPGET_DELAY,//ȡ����ʱ
	ID_MACH_EPSET_DELAY,//�㽺��ʱ
	ID_MACH_CAM1_PREP_DELAY, //���1����ǰ��ʱ
	ID_MACH_CAM2_PREP_DELAY, //���1����ǰ��ʱ
	ID_MACH_CAM3_PREP_DELAY , //���1����ǰ��ʱ
	MACH_BD_CAM_AFTER_DELAY, //�̾���ͼ����ʾ��ʱ


	//ͼ��
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

	MACH_EP_OFFSET_X, //�㽺ƫ��X
	MACH_EP_OFFSET_Y, //�㽺ƫ��Y	
	MACH_CAM2_OFFSET_X,
	MACH_CAM2_OFFSET_Y,
	MACH_CAM3_OFFSET_X,
	MACH_CAM3_OFFSET_Y,

	MACH_WF_T_CPP_DIR,

	//�ع�����
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

//��ʽ��Ϣ�壺��������Ⱥ������ʽ����
struct ProgInfo_Blk
{
	int prg;
	int group_total;
	int pos_total;
	char name[255];
	char lasttime[255];

};

//��λ��x��y��
struct Pos_Blk//POSX,Y
{
	int x;
	int y;
};

//�װ嶨λ��
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

//�����������Ĺ��������õ�����
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
union AllPrPara_Blk//����ʵ��������������
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

struct Pr_Blk//�������й������Ĳ���
{	
	unsigned char* pimage;
	AllPrPara_Blk AllPrPara;
	
	Pr_Blk()
	{
		pimage = 0;
	}
};
struct Para_Blk//�Ե��׼λ�����ʽ��Ӧ����
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

	//�����Ĳ������η��ں��棬������������Ĳ�����������λ
	//about delay
	int delay_ep_pick;
	int delay_ep_bond;

	//about wf
	int srh_die_miss_cnt;//©������1��10
	int die_accept;//��Ƭ���ƶȣ�40 �� 100 %
	int die_grab_time;//ȡͼʱ�䣺20 �� 50 ms
	
	//about wh
	int alg_mode;//�Ե�ģʽ��1=���Ե�  2=��У���̾��㣨֧��ģʽ��  3=�Ե�+У���̾���
	int adj_mode;// У��ģʽ  1=��ǰУ��  
	int alg_pr_dly;// �Ե�ͼ����ʱ:У��ǰ��ʱ��20ms
	int alg_accept;// �Ե����ƶ�:  40~100%
	int pt_pr_dly;// �̾���ͼ����ʱ: У��ǰ��ʱ��20ms
	int pt_accept;// �̾������ƶȣ�  40~100%
	int db_show_dly;// �̾���ͼ����ʱ���̾���ɺ���ʾͼ��ʱ��,25ms

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
union AllProgPara_Blk//��ʽ���ݹ�����
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
//��̨�����ĳɳ�ʽ����
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
	int LoadParaDB();//loadԭ��Ӧ����ʽ�Ĳ���
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
	void SetBaseAlg(int alg1_x, int alg1_y, int alg2_x, int alg2_y);//���õ�һ����Ⱥ�������Ե�����׼��
	void AddGroup(int alg1_x, int alg1_y);//������Ⱥ��ĩβ��ƫ��ֵΪ��������͵�һ����Ⱥ�ĵ�һ���Ե�ľ���
	void AddGroup(int alg1_x, int alg1_y, int grp_st, int grp_ed);//������Ⱥ��ĩβ
	void AddGroup(int group, int alg1_x, int alg1_y);//��group��������Ⱥ
	void DelGroup(int group);
	void SetAlg1(int group, int x, int y);//�޸���Ⱥ�Ե�
	void SetAlg2(int group, int x, int y);
	void SetBaseAlg1(int x, int y);//�޸ĶԵ�
	void SetBaseAlg2(int x, int y);
	void AddPos(int x, int y);
	void AddPos(int x, int y, int pos_st, int pos_ed);
	void AddPos(int pos, int x, int y);//��pos�����ӹ̾���
	void DelPos(int pos);
	void SetPos(int pos, int x, int y);//�޸Ĺ̾���
	void SetRefAlg(int group, int alg1_x, int alg1_y, int alg2_x, int alg2_y);//�ڶԵ�������������ҵ��ĶԵ�
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

	Group_Blk m_WHStripAlgChk;// �̾���Ƭ�Ե���

	vector<Pos_Blk> d_AllPosVec_temp;
	vector<Group_Blk> d_GroupVec_temp;


	Para_Blk d_ParaBlk;//�װ嶨λ����

	ProgPara_Blk d_ProgPara;//ԭ��Ӧ����ʽ�Ĳ���


	//====


	Pr_Blk d_PrWf;
	Pr_Blk d_PrPt;
	Pr_Blk d_PrAlg1;
	Pr_Blk d_PrAlg2;

	MachProg_Blk d_MachProg;

//���мӹ�
public:
	int GetRow(){return m_row;}
	int GetCol(){return m_col;}
	void GetRectPoint(int num,Pos_Blk& pos); //num 0:���ϣ�1�����ϣ�2������

	void SetRow(int row);
	void SetCol(int col);
	void SetRectPoint(int num,Pos_Blk pos);//num 0:���ϣ�1�����ϣ�2������

	void SetGrpRow(int row);
	void SetGrpCol(int col);
	void SetGrpRectPoint(int num, int x, int y);//num 0:���ϣ�1�����ϣ�2������
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

//��Դ
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

//�ֵ�
public:
	BOOL m_bEnableFd; //�����ֵ㹦��
	int  m_iTTFd;	  //�ֵ�����
	int  m_iCurFd;	  //��ǰ�ֵ�

	void GetFdPos(int idx,double &x,double &y);
	void SetFdPos(int idx,double x,double y);

	void AddFdPos(double x,double y);
	void ChangeFdPos(int idx,double x,double y);
	void DelFdPos();//ɾ�����һ��

	void SetCurFd(int idx);

	void SetEnableFd(BOOL bFd);

public:
	void Set_Modify_GrpAlg1(int group, int x, int y);//�޸���Ⱥ��

private:
	double m_dFdX[100];
	double m_dFdY[100];

public:
	int m_iBdOffX;
	int m_iBdOffY;
};


extern CProgData g_ProgDataBd; //�̾�




extern int GetProgInfo(int prg_no, ProgInfo_Blk& ProgInfo);

#endif//_WH_DATA_H_

