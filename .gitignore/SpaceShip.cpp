#include "StdAfx.h"
#include "SpaceShip.h"

const int NumLanderVerts = 30;

const SPoint lander[NumLanderVerts] = {
	//middle of lander
	SPoint(-1, 0),
	SPoint(1, 0),    
	SPoint(1, -0.5),
	SPoint(-1, -0.5),
	//top of lander
	SPoint(-0.5, 0),
	SPoint(-1, 0.3),
	SPoint(-1, 0.7),
	SPoint(-0.5, 1),
	SPoint(0.5, 1),
	SPoint(1, 0.7),
	SPoint(1, 0.3),
	SPoint(0.5, 0),
	//legs
	SPoint(-1, -0.4),
	SPoint(-1.3, -0.8),
	SPoint(-1.3, -1.2),
	SPoint(-1.5, -1.2),
	SPoint(-1.1, -1.2),
	SPoint(-0.9, -0.5),
	SPoint(-1.3, -0.8),

	SPoint(1, -0.4),
	SPoint(1.3, -0.8),
	SPoint(1.3, -1.2),
	SPoint(1.5, -1.2),
	SPoint(1.1, -1.2),
	SPoint(0.9, -0.5),
	SPoint(1.3, -0.8),
	//rocket
	SPoint(-0.2, -0.5),
	SPoint(-0.3, -0.8),
	SPoint(0.3, -0.8),
	SPoint(0.2, -0.5)};

	//and the vertices for the jet
	const int NumJetVerts = 5;

	const SPoint jet[NumJetVerts] = {SPoint(-0.1, -0.9),
		SPoint(-0.2, -1.2),
		SPoint(0, -1.6),
		SPoint(0.2, -1.2),
		SPoint(0.1, -0.9)};

	void CSpaceShip::Transform(vector<SPoint>&v)
	{
		CMatrix2D m;
		m.Scale(m_dScale,m_dScale);
		m.Rotate(m_dRotate);
		m.Translate(m_spPos.x,m_spPos.y);
		m.ApplyToShape(v);
	}

	bool CSpaceShip::TestForImpact(vector<SPoint>&v)
	{
		const int groundlevel=WINDOW_HEIGHT-80;
		for (int i=0;i<v.size();i++)
		{
			if (v[i].y>groundlevel)
			{
				return true;
			}
		}
		return false;
	}

	bool CSpaceShip::LandOk()
    {
		
		if(disttopad<DISTTOPAD && speed<SPEEDLAND && fabs(m_dRotate)<ROTATIONLAND)
		{
			return true;
		}
		return false;
	}

	CSpaceShip::CSpaceShip(SPoint& panpos)
{
	for (int i=0;i<NumLanderVerts;i++)
	{
		m_vecShipVB.push_back(lander[i]);
	}
	m_vecShipVBTrans=m_vecShipVB;
	for (int i=0;i<NumJetVerts;i++)
	{
		m_vecJetVB.push_back(jet[i]);
	}
	m_vecJetVBTrans=m_vecJetVB;
	m_spPos.x=WINDOW_WIDTH/2;
	m_spPos.y=WINDOW_HEIGHT-500;
	m_dRotate=0;
	m_dScale=10;
	m_bJet=false;
	m_vVelocity=SVector2D(0,0);
	m_bCheckedLanded=false;
	m_spPanPos=panpos;
}


CSpaceShip::~CSpaceShip(void)
{
}

void CSpaceShip::RanderShip(HDC surface)
{
	//m_vecShipVBTrans=m_vecShipVB;
	//Transform(m_vecShipVBTrans);
	MoveToEx(surface,m_vecShipVBTrans[0].x,m_vecShipVBTrans[0].y,NULL);
	for (int i=0;i<30;i++)
	{
		LineTo(surface,m_vecShipVBTrans[i].x,m_vecShipVBTrans[i].y);
	}
	LineTo(surface,m_vecShipVBTrans[0].x,m_vecShipVBTrans[0].y);
	if (m_bJet)
	{
		m_vecJetVBTrans=m_vecJetVB;
		Transform(m_vecJetVBTrans);
		MoveToEx(surface,m_vecJetVBTrans[0].x,m_vecJetVBTrans[0].y,NULL);
		for (int i=0;i<NumJetVerts;i++)
		{
			LineTo(surface,m_vecJetVBTrans[i].x,m_vecJetVBTrans[i].y);
		}
	}
	SetBkColor(surface,RGB(0,0,0));
	wstring strspeed=TEXT("飞行速度：")+ftos(speed);
	wstring strdis=TEXT("登陆点距离：")+ ftos(disttopad);
	wstring strrotate=TEXT("飞行角度：")+ ftos(fabs(m_dRotate));
	TextOut(surface,600,0,strspeed.c_str(),strspeed.size());
	TextOut(surface,600,20,strdis.c_str(),strdis.size());
	TextOut(surface,600,40,strrotate.c_str(),strrotate.size());
	if (m_bCheckedLanded)
	{
      	if (LandOk())
		{	
			SetBkColor(surface,RGB(255,255,0));
			wstring ws=TEXT("登陆成功！！");
			TextOut(surface,WINDOW_WIDTH/2,WINDOW_HEIGHT/2,ws.c_str(),ws.size());
		}else
		{
			SetBkColor(surface,RGB(255,0,0));
			wstring s=TEXT("坠毁！！");
			TextOut(surface,WINDOW_WIDTH/2,WINDOW_HEIGHT/3,s.c_str(),s.size());
		}
		
	}
}

void CSpaceShip::UpdateShip(double timeelapsed)
{
	if (m_bCheckedLanded)
	{
		return;
	}
	m_bJet=false;
	if (KEYDOWN(VK_SPACE))
	{
		m_bJet=true;
		double acceleration=(THRUST_PER_SECOND*timeelapsed)/SHIPMASS;
		m_vVelocity.x+=acceleration*sin(m_dRotate);
		m_vVelocity.y+=acceleration*cos(m_dRotate);
	}
	if (KEYDOWN(VK_LEFT))
	{
		m_dRotate-=ROTATION_PER_SECOND*timeelapsed;
		
	}
	if (KEYDOWN(VK_RIGHT))
	{
		m_dRotate+=ROTATION_PER_SECOND*timeelapsed;
	}
	if (m_spPos.x>WINDOW_WIDTH)
	{
		m_spPos.x=0;
	}
	if (m_spPos.x<0)
	{
		m_spPos.x=WINDOW_WIDTH;
	}
	m_vVelocity.y+=GRAVITY*timeelapsed*20;
	m_spPos.y+=m_vVelocity.y*timeelapsed;
	m_spPos.x-=m_vVelocity.x*timeelapsed;

	disttopad=fabs(m_spPos.x-m_spPanPos.x);
	speed=sqrt((m_vVelocity.x*m_vVelocity.x)+(m_vVelocity.y*m_vVelocity.y));

	m_vecShipVBTrans=m_vecShipVB;
	Transform(m_vecShipVBTrans);
	if (TestForImpact(m_vecShipVBTrans))
	{
		m_bCheckedLanded=true;
	}
}

void CSpaceShip::Reset()
{
	m_spPos.x=WINDOW_WIDTH/2;
	m_spPos.y=WINDOW_HEIGHT-500;
	m_dRotate=0;
	m_dScale=10;
	m_bJet=false;
	m_vVelocity=SVector2D(0,0);
	m_bCheckedLanded=false;
}
