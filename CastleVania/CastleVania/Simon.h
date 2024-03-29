#pragma once
#include <algorithm>
#include "define.h"
#include "Weapon.h"
#include "Whip.h"
#include "GameObject.h"
#include  "Door.h"
#include  "Item.h"
#define SIMON_WALKING_SPEED			0.5f 

#define SIMON_JUMP_SPEED_Y			0.5f
#define SIMON_JUMP_DEFLECT_SPEED	0.2f
#define SIMON_DIE_DEFLECT_SPEED		0.5f
#define SIMON_HURT_SPEED_Y			0.2f

#define SIMON_GRAVITY				0.002f

#define SIMON_BBOX_WIDTH  30
#define SIMON_BBOX_HEIGHT 58

#define SIMON_UNTOUCHABLE_TIME 5000

#define MAX_FRAME_ATTACK	3 // 4 frame
#define MAX_FRAME_ONSTAIR	1 // 2 frame



class CSimon : public CGameObject
{
	static CSimon* __instance; // trong game chi co 1 player
	int untouchable;
	DWORD untouchable_start;

	DWORD timeWait;

public:
	Weapon* subWeapon;
	WeaponType curSupWeapon = WeaponType::NONE;
	//WeaponType curSupWeapon = WeaponType::DAGGER;
	CSimon();

	int ani;

	bool isUsingSupWeapon = false;

	bool isWalking = false;
	bool isAttacking = false;
	bool isJumping = false;
	bool isSitting = false;
	bool isChangeColor = false;
	bool isHurting = false;

	bool isAutoGo = false;
	bool isUpStair = false;
	bool isDownStair = false; 
	bool isCollisionDoor = false;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	static CSimon* GetInstance();

	float GetVx() { return this->vx; };

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void AttackingState();

	bool isCollisionItem(Item *item);


	//void SetWeapon(Weapon* subWeapon);

	//bool CheckCollisionDoor(CDoor* door);
	//bool isCanChangeScene(vector<LPGAMEOBJECT> coObjects);
	//bool IscollisionItem(CCandle *item = NULL);
	//void SetSubWeapon(CCandle* item); // set vu khi phu cho Simon
};
