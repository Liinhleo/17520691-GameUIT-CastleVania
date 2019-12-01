#pragma once
#include "define.h"

enum EnemyType {
	ZOMBIE,
	DOG,
	FISHMAN,
	BAT,
	BOSS
};

class CEnemy : public CGameObject
{
public:
	int ani;
	EnemyType enemyID;
	ItemType itemstate;

	bool isHit = false;
	bool isFallingItem = false;

	CEnemy();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) = 0 ;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	
	virtual void Render() = 0;
	void SetState(int state);

	void SetItemState(ItemType itemstate);
};

