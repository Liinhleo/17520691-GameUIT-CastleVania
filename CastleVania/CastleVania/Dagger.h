#pragma once
#include <algorithm>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"
#include "Goomba.h"

#define WHIP_SPEED			0.1f 

#define DAGGER_STATE_HIT			0
#define DAGGER_STATE_DISABLE		100

#define DAGGER_ANI_HIT_RIGHT	0
#define DAGGER_ANI_HIT_LEFT		1
#define DAGGER_ANI_DISABLE		2

#define DAGGER_BBOX_WIDTH  30
#define DAGGER_BBOX_HEIGHT 58

#define DAGGER_UNTOUCHABLE_TIME 5000


class CDagger : public CGameObject
{
	static CDagger* __instance;
	int untouchable;
	DWORD untouchable_start;
public:
	int ani;
	bool isDisable = false;
	bool isAble = false;

	CDagger() : CGameObject()
	{
		untouchable = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render();
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	static CDagger* GetInstance();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};


