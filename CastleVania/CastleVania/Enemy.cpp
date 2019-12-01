#include "Enemy.h"

CEnemy::CEnemy()
{
	type = ObjectType::ENEMY;

	AddAnimation(260);	//DOG_RIGHT
	AddAnimation(261);  //DOG_LEFT
	AddAnimation(262);	//FISHMAN_RIGHT
	AddAnimation(263);	//FISHMAN_LEFT
	AddAnimation(264);	//ZOMBIE_RIGHT
	AddAnimation(265);	//ZOMBIE_LEFT
	AddAnimation(266);	//BAT_HANG_OUT
	AddAnimation(267);	//BAT_RIGHT
	AddAnimation(268);	//BAT_LEFT
	AddAnimation(269);	//BOSS_HANGOUT
	AddAnimation(270);	//BOSS_ATTACK
	AddAnimation(252); // FIRE

	AddAnimation(300);	// BIG_HEART
	AddAnimation(301);	// SMALL_HEART
	AddAnimation(302);	// UPGRADE_WHIP
	AddAnimation(303);	// DAGGER
	AddAnimation(304);	// AXE
	AddAnimation(305);	// STOP_WATCH
	AddAnimation(306);	// HOLLY_WATER

}


void CEnemy::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMY_STATE_WALKING:
		SetState(enemyID);
		break;
	case ENEMY_STATE_FIRE:
		isHit = true;
		break;

	case ENEMY_STATE_FALLING_ITEM:
		isFallingItem = true;
		SetItemState(itemstate);
		break;

	case ENEMY_STATE_DEAD:
		isAble = false;
		break;

	}
}

void CEnemy::SetItemState(ItemType itemstate)
{
	this->itemstate = itemstate;
	switch (itemstate)
	{
	case ItemType::ITEM_BIG_HEART:
		ani = ITEM_ANI_BIG_HEART;
		vy = ITEM_GRAVITY;
		break;

	case ItemType::ITEM_SMALL_HEART:
		ani = ITEM_ANI_SMALL_HEART;
		vy = SMALL_HEART_GRAVITY;
		break;

	case ItemType::ITEM_UPGRADE_WHIP:
		ani = ITEM_ANI_UPGRADE_WHIP;
		vy = ITEM_GRAVITY;
		break;

	case ItemType::ITEM_DAGGER:
		ani = ITEM_ANI_DAGGER;
		vy = ITEM_GRAVITY;
		break;

	case ItemType::ITEM_AXE:
		ani = ITEM_ANI_AXE;
		vy = ITEM_GRAVITY;
		break;

	case ItemType::ITEM_STOP_WATCH:
		ani = ITEM_ANI_STOP_WATCH;
		vy = ITEM_GRAVITY;
		break;

	case ItemType::ITEM_HOLLY_WATER:
		ani = ITEM_ANI_HOLLY_WATER;
		vy = ITEM_GRAVITY;
		break;
	}
}
