#include "StdAfx.h"
#include "Timer.h"


CTimer::CTimer(double fps)
{
	m_dFPS=fps;
	LONGLONG perforance;
	QueryPerformanceFrequency((LARGE_INTEGER*)&perforance);
	m_lFrameTime=perforance/m_dFPS;
	m_dTimeScale=1.0f/perforance;
	m_lNextTime=0;
	m_lLasttime=0;
}


CTimer::~CTimer(void)
{
}

void CTimer::Start()
{
	LONGLONG current;
	QueryPerformanceCounter((LARGE_INTEGER*)&current);
	m_lNextTime=current+m_lFrameTime;
	m_lLasttime=current;
}

bool CTimer::ReadyForNextTime()
{
	LONGLONG current;
	QueryPerformanceCounter((LARGE_INTEGER*)&current);
	if (current>m_lNextTime)
	{
		m_lNextTime=current+m_lFrameTime;
		m_dTimeElapsed=(current-m_lLasttime)*m_dTimeScale;
		m_lLasttime=current;
		return true;
	}
	return false;
}
