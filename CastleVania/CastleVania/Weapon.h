#pragma once
#include <algorithm>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"
#include "Candle.h"
#include "Simon.h"


#define WEAPON_GRAVITY			0.002f
#define DAGGER_SPEED			0.3f
#define AXE_SPEED				0.01f
#define HOLLYWATER_SPEED		0.015f



#define DAGGER_ANI_RIGHT		0
#define DAGGER_ANI_LEFT			1
#define AXE_ANI_RIGHT			2	
#define AXE_ANI_LEFT			3
#define HOLLY_WATER_ANI_RIGHT	4
#define HOLLY_WATER_ANI_LEFT	5
#define HOLLY_WATER_ANI_FIRE	6
#define STOP_WATCH_ANI_LEFT		7
#define STOP_WATCH_ANI_RIGHT	8


#define DAGGER_BBOX_WIDTH		35
#define DAGGER_BBOX_HEIGHT		15
#define WEAPON_BBOX				35
#define HOLY_WATER_BBOX			20



enum WeaponType {
	NONE,
	DAGGER,
	HOLLY_WATER,
	AXE,
	STOP_WATCH
};

class Weapon : public CGameObject
{

public:
	int ani;
	Weapon();


	bool isFlying = false;
	bool isThrowing = false;

	//void UpdateCurWeapon(DWORD dt);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	void Render();
	//bool isCollision(float obj_left, float obj_top, float obj_right, float obj_bottom);

	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

