#pragma once
#include "GameObject.h"

#define SIMON_WALKING_SPEED			0.1f 

#define SIMON_JUMP_SPEED_Y			0.5f
#define SIMON_JUMP_DEFLECT_SPEED	0.2f
#define SIMON_GRAVITY				0.002f
#define SIMON_DIE_DEFLECT_SPEED		0.5f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_ATTACK			500
#define SIMON_STATE_SIT				600
#define SIMON_STATE_SIT_ATTACK		700
#define SIMON_STATE_HURT			800


#define SIMON_ANI_IDLE_RIGHT			0
#define SIMON_ANI_IDLE_LEFT				1
#define SIMON_ANI_WALKING_RIGHT			2
#define SIMON_ANI_WALKING_LEFT			3
#define SIMON_ANI_DIE					4
#define SIMON_ANI_JUMP_RIGHT			5
#define SIMON_ANI_JUMP_LEFT				6
#define SIMON_ANI_ATTACK_RIGHT			7
#define SIMON_ANI_ATTACK_LEFT			8
#define SIMON_ANI_SIT_RIGHT				9
#define SIMON_ANI_SIT_LEFT				10
#define SIMON_ANI_SIT_ATTACK_RIGHT		11
#define SIMON_ANI_SIT_ATTACK_LEFT		12
#define SIMON_ANI_HURT_RIGHT			13
#define SIMON_ANI_HURT_LEFT				14


#define SIMON_BBOX_WIDTH  30
#define SIMON_BBOX_HEIGHT 58

#define SIMON_UNTOUCHABLE_TIME 5000


class CSimon : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;
public:
	CSimon() : CGameObject()
	{
		untouchable = 0;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
