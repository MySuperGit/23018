#include "stdafx.h"
#include <direct.h>
#include <math.h>
#include "progdata.h"

//char s_prog_path[30]=".\\product";
//char s_ProgMa[30]=".\\ParaMa";
static CString s_prog_path = GetAppFolder() + "product";
static CString s_ProgMa= GetAppFolder() + "ParaMa";

ProgInfo_Blk g_ProgInfo[PROG_TOTAL];


CProgData g_ProgDataBd(1); //固晶

int GetProgInfo(int prg_no, ProgInfo_Blk& ProgInfo,int sub_id)
{
	//外部调用（for循环）获取所有程式的信息
	if (prg_no < 0) return 0;

	ProgInfo.prg = prg_no;
	char file_name[255];
	FILE* pFile;

	sprintf(file_name, "%s\\%03d_%03d.prg", s_prog_path, prg_no,sub_id);
	pFile = fopen(file_name, "rb");
	if(!pFile)
	{
		return 0;	
	}
	int no = 0;
	fread(&no, sizeof(int), 1, pFile);
//	ASSERT(no==prg_no);



	int len = 0;
	fread(&len, sizeof(int), 1, pFile);
	if(len>0)
	{
		fread(ProgInfo.name, sizeof(char), len, pFile);
	}
	ProgInfo.name[len] = 0;
	fread(&ProgInfo.group_total, sizeof(int), 1, pFile);
	fread(&ProgInfo.pos_total, sizeof(int), 1, pFile);
	fclose(pFile);

	if (0){

		CFileFind ff;
		CTime time;
		CString stname;
		stname.Format(_T("s%\\%03d_%03d.prg"),s_prog_path,prg_no,sub_id);
		if(ff.FindFile(stname))
		{
			ff.GetLastWriteTime(time);
			CString str;
			str.Format(_T("%02d.%02d/%04d %02d:%02d:%02d"), 
				time.GetMonth(), time.GetDay(), time.GetYear(),
				time.GetHour(), time.GetMinute(), time.GetSecond());

			sprintf(ProgInfo.lasttime,"%s\n",str.GetBuffer(str.GetLength()));
				
		}
		ff.Close();

	}
	return 1;




}

void UpdateCurProcProgInfo()
{
//	return;

	ProgInfo_Blk& CurProcProgInfo = g_ProgInfo[g_SysData.GetCurProcProg()-1];
	CurProcProgInfo.group_total = g_ProgDataBd.GetGroupTotal();
	CurProcProgInfo.pos_total = g_ProgDataBd.GetPosTotal();
	if(strlen(g_ProgDataBd.GetName()))
		strcpy(CurProcProgInfo.name, g_ProgDataBd.GetName());
	else
		CurProcProgInfo.name[0] = 0;

}
///////////////////////////////////
CProgData::CProgData(int subid)
{
	m_nSubID = subid;
	m_iTTFd = 0;
	m_iCurFd = 0;
	m_sSubName = _T("固晶编程");
}
CProgData::~CProgData()
{
}

int CProgData::SetPrgID(int prgid)
{
	d_ParaBlk.no = prgid;
		return 0;
}

int CProgData::DeletFile(int prg)
{
	if (prg < 0) return 0;
	if (prg > PROG_TOTAL) return 0;

	char name[255];
	FILE* pFile=NULL;
	sprintf(name, "%s\\%03d_%03d.prg", s_prog_path, prg,m_nSubID);
	DeleteFile(name);
	return 1;
}


int CProgData::Load(int prg)
{
	flg_ResetProg=1;

	Empty();
	//ASSERT(prg>0 && prg<=PROG_TOTAL);

	if (prg < 0) return 0;

	char name[255];
	FILE* pFile;
	sprintf(name, "%s\\%03d_%03d.prg", s_prog_path, prg,m_nSubID);
	pFile = fopen(name, "rb");
	if(!pFile)
	{
		d_ParaBlk.no = prg;
		return 0;	
	}
	fread(&(d_ParaBlk.no), sizeof(int), 1, pFile);
	
	//ASSERT(d_ParaBlk.no==prg);

	Load(pFile);
	fclose(pFile);



	return 1;
}

int CProgData::Save()
{//=
//	g_EpxProgData.SaveParaEpx();

	if (GetPosTotal()<=0)
	{
		return -1;
	}

	char name[255];
	sprintf(name, "%s", s_prog_path);
	_mkdir(s_prog_path);// 先保证目录的存在

	FILE* pFile;
	sprintf(name, "%s\\%03d_%03d.prg", s_prog_path, d_ParaBlk.no,m_nSubID);
	pFile = fopen(name, "wb");
	if(!pFile)
		return 0;	
	Save(pFile);
	fflush(pFile);
	fclose(pFile);


	//===========================
	sprintf(name, "%s", s_ProgMa);
	_mkdir(s_ProgMa);
	sprintf(name, "%s\\ProgPar_%03d.dat", s_ProgMa,m_nSubID);
	pFile = fopen(name, "wb");
	if(!pFile)
		return 0;	
	fwrite(&d_ProgPara, sizeof(d_ProgPara), 1, pFile);

	fflush(pFile);
	fclose(pFile);


	return 1;
}

int CProgData::SaveParaDB()
{
	if (GetPosTotal()<=0)
	{
		return -1;
	}

	FILE* pFile;

	char name[255];
	sprintf(name, "%s", s_prog_path);
	_mkdir(s_prog_path);// 先保证目录的存在

	sprintf(name, "%s", s_ProgMa);
	_mkdir(s_ProgMa);
	sprintf(name, "%s\\ProgPar_%03d.dat", s_ProgMa,m_nSubID);
	pFile = fopen(name, "wb");
	if(!pFile)
		return 0;	
	fwrite(&d_ProgPara, sizeof(d_ProgPara), 1, pFile);

	fflush(pFile);
	fclose(pFile);

	return 1;
}

