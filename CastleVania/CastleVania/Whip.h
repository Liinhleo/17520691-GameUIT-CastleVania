#pragma once
#include "GameObject.h"

#define WHIP_SPEED			0.1f 

#define WHIP_STATE_DISABLE		0
#define WHIP_STATE_HIT_RIGHT	100
#define WHIP_STATE_HIT_LEFT		200

#define WHIP_ANI_HIT_RIGHT		0
#define WHIP_ANI_HIT_LEFT		1
#define WHIP_ANI_DISABLE		2

#define WHIP_BBOX_WIDTH  30
#define WHIP_BBOX_HEIGHT 58

#define WHIP_UNTOUCHABLE_TIME 5000

class CWhip : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;
public:
	CWhip() : CGameObject()
	{
		untouchable = 0;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};


