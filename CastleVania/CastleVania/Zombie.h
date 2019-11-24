#pragma once
#include "GameObject.h"


#define ZOMBIE_WALKING_SPEED 0.1f;

#define ZOMBIE_BBOX_WIDTH 30
#define ZOMBIE_BBOX_HEIGHT 65

#define ZOMBIE_STATE_WALKING	100
#define ZOMBIE_STATE_DIE		200

#define ZOMBIE_ANI_WALKING_RIGHT	0
#define ZOMBIE_ANI_WALKING_LEFT		1


class CZombie : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	

public:
	CZombie();

	int ani;
	virtual void SetState(int state);
};