int CProgData::LoadParaDB()
{		
//	g_EpxProgData.LoadParaEpx();

	FILE* pFilepp;
	char name[255];
	sprintf(name, "%s\\ProgPar_%03d.dat", s_ProgMa,m_nSubID);
	pFilepp = fopen(name, "rb");
	if(!pFilepp)
		return 0;	
	fread(&d_ProgPara, sizeof(d_ProgPara), 1, pFilepp);
	fclose(pFilepp);

	return 1;	
}
int CProgData::Import(char* file_name)
{
	ASSERT(file_name);
	Empty();
	FILE* pFile;
	pFile = fopen(file_name, "rb");
	if(!pFile)
	{
		return 0;	
	}
	fseek(pFile, sizeof(int), SEEK_SET);//跳过第一个变量表示文件内的程式号
	Load(pFile);
	fclose(pFile);
	return 1;
}
int CProgData::Export(char* file_name)
{
	ASSERT(file_name);
	FILE* pFile;
	pFile = fopen(file_name, "wb");
	if(!pFile)
		return 0;	
	Save(pFile);

	fflush(pFile);
	fclose(pFile);
	return 1;
}
void CProgData::Empty()
{
	//int rt = ::AfxMessageBox("是否删除编程数据3，点击[是]清空数据，[否]返回",MB_YESNO);
	//if (rt!=IDYES)
	//{
	//	return;
	//}

	flg_ResetProg=1;

	d_ParaBlk.name[0] = 0;
	d_ParaBlk.base_x = 0;
	d_ParaBlk.base_y = 0;
	d_ParaBlk.base_angle = 0.0;
	d_PosVec.clear();
	d_GroupVec.clear();
	m_Pos[0].x = 0;
	m_Pos[0].y = 0;
	m_Pos[1].x = 0;
	m_Pos[1].y = 0;
	m_Pos[2].x = 0;
	m_Pos[2].y = 0;

	m_GrpPos[0].x = 0;
	m_GrpPos[0].y = 0;
	m_GrpPos[1].x = 0;
	m_GrpPos[1].y = 0;
	m_GrpPos[2].x = 0;
	m_GrpPos[2].y = 0;

	m_row = 0;
	m_col = 0;

	m_GrpRow = 0;
	m_GrpCol = 0;

	m_BdLight = 0;
	m_CalLight = 0;
	m_PkLight = 0;
	memset(d_MachProg.m_iVal,0,MAX_PROG_MACH*sizeof(int));
	memset(d_MachProg.m_fVal,0,MAX_PROG_MACH*sizeof(double));
}

void CProgData::EmptyGroup()
{

	int rt = ::AfxMessageBox("是否删除组群信息1，点击[是]清空数据，[否]返回",MB_YESNO);
	if (rt!=IDYES)
	{
		return;
	}
	d_GroupVec.clear();
}
void CProgData::EmptyPt()
{
	//int rt = ::AfxMessageBox("是否删除点位信息2，点击[是]清空数据，[否]返回",MB_YESNO);
	//if (rt!=IDYES)
	//{
	//	return;
	//}
	d_PosVec.clear();	
}

//set data
void CProgData::SetBaseAlg(int alg1_x, int alg1_y, int alg2_x, int alg2_y)//设置第一个组群的两个对点计算基准点
{
	d_ParaBlk.base_x = (alg1_x + alg2_x)/2;
	d_ParaBlk.base_y = (alg1_y + alg2_y)/2;
	d_ParaBlk.base_angle = atan2(alg2_y-alg1_y+0.0, alg2_x-alg1_x+0.0);
}
void CProgData::AddGroup(int alg1_x, int alg1_y)//增加组群到末尾，偏移值为输入参数和第一个组群的第一个对点的距离
{
	flg_ResetProg=1;

	if(GetGroupTotal()==0)
	{
		Group_Blk Grp;
		Grp.Alg1.x = alg1_x;
		Grp.Alg1.y = alg1_y;
		d_GroupVec.push_back(Grp);
		return;
	}
	int x, y, x2, y2;
	GetAlg1(1, x, y);
	GetAlg2(1, x2, y2);
	Group_Blk Grp;
	Grp.Alg1.x = alg1_x;
	Grp.Alg1.y = alg1_y;
	Grp.Alg2.x = alg1_x - x + x2; 
	Grp.Alg2.y = alg1_y - y + y2; 
	d_GroupVec.push_back(Grp);
}
void CProgData::AddGroup(int alg1_x, int alg1_y, int grp_st, int grp_ed)//增加组群到末尾
{
	ASSERT(grp_st<=grp_ed);
	ASSERT(grp_st>0 && grp_st<=GetGroupTotal());
	ASSERT(grp_ed>0 && grp_ed<=GetGroupTotal());

	AddGroup(alg1_x, alg1_y);
	int base_x, base_y;
	GetAlg1(grp_st, base_x, base_y);
	int x, y;
	for(int i=grp_st+1; i<=grp_ed; i++)
	{
		GetAlg1(i, x, y);
		AddGroup(alg1_x+x-base_x, alg1_y+y-base_y);
	}
}
void CProgData::AddGroup(int group, int alg1_x, int alg1_y)//在group后增加组群
{
	ASSERT(group>0 && group<=GetGroupTotal());

	CString strLog;
	strLog.Format(_T("在组群%d后增加组群"), group);
	g_Log.WriteDataLog(strLog);
	g_Log.LogShow(strLog);

	if(group == GetGroupTotal())
	{
		AddGroup(alg1_x, alg1_y);
		return;
	}
	int x, y, x2, y2;
	GetAlg1(1, x, y);
	GetAlg2(1, x2, y2);
	Group_Blk Grp;
	Grp.Alg1.x = alg1_x;
	Grp.Alg1.y = alg1_y;
	Grp.Alg2.x = alg1_x - x + x2; 
	Grp.Alg2.y = alg1_y - y + y2; 
	vector<Group_Blk>::iterator theit = d_GroupVec.begin() + group;	
	d_GroupVec.insert(theit, Grp);
}
void CProgData::DelGroup(int group)
{
	flg_ResetProg=1;

	ASSERT(group>0 && group<=GetGroupTotal());
	vector<Group_Blk>::iterator theit = d_GroupVec.begin() + group - 1;	
	d_GroupVec.erase(theit);
}

void CProgData::SetAlg1(int group, int x, int y)//修改组群对点
{
	ASSERT(group>0 && group<=GetGroupTotal());
	d_GroupVec[group-1].Alg1.x = x;
	d_GroupVec[group-1].Alg1.y = y;
}

void CProgData::SetAlg2(int group, int x, int y)
{
	ASSERT(group>0 && group<=GetGroupTotal());
	d_GroupVec[group-1].Alg2.x = x;
	d_GroupVec[group-1].Alg2.y = y;
}

