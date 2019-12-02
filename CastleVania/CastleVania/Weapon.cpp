#include "Weapon.h"
#include "Candle.h"
#include "Game.h"
#include "Simon.h"
#include "Enemy.h"


Weapon::Weapon()
{
	type = ObjectType::WEAPON;

	//state = WeaponType::DAGGER;
	state = WeaponType::NONE;

	AddAnimation(156); // dagger right
	AddAnimation(157); // dagger left
	AddAnimation(158); // axe right
	AddAnimation(159); // axe left
	AddAnimation(160); // hollywater right
	AddAnimation(161); // hollywater left
	AddAnimation(162); // hollywater - fire effect
}

void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	// Calculate dx, dy 
	if (isFlying)
	{
		x += dx;

		//Xet va cham voi candle bang bbox 
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			float left_a, top_a, right_a, bottom_a;// obj khac
			float left, top, right, bottom; // dagger

			coObjects->at(i)->GetBoundingBox(left_a, top_a, right_a, bottom_a);			// bbox obj 
			GetBoundingBox(left, top, right, bottom);									// bbox dagger 

			if (CheckAABB(left_a, top_a, right_a, bottom_a, left, top, right, bottom))
			{
				
				if (dynamic_cast<CCandle*>(coObjects->at(i))) // if e->obj is CANDLE 				
					coObjects->at(i)->SetState(CANDLE_STATE_FIRE);			
				
				if(dynamic_cast<CEnemy*>(coObjects->at(i))) // if e->obj is CANDLE 				
					coObjects->at(i)->SetState(ENEMY_STATE_DEAD);

				CSimon::GetInstance()->isUsingSupWeapon = false;
			}
		}

		if (x > CGame::GetInstance()->GetCam_x() + SCREEN_WIDTH )
		{
			isFlying = false;
			CSimon::GetInstance()->isUsingSupWeapon = false;
		}
	}
}

void Weapon::Render()
{
	if (isFlying)
	{
		std::cout << "Ve cai coi" << endl;
		if (nx > 0) ani = DAGGER_ANI_RIGHT;
		else ani = DAGGER_ANI_LEFT;
	}
	else if (isThrowing)
	{
		if (nx > 0) ani = AXE_ANI_RIGHT;
		else ani = AXE_ANI_LEFT;
	}

	/*switch (state)
	{
	case WeaponType::NONE:
		break;
	case WeaponType::DAGGER:
		if (nx > 0) ani = DAGGER_ANI_RIGHT;
		else ani = DAGGER_ANI_LEFT;
		break;

	case WeaponType::AXE:
		if (nx > 0) ani = AXE_ANI_RIGHT;
		else ani = AXE_ANI_LEFT;
		break;

	case WeaponType::HOLLY_WATER:
		if (nx > 0) ani = HOLLY_WATER_ANI_RIGHT;
		else ani = HOLLY_WATER_ANI_LEFT;
		break;
	case WeaponType::STOP_WATCH:
		if (nx > 0) ani = STOP_WATCH_ANI_LEFT;
		else ani = STOP_WATCH_ANI_LEFT;
		break;
	}*/
	int alpha = 255;
	animations[ani]->Render(x, y, alpha);
	RenderBoundingBox();
}
//void Weapon::UpdateCurWeapon(DWORD dt)
//{
//	CGameObject::Update(dt);
//
//}

void Weapon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WeaponType::NONE:
		isFlying = false;
		isThrowing = false;
		break;
	case WeaponType::DAGGER:
		std::cout << "vo state dagger" << endl;
		isFlying = true;
		vx = DAGGER_SPEED * nx;
		vy = WEAPON_GRAVITY;
		break;

	case WeaponType::AXE:
		isThrowing = true;
		vx = AXE_SPEED * nx;
		vy = WEAPON_GRAVITY;
		break;

	case WeaponType::HOLLY_WATER:
		isThrowing = true;
		vx = HOLLYWATER_SPEED * nx;
		vy = WEAPON_GRAVITY;
		break;
	case WeaponType::STOP_WATCH:
		isThrowing = true;
		vx = HOLLYWATER_SPEED * nx;
		vy = WEAPON_GRAVITY;
		break;
	}
}

void Weapon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	switch (state)
	{
	case WeaponType::DAGGER:
		right = left +  DAGGER_BBOX_WIDTH;
		bottom = top + DAGGER_BBOX_HEIGHT;
		break;

	case WeaponType::AXE:
		right = left + WEAPON_BBOX;
		bottom = top + WEAPON_BBOX;
		break;

	case WeaponType::HOLLY_WATER:
		right = left + WEAPON_BBOX;
		bottom = top + WEAPON_BBOX;

		break;

	case WeaponType::STOP_WATCH:
		right = left + WEAPON_BBOX;
		bottom = top + WEAPON_BBOX;
		break;
	}
}








