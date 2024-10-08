#pragma once

#include "afxmt.h"

//控制卡品牌
enum eMotorBrand
{
	eVirtualCard = -1,
	eJotCard8,
	eJotCard4,
	eHYCard,
	eLeiSaiCard,
	eGTSCard
};

//控制卡类型
enum eMotorType
{
	eMotorTypeNone = 0,
	eStepType,  //步进电机
	eServoType,  //伺服电机
};

//返回值
#define CARD_OK				1
#define CARD_NG_NOT_HOME	-1
#define CARD_NG_OUT_LIMIT	-2
#define CARD_NG_NOT_INIT	-3

class AFX_CLASS_IMPORT CInBit
{
public:
	CInBit(int canno,int cardno,int bitno);
	~CInBit();
public:
	void SetReverse(int reverse);
	int Get();
private:
	int m_canno;
	int m_cardno;
	int m_bitno;

	int m_status;
	int m_reverse;
};

class AFX_CLASS_IMPORT CAxisInBit
{
public:
	CAxisInBit(int canno,int cardno,int bitno);
	~CAxisInBit();
public:
	void Set(int canno,int cardno,int bitno);
	void SetReverse(int reverse);
	int Get();
private:
	int m_canno;
	int m_cardno;
	int m_bitno;

	int m_status;
	int m_reverse;
};

class AFX_CLASS_IMPORT COutBit
{
public:
	COutBit(int canno,int cardno,int bitno);
	~COutBit();
public:
	void Set(int canno,int cardno,int bitno);
	void SetReverse(int reverse);
	int On();
	int Off();
	int Get();
private:
	int m_canno;
	int m_cardno;
	int m_bitno;

	int m_status;
	int m_reverse;
};

class AFX_CLASS_IMPORT COutPWM
{
public:
	COutPWM(int canno,int cardno,int bitno);
	~COutPWM();
public:
	void Set(int canno,int cardno,int bitno);
	int Out(int value);
	int GetValue();
	int OutFreq(int freq);
	int GetFreq();
private:
	int m_canno;
	int m_cardno;
	int m_bitno;

	int m_value;
	int m_cycle;
	int m_freq;
};


class AFX_CLASS_IMPORT CBaseMotor
{
public:
	CBaseMotor(int canno,int id );
	virtual ~CBaseMotor(void);

public:
	virtual void SetCardInitOK(BOOL bOK);
	virtual	int SetMtrID(int id);
	virtual int Init();
	virtual int Exit();

	virtual int LoadConfig();
	virtual int SaveConfig();

	//运动相关
public:
	virtual int ServoOn();
	virtual int ServoOff();

	virtual int IsAlarm();
	virtual int ClearAlarm();

	virtual int Home();
	virtual int HomeZero();
	virtual int GetHomingSts(){return m_bhoming;}
	virtual int WaitHome();
	virtual int IsHomeOk();

	virtual int SetSoftLimit(int limitP,int limitN);

	virtual	int SetPfPara(int pfno,double stvel,double maxvel,double stopvel,double acc,double dec);
	virtual int MoveAbs(int pos);
	virtual int MoveAbs(int pos,double dvel);
	virtual int MoveRel(int pos);
	virtual int MoveRel(int pos,double dvel);
	virtual int MmToPulse(double mm);
	virtual double PulseToMm(int pulse);
	virtual int MoveAbsMm(double pos);
	virtual int MoveRelMm(double pos);
	virtual int ConstMove(int pos,double dvel);
	virtual int ConstMove(int pos);
	virtual int ChangePosMove(int pos);

	virtual int IsMoving();
	virtual int WaitStop();
	virtual int StopMove();

	//位置相关
public:
	virtual int GetPos();
	virtual double GetPosMm();
	virtual int SetPos(int pos);
	virtual int GetEncPos();
	virtual int SetEncPos(int pos);
	virtual int GetErrorPos();
	virtual int SetEncDir(int ifreverse);// 0－不取反， 1－取反
	virtual int CheckPosError(int error = 100);

	virtual int GetSnr0();
	virtual int GetSnr1();
	virtual int GetSnr2();
	virtual int GetSnrP();
	virtual int GetSnrN();

	//参数获取设置
public:
	int GetMtrID();
	int SetMtrName(CString name);
	CString GetMtrName();
	int SetCanNo(int no);
	int GetCanNo();
	int SetCardNo(int no);
	int GetCardNo();
	int SetAxisNo(int no);
	int GetAxisNo();
	int SetMotor4(int motor4);
	int GetIsMotor4();

	int SetPerCircleMm(int mm);
	int GetPerCircleMm();
	int SetPerCirclePulse(int pulse);
	int GetPerCirclePulse();
	int SetMmPerPulse(double value);
	double GetMmPerPulse();

	int SetHomeDist(int dist);
	int GetHomeDist();
	int SetHomeDir(int dir);
	int GetHomeDir();
	int SetHomeHighStartSpd(double spd);
	double GetHomeHighStartSpd();
	int SetHomeLowStartSpd(double spd);
	double GetHomeLowStartSpd();

	int SetLimitP(int pos);
	int GetLimitP();
	int SetLimitN(int pos);
	int GetLimitN();

	int SetPf1IniSpd(double spd);
	double GetPf1IniSpd();
	int SetPf1MaxSpd(double spd);
	double GetPf1MaxSpd();
	int SetPf1Acc(double acc);
	double GetPf1Acc();
	int SetPf1Dec(double dec);
	double GetPf1Dec();

	int SetEncReverse(int reverse);
	int GetEncReverse();
	int SetStartPos(int pos);
	int GetStartPos();
	int SetEndPos(int pos);
	int GetEndPos();
	int SetRelMovePos(int pos);
	int GetRelMovePos();

	int SetConstMvVel(double vel);
	double GetConstMvVel();
	int SetConstMvVel_H(double vel);
	double GetConstMvVel_H();

public:
	BOOL m_bIsHomeOk;	
	BOOL m_bhoming;

	BOOL m_bCardInitOK;

	int m_iVirtualPos;
protected:
	CCriticalSection m_Lock;

	//保存参数
	eMotorBrand m_eMotorBrand;
	eMotorType  m_eMotorType;
	int m_iMtrID; //所有马达序号，从0开始
	CString strName;

	int m_iCanNo;
	int m_iCardNo;
	int m_iAxisNo;
	int m_iIsMotor4;

	int m_iPerCircleMm;
	int m_iPerCirclePulse;
	double m_dMmPerPulse;   //每个脉冲mm数

	int m_iHomeDist;
	int m_iHomeDir;
	double m_dHomeHighStartSpd;
	double m_dHomeLowStartSpd;

	int m_iLimitP;
	int m_iLimitN;

	double m_dPf1IniSPd;
	double m_dPf1MaxSpd;
	double m_dPf1StopSpd;
	double m_dPf1AccA;
	double m_dPf1DecA;

	int m_bEncReverse;
	int m_iStartPos;
	int m_iEndPos;
	int m_iRelMovePos;

	double m_dConstMvVel;
	double m_dConstMvVel_H;
};
