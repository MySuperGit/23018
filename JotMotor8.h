#pragma once

#include "BaseMotor.h"

class AFX_CLASS_IMPORT CJotMotor8 : public CBaseMotor
{
public:
	CJotMotor8(int canno,int id);
	virtual ~CJotMotor8(void);

private:
	
	void CheckErrorLog(CString funcName,int Error);
	CString GetErrorInfo(int Error);

public:
	int SetMtrID(int id);
	int Init();
	int Exit();

	//运动相关
public:
	int ServoOn();
	int ServoOff();

	int IsAlarm();
	int ClearAlarm();	

	int SetSerachSpd( int startSpd ,int maxSpd  ,int acc);
	int SetSerachLowSpd();
	int SetSerachHighSpd();
	int SearchSnsFor();
	int SearchSnsReverse();
	int SerachSns(int snsSts,int homedir);
	int Home();
	int HomeZero();
	static UINT ThreadHome(LPVOID lp);
	int GetHomingSts(){return m_bhoming;}
	int WaitHome();
	int IsHomeOk();

	int SetSoftLimit(int limitP,int limitN);

	int SetPfPara(int pfno,double stvel,double maxvel,double stopvel,double acc,double dec);
	int MoveAbsPf(int pos,int pfno);
	int MoveRelPf(int pos,int pfno);
	int MoveAbs(int pos);
	int MoveAbs(int pos,double dvel);
	int MoveRel(int pos);
	int MoveAbsMm(double pos);
	int MoveRelMm(double pos);
	int ConstMove(int pos,double dvel);
	int ConstMove(int pos);
	int MmToPulse(double mm);
	double PulseToMm(int pulse);
	int ChangePosMove(int pos);

	int IsMoving();
	int WaitStop();
	int StopMove();

	//位置相关
public:
	int GetPos();
	double GetPosMm();
	int SetPos(int pos);
	int GetEncPos();
	int SetEncPos(int pos);
	int GetErrorPos();
	int CheckPosError(int error = 100);

	int GetAllSnr(int* snr0,int* snr1,int* snr2,int* snrp,int* snrn);
	int GetSnr0();
	int GetSnr1();
	int GetSnr2();
	int GetSnrP();
	int GetSnrN();


};

