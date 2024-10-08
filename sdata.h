#pragma once

#pragma comment(lib,"..\\exlib\\bt929sdata.lib")

enum eLanID
{
	LAN_ENG=0,// Ӣ��
	LAN_CHS,// ����
	LAN_END
};

//---- ���¹����ڴ����������

//---- mode ģʽ: 
//----         1=д����������
//----         2=��ȡ��������
//----------------------------------------
#define SWAPDATA_LAN_ID				  1	// 0��eng 1��chs
#define SWAPDATA_USER_LEVEL			  2	// �û�Ȩ��
#define SWAPDATA_TAB1_DN_FLAG		  10	//��ʼ���ϱ�־1�����Ͻ���0
#define SWAPDATA_TAB1_ERR_FLAG		  11  
#define SWAPDATA_TAB1_UNSAFE_FLAG	  12
#define SWAPDATA_TAB1_X_CUR_POS		  13
#define SWAPDATA_TAB1_X_HM_FLAg		  14

#define SWAPDATA_nDB_A_Cycle		  20 
#define SWAPDATA_nDB_A_Total		  21	
#define SWAPDATA_nDB_A_UPH			  22	
#define SWAPDATA_nEJP_A_Cnt_Cur		  23 	
#define SWAPDATA_nCollet_A_Cnt_Cur	  24
#define SWAPDATA_nPrg_A_Pnt_Cur		  25
#define SWAPDATA_nPrg_A_Grp_Cur       26

#define SWAPDATA_IN_Img_Stop			  27 //��ͣ�ź�
#define SWAPDATA_IN_Air_Pressure		  28 //��ѹ�ź�
#define SWAPDATA_IN_Neg_Pressure		  29 //��ѹ�ź�


#define SWAPDATA_TAB2_UP_FLAG		  51    //׼��Ҫ��1,Ҫ�Ͻ���0
#define SWAPDATA_TAB2_ERR_FLAG		  52 
#define SWAPDATA_TAB2_UNSAFE_FLAG	  52
#define SWAPDATA_TAB2_X_CUR_POS		  53			 
#define SWAPDATA_TAB2_X_HM_FLAg		  54

#define SWAPDATA_nDB_B_Cycle		  60 
#define SWAPDATA_nDB_B_Total		  61	
#define SWAPDATA_nDB_B_UPH			  62	
#define SWAPDATA_nEJP_B_Cnt_Cur		  63 	
#define SWAPDATA_nCollet_B_Cnt_Cur	  64
#define SWAPDATA_nPrg_B_Pnt_Cur		  65
#define SWAPDATA_nPrg_B_Grp_Cur       66
//----------------------------------------
//---- index ����: Aͷ
#define  SWAPDATA_CUR_POINT_A     100  //--- ��ǰ��λ
#define  SWAPDATA_CUR_GROUP_A     101  //--- ��ǰ��Ⱥ
#define  SWAPDATA_CUR_EP1_PT_A    102
#define  SWAPDATA_CUR_EP1_GRP_A   103
#define  SWAPDATA_CUR_EP2_PT_A    104
#define  SWAPDATA_CUR_EP2_GRP_A   105
#define  SWAPDATA_CUR_TIME_A      106  //--- �̾�����
#define  SWAPDATA_CUR_TOTAL_A     107  //--- �ܹ̾���
#define  SWAPDATA_EP1_CYCTIME_A   108
#define  SWAPDATA_EP2_CYCTIME_A   109


//---- index ����: Bͷ
#define  SWAPDATA_CUR_POINT_B     200  //--- ��ǰ��λ
#define  SWAPDATA_CUR_GROUP_B     201  //--- ��ǰ��Ⱥ
#define  SWAPDATA_CUR_EP_PT_B     202
#define  SWAPDATA_CUR_EP_GRP_B    203
#define  SWAPDATA_CUR_TIME_B      206  //--- �̾�����
#define  SWAPDATA_CUR_TOTAL_B     207  //--- �ܹ̾���
#define  SWAPDATA_EP_CYCTIME_B    208

#define  SWAPDATA_BD_INPUT_GetY  300  //--- B��̨�ڹ̾�̨���ϵȴ�
#define  SWAPDATA_INPUT_OVER	  301  //--- A��̨�̾�̨���ӳ����Ϻ�������
#define  SWAPdATA_BDTAB_VAC		  302  //--- �̾�̨������ź�


