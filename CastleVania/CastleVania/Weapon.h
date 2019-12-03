#pragma once
#include <algorithm>
#include "GameObject.h"

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
#define STOP_WATCH_ANI_RIGHT	7
#define STOP_WATCH_ANI_LEFT		8

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
	DWORD timeStart = 0;	// dem time isFire
public:
	int ani;
	Weapon();

	bool isHide = false;	// sau khi weapon VS enemy/candle || bay ra khoi camera -> true
	bool isFlying = false;	// khi xai dagger
	bool isThrowing = false;// khi xai axe
	bool isPutting = false; // khi xai cho stop watch + holly water
	bool isFire = false;	// khi stopwatch + holly water va cham voi ground / enemy

	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	void Render();
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void WeaponCollisionObject(vector<LPGAMEOBJECT> coObjects);

};

