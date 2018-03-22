#pragma once
#include "SpaceShip.h"
class CController
{
private:
	vector<SPoint>m_vecStarVB;
	vector<SPoint>m_vecLandVB;
	SPoint m_spLandPos;
	CSpaceShip* m_pSpaceship;
private:
	void RanderLand(HDC surface);
	void TransformLand(vector<SPoint>&sp);
public:
	CController(void);
	~CController(void);
	void Rander(HDC surface);
	void NewRun();
	void Update(double timeElapsed);
};