#define SWAPdATA_CCD1_START		  400		//���1��ʼ���
#define SWAPdATA_CCD2_START		  401		//���2��ʼ���
#define SWAPdATA_CCD3_START		  402       //���3��ʼ���
#define SWAPdATA_CCD4_START		  403       //���4��ʼ���

#define SWAPdATA_CCD1_STS		  410		//���1���״̬
#define SWAPdATA_CCD2_STS		  411		//���2��ʼ״̬
#define SWAPdATA_CCD3_STS		  412       //���3��ʼ״̬
#define SWAPdATA_CCD4_STS		  413       //���4��ʼ״̬


#define SWAPdATA_CCD1_FRST		  450		//���1��һ�μ��
#define SWAPdATA_CCD2_FRST		  451		//���2��һ�μ��
#define SWAPdATA_CCD3_FRST		  452       //���3��һ�μ��
#define SWAPdATA_CCD4_FRST	      453       //���4��һ�μ��

#define SWAPdATA_CCD1_LAST		  420		//���1���һ�μ��
#define SWAPdATA_CCD2_LAST		  421		//���2���һ�μ��
#define SWAPdATA_CCD3_LAST		  422       //���3���һ�μ��
#define SWAPdATA_CCD4_LAST		  423       //���4���һ�μ��

#define SWAPdATA_CCD1_RLT		  430		//���1�����OK1,NG0
#define SWAPdATA_CCD2_RLT		  431		//���2�����OK1,NG0
#define SWAPdATA_CCD3_RLT		  432       //���3�����OK1,NG0
#define SWAPdATA_CCD4_RLT		  433       //���4�����OK1,NG0


#define SWAPdATA_PROC_START		  440       //����������1��ֹͣ����0

#define SWAPdATA_CCD1_IDX		  450		//���1�����
#define SWAPdATA_CCD2_IDX		  451		//���2�����
#define SWAPdATA_CCD3_IDX		  452       //���3�����
#define SWAPdATA_CCD4_IDX		  453       //���4�����


#define SWAPdATA_CCD1_SEL_PR    460  //���1���SEL_PR
#define SWAPdATA_CCD2_SEL_PR    461  //���2���SEL_PR
#define SWAPdATA_CCD3_SEL_PR    462       //���3���SEL_PR
#define SWAPdATA_CCD4_SEL_PR    463       //���4���SEL_PR

#define SWAPdATA_BDTAB1_IN_SAFE_POS    470       //�̾�̨1�ڰ�ȫλ
#define SWAPdATA_BDTAB1_IN_OUT_POS     471		 //�̾�̨1������λ
#define SWAPdATA_BDTAB1_READY		   472		 //�̾�̨1����
#define SWAPdATA_BDTAB1_RUN_FLAG	   473		 //�̾�̨1������������
#define SWAPdATA_BDTAB1_OUT_CLAW_READY 474       //�̾���1����צ����
#define SWAPdATA_BDTAB1_PK_OVER		   475		 //�̾�̨1��Ƭ��ȡ��

#define SWAPdATA_BDTAB2_IN_SAFE_POS    480       //�̾�̨2�ڰ�ȫλ
#define SWAPdATA_BDTAB2_IN_POS_READY   481       //�̾�̨2������λ��
#define SWAPdATA_BDTAB2_READY		   482		 //�̾�̨2������
#define SWAPdATA_BDTAB2_RUN_FLAG	   483		 //�̾�̨2������������
#define SWAPdATA_BDTAB2_PK_CLAW_READY  484       //�̾���2ȡ��צ����
#define SWAPdATA_BDTAB2_OUT_POS_READY   485       //�̾�̨2������λ��

#define SWAPdATA_WFTAB1_GetY			490
#define SWAPdATA_WFTAB1_OVER			491
#define SWAPdATA_WFTAB1_IN_CHANGE_POS	492
#define SWAPdATA_WFTAB1_JL_SYN		    493

//---- ����CCD����ʾ����
//---- CCD���:1..4
//---- CCDģʽ: 
//----         1=д�� CCDͼ������ 640x480
//----         2=��ȡ CCDͼ������ 640x480  
AFX_API_IMPORT int DataSwapCCD(int ccd,int mode,void* pdata);


// �����ڴ桪����д�����־λ����
AFX_API_IMPORT int DataSwapSys(int mode,int index,int data);