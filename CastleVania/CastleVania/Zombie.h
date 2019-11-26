#pragma once
#include "define.h"
#include "Enemy.h"




class CZombie : public CEnemy
{
public:
	CZombie();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	int ani;
	virtual void SetState(int state);
};