void CProgData::SetBaseAlg1(int x, int y)//修改对点
{
	CString strLog;
	strLog.Format(_T("设置对点1位置：（%d,%d）-->（%d,%d）"), m_WHStripAlgChk.Alg1.x,m_WHStripAlgChk.Alg1.y,x,y);
	g_Log.WriteDataLog(strLog);
	g_Log.LogShow(strLog);

	m_WHStripAlgChk.Alg1.x = x;
	m_WHStripAlgChk.Alg1.y = y;
}

void CProgData::SetBaseAlg2(int x, int y)
{
	CString strLog;
	strLog.Format(_T("设置对点2位置：（%d,%d）-->（%d,%d）"), m_WHStripAlgChk.Alg2.x,m_WHStripAlgChk.Alg2.y,x,y);
	g_Log.WriteDataLog(strLog);
	g_Log.LogShow(strLog);

	m_WHStripAlgChk.Alg2.x = x;
	m_WHStripAlgChk.Alg2.y = y;
}

void CProgData::Set_Modify_GrpAlg1(int group, int x, int y)//修改组群点
{
	ASSERT(group>0 && group<=GetGroupTotal());

	CString strLog;
	strLog.Format(_T("修改组群第%d组"), group);
	g_Log.WriteDataLog(strLog);
	g_Log.LogShow(strLog);
	
	int oldx = d_GroupVec[group-1].Alg1.x;
	int oldy = d_GroupVec[group-1].Alg1.y;
	int dd_x = oldx-x;
	int dd_y = oldy-y;

	d_GroupVec[group-1].Alg1.x = x;
	d_GroupVec[group-1].Alg1.y = y;
	
	d_GroupVec[group-1].Alg2.x = d_GroupVec[group-1].Alg2.x+dd_x;
	d_GroupVec[group-1].Alg2.y = d_GroupVec[group-1].Alg2.x+dd_y;


}

void CProgData::AddPos(int x, int y)
{
	flg_ResetProg=1;

	Pos_Blk Pos;
	Pos.x = x;
	Pos.y = y;
	d_PosVec.push_back(Pos);

	/*CString strLog;
	strLog.Format(_T("增加贴点：（%d,%d）"), x,y);
	g_Log.WriteDataLog(strLog);
	g_Log.LogShow(strLog);*/
}
void CProgData::AddPos(int x, int y, int pos_st, int pos_ed)
{
	ASSERT(pos_st<=pos_ed);
	ASSERT(pos_st>0 && pos_st<=GetPosTotal());
	ASSERT(pos_ed>0 && pos_ed<=GetPosTotal());

	AddPos(x, y);
	int base_x, base_y;
	GetPos(1, pos_st, base_x, base_y);
	int pos_x, pos_y;
	for(int i=pos_st+1; i<=pos_ed; i++)
	{
		GetPos(1, i, pos_x, pos_y);
		AddPos(x+pos_x-base_x, y+pos_y-base_y);
	}
}
void CProgData::AddPos(int pos, int x, int y)//在pos后增加固晶点
{
	flg_ResetProg=1;

	ASSERT(pos>0 && pos<=GetPosTotal());
	Pos_Blk Pos;
	Pos.x = x;
	Pos.y = y;
	if(pos==GetPosTotal())
	{
		d_PosVec.push_back(Pos);
	}
	else
	{
		vector<Pos_Blk>::iterator theit = d_PosVec.begin()+pos;
		d_PosVec.insert(theit, Pos);
	}

	CString strLog;
	strLog.Format(_T("增加贴点：（%d,%d）"), x,y);
	g_Log.WriteDataLog(strLog);
	g_Log.LogShow(strLog);
}
void CProgData::DelPos(int pos)
{
	flg_ResetProg=1;

	ASSERT(pos>0 && pos<=GetPosTotal());
	vector<Pos_Blk>::iterator theit = d_PosVec.begin()+pos-1;
	d_PosVec.erase(theit);

	CString strLog;
	strLog.Format(_T("删除第%d个贴点"), pos);
	g_Log.WriteDataLog(strLog);
	g_Log.LogShow(strLog);
	
}
void CProgData::SetPos(int pos, int x, int y)//修改固晶点
{
	flg_ResetProg=1;

	ASSERT(pos>0 && pos<=GetPosTotal());

	CString strLog;
	strLog.Format(_T("修改编程点位%d：（%d,%d）-->（%d,%d）"), pos,d_PosVec[pos-1].x,d_PosVec[pos-1].y,x,y);
	g_Log.WriteDataLog(strLog);
	g_Log.LogShow(strLog);
	d_PosVec[pos-1].x = x;
	d_PosVec[pos-1].y = y;
}
void CProgData::SetRefAlg(int group, int alg1_x, int alg1_y, int alg2_x, int alg2_y)//在对点找完后设置新找到的对点
{
	if (group<=0 || group > GetGroupTotal())
	{
		AfxMessageBox("编程数据错误");	
		return;
	}
	d_GroupVec[group-1].ref_x = (alg1_x + alg2_x)/2;
	d_GroupVec[group-1].ref_y = (alg1_y + alg2_y)/2;
	d_GroupVec[group-1].ref_angle = atan2(alg2_y-alg1_y+0.0, alg2_x-alg1_x+0.0);
}
//get data
int CProgData::GetGroupTotal()
{
	return d_GroupVec.size();
}
int CProgData::GetPosTotal()
{
	return d_PosVec.size();
}

void CProgData::GetAlg1(int group, int& outx, int& outy)//base 1
{
	if (group<=0)
	{
		AfxMessageBox("编程数据错误");	
		return;
	}

	if (group>GetGroupTotal())
	{
		group = GetGroupTotal();
	}

	if (group<=0)
	{
		outx=0;
		outy=0;
		return ;
	}


	outx = d_GroupVec[group-1].Alg1.x;
	outy = d_GroupVec[group-1].Alg1.y;
}
void CProgData::GetAlg2(int group, int& outx, int& outy)	
{
	if (group<=0)
	{
		AfxMessageBox("编程数据错误");	
		return;
	}
	
	if (group>GetGroupTotal())
	{
		group = GetGroupTotal();
	}

	if (group<=0)
	{
		outx=0;
		outy=0;
		return ;
	}

	outx = d_GroupVec[group-1].Alg2.x;
	outy = d_GroupVec[group-1].Alg2.y;
}

