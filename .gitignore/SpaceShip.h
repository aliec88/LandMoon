#pragma once
class CSpaceShip
{
private:
	vector<SPoint>m_vecShipVB;
	vector<SPoint>m_vecShipVBTrans;
	vector<SPoint>m_vecJetVB;
	vector<SPoint>m_vecJetVBTrans;
	double m_dRotate;
	SPoint m_spPos;
	double m_dScale;
	SVector2D m_vVelocity;
	bool m_bJet;
	bool m_bCheckedLanded;
	SPoint m_spPanPos;
private:
	double disttopad;
	double speed;
private:
	void Transform(vector<SPoint>&v);
	bool TestForImpact(vector<SPoint>&v);
	bool LandOk();
public:
	CSpaceShip(SPoint& panpos);
	~CSpaceShip(void);
	void RanderShip(HDC surface);
	void UpdateShip(double timeelapsed);
	void Reset();
};

