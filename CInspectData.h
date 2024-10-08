#pragma once

using std::vector;

struct InsPos 
{
	int X;
	int Y;
	int bChecked; //检测过
	InsPos()
	{
		X = 0;
		Y = 0;
		bChecked = 0;
	}
};

class CInspectData
{
public:
	CInspectData(int num = 0);
	~CInspectData();

public:
	int GetPosTotal();
	int AddPos(int x,int y);
	int DelPos(int iIndex); //所有iIndex从0开始
	int ChangePos(int iIndex,int x,int y);
	int GetPos(int iIndex,int &x,int &y);

	int Save();
	int Load();
	int Reset();

private:
	vector<InsPos> m_VecPos;
	int iCount;
};