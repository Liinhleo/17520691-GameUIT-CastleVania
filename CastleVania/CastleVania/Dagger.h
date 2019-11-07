#pragma once
#include <algorithm>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"
#include "Goomba.h"
#include "Simon.h"

#define DAGGER_SPEED			0.3f 

#define DAGGER_STATE_HIT			0
#define DAGGER_STATE_DISABLE		100

#define DAGGER_ANI_HIT_RIGHT	0
#define DAGGER_ANI_HIT_LEFT		1

#define DAGGER_BBOX_WIDTH  30
#define DAGGER_BBOX_HEIGHT 15

#define DAGGER_UNTOUCHABLE_TIME 5000


class CDagger : public CGameObject
{
	static CDagger* __instance;
	
public:
	int ani;
	bool isFlying = false;


	CDagger() : CGameObject(){}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render();
	void SetState(int state);

	static CDagger* GetInstance();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};


