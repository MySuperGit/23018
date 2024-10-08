#ifndef CCD_FUNC_H_
#define CCD_FUNC_H_

#include "BaseCamera.h"

class  AFX_CLASS_EXPORT CMSZCamera
{
public:
	CMSZCamera();
	~CMSZCamera();
	
public:
	BOOL Create(int nBand);
	int SetID(int id); 
	int Init();
	int Exit();
	int GetImageBuf(BYTE* buf);  //copy image from the CCD buffer
	int GetImageBufDirect(BYTE* buf); 
	int SetCCDPara(int etime,int gain);
	int SetTrigMode(int mode);
	int SoftTrig();
	int GetImageOk();
	int WaitImageOk();

	void SetImgNum(int num);
	void SetImgWnd(HWND hWnd);
public:
	int GetHandle();

private:
	CBaseCamera* m_pBaseCamera;
};

#endif