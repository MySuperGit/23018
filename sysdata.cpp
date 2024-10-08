#include "stdafx.h"
#include <direct.h>
#include "sysdata.h"

static char s_para_path[30]=".\\ParaSy";

CSysData::CSysData()
{
	//Load();
}
CSysData::~CSysData()
{
	//Save();
}
void CSysData::Save()
{
	char name[255];
	sprintf(name, "%s", s_para_path);
	 _mkdir(s_para_path);// 先保证目录的存在

	FILE* pFile;
	sprintf(name, "%s\\SysPara.dat", s_para_path);
	pFile = fopen(name, "wb");
	if(!pFile)
		return;	
	fwrite(&d_SysBlk, sizeof(d_SysBlk), 1, pFile);
	fclose(pFile);	
}
void CSysData::Load()
{
	FILE* pFile;
	char name[255];
	sprintf(name, "%s\\SysPara.dat", s_para_path);
	pFile = fopen(name, "rb");
	if(!pFile)
		return;	
	fread(&d_SysBlk, sizeof(d_SysBlk), 1, pFile);
	fclose(pFile);
}

void CSysData::SetCurProcProg(int prog)
{
	d_SysBlk.cur_proc_prog = prog;
}
void CSysData::SetCurSelProg(int prog)
{
	d_SysBlk2.cur_sel_prog = prog;
}
int CSysData::GetCurProcProg()
{
	return d_SysBlk.cur_proc_prog;
}
int CSysData::GetCurSelProg()
{
	return d_SysBlk2.cur_sel_prog;
}
void CSysData::SetTotalDieBonded(int total)
{
	d_SysBlk.total_die_bonded = total;
}
void CSysData::AddTotalDieBonded(int incr)
{
	d_SysBlk.total_die_bonded += incr;
}
int CSysData::GetTotalDieBonded()
{
	return d_SysBlk.total_die_bonded;
}
void CSysData::SetTotalDbTime(int total)
{
	d_SysBlk.total_db_time = total;
}
void CSysData::AddTotalDbTime(int ms)
{
	d_SysBlk.total_db_time += ms;//?
}
int CSysData::GetTotalDbTime()
{
	return d_SysBlk.total_db_time;//?
}
void CSysData::SetCurCycleTime(int time)
{
	d_SysBlk2.cur_cycle_time = time;
}
int CSysData::GetCurCycleTime()
{
	return d_SysBlk2.cur_cycle_time;
}


//=================Dialog Color config==========================
int CSysData::GetDialogBkColor()
{
	int clr = RGB(235, 235, 220);
	clr = RGB(107, 201, 253);
	clr = RGB(242, 242, 242);
	clr = RGB(226, 237, 248);
	
	return clr;
}
int CSysData::GetStaticTextColor()
{
	int clr = RGB(255, 255, 255);
		clr = RGB(0, 0, 0);
	//	clr = RGB(53, 89, 101);
	return clr;
}
int CSysData::GetButtonBkColor()
{
	int clr = RGB(195, 177, 169);

	clr = RGB(128, 69, 125);

	clr = RGB(140, 240, 240);

	return clr;
}
int CSysData::GetButtonFocusBkColor()
{
	int clr = RGB(105, 182, 174);
	clr = RGB(28, 69, 125);

	clr = RGB(240, 240, 240);

	return clr;
}
int CSysData::GetCheckBkColor()
{
	int clr = RGB(63, 118, 7);
	clr = RGB(28, 69, 125);

	clr = RGB(240, 240, 240);

	return clr;
}
int CSysData::GetCheckFocusBkColor()
{
	int clr = RGB(116, 218, 14);
//	clr = RGB(18, 78, 36);

//	clr = RGB(240, 240, 240);

	return clr;
}