void CProgData::GetBaseAlg1(int& outx, int& outy)//base 1
{
	outx = m_WHStripAlgChk.Alg1.x;
	outy = m_WHStripAlgChk.Alg1.y;
}

void CProgData::GetBaseAlg2(int& outx, int& outy)	
{
	outx = m_WHStripAlgChk.Alg2.x;
	outy = m_WHStripAlgChk.Alg2.y;
}

void CProgData::GetPos(int group, int pt, int& out_x, int& out_y)//base 1
{
	if (group<=0 || group > GetGroupTotal())
	{
		AfxMessageBox("编程数据错误");	
		return;
	}


	if(pt<=0 || pt>GetPosTotal())
	{
		AfxMessageBox("编程点位错误");
		return;
	}

	out_x=0;
	out_y=0;
	
	if (GetPosTotal() <= 0)
	{
		return;
	}

	if (pt>GetPosTotal())
	{
		pt = GetPosTotal();
	}


	if (pt<=0)
	{
		return;
	}

	int x = d_PosVec[pt-1].x;
	int y = d_PosVec[pt-1].y;
	if(group==1)
	{
		out_x = x;
		out_y = y;
	}
	else
	{
		int x1, y1, x2, y2;
		GetAlg1(1, x1, y1);
		GetAlg1(group, x2, y2);
		out_x = x + x2- x1;
		out_y = y + y2 - y1;
	}
}



void CProgData::GetTempPos()
{	
	d_AllPosVec_temp.clear();
	
	
	int x=0;
	int y=0;
	Pos_Blk Pos;
	
	for (int bt=1; bt <= g_ProgDataBd.GetPosTotal(); bt++)
	{				
		GetAdjPos(1, bt, x, y);
		
		Pos.x = x;
		Pos.y = y;
		
		d_AllPosVec_temp.push_back(Pos);
	}
	
	
}

void CProgData::SetTempPos(int x, int y)
{	
	d_AllPosVec_temp.clear();	
	
	int a=0;
	int b=0;
	Pos_Blk Pos;
	
	for (int bt=1; bt <= g_ProgDataBd.GetPosTotal(); bt++)
	{				
		GetPos(1, bt, a, b);
		int x1=a+x;
		int y1=b+y;
		
		Pos.x = x1;
		Pos.y = y1;
		
		d_AllPosVec_temp.push_back(Pos);
	}
	
	d_PosVec.clear();
	
	d_PosVec = d_AllPosVec_temp;
	
	g_ProgDataBd.Save();
	
}


void CProgData::GetRectPoint( int num,Pos_Blk& pos )
{
	pos.x = 0;
	pos.y = 0;
	if (num < 0 || num > 3)
	{
		return;
	}
	switch (num)
	{
	case 0:
		pos.x = m_Pos[0].x;
		pos.y = m_Pos[0].y;
		break;
	case 1:
		pos.x = m_Pos[1].x;
		pos.y = m_Pos[1].y;
		break;
	case 2:
		pos.x = m_Pos[2].x;
		pos.y = m_Pos[2].y;
		break;
	}
	return;
}

void CProgData::SetRectPoint( int num,Pos_Blk pos )
{
	if (num < 0 || num > 3)
	{
		return;
	}
	CString strLog;
	strLog.Format(_T("设置点%d：（%d,%d）-->（%d,%d）"), num+1,m_Pos[num].x,m_Pos[num].y,pos.x,pos.y);
	g_Log.WriteDataLog(strLog);
	g_Log.LogShow(strLog);

	m_Pos[num].x = pos.x;
	m_Pos[num].y = pos.y;
}

int CProgData::GetMachPara( int id )
{
	if (id < 0 || id >= MAX_PROG_MACH)
	{
		return -1;
	}
	return d_MachProg.m_iVal[id];
}

int CProgData::SetMachPara( int id,int val )
{
	if (id < 0 || id >= MAX_PROG_MACH)
	{
		return -1;
	}
	d_MachProg.m_iVal[id] = val;
	return 0;
}

int CProgData::GetMachParaF( int id,double &val )
{
	if (id < 0 || id >= MAX_PROG_MACH)
	{
		val = -1.0;
		return -1;
	}
    val = d_MachProg.m_fVal[id];
	 return 0;
}

int CProgData::SetMachParaF( int id,double val )
{
	if (id < 0 || id >= MAX_PROG_MACH)
	{
		val = -1.0;
		return -1;
	}
	d_MachProg.m_fVal[id] = val ;
	return 0;
}

void CProgData::ResetProgPoint()
{
	d_PosVec.clear();
	
	d_PosVec = d_AllPosVec_temp;
	
	g_ProgDataBd.Save();
	
}

///---
void CProgData::GetAdjPos(int group, int pt, int& out_x, int& out_y)//base 1
{
	if (group<=0 || group > GetGroupTotal())
	{
		AfxMessageBox("编程数据错误");	
		return;
	}


	if(pt<=0 || pt>GetPosTotal())
	{
		AfxMessageBox("编程点位错误");
		return;
	}

	GetPos( group, pt, out_x, out_y);
	return;
	out_x=0;
	out_y=0;


	if (GetPosTotal() <= 0)
	{
		return;
	}

	int x = d_PosVec[pt-1].x;
	int y = d_PosVec[pt-1].y;
	//计算固晶点与基点的极坐标关系
	double distx ,disty;
	distx = x-d_ParaBlk.base_x;
	disty = y-d_ParaBlk.base_y;
	double r = sqrt(distx*distx + disty*disty);
	double a = atan2(disty, distx);

	double a1=d_GroupVec[group-1].ref_angle;
	double a2=d_ParaBlk.base_angle;

	//求得新对点后的固晶点坐标
	a += d_GroupVec[group-1].ref_angle-d_ParaBlk.base_angle;
	out_x = int(r*cos(a)) + d_GroupVec[group-1].ref_x;
	out_y = int(r*sin(a)) + d_GroupVec[group-1].ref_y;

	//out_x = int(r*cos(a)) + d_GroupVec[group-1].ref_x - d_ParaBlk.base_x;
    //out_y = int(r*sin(a)) + d_GroupVec[group-1].ref_y - d_ParaBlk.base_y;
}

