#pragma once
class CTimer
{
private:
	LONGLONG m_lFrameTime;
	LONGLONG m_lNextTime;
	LONGLONG m_lLasttime;
	double m_dTimeScale;
	double m_dFPS;
	double m_dTimeElapsed;
public:
	CTimer(double fps);
	~CTimer(void);
	void Start();
	bool ReadyForNextTime();
	double GetTimeElapsed(){return m_dTimeElapsed;}

};

