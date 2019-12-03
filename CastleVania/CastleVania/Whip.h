#pragma once
#include <algorithm>
#include "define.h"
#include "GameObject.h"

#define WHIP_SPEED			0.1f 

#define WHIP_STATE_HIT			0
#define WHIP_STATE_DISABLE		100

#define WHIP_ANI_LEVEL1_HIT_RIGHT		0
#define WHIP_ANI_LEVEL1_HIT_LEFT		1
#define WHIP_ANI_LEVEL2_HIT_RIGHT		2
#define WHIP_ANI_LEVEL2_HIT_LEFT		3
#define WHIP_ANI_LEVEL3_HIT_RIGHT		4
#define WHIP_ANI_LEVEL3_HIT_LEFT		5

#define WHIP_LEVEL_1			1
#define WHIP_LEVEL_2			2
#define WHIP_LEVEL_3			3

#define WHIP_BBOX_HEIGHT		 15
#define WHIP_BBOX_WIDTH_LEVEL_1  55 //Level 1 va 2 giong bbox
#define WHIP_BBOX_WIDTH_LEVEL_3  85

#define WHIP_UNTOUCHABLE_TIME 5000

#define MAX_LEVEL				3
#define MAX_FRAME_WHIP_ATTACK	3
#define DISTANCE_XWHIP_HANDSIMON  135 // kc tu vi tri x cua whip toi khoang cach ban tay cua simon (ban tay tren whip trung tay simon - 5px)


class CWhip : public CGameObject
{
	static CWhip* __instance; // trong game chi co 1 player
	int level;
public:
	int ani; 
	bool isWhip = false;

	CWhip() : CGameObject()
	{
		AddAnimation(150); // LEVEL 1 RIGHT
		AddAnimation(151); // LEVEL 1 LEFT
		AddAnimation(152); // LEVEL 2 RIGHT
		AddAnimation(153); // LEVEL 2 LEFT
		AddAnimation(154); // LEVEL 3 RIGHT
		AddAnimation(155); // LEVEL 3 LEFT
		
		level = WHIP_LEVEL_1;

	}

	void SetLevel(int l) { level = l; }
	void UpgradeWhip();

	void WhipCollisionObject(vector<LPGAMEOBJECT> coObjects);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render();

	void SetState(int state);
	static CWhip* GetInstance();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};