//other data
int CProgData::GetProgNo()
{
	return d_ParaBlk.no; 
}
void CProgData::SetName(char* name)
{
	ASSERT(name);
	strcpy(d_ParaBlk.name, name);
}
char* CProgData::GetName()
{
	return d_ParaBlk.name;
}
int CProgData::GetPara(int para_id) const
{
	switch(para_id)
	{
	case PROG_RUN_MODE:
		return d_ProgPara.run_mode;
	case PROG_CHECK_DIE:
		return d_ProgPara.check_die;

	case PROG_STREET_X:
		return d_ProgPara.streetx;
	case PROG_STREET_Y:
		return d_ProgPara.streety;	
	case PROG_SRH_DIE_MODE:
		return d_ProgPara.srh_die_mode;
	case PROG_SRH_DIE_DIR:
		return d_ProgPara.srh_die_dir;
	case PROG_SRH_DIE_MISS_CNT:
		return d_ProgPara.srh_die_miss_cnt;
	case PROG_DIE_ACCEPT:
		return d_ProgPara.die_accept;
	case PROG_DIE_GRAB_TIME:
		return d_ProgPara.die_grab_time;
	case PROG_EPXDIE_OFFSET:
		return d_ProgPara.curpos_x;
	case PROG_DB_ANGLE:
		return d_ProgPara.curpos_y;

	case PROG_ALG_MODE:
		return d_ProgPara.alg_mode;
	case PROG_ADJ_MODE:
		return d_ProgPara.adj_mode;
	case PROG_ALG_PR_DELAY:
		return d_ProgPara.alg_pr_dly;
	case PROG_ALG_ACCEPT:
		return d_ProgPara.alg_accept;
	case PROG_PT_PR_DELAY:
		return d_ProgPara.pt_pr_dly;
	case PROG_PT_ACCEPT:
		return d_ProgPara.pt_accept;
	case PROG_DB_SHOW_DELAY:
		return d_ProgPara.db_show_dly;

	case PROG_POS_DBZ_PICK:
		return d_ProgPara.pos_dbz_pick;
	case PROG_POS_DBZ_PICK_RESET:
		return d_ProgPara.pos_dbz_pick_reset;
	case PROG_POS_DBZ_BOND:
		return d_ProgPara.pos_dbz_bond;
	case PROG_POS_DBZ_BOND_RESET:
		return d_ProgPara.pos_dbz_bond_reset;

	case PROG_POS_EJP_PICK:
		return d_ProgPara.pos_ejp_pick;
	case PROG_POS_EJP_PICK_RESET:
		return d_ProgPara.pos_ejp_reset;

	case PROG_POS_EPZ_PICK:
		return d_ProgPara.pos_epz_pick;
	case PROG_POS_EPZ_PICK_RESET:
		return d_ProgPara.pos_epz_pick_reset;

	case PROG_LIGHT_WH_RING2:
		return d_ProgPara.pos_epz_pick_rupture;

	case PROG_POS_EPZ_BOND_RUPTURE:
		return d_ProgPara.pos_epz_bond_rupture;


	case PROG_VEL_EPZ_RUPTURE:
		return d_ProgPara.vel_epz_rupture;
		
	case PROG_POS_EPZ_BOND:
		return d_ProgPara.pos_epz_bond;
	case PROG_POS_EPZ_BOND_RESET:
		return d_ProgPara.pos_epz_bond_reset;

	case PROG_POS_EPZ_PREBOND:
		return d_ProgPara.pos_epz_prebond;

	case PROG_DELAY_DB_PICK:
		return d_ProgPara.delay_db_pick;
	case PROG_DELAY_DB_BOND:
		return d_ProgPara.delay_db_bond;

	case PROG_DELAY_DB_PREPICK:
		return d_ProgPara.delay_db_prepick;
	case PROG_DELAY_DB_PREBOND:
		return d_ProgPara.delay_db_prebond;

	case PROG_DELAY_EP_PICK:
		return d_ProgPara.delay_ep_pick;

	case PROG_DELAY_EP_LEAVE:
		return d_ProgPara.delay_ep_leave;
	case PROG_DELAY_COLLETPUTDOWN:
		return d_ProgPara.vel_mode;
	case PROG_DELAY_EP_BOND:
		return d_ProgPara.delay_ep_bond;
	case PROG_DELAY_CLAMPSWITCH:
		return d_ProgPara.delay_epx_timeout;

	case PROG_LIGHT_WH_RING:
		return d_ProgPara.light_wh_ring;
	case PROG_LIGHT_WH_COAX:
		{
			int val= d_PrPt.AllPrPara.PrPara.coax;
			//d_ProgPara.light_wh_coax =val;
			//d_ProgPara.light_wh_coax;
			return val;
		}
	case PROG_LIGHT_WF_RING:
		{
			return  d_ProgPara.light_wf_ring;
		}
	case PROG_LIGHT_WF_COAX:
		return d_ProgPara.light_wf_coax;

	default:
		ASSERT(FALSE);
	}
	return 0;
}
void CProgData::SetPara(int para_id, int para_val)
{
	switch(para_id)
	{
	case PROG_RUN_MODE:
		d_ProgPara.run_mode = para_val;
		break;
	case PROG_CHECK_DIE:
		d_ProgPara.check_die = para_val;
		break;

	case PROG_STREET_X:
		d_ProgPara.streetx = para_val;
		break;
	case PROG_STREET_Y:
		d_ProgPara.streety = para_val;	
		break;
	case PROG_SRH_DIE_MODE:
		d_ProgPara.srh_die_mode = para_val;
		break;
	case PROG_SRH_DIE_DIR:
		d_ProgPara.srh_die_dir = para_val;
		break;
	case PROG_SRH_DIE_MISS_CNT:
		d_ProgPara.srh_die_miss_cnt = para_val;
		break;
	case PROG_DIE_ACCEPT:
		d_ProgPara.die_accept = para_val;
		break;
	case PROG_DIE_GRAB_TIME:
		d_ProgPara.die_grab_time = para_val;
		break;
	case PROG_EPXDIE_OFFSET:
		d_ProgPara.curpos_x = para_val;
		break;
	case PROG_DB_ANGLE:
		d_ProgPara.curpos_y = para_val;
		break;

	case PROG_ALG_MODE:
		d_ProgPara.alg_mode = para_val;
		break;
	case PROG_ADJ_MODE:
		d_ProgPara.adj_mode = para_val;
		break;
	case PROG_ALG_PR_DELAY:
		d_ProgPara.alg_pr_dly = para_val;
		break;
	case PROG_ALG_ACCEPT:
		d_ProgPara.alg_accept = para_val;
		break;
	case PROG_PT_PR_DELAY:
		d_ProgPara.pt_pr_dly = para_val;
		break;
	case PROG_PT_ACCEPT:
		d_ProgPara.pt_accept = para_val;
		break;
	case PROG_DB_SHOW_DELAY:
		d_ProgPara.db_show_dly = para_val;
		break;

	case PROG_POS_DBZ_PICK:
		d_ProgPara.pos_dbz_pick = para_val;
		break;
	case PROG_POS_DBZ_PICK_RESET:
		d_ProgPara.pos_dbz_pick_reset = para_val;
		break;
	case PROG_POS_DBZ_BOND:
		d_ProgPara.pos_dbz_bond = para_val;
		break;
	case PROG_POS_DBZ_BOND_RESET:
		d_ProgPara.pos_dbz_bond_reset = para_val;
		break;

	case PROG_POS_EJP_PICK:
		d_ProgPara.pos_ejp_pick = para_val;
		break;
	case PROG_POS_EJP_PICK_RESET:
		d_ProgPara.pos_ejp_reset = para_val;
		break;

	case PROG_POS_EPZ_PICK:
		d_ProgPara.pos_epz_pick = para_val;
		break;
	case PROG_POS_EPZ_PICK_RESET:
		d_ProgPara.pos_epz_pick_reset = para_val;
		break;

	case PROG_LIGHT_WH_RING2:
		d_ProgPara.pos_epz_pick_rupture  = para_val;
		break;		

	case PROG_POS_EPZ_BOND_RUPTURE:
		d_ProgPara.pos_epz_bond_rupture = para_val;
		break;

	case PROG_VEL_EPZ_RUPTURE:
		d_ProgPara.vel_epz_rupture  = para_val;
		break;

	case PROG_POS_EPZ_BOND:
		d_ProgPara.pos_epz_bond = para_val;
		break;

	case PROG_POS_EPZ_PREBOND:
		d_ProgPara.pos_epz_prebond = para_val;
		break;

	case PROG_POS_EPZ_BOND_RESET:
		d_ProgPara.pos_epz_bond_reset = para_val;
		break;

	case PROG_DELAY_DB_PICK:
		d_ProgPara.delay_db_pick = para_val;
		break;

	case PROG_DELAY_DB_PREPICK:
		d_ProgPara.delay_db_prepick = para_val;
		break;

	case PROG_DELAY_DB_BOND:
		d_ProgPara.delay_db_bond = para_val;
		break;

	case PROG_DELAY_DB_PREBOND:
		d_ProgPara.delay_db_prebond = para_val;
		break;

	case PROG_DELAY_EP_PICK:
		d_ProgPara.delay_ep_pick = para_val;
		break;
	case PROG_DELAY_EP_LEAVE:
		d_ProgPara.delay_ep_leave = para_val;
		break;
	case PROG_DELAY_COLLETPUTDOWN:
		d_ProgPara.vel_mode = para_val;
		break;
	case PROG_DELAY_EP_BOND:
		d_ProgPara.delay_ep_bond = para_val;
		break;
	case PROG_DELAY_CLAMPSWITCH:
		d_ProgPara.delay_epx_timeout = para_val;
		break;

	case PROG_LIGHT_WH_RING:
		d_ProgPara.light_wh_ring = para_val;
		break;
	case PROG_LIGHT_WH_COAX:
		d_ProgPara.light_wh_coax = para_val;
		break;
	case PROG_LIGHT_WF_RING:
		d_ProgPara.light_wf_ring = para_val;
		break;
	case PROG_LIGHT_WF_COAX:
		d_ProgPara.light_wf_coax = para_val;
		break;
	default:
		ASSERT(FALSE);
	}
}
//////////////////////////////////////////////////////////
int CProgData::Load(FILE* pFile)
{	
	//先读取para，再读取point，最后image
	int len = 0;
	fread(&len, sizeof(int), 1, pFile);
	if(len>0)
	{
		char name[255];
		fread(name, sizeof(char), len, pFile);
		name[len] = 0;
		SetName(name);
	}
	int grp_total = 0;
	fread(&grp_total, sizeof(int), 1, pFile);
	int pos_total = 0;
	fread(&pos_total, sizeof(int), 1, pFile);
	
	fread(&(d_ParaBlk.base_x), sizeof(int), 1, pFile);
	fread(&(d_ParaBlk.base_y), sizeof(int), 1, pFile);
	fread(&(d_ParaBlk.base_angle), sizeof(double), 1, pFile);
//	fread(d_ParaBlk.AllProgPara.all_para, sizeof(d_ParaBlk.AllProgPara.all_para), 1, pFile);

	int val[4];
	int i = 0;
	for(i=0; i<grp_total; i++)
	{
		fread(val, sizeof(int), 4, pFile);
		Group_Blk Grp;
		Grp.Alg1.x = val[0];
		Grp.Alg1.y = val[1];
		Grp.Alg2.x = val[2];
		Grp.Alg2.y = val[3];
		d_GroupVec.push_back(Grp);
	}
	for(i=0; i<pos_total; i++)
	{
		fread(val, sizeof(int), 2, pFile);
		Pos_Blk Pos;
		Pos.x = val[0];
		Pos.y = val[1];
		d_PosVec.push_back(Pos);
	}
	fread(&m_row,sizeof(int),1,pFile);
	fread(&m_col,sizeof(int),1,pFile);
	for (i=0;i<3;i++)
	{
		fread(&m_Pos[i],sizeof(Pos_Blk),1,pFile);
	}
	fread(&m_BdLight,sizeof(int),1,pFile);
	fread(&m_CalLight,sizeof(int),1,pFile);
	fread(&m_PkLight,sizeof(int),1,pFile);

	if (m_nSubID == 1)
	{
		fread(&d_MachProg.m_iVal,sizeof(int),MAX_PROG_MACH,pFile);
		fread(&d_MachProg.m_fVal,sizeof(double),MAX_PROG_MACH,pFile);
	}
	fread(&m_iTTFd,sizeof(int),1,pFile);
	fread(&m_iCurFd,sizeof(int),1,pFile);
	fread(&m_dFdX,sizeof(double),100,pFile);
	fread(&m_dFdY,sizeof(double),100,pFile);
	fread(&m_bEnableFd,sizeof(int),1,pFile);

	fread(&m_GrpRow,sizeof(int),1,pFile);
	fread(&m_GrpCol,sizeof(int),1,pFile);
	for (i=0;i<3;i++)
	{
		fread(&m_GrpPos[i],sizeof(Pos_Blk),1,pFile);
	}
	fread(&m_iBdOffX, sizeof(int), 1, pFile);
	fread(&m_iBdOffY, sizeof(int), 1, pFile);

	fread(val, sizeof(int), 4, pFile);
	m_WHStripAlgChk.Alg1.x = val[0];
	m_WHStripAlgChk.Alg1.y = val[1];
	m_WHStripAlgChk.Alg2.x = val[2];
	m_WHStripAlgChk.Alg2.y = val[3];
	/*
	int img_len = 0;
	fread(d_PrWf.AllPrPara.all_para, sizeof(d_PrWf.AllPrPara.all_para), 1, pFile);
	if(d_PrWf.AllPrPara.PrPara.valid)//wf img
	{
		img_len = d_PrWf.AllPrPara.PrPara.w * d_PrWf.AllPrPara.PrPara.h;
		ASSERT(img_len>25);
		fread(d_PrWf.pimage, sizeof(unsigned char), img_len, pFile);
	}

	fread(d_PrPt.AllPrPara.all_para, sizeof(d_PrPt.AllPrPara.all_para), 1, pFile);
	if(d_PrPt.AllPrPara.PrPara.valid)//pt img
	{
		img_len = d_PrPt.AllPrPara.PrPara.w * d_PrPt.AllPrPara.PrPara.h;
		ASSERT(img_len>25);
		fread(d_PrPt.pimage, sizeof(unsigned char), img_len, pFile);
	}

	fread(d_PrAlg1.AllPrPara.all_para, sizeof(d_PrAlg1.AllPrPara.all_para), 1, pFile);
	if(d_PrAlg1.AllPrPara.PrPara.valid)//alg1 img
	{
		img_len = d_PrAlg1.AllPrPara.PrPara.w * d_PrAlg1.AllPrPara.PrPara.h;
		ASSERT(img_len>25);
		fread(d_PrAlg1.pimage, sizeof(unsigned char), img_len, pFile);
	}

	fread(d_PrAlg2.AllPrPara.all_para, sizeof(d_PrAlg2.AllPrPara.all_para), 1, pFile);
	if(d_PrAlg2.AllPrPara.PrPara.valid)//alg2 img
	{
		img_len = d_PrAlg2.AllPrPara.PrPara.w * d_PrAlg2.AllPrPara.PrPara.h;
		ASSERT(img_len>25);
		fread(d_PrAlg2.pimage, sizeof(unsigned char), img_len, pFile);
	}*/

	return 1;
}

