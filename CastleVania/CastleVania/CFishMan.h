#pragma once
#include "Enemy.h"

class CFishMan : public CEnemy
{
public:
	CFishMan();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	int ani;
	virtual void SetState(int state);
};

