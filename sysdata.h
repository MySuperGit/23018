#ifndef _SYS_DATA_H_
#define _SYS_DATA_H_

struct SysBlk
{
	//need save
	int cur_proc_prog;
	int total_die_bonded;
	int total_db_time;

	int reserved[17];
	SysBlk()
	{
		cur_proc_prog = 1;
		total_die_bonded = 0;
		total_db_time = 0;
	}
};
struct SysBlk2
{
	//not need save
	int cur_sel_prog;
	int cur_cycle_time;
	SysBlk2()
	{
		cur_sel_prog = 1;
		cur_cycle_time = 0;
	}	
};

class CSysData
{
public:
	CSysData();
	~CSysData();

	void Save();
	void Load();
public:
	void SetCurProcProg(int prog);
	void SetCurSelProg(int prog);
	int GetCurProcProg();
	int GetCurSelProg();

	void SetTotalDieBonded(int total);
	void AddTotalDieBonded(int incr=1);
	int GetTotalDieBonded();
	void SetTotalDbTime(int total);
	void AddTotalDbTime(int ms);
	int GetTotalDbTime();//返回时s还是min比较好
	void SetCurCycleTime(int time);
	int GetCurCycleTime();

	int GetDialogBkColor();
	int GetStaticTextColor();
	int GetButtonBkColor();
	int GetButtonFocusBkColor();
	int GetCheckBkColor();
	int GetCheckFocusBkColor();
public:
	SysBlk d_SysBlk;
	SysBlk2 d_SysBlk2;
};

#endif//_SYS_DATA_H_

