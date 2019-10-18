#pragma once
#include "Weapon.h"
//
//#define WHIP_SPEED_X			0 
//#define WHIP_SPEED_Y			0 
//
//#define WHIP_LEVEL_1			1
//#define WHIP_LEVEL_2			2
//#define WHIP_LEVEL_3			3
//
//
//#define WHIP_BBOX_HEIGHT		10  //cao
//#define WHIP_BBOX_WIDTH_LEVEL_1 30	//rong
//#define WHIP_BBOX_WIDTH_LEVEL_2 35
//#define WHIP_BBOX_WIDTH_LEVEL_3 42
//
//
//#define WHIP_IN_HAND_SIMON				
//
//#define WHIP_ANI_HIT_RIGHT_LEVEL_1		11
//#define WHIP_ANI_HIT_LEFT_LEVEL_1		12
//#define WHIP_ANI_HIT_RIGHT_LEVEL_2		21
//#define WHIP_ANI_HIT_LEFT_LEVEL_2		22
//#define WHIP_ANI_HIT_RIGHT_LEVEL_3		31
//#define WHIP_ANI_HIT_LEFT_LEVEL_3		32
//
//#define WHIP_UNTOUCHABLE_TIME 5000

class CWhip : public CWeapon
{
	int currentLevel;
public:
	
	void SetLevel(int level)
	{
		this->currentLevel = level;
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};
	void Render() {};

	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
};


