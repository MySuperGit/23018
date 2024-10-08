#include "stdafx.h"
#pragma comment(lib,"RotateAngle.lib")

class CHomMat2D;
class AFX_CLASS_IMPORT CHomMat2DEx
{
public:
	CHomMat2DEx();
	~CHomMat2DEx();
public:
	void SetCenter(double row, double col);
	void GetCalPos(double row,double col,double angle,double& OutRow, double& OutCol);

private:
	CHomMat2D* m_pHomMat2D;
};
