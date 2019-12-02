#pragma once
#include "define.h"
#include "GameObject.h"

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

	bool isHit = false;
	bool isFallingItem = false;

	CEnemy();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) = 0 ;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	
	virtual void Render() = 0;
	void SetState(int state);

};

