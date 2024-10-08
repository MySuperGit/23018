#include "StdAfx.h"
#include "tools.h"
#include "CInspectData.h"

CInspectData::CInspectData(int num):
iCount(num)
{

}

CInspectData::~CInspectData()
{

}

int CInspectData::GetPosTotal()
{
	return m_VecPos.size();
}

int CInspectData::Reset()
{
	m_VecPos.clear();
	return 0;
}

int CInspectData::AddPos(int x,int y)
{
	InsPos pos;
	pos.X = x;
	pos.Y = y;
	m_VecPos.push_back(pos);
	return 0;
}

int CInspectData::DelPos(int iIndex)
{
	ASSERT(iIndex > 0 && iIndex <= GetPosTotal());
	vector<InsPos>::iterator iter = m_VecPos.begin() + iIndex -1;
	
	m_VecPos.erase(iter);
	return 0;
}

int CInspectData::ChangePos(int iIndex,int x,int y)
{
	ASSERT(iIndex > 0 && iIndex <= GetPosTotal());
	m_VecPos[iIndex-1].X = x;
	m_VecPos[iIndex-1].Y = y;
	return 0;
}

int CInspectData::GetPos(int iIndex,int &x,int &y)
{
	ASSERT(iIndex > 0 && iIndex <= GetPosTotal());
	x = m_VecPos[iIndex-1].X;
	y = m_VecPos[iIndex-1].Y;
	return 0;
}

int CInspectData::Save()
{
	FILE* pFile;
	char name[255];
	sprintf(name, "%s\\para", GetAppFolder());
	MakeFolder(name);
	sprintf(name, "%s\\InspectData%d.dat",name,iCount);

	pFile = fopen(name,"wb");
	if (!pFile)
	{
		return -1;
	}
	int pos_toal = GetPosTotal();
	fwrite(&pos_toal,sizeof(int),1,pFile);
	for (int i=0;i< pos_toal;i++)
	{
		fwrite(&m_VecPos[i].X,sizeof(int),1,pFile);
		fwrite(&m_VecPos[i].Y,sizeof(int),1,pFile);
		fwrite(&m_VecPos[i].bChecked,sizeof(int),1,pFile);
	}
	fclose(pFile);
	return 0;
}

int CInspectData::Load()
{
	FILE* pFile;
	char name[255];
	sprintf(name, "%s\\para\\InspectData%d.dat", GetAppFolder(),iCount);
	pFile = fopen(name, "rb");
	if(!pFile)
		return -1;	
	int pos_total;
	fread(&pos_total,sizeof(int),1,pFile);
	m_VecPos.clear();
	int iVal[3];
	for (int i=0;i<pos_total;i++)
	{
		fread(&iVal[0],sizeof(int),1,pFile);
		fread(&iVal[1],sizeof(int),1,pFile);
		fread(&iVal[2],sizeof(int),1,pFile);

		InsPos pos;
		pos.X = iVal[0];
		pos.Y = iVal[1];
		pos.bChecked = iVal[2];
		m_VecPos.push_back(pos);
	}
	fclose(pFile);
	return 0;
}