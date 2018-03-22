#include "StdAfx.h"
#include "Controller.h"
const int StarNumber=30;
const int NumPanVertex=4;
const SPoint Pan[NumPanVertex]={SPoint(-20,0),SPoint(20,0),SPoint(20,5),SPoint(-20,5)};

void CController::RanderLand(HDC surface)
{
	vector<SPoint>temp=m_vecLandVB;
	TransformLand(temp);
	MoveToEx(surface,temp[0].x,temp[0].y,NULL);
	for (int i=0;i<NumPanVertex;i++)
	{
		LineTo(surface,temp[i].x,temp[i].y);
	}
	LineTo(surface,temp[0].x,temp[0].y);
}

void CController::TransformLand(vector<SPoint>&sp)
{
	CMatrix2D m;
	m.Translate(m_spLandPos.x,m_spLandPos.y);
	m.ApplyToShape(sp);
}

CController::CController(void)
{
	SPoint p;
	for (int i=0;i<StarNumber;i++)
	{
		p.x=RandInt(0,WINDOW_WIDTH);
		p.y=RandInt(0,WINDOW_HEIGHT);
		m_vecStarVB.push_back(p);		
	}
	for(int i=0;i<NumPanVertex;i++)
	{
		m_vecLandVB.push_back(Pan[i]);
	}
	m_spLandPos.x=RandInt(100,WINDOW_WIDTH-100);
	m_spLandPos.y=WINDOW_HEIGHT-80;
	m_pSpaceship=new CSpaceShip(m_spLandPos);
}


CController::~CController(void)
{
	delete m_pSpaceship;
}

void CController::Rander(HDC surface)
{
	HPEN hWhitePen=(HPEN)GetStockObject(WHITE_PEN);
	HPEN hOldPen=(HPEN)SelectObject(surface,hWhitePen);
	for (int i=0;i<m_vecStarVB.size();i++)
	{
		if (RandFloat()>0.1)
		{
			SetPixel(surface,m_vecStarVB[i].x,m_vecStarVB[i].y,RGB(255,255,255));

		}
	}

	RanderLand(surface);
	m_pSpaceship->RanderShip(surface);

	SetBkColor(surface,RGB(0,0,0));
	SetTextColor(surface,RGB(255,255,255));
	wstring r=TEXT("R键重新开始");
	wstring jet=TEXT("空格键打开动力系统");
	wstring d=TEXT("方向键调整登陆舱角度");
	TextOut(surface,0,0,r.c_str(),r.size());
	TextOut(surface,0,20,jet.c_str(),jet.size());
	TextOut(surface,0,40,d.c_str(),d.size());
}

void CController::NewRun()
{
	m_spLandPos.x=RandInt(100,WINDOW_WIDTH-100);
	m_pSpaceship->Reset();
}

void CController::Update(double timeElapsed)
{
	m_pSpaceship->UpdateShip(timeElapsed);
}
