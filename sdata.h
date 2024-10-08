#pragma once

#pragma comment(lib,"..\\exlib\\bt929sdata.lib")

enum eLanID
{
	LAN_ENG=0,// 英文
	LAN_CHS,// 中文
	LAN_END
};

//---- 更新共享内存的配置数据

//---- mode 模式: 
//----         1=写入配置数据
//----         2=读取配置数据
//----------------------------------------
#define SWAPDATA_LAN_ID				  1	// 0：eng 1：chs
#define SWAPDATA_USER_LEVEL			  2	// 用户权限
#define SWAPDATA_TAB1_DN_FLAG		  10	//开始下料标志1：下料结束0
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

#define SWAPDATA_IN_Img_Stop			  27 //急停信号
#define SWAPDATA_IN_Air_Pressure		  28 //正压信号
#define SWAPDATA_IN_Neg_Pressure		  29 //正压信号


#define SWAPDATA_TAB2_UP_FLAG		  51    //准备要料1,要料结束0
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
//---- index 数据: A头
#define  SWAPDATA_CUR_POINT_A     100  //--- 当前点位
#define  SWAPDATA_CUR_GROUP_A     101  //--- 当前组群
#define  SWAPDATA_CUR_EP1_PT_A    102
#define  SWAPDATA_CUR_EP1_GRP_A   103
#define  SWAPDATA_CUR_EP2_PT_A    104
#define  SWAPDATA_CUR_EP2_GRP_A   105
#define  SWAPDATA_CUR_TIME_A      106  //--- 固晶周期
#define  SWAPDATA_CUR_TOTAL_A     107  //--- 总固晶数
#define  SWAPDATA_EP1_CYCTIME_A   108
#define  SWAPDATA_EP2_CYCTIME_A   109


//---- index 数据: B头
#define  SWAPDATA_CUR_POINT_B     200  //--- 当前点位
#define  SWAPDATA_CUR_GROUP_B     201  //--- 当前组群
#define  SWAPDATA_CUR_EP_PT_B     202
#define  SWAPDATA_CUR_EP_GRP_B    203
#define  SWAPDATA_CUR_TIME_B      206  //--- 固晶周期
#define  SWAPDATA_CUR_TOTAL_B     207  //--- 总固晶数
#define  SWAPDATA_EP_CYCTIME_B    208

#define  SWAPDATA_BD_INPUT_GetY  300  //--- B机台在固晶台上料等待
#define  SWAPDATA_INPUT_OVER	  301  //--- A机台固晶台交接出下料后升起来
#define  SWAPdATA_BDTAB_VAC		  302  //--- 固晶台开真空信号


#define SWAPdATA_CCD1_START		  400		//相机1开始检测
#define SWAPdATA_CCD2_START		  401		//相机2开始检测
#define SWAPdATA_CCD3_START		  402       //相机3开始检测
#define SWAPdATA_CCD4_START		  403       //相机4开始检测

#define SWAPdATA_CCD1_STS		  410		//相机1检测状态
#define SWAPdATA_CCD2_STS		  411		//相机2开始状态
#define SWAPdATA_CCD3_STS		  412       //相机3开始状态
#define SWAPdATA_CCD4_STS		  413       //相机4开始状态


#define SWAPdATA_CCD1_FRST		  450		//相机1第一次检测
#define SWAPdATA_CCD2_FRST		  451		//相机2第一次检测
#define SWAPdATA_CCD3_FRST		  452       //相机3第一次检测
#define SWAPdATA_CCD4_FRST	      453       //相机4第一次检测

#define SWAPdATA_CCD1_LAST		  420		//相机1最后一次检测
#define SWAPdATA_CCD2_LAST		  421		//相机2最后一次检测
#define SWAPdATA_CCD3_LAST		  422       //相机3最后一次检测
#define SWAPdATA_CCD4_LAST		  423       //相机4最后一次检测

#define SWAPdATA_CCD1_RLT		  430		//相机1检测结果OK1,NG0
#define SWAPdATA_CCD2_RLT		  431		//相机2检测结果OK1,NG0
#define SWAPdATA_CCD3_RLT		  432       //相机3检测结果OK1,NG0
#define SWAPdATA_CCD4_RLT		  433       //相机4检测结果OK1,NG0


#define SWAPdATA_PROC_START		  440       //检测程序运行1，停止运行0

#define SWAPdATA_CCD1_IDX		  450		//相机1检测编号
#define SWAPdATA_CCD2_IDX		  451		//相机2检测编号
#define SWAPdATA_CCD3_IDX		  452       //相机3检测编号
#define SWAPdATA_CCD4_IDX		  453       //相机4检测编号


#define SWAPdATA_CCD1_SEL_PR    460  //相机1检测SEL_PR
#define SWAPdATA_CCD2_SEL_PR    461  //相机2检测SEL_PR
#define SWAPdATA_CCD3_SEL_PR    462       //相机3检测SEL_PR
#define SWAPdATA_CCD4_SEL_PR    463       //相机4检测SEL_PR

#define SWAPdATA_BDTAB1_IN_SAFE_POS    470       //固晶台1在安全位
#define SWAPdATA_BDTAB1_IN_OUT_POS     471		 //固晶台1在下料位
#define SWAPdATA_BDTAB1_READY		   472		 //固晶台1有料
#define SWAPdATA_BDTAB1_RUN_FLAG	   473		 //固晶台1程序正在运行
#define SWAPdATA_BDTAB1_OUT_CLAW_READY 474       //固晶出1出料爪有料
#define SWAPdATA_BDTAB1_PK_OVER		   475		 //固晶台1料片被取走

#define SWAPdATA_BDTAB2_IN_SAFE_POS    480       //固晶台2在安全位
#define SWAPdATA_BDTAB2_IN_POS_READY   481       //固晶台2到上料位了
#define SWAPdATA_BDTAB2_READY		   482		 //固晶台2有料了
#define SWAPdATA_BDTAB2_RUN_FLAG	   483		 //固晶台2程序正在运行
#define SWAPdATA_BDTAB2_PK_CLAW_READY  484       //固晶出2取料爪有料
#define SWAPdATA_BDTAB2_OUT_POS_READY   485       //固晶台2到上料位了

#define SWAPdATA_WFTAB1_GetY			490
#define SWAPdATA_WFTAB1_OVER			491
#define SWAPdATA_WFTAB1_IN_CHANGE_POS	492
#define SWAPdATA_WFTAB1_JL_SYN		    493

//---- 更新CCD的显示数据
//---- CCD编号:1..4
//---- CCD模式: 
//----         1=写入 CCD图像数据 640x480
//----         2=读取 CCD图像数据 640x480  
AFX_API_IMPORT int DataSwapCCD(int ccd,int mode,void* pdata);


// 共享内存——读写各项标志位数据
AFX_API_IMPORT int DataSwapSys(int mode,int index,int data);