int CProgData::Save(FILE* pFile)
{
	//先存para，再存point，最后存img
	fwrite(&(d_ParaBlk.no), sizeof(int), 1, pFile);
	int len = strlen(GetName());
	fwrite(&len, sizeof(int), 1, pFile);
	if(len>0)
		fwrite(GetName(), sizeof(char), len, pFile);
	int grp_total = GetGroupTotal();
	fwrite(&grp_total, sizeof(int), 1, pFile);//该信息是为了程式选择时显示基本信息
	int pos_total = GetPosTotal();
	fwrite(&pos_total, sizeof(int), 1, pFile);
	
	fwrite(&(d_ParaBlk.base_x), sizeof(int), 1, pFile);
	fwrite(&(d_ParaBlk.base_y), sizeof(int), 1, pFile);
	fwrite(&(d_ParaBlk.base_angle), sizeof(double), 1, pFile);
//	fwrite(d_ParaBlk.AllProgPara.all_para, sizeof(d_ParaBlk.AllProgPara.all_para), 1, pFile);

	int val[4];
	int i=0;
	for(i=0; i<grp_total; i++)
	{
		val[0] = d_GroupVec[i].Alg1.x;
		val[1] = d_GroupVec[i].Alg1.y;
		val[2] = d_GroupVec[i].Alg2.x;
		val[3] = d_GroupVec[i].Alg2.y;
		fwrite(val, sizeof(int), 4, pFile);
	}
	for(i=0; i<pos_total; i++)
	{
		val[0] = d_PosVec[i].x;
		val[1] = d_PosVec[i].y;
		fwrite(val, sizeof(int), 2, pFile);
	}
	//row,col,三点
	fwrite(&m_row,sizeof(int),1,pFile);
	fwrite(&m_col,sizeof(int),1,pFile);
	for (i=0;i<3;i++)
	{
		fwrite(&m_Pos[i],sizeof(Pos_Blk),1,pFile);
	}

	fwrite(&m_BdLight,sizeof(int),1,pFile);
	fwrite(&m_CalLight,sizeof(int),1,pFile);
	fwrite(&m_PkLight,sizeof(int),1,pFile);

	if (m_nSubID == 1)
	{
		fwrite(&d_MachProg.m_iVal,sizeof(int),MAX_PROG_MACH,pFile);
		fwrite(&d_MachProg.m_fVal,sizeof(double),MAX_PROG_MACH,pFile);
	}

	fwrite(&m_iTTFd,sizeof(int),1,pFile);
	fwrite(&m_iCurFd,sizeof(int),1,pFile);
	fwrite(&m_dFdX,sizeof(double),100,pFile);
	fwrite(&m_dFdY,sizeof(double),100,pFile);
	fwrite(&m_bEnableFd,sizeof(int),1,pFile);

	fwrite(&m_GrpRow,sizeof(int),1,pFile);
	fwrite(&m_GrpCol,sizeof(int),1,pFile);
	for (i=0;i<3;i++)
	{
		fwrite(&m_GrpPos[i],sizeof(Pos_Blk),1,pFile);
	}
	fwrite(&m_iBdOffX, sizeof(int), 1, pFile);
	fwrite(&m_iBdOffY, sizeof(int), 1, pFile);

	val[0] = m_WHStripAlgChk.Alg1.x;
	val[1] = m_WHStripAlgChk.Alg1.y;
	val[2] = m_WHStripAlgChk.Alg2.x;
	val[3] = m_WHStripAlgChk.Alg2.y;
	fwrite(val, sizeof(int), 4, pFile);
/*
	int img_len = 0;
	fwrite(d_PrWf.AllPrPara.all_para, sizeof(d_PrWf.AllPrPara.all_para), 1, pFile);
	if(d_PrWf.AllPrPara.PrPara.valid)//wf img
	{
		img_len = d_PrWf.AllPrPara.PrPara.w * d_PrWf.AllPrPara.PrPara.h;
		ASSERT(img_len>25);
		fwrite(d_PrWf.pimage, sizeof(unsigned char), img_len, pFile);
	}

	fwrite(d_PrPt.AllPrPara.all_para, sizeof(d_PrPt.AllPrPara.all_para), 1, pFile);
	if(d_PrPt.AllPrPara.PrPara.valid)//pt img
	{
		img_len = d_PrPt.AllPrPara.PrPara.w * d_PrPt.AllPrPara.PrPara.h;
		ASSERT(img_len>25);
		fwrite(d_PrPt.pimage, sizeof(unsigned char), img_len, pFile);
	}

	fwrite(d_PrAlg1.AllPrPara.all_para, sizeof(d_PrAlg1.AllPrPara.all_para), 1, pFile);
	if(d_PrAlg1.AllPrPara.PrPara.valid)//alg1 img
	{
		img_len = d_PrAlg1.AllPrPara.PrPara.w * d_PrAlg1.AllPrPara.PrPara.h;
		ASSERT(img_len>25);
		fwrite(d_PrAlg1.pimage, sizeof(unsigned char), img_len, pFile);
	}

	fwrite(d_PrAlg2.AllPrPara.all_para, sizeof(d_PrAlg2.AllPrPara.all_para), 1, pFile);
	if(d_PrAlg2.AllPrPara.PrPara.valid)//alg2 img
	{
		img_len = d_PrAlg2.AllPrPara.PrPara.w * d_PrAlg2.AllPrPara.PrPara.h;
		ASSERT(img_len>25);
		fwrite(d_PrAlg2.pimage, sizeof(unsigned char), img_len, pFile);
	}*/

	return 1;
}

