#ifndef _ALG_THMS_H_
#define _ALG_THMS_H_
//----- calculate the angle with radian
double Radian2Angle(double radian);
//----- calculate the radian with angle
double Angle2Radian(double angle);


//------ class for point in X/Y coordinate system -----------
//
class CTRealPoint
{
	
public: //point pos data
	
	double X;
	double Y;
	
public: //operator function
	
	CTRealPoint();
	CTRealPoint(double xx, double yy);
	virtual ~CTRealPoint();
	
	//operate
	virtual void   Set(double xx, double yy); 
	virtual double Add(double dx, double dy); //add the shift
	
	//calculate point P to cur point distance 
	//cur point is height of the line to P
	//lenght is p pos-cur pos
	virtual double CalDist(CTRealPoint& p);  //get the line dist
	virtual double CalDX(CTRealPoint& p); //dist at x axis
	virtual double CalDY(CTRealPoint& p); //dist at y axis
	
	//calculate the angle from point P to cur point
	//cur point is height of the line to P
	virtual double CalTan(CTRealPoint& p); //tangent
	virtual double CalSin(CTRealPoint& p); //sine
	virtual double CalCos(CTRealPoint& p); //cosine
	
	virtual double CalRadian(CTRealPoint& p);
	virtual double CalAngle(CTRealPoint& p);
	
	//rotate the P with the radian/angle to cur point
	//cur point is height of the line to P
	virtual double Rotate2R(CTRealPoint *p, double radian);
	virtual double Rotate2A(CTRealPoint *p, double angle);
	
}; //end class CTRealPoint




//------------- class of beeline,func: a*x+b*y+c=0 ------------ 
class CTBeeLine  
{
public: //function
	
	//create 0=0
	CTBeeLine();
	
	//create the function by set coefficients
	CTBeeLine(double a, double b, double c);  
	
	//create the function by set A,B point
	CTBeeLine(double ax, double ay, double bx, double by);
	
	CTBeeLine(CTRealPoint& a, CTRealPoint& b);  
	
	//create the function by set coefficients
	virtual void Create(double a, double b, double c); 
	
	//create the function by set A,B point
	virtual void Create(double ax, double ay, double bx, double by);
	
	//get x/Y of point
	virtual double CalX(double y);
	virtual double CalY(double x);
	
	virtual void GetFunc(double *a, double *b, double *c);
	
	virtual int  Intersect(CTBeeLine& line); //return 1 for intersect with line
	virtual int  GetPtI(CTBeeLine& line, double *x, double *y); //return 1 for intersect with line,x,y is point
	
	virtual ~CTBeeLine();
	
protected: //datas,coefficients of line equation
	
	double A;
	double B;
	double C;
	
}; //end class CTBeeLine 

//---------  class of Perpendicular Bisector ---------------
class CTPBLine : public CTBeeLine 
{
public: //functions
	
	//create 0=0
	CTPBLine();
	
	//create the function by set coefficients
	CTPBLine(double a, double b, double c);  
	
	//create the function by set A,B point
	CTPBLine(double ax, double ay, double bx, double by);
	
	CTPBLine(CTRealPoint& a,CTRealPoint& b);  
	
	//create the function by set coefficients
	//virtual void Create(double a,double b,double c); 
	
	//create the function by set A,B point
	virtual void Create(double ax, double ay, double bx, double by);
	
	virtual ~CTPBLine();
	
protected:  
	
}; //end class CTPBLine


//------------- class of circle ,func: (x-cx)(x-cx)+(y-cy)(y-cy)=r*r ------------ 
class CTCircle
{
public:  //functions
	
	virtual void GetCenter(double& x, double& y);
	virtual double GetR();
	
	//get x/y of point
	virtual int CalX(double y, double& xl, double& xr);
	virtual int CalY(double x, double& ya, double& yu);
	
	CTCircle();
	CTCircle(CTRealPoint& c, double r);
	CTCircle(CTRealPoint& a, CTRealPoint& b, CTRealPoint& c);  //3 point
	virtual ~CTCircle();
	
	virtual double Create(CTRealPoint& c, double r);
	virtual double Create(CTRealPoint& a, CTRealPoint& b, CTRealPoint& c);  //3 point
	
	//X线在圆内
	int isXLineIn(int y)
	{
		
		double dr=fabs(y-Center.Y);
		
		if (dr <= R)
		{
			return(1);
		}
		
		return(0);
	}
	
	//Y线在圆内
	int isYLineIn(int x)
	{
		
		double dr=fabs(x-Center.X);
		
		if (dr <= R)
		{
			return(1);
		}
		
		return(0);
	}
	
	int isPtIn(int xpos,int ypos)
	{
		CTRealPoint pt;
		pt.Set(xpos,ypos);
		
		if (Center.CalDist(pt) < R)
		{
			return 1;
		}
		
		return 0;
	}

protected:  //datas,3 point of triangle 
	
	CTRealPoint Center;  //center point
	double R;          //radius
    
}; //end class CTCircle

#endif