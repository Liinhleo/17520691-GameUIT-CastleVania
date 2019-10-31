#pragma once
#include <algorithm>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"
#include "Goomba.h"

#define WHIP_SPEED			0.1f 

#define WHIP_STATE_HIT			0
//#define WHIP_STATE_HIT_LEFT		100
#define WHIP_STATE_DISABLE		100

#define WHIP_ANI_LEVEL1_HIT_RIGHT		0
#define WHIP_ANI_LEVEL1_HIT_LEFT		1
#define WHIP_ANI_LEVEL2_HIT_RIGHT		2
#define WHIP_ANI_LEVEL2_HIT_LEFT		3
#define WHIP_ANI_LEVEL3_HIT_RIGHT		4
#define WHIP_ANI_LEVEL3_HIT_LEFT		5
#define WHIP_ANI_DISABLE				6

#define WHIP_LEVEL_1			1
#define WHIP_LEVEL_2			2
#define WHIP_LEVEL_3			3


#define WHIP_BBOX_WIDTH_LEVEL_1  30 //Level 1 va 2 giong bbox
#define WHIP_BBOX_HEIGHT_LEVEL_1 58

#define WHIP_BBOX_WIDTH_LEVEL_3  30
#define WHIP_BBOX_HEIGHT_LEVEL_3 58

#define WHIP_UNTOUCHABLE_TIME 5000

#define MAX_FRAME_WHIP_ATTACK 3


class CWhip : public CGameObject
{
	static CWhip* __instance; // trong game chi co 1 player
	int level;
	int untouchable;
	DWORD untouchable_start;
public:
	int ani; 
	bool isDisable = false;
	bool isAble = false;

	CWhip() : CGameObject()
	{
		level = WHIP_LEVEL_1;
		untouchable = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render();
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	static CWhip* GetInstance();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};