void CProgData::GetFdPos(int idx,double &x,double &y)
{
	//ASSERT(idx>0 && idx<= 100);
	if (idx <= 0 || idx > 100)
	{
		x = 0.0;
		y = 0.0;
		return;
	}
	x = m_dFdX[idx-1];
	y = m_dFdY[idx-1];
}
void CProgData::SetFdPos(int idx,double x,double y)
{
	//ASSERT(idx>0 && idx<= 100);
	if (idx <= 0 || idx > 100)
	{
		return;
	}
	m_dFdX[idx-1] = x;
	m_dFdY[idx-1] = y;
}

void CProgData::AddFdPos(double x,double y)
{
	m_iTTFd++;
	m_iCurFd++;
	ASSERT(m_iTTFd>0 && m_iTTFd<= 100);
	SetFdPos(m_iCurFd,x,y);	
}

void CProgData::ChangeFdPos(int idx,double x,double y)
{
	SetFdPos(idx,x,y);
}

void CProgData::DelFdPos()//删除最后一个
{
	SetFdPos(m_iTTFd,0.0,0.0);
	m_iTTFd--;
	if (m_iCurFd > m_iTTFd)
	{
		m_iCurFd=m_iTTFd;
	}
}


void CProgData::SetCurFd(int idx)
{
	m_iCurFd = idx;
}

