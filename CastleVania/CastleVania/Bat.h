#pragma once
#include "define.h"
#include "Enemy.h"

class CBat : public CEnemy
{
public:
	CBat();
	int ani;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual void SetState(int state);
};

