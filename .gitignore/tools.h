#pragma once
#include "stdafx.h"
inline int RandInt(int a,int b)
{
	return rand()%(b-a)+a;
}
inline double RandFloat()
{
	return rand()/(RAND_MAX+1.0);
}
inline wstring ftos(double f)
{
	wostringstream s;
	s<<f;
	return s.str();
}