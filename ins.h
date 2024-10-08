#pragma once

#include "..\\exh\\BaseCamera.h"
enum ePRPara
{
	PR_INT_START = 0,
	eSCORE,
	eMODWIDTH,
	eMODHEIGHT,
	eROIWIDTH,
	eROIHEIGHT,
	ePATCREATED,
	eMODCREATED,
	eFINDMODE, //0,�Ҷȣ�1����

	eENABLE_BLOB,
	eBLOB_OFF_X,
	eBLOB_OFF_Y,
	eBLOB_MIN_AREA,
	eBLOB_THRESHOLD,

	eCENTOFFX,
	eCENTOFFY,

	PR_INT_END=99
};

enum ePRParaF
{
	PR_DOUBLE_START = 0,
	ePT_POS1_X,
	ePT_POS1_Y,

	//eCAL_POS1_X,
	//eCAL_POS1_Y,
	//eCAL_POS2_X,
	//eCAL_POS2_Y,
	//eCAL_RESULT_RX,
	//eCAL_RESULT_RY,
	//eCAL_RX_DIR,
	//eCAL_RY_DIR,

	PR_DOUBLE_END=99
};

enum eInsPara
{
	INS_INT_START = 0,
	eLIGHT,
	eEXPOUSRE,
	eGAIN,
	eLIGHT_G,// �̹�
	eLIGHT_B,// ����

	INS_INT_END = 99
};

enum eInsParaF
{
	INS_DOUBLE_START = 0,

	//�궨����
	eCAL_POS1_X,
	eCAL_POS1_Y,
	eCAL_POS2_X,
	eCAL_POS2_Y,
	eCAL_RESULT_RX,
	eCAL_RESULT_RY,
	eCAL_RX_DIR,
	eCAL_RY_DIR,
	//����ƫ��
	eOFFSET_NZ_X,
	eOFFSET_NZ_Y,
	eOFFSET_CAM_X,
	eOFFSET_CAM_Y,
	eOFFSETX,
	eOFFSETY,

	INS_DOUBLE_END = 99
};

enum eMachParaI
{
	MACH_INT_START = 0,

	MACH_INT_END = 99,
};

enum eMachParaF
{
	MACH_DOUBLE_START = 0,



	MACH_DOUBLE_END =99,
};


enum ePRName
{
	ePR_PT = 0,
	ePR_ALG1,
	ePR_ALG2,	//�̾�λ��prID
	ePR_PRE,// ��ǰ���
	ePR_AFTA,// �̺���
	ePR_END
};

enum eCCDName
{
	eCCD_WH = 0, 
	eCCD_WF,
	eCCD_END
};

class CMach_Data;
class CPRTemp;
class CBaseMotor;
class COutPWM;
class CHomMat2D;

class AFX_CLASS_IMPORT CIns
{
public:
	CIns(void);
	~CIns(void);

public:	
	int Init(int cam,int nBand);//cam �ڼ��������0Ϊ��һ�飬ÿ������������eCCD_END
	int Exit();
	int Load();
	int Save();
	int LoadMach();
	int SaveMach();

	//����
public:
	int SetPara(eCCDName ccdid,ePRName prid,ePRPara para,int value);
	int GetPara(eCCDName ccdid,ePRName prid,ePRPara para);
	
	int SetParaF(eCCDName ccdid,ePRName prid,ePRParaF para,double value);
	double GetParaF(eCCDName ccdid,ePRName prid,ePRParaF para);

	int SetPara(eCCDName ccdid,eInsPara para,int value);
	int GetPara(eCCDName ccdid,eInsPara para);

	int SetParaF(eCCDName ccdid,eInsParaF para,double value);
	double GetParaF(eCCDName ccdid,eInsParaF para);

	int SetPara(enum eCCDName ccdid,enum eMachParaI para,int value);
	int GetPara(enum eCCDName ccdid,enum eMachParaI para);
	int SetParaF(enum eCCDName ccdid,enum eMachParaF para,double value);
	double GetParaF(enum eCCDName ccdid,enum eMachParaF para);
public:
	int GetImageBuf(eCCDName ccdid,PBYTE pBuf);
	void SetCCDPara( eCCDName ccdid);//�����������
	int SetTrigMode( eCCDName ccdid,int mode);
	int SoftTrig( eCCDName ccdid);
	int GetImageOk(eCCDName ccdid );
	int WaitImageOk(eCCDName ccdid);

	int Create(eCCDName ccdid,ePRName prid);//����ģ��
	int DoSerach(eCCDName ccdid,ePRName prid);
	int GetResult(eCCDName ccdid,ePRName prid,double* score,double* posx,double* posy,double* angle,double* time);
	int GetResult(eCCDName ccdid,ePRName prid,int* num,double* score,double* posx,double* posy,double* angle,double* time); 
	void GetTpBuf(eCCDName ccdid,ePRName prid,PBYTE pBuf);
	void SetImgNum(eCCDName ccdid,int num);
	void SetImgWnd(eCCDName ccdid,HWND hWnd);// �����ˢ�´���
public:
	int ShowDlg(eCCDName ccdid,ePRName prid,CBaseMotor* x,CBaseMotor* y , CBaseMotor* z, COutPWM* pLight, COutPWM* pLightB = NULL, COutPWM* pLightG = NULL, double cenR=0,double cenX=0,double cenY=0);
	void SetProg(int id);

private:
	CPRTemp* pIns; //6�����
	CMach_Data* pMachData;
	int m_curProg;

	CHomMat2D* m_pHomMat2D;
};

AFX_CLASS_IMPORT CIns g_Ins;