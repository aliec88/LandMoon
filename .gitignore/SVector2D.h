#pragma once
struct SPoint
{
	double x,y;
	SPoint(double a=0,double b=0){x=a;y=b;}
};
struct SVector2D
{
	double x,y;
	SVector2D(double a=0,double b=0){x=a;y=b;}
	SVector2D& operator*(const double &r)
	{
		x*=r;
		y*=r;
		return *this;
	}
};
inline SVector2D operator+(const SVector2D& a,const SVector2D& b)
{
	SVector2D temp;
	temp.x=a.x+b.x;
	temp.y=a.y+b.y;
	return temp;
}
inline SVector2D operator-(const SVector2D& a,const SVector2D& b)
{
	SVector2D temp;
	temp.x=a.x-b.x;
	temp.y=a.y-b.y;
	return temp;
}
inline SVector2D operator*(double n,const SVector2D& v)
{
	SVector2D temp;
	temp.x=n*v.x;
	temp.y=n*v.y;
	return temp;
}
inline double VectorLength(const SVector2D& v)
{
	return sqrt(v.x*v.x+v.y*v.y);
}
inline void VectorNormolize(SVector2D& v)
{
	double length=VectorLength(v);
	v.x/=length;
	v.y/=length;	
}
inline double VectorDot(const SVector2D& a,const SVector2D& b)
{
	return a.x*b.x+a.y*b.y;
}
inline int VectorSign(const SVector2D& v1,const SVector2D& v2)
{
	if (v1.y*v2.x>v1.x*v2.y)
	{
		return 1;
	}else
	{
		return -1;
	}
}