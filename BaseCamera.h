#pragma once
#include <afxtempl.h>
#include <vector>
using std::vector;
#include "cputimer.h"


#define CCD_W	640
#define CCD_H	480

#define WM_USER_DRAW_IMGVIEW (WM_USER+2198) // ˢ�����ͼ��

//���Ʒ��
typedef enum CamBrand
{
	eVirtual = 0,      //�������
	eHIKVISION,        //�������
	eDOTHINK,          //�������
	eMICROVIEW_MSZ     //����΢��MSZ���
};

enum TriggerMode
{
	CONTINUE =0,  //����ģʽ
	SOFTWARE,     //����
	EXTERNAL,     //Ӳ����
};

//�����������д����Ҫ����
struct CamParameter
{
	int ExposureTime;  //�ع�ʱ��
	int Gain;          //����
	TriggerMode TrigMode;  //����ģʽ
	int TimeOut;        //�ɼ���ʱʱ��

	CamParameter()
	{
		ExposureTime = 10000;  //Ĭ��10ms
		Gain = 1;			//Ĭ��1
		TrigMode = CONTINUE;
		TimeOut = 1000;
	}
};

//�����Ϣ��ֻ��
struct CameraInfo
{
	CamBrand eBrand;    //���Ʒ��
	CString strBrand;   //���Ʒ��
	CString strSN;      //���SN��
	BOOL IsConnected;   //�Ƿ�������
	unsigned int MaxWidth;      //��������
	unsigned int MaxHeight;     //������߶�
	unsigned int DevIndex;      //ͬһ���ͺŵ�������

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
	BYTE* pImageBuf; //ͼ������

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
////	CBaseCamera* GetCameraInstance(int iIndex); //����Ʒ�������0��ʼ�����
//	CBaseCamera* InitCamera(CamBrand brand,int index);
//	void Clear();
//
//private:
//	vector<CBaseCamera*>   m_CameraVect;
//};

