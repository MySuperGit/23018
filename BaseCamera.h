#pragma once
#include <afxtempl.h>
#include <vector>
using std::vector;
#include "cputimer.h"


#define CCD_W	640
#define CCD_H	480

#define WM_USER_DRAW_IMGVIEW (WM_USER+2198) // 刷新相机图像

//相机品牌
typedef enum CamBrand
{
	eVirtual = 0,      //虚拟相机
	eHIKVISION,        //海康相机
	eDOTHINK,          //度申相机
	eMICROVIEW_MSZ     //北京微视MSZ相机
};

enum TriggerMode
{
	CONTINUE =0,  //连续模式
	SOFTWARE,     //软触发
	EXTERNAL,     //硬触发
};

//相机参数，读写，需要保存
struct CamParameter
{
	int ExposureTime;  //曝光时间
	int Gain;          //增益
	TriggerMode TrigMode;  //触发模式
	int TimeOut;        //采集超时时间

	CamParameter()
	{
		ExposureTime = 10000;  //默认10ms
		Gain = 1;			//默认1
		TrigMode = CONTINUE;
		TimeOut = 1000;
	}
};

//相机信息，只读
struct CameraInfo
{
	CamBrand eBrand;    //相机品牌
	CString strBrand;   //相机品牌
	CString strSN;      //相机SN号
	BOOL IsConnected;   //是否已连接
	unsigned int MaxWidth;      //相机最大宽度
	unsigned int MaxHeight;     //相机最大高度
	unsigned int DevIndex;      //同一种型号的相机序号

	CameraInfo()
	{
		eBrand = eVirtual;
		strBrand = "";
		strSN = "";
		IsConnected = FALSE;
		MaxWidth = 0;
		MaxHeight = 0;
		DevIndex = 0;		
	}
};

class AFX_CLASS_EXPORT CBaseCamera
{
public:
	CBaseCamera();
	CBaseCamera(int index);
	~CBaseCamera(void);

public:
	int SetID(int id);
	virtual BOOL StartConnect() = 0;
	virtual BOOL StopConnect() = 0;
	virtual BOOL StartCapture() = 0;
	virtual BOOL StopCapture() = 0;
	virtual void SetCamParameter(CamParameter para)=0 ;
	virtual BOOL SetCamParameter()=0 ;
	virtual BOOL DoSoftTrigger() = 0;
	virtual int GetImageOk() = 0;
	virtual int WaitImageOk() = 0;
	virtual void SetImgNum(int num) = 0;
	void GetCamParameter(CamParameter &para);
	void GetCameraInfo(CameraInfo &CamInfo);
	BOOL GetImageBuf(BYTE* pBuf,int Width,int Height);
	BOOL GetImageBufDirect(BYTE* pBuf, int Width, int Height);
	int Width();
	int Height();
	int SleepExms(int ms);
	void SetImgWnd(HWND hWnd);

public:
	BYTE* pImageBuf; //图像数据

public:
	CamParameter m_CamParameter;
	CameraInfo m_CameraInfo;
	BOOL m_bImageOK;
	CCpuTimer framtm;
	HWND m_hImgWnd;
};

//class AFX_CLASS_EXPORT CCameraManager
//{
//public:
//	CCameraManager();
//	~CCameraManager();
//public:
////	CBaseCamera* GetCameraInstance(int iIndex); //所有品牌相机从0开始的序号
//	CBaseCamera* InitCamera(CamBrand brand,int index);
//	void Clear();
//
//private:
//	vector<CBaseCamera*>   m_CameraVect;
//};

