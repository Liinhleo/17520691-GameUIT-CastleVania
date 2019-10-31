#pragma once
#include "GameObject.h"
#include "Sprites.h"
#include "Whip.h"

#define SIMON_WALKING_SPEED			0.1f 

#define SIMON_JUMP_SPEED_Y			0.5f
#define SIMON_JUMP_DEFLECT_SPEED	0.2f
#define SIMON_DIE_DEFLECT_SPEED		0.5f

#define SIMON_GRAVITY				0.002f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_ATTACK			500
#define SIMON_STATE_SIT				600
#define SIMON_STATE_SIT_ATTACK		700
#define SIMON_STATE_HURT			800
#define SIMON_STATE_STAND_UP		900

#define SIMON_ANI_IDLE_RIGHT			0
#define SIMON_ANI_IDLE_LEFT				1
#define SIMON_ANI_WALKING_RIGHT			2
#define SIMON_ANI_WALKING_LEFT			3
#define SIMON_ANI_DIE_RIGHT				4
#define SIMON_ANI_DIE_LEFT				5
#define SIMON_ANI_JUMP_RIGHT			6
#define SIMON_ANI_JUMP_LEFT				7
#define SIMON_ANI_ATTACK_RIGHT			8
#define SIMON_ANI_ATTACK_LEFT			9
#define SIMON_ANI_SIT_RIGHT				10
#define SIMON_ANI_SIT_LEFT				11
#define SIMON_ANI_SIT_ATTACK_RIGHT		12
#define SIMON_ANI_SIT_ATTACK_LEFT		13
#define SIMON_ANI_HURT_RIGHT			14
#define SIMON_ANI_HURT_LEFT				15


#define SIMON_BBOX_WIDTH  30
#define SIMON_BBOX_HEIGHT 58

#define SIMON_UNTOUCHABLE_TIME 5000

#define MAX_FRAME_ATTACK 3



class CSimon : public CGameObject
{
	static CSimon* __instance; // trong game chi co 1 player
	int untouchable;
	DWORD untouchable_start;

public:
	int ani;

	CWhip* whip = CWhip::GetInstance();

	bool isWalking = false;
	bool isAttacking = false;
	bool isJumping = false;
	bool isSitting = false;
	//bool isHurting;

	/*void AttackingState();
	void WalkingState();
	void JumpingState();
	void SittingState();*/

	CSimon() : CGameObject()
	{
		untouchable = 0;
	}
	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	
	static CSimon* GetInstance();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
