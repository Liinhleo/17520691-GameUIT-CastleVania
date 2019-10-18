#pragma once
#include "GameObject.h"

class CWeapon:public CGameObject
{
public: 
	int width, height;
	float SimonX, SimonY; // vi tri tren tay Simon
	int currentLevel;
	DWORD timeLive;

	virtual void Render();
	void CWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	void SetState(int state);// trang thai hien tai
	void SetPosition(float x, float y) 
	{
		this->x = x;
		this->y = y;
	}

	void SetTimeLive(DWORD timeLive)
	{
		this->timeLive = timeLive;
	}
	DWORD GetTimeLive(){return timeLive;}
};