void CProgData::SetEnableFd(BOOL bFd)
{
	CString strLog;
	strLog.Format(_T("分点开关：%d-->%d"), m_bEnableFd, bFd);
	g_Log.WriteDataLog(strLog);
	g_Log.LogShow(strLog);
	m_bEnableFd = bFd;
}

void CProgData::SetRow(int row)
{
	if (m_row != row)
	{
		CString strLog;
		strLog.Format(_T("阵列加工行数：%d-->%d"), m_row, row);
		g_Log.WriteDataLog(strLog);
		g_Log.LogShow(strLog);
		m_row = row;
	}
}

void CProgData::SetCol(int col)
{
	if (m_col != col)
	{
		CString strLog;
		strLog.Format(_T("阵列加工列数：%d-->%d"), m_col, col);
		g_Log.WriteDataLog(strLog);
		g_Log.LogShow(strLog);
		m_col = col;
	}
}


void CProgData::SetGrpRow(int row)
{
	if (m_GrpRow != row)
	{
		CString strLog;
		strLog.Format(_T("组群矩阵行数：%d-->%d"), m_GrpRow, row);
		g_Log.WriteDataLog(strLog);
		g_Log.LogShow(strLog);
		m_GrpRow = row;
	}
}

void CProgData::SetGrpCol(int col)
{
	if (m_GrpCol != col)
	{
		CString strLog;
		strLog.Format(_T("组群矩阵列数：%d-->%d"), m_GrpCol, col);
		g_Log.WriteDataLog(strLog);
		g_Log.LogShow(strLog);
		m_GrpCol = col;
	}
}

void CProgData::SetGrpRectPoint(int num, int x, int y)
{
	if (num < 0 || num > 3)
	{
		return;
	}
	CString strLog;
	strLog.Format(_T("组群矩阵-设置点%d：（%d,%d）-->（%d,%d）"), num+1,m_GrpPos[num].x,m_GrpPos[num].y,x,y);
	g_Log.WriteDataLog(strLog);
	g_Log.LogShow(strLog);

	m_GrpPos[num].x = x;
	m_GrpPos[num].y = y;
}

void CProgData::SetBdOffsetX(int x)
{
	if (m_iBdOffX == x)
	{
		return;
	}
	CString strLog;
	strLog.Format(_T("偏移弥补X：%d-->%d"), m_iBdOffX, x);
	g_Log.WriteDataLog(strLog);
	g_Log.LogShow(strLog);

	m_iBdOffX = x;
}

void CProgData::SetBdOffsetY(int y)
{
	if (m_iBdOffY == y)
	{
		return;
	}

	CString strLog;
	strLog.Format(_T("偏移弥补Y：%d-->%d"), m_iBdOffY, y);
	g_Log.WriteDataLog(strLog);
	g_Log.LogShow(strLog);

	m_iBdOffY = y;
